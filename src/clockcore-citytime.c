#include <time.h>
#include <clockd/libtime.h>

#include <string.h>
#include <libintl.h>

#include "clockcore.h"

void
clock_citytime_free(Citytime *city)
{
  if (city)
  {
    if (city->city)
    {
      cityinfo_free(city->city);
      city->city = NULL;
    }

    if (city->date)
    {
      g_free(city->date);
      city->date = NULL;
    }

    g_free(city);
  }
}

Citytime *
clock_get_time_in_city(Cityinfo *city)
{
  Citytime *ct;
  char buf[200];

  if (!city)
    return NULL;

  ct = g_try_new0(Citytime, 1);

  if (!ct)
    return NULL;

  ct->city = city;
  ct->gmt_offset = time_get_utc_offset(cityinfo_get_zone(city)) / -3600;
  time_get_remote(time_get_time(), cityinfo_get_zone(ct->city), &ct->time);
  memset(buf, 0, sizeof(buf));
  time_format_time(&ct->time,
                   dgettext("hildon-libs", "wdgt_va_date_day_name_short"),
                   buf, sizeof(buf) - 1);
  ct->date = g_strdup(buf);

  return ct;
}

gint
clock_citytime_get_gmt_offset(Citytime *ct)
{
  return time_get_utc_offset(cityinfo_get_zone(ct->city));
}
