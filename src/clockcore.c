#include <time.h>
#include <clockd/libtime.h>

#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "clockcore.h"
#include "clockcore-gconf.h"

struct cityinfo_foreach_cb_data
{
  /** returned location id */
  gint id;
  /** time zone */
  const gchar *zone;
  /** city */
  const gchar *city;
};

gboolean
clock_is_autosync_available()
{
  return time_is_operator_time_accessible() > 0;
}

void
clock_set_24h_format(gboolean state)
{
  if (state)
    time_set_time_format("%R");
  else
    time_set_time_format("%r");

  clock_gconf_set_24h_format(state);
}

gboolean
clock_get_is_24h_format()
{
  gboolean rv;
  char buf[16];

  if (time_get_time_format(buf, sizeof(buf)) < 0)
    return clock_gconf_is_24h_format();

  rv = !g_strcmp0(buf, "%R") || g_strcmp0(buf, "%r");

  if (clock_gconf_is_24h_format() != rv)
    clock_gconf_set_24h_format(rv);

  return rv;
}

void
clock_enable_autosync(gboolean enable)
{
  if (!time_set_autosync(enable != TRUE))
    clock_gconf_set_auto_sync_time(enable);
}

Citytime *
clock_change_current_location(Cityinfo *city)
{
  Citytime *ct;

  if (!city || cityinfo_get_id(city) == -1)
    return NULL;

  city = cityinfo_clone(city);

  if (!city)
    return NULL;

  ct = clock_get_time_in_city(city);

  if (ct)
  {
    gchar *zone = g_strconcat(":", cityinfo_get_zone(city), NULL);
    gboolean ok = clock_gconf_set_home_location(cityinfo_get_id(city));

    ok &= (time_set_timezone(zone) != -1);

    g_free(zone);

    if (!ok)
    {
      clock_citytime_free(ct);
      ct = NULL;
    }
  }
  else
    cityinfo_free(city);

  return ct;
}

Citytime *
clock_get_home_location(void)
{
  gint id = clock_gconf_get_home_location();
  Cityinfo *city;
  Citytime *ct;


  if (id == -1)
  {
    char buf[128];

    if (time_get_timezone(buf, sizeof(buf)) <= 0)
      city = clock_get_location_from_timezone("Europe/London");
    else
    {
      char *p = strchr(buf, ':');

      if (p)
        p++;
      else
        p = buf;

      city = clock_get_location_from_timezone(g_strchomp(g_strchug(p)));
    }
  }
  else
    city = clock_get_location(id);

  if (!city)
    return NULL;

  ct = clock_get_time_in_city(city);

  if (!ct)
    cityinfo_free(city);

  return ct;
}

Cityinfo *
clock_get_location(gint id)
{
  if (id == -1)
    return NULL;

  return cityinfo_from_id(id);
}

static gboolean
_cityinfo_foreach_cb(const Cityinfo *city, gpointer user_data)
{
  struct cityinfo_foreach_cb_data *data = user_data;

  if (g_strcmp0(data->zone, city->zone))
    return TRUE;

  if (!data->city || !g_strcmp0(data->city, city->name))
  {
    data->id = city->id;
    return FALSE;
  }

  return TRUE;
}

Cityinfo *
clock_get_location_from_timezone(const gchar *timezone)
{
  char *endptr;
  gint id = strtol(timezone, &endptr, 10);
  Cityinfo *rv;

  if (endptr == timezone || errno || (rv = cityinfo_from_id(id)) == 0 )
  {
    struct cityinfo_foreach_cb_data *data =
        g_slice_new(struct cityinfo_foreach_cb_data);
    gchar *old_loc;

    errno = 0;
    data->id = -1;
    data->zone = timezone;
    data->city = strchr(timezone, '/');

    if (data->city)
      data->city++;

    old_loc = g_strdup(setlocale(LC_ALL, NULL));
    setlocale(LC_ALL, "en_GB");
    cityinfo_foreach(_cityinfo_foreach_cb, data);
    setlocale(LC_ALL, old_loc);
    g_free(old_loc);

    if (data->id == -1)
      rv = NULL;
    else
      rv = clock_get_location(data->id);

    g_slice_free(struct cityinfo_foreach_cb_data, data);
  }

  return rv;
}

gboolean
clock_change_time(gint year, gint month, gint day, gint hour, gint minute)
{
  struct tm tm = {};
  struct tm current_tm = {};

  time_get_local(&current_tm);

  tm.tm_year = current_tm.tm_year;
  tm.tm_mon = current_tm.tm_mon;
  tm.tm_mday = current_tm.tm_mday;
  tm.tm_hour = current_tm.tm_hour;
  tm.tm_min = current_tm.tm_min;
  tm.tm_sec = current_tm.tm_sec;
  tm.tm_isdst = -1;

  if (year != -1)
    tm.tm_year = year - 1900;

  if (month != -1)
    tm.tm_mon = month;

  if (day != -1)
    tm.tm_mday = day;

  if (hour != -1)
    tm.tm_hour = hour;

  if (minute != -1)
    tm.tm_min = minute;

  return time_set_time(time_mktime(&tm, NULL)) == 0;
}
