/**
 * @file clockcore.h
 * @brief Clock core  - header
 *
 * Defines clock core general usage functions
 */

#ifndef CLOCK_CORE_H
#define CLOCK_CORE_H

#include "clockcore-citytime.h"

/**
 * @brief Check if time auto synchronization is available.
 *
 * @returns TRUE if time auto synchronization is available, FALSE otherwise.
 */
gboolean
clock_is_autosync_available(void);

/**
 * @brief Change current Time Zone (user location/home city).
 *
 * @param city City to return information for.
 *
 * @returns A newly allocated #Citytime structure for the new location or NULL
 *          if error occured, free with #clock_citytime_free
 */
Citytime *
clock_change_current_location(Cityinfo* city);

/**
 * @brief Set 24h time format on or off.
 *
 * @param state TRUE to set time format to 24h FALSE to set it to 12h am/pm
 */
void
clock_set_24h_format(gboolean state);

/**
 * @brief Enable or disable time auto synchronization.
 *
 * @param enable TRUE to enable time auto synchronization FALSE to disable
 */
void
clock_enable_autosync(gboolean enable);

/**
 * @brief Set new system time (in the current time zone).
 *
 * @param year Year to set or -1 to keep the current.
 * @param month Month to set or -1 to keep the current.
 * @param day Day to set or -1 to keep the current.
 * @param hour Hour to set or -1 to keep the current.
 * @param minute Minute to set or -1 to keep the current.
 *
 * @returns TRUE on success FALSE otherwise.
 */
gboolean
clock_change_time(gint year, gint month, gint day, gint hour, gint minute);

/**
 * @brief Get current home city.
 *
 * @returns A newly allocated #Citytime structure for the current home city or
 *          NULL if error occured, free with #clock_citytime_free
 */
Citytime *
clock_get_home_location(void);

/**
 * @brief Get if 24h clock format is enabled.
 *
 * @returns TRUE if 24h clock format is enabled, FALSE otherwise.
 */
gboolean
clock_get_is_24h_format(void);

/**
 * @brief Get information about a city.
 *
 * @param id Location id of the city
 *
 * @returns Pointer to a newly allocated Cityinfo structure or NULL on error.
 */
Cityinfo*
clock_get_location(gint id);

/**
 * @brief Get information about a city.
 *
 * @param timezone Timezone string, like "Europe/London"
 *
 * @returns Pointer to a newly allocated Cityinfo structure or NULL on error.
 */

Cityinfo*
clock_get_location_from_timezone (const gchar *timezone);

#endif /* CLOCK_CORE_H */
