/**
 * @file clockcore-gconf.h
 * @brief Clock core gconf - header
 *
 * Defines clock core GConf paths used in application
 */

#ifndef CLOCK_CORE_GCONF_H
#define CLOCK_CORE_GCONF_H

/**
 * @brief GConf root path for clock settings
 */
#define CLOCK_GCONF_PATH    "/apps/clock"

/**
 * @brief TRUE if 24hour format should be used; FALSE if 12h format.
 */
#define CLOCK_GCONF_IS_24H_FORMAT CLOCK_GCONF_PATH "/time-format"

/**
 * @brief Path to current alarm tone.
 */
#define CLOCK_GCONF_ALARM_TONE CLOCK_GCONF_PATH "/alarm-tone"

/**
 * @brief TRUE if time auto syncronization is enabled, FALSE otherwise.
 */
#define CLOCK_GCONF_AUTO_TIME_SYNC CLOCK_GCONF_PATH "/auto-sync"

/**
 * @brief Path to the current home location
 */
#define CLOCK_GCONF_HOME_LOCATION CLOCK_GCONF_PATH "/home-location"

/**
 * @brief Get the location id of the current home city.
 *
 * @returns The location id of the current home city or -1 on error.
 */
gint
clock_gconf_get_home_location(void);

/**
 * @brief Set home city.
 *
 * @param id Location id of the location to set home city to.
 *
 * @returns TRUE on success FALSE otherwise.
 */
gboolean
clock_gconf_set_home_location(gint id);

/**
 * @brief Enable time auto synchronisation to operator time
 *
 * @param enable TRUE to enable, FALSE to disable
 *
 * @returns TRUE on success FALSE otherwise.
 */
gboolean
clock_gconf_set_auto_sync_time(gboolean enable);

/**
 * @brief Get if time should be displayed in 24h format or in 12h(am/pm) format
 *
 * @returns TRUE for 24h format, FALSE for 12h format
 */
gboolean
clock_gconf_is_24h_format(void);

/**
 * @brief Set if time should be displayed in 24h format or in 12h(am/pm) format
 *
 * @param state TRUE for 24h format, FALSE for 12h format
 *
 * @returns TRUE on success FALSE otherwise.
 */
gboolean
clock_gconf_set_24h_format(gboolean state);

#endif /* CLOCK_CORE_GCONF_H */

