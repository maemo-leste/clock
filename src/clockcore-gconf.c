#include <gconf/gconf-client.h>

#include "clockcore-gconf.h"
#include "clockcore-gconf-private.h"

static GConfClient *
_gc_init()
{
  GConfClient *gc = gconf_client_get_default();

  g_assert(gc);

  return gc;
}

static void
_gc_exit(GConfClient *gc)
{
  if (gc)
    g_object_unref(gc);
}

static gboolean
_get_bool(const gchar *path)
{
  GConfClient *gc;
  gboolean rv;

  g_assert(path);

  gc = _gc_init();
  rv = gconf_client_get_bool(gc, path, NULL);
  _gc_exit(gc);

  return rv;
}

static gboolean
_set_bool(const gchar *path, gboolean val)
{
  GConfClient *gc;
  gboolean rv;

  g_assert(path);

  gc = _gc_init();
  rv = gconf_client_set_bool(gc, path, val, NULL);
  gconf_client_suggest_sync(gc, NULL);
  _gc_exit(gc);

  return rv;
}

static gboolean
_set_int(const gchar *path, gint val)
{
  GConfClient *gc;
  gboolean rv;

  g_assert(path);

  gc = _gc_init();
  rv = gconf_client_set_int(gc, path, val, NULL);
  gconf_client_suggest_sync(gc, NULL);
  _gc_exit(gc);

  return rv;
}

static gint
_get_id(const gchar *path)
{
  GConfClient *gc;
  gint rv;
  GError *err = NULL;

  g_assert(path);

  gc = _gc_init();
  rv = gconf_client_get_int(gc, path, &err);
  _gc_exit(gc);

  if (err)
  {
    g_error_free(err);
    rv = -1;
  }

  return rv;
}

gboolean
clock_gconf_is_24h_format(void)
{
  return _get_bool(CLOCK_GCONF_IS_24H_FORMAT);
}

gboolean
clock_gconf_set_24h_format(gboolean state)
{
  return _set_bool(CLOCK_GCONF_IS_24H_FORMAT, state);
}

gboolean
clock_gconf_set_auto_sync_time(gboolean enable)
{
  return _set_bool(CLOCK_GCONF_AUTO_TIME_SYNC, enable);
}

gint
clock_gconf_get_home_location()
{
  return _get_id("CLOCK_GCONF_HOME_LOCATION");
}

gboolean
clock_gconf_set_home_location(gint id)
{
  if (id < 0)
    return FALSE;

  return _set_int(CLOCK_GCONF_HOME_LOCATION, id);
}
