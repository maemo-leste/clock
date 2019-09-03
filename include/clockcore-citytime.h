#ifndef CLOCK_CORE_CITYTIME_H
#define CLOCK_CORE_CITYTIME_H

#include <cityinfo.h>

/**
 * @brief Structure containing all the data needed by World Clock View.
 */
struct _Citytime
{
  Cityinfo* city;       /** city information */
  struct tm time;       /** city local time */
  gint      gmt_offset; /** city GMT offset */
  gchar*    date;       /** city date, string represented */
};

typedef struct _Citytime Citytime;

/**
 * @brief frees allocated #Citytime structure returned by a call to some of the
 *        other functions
 *
 * @param city - #Citytime structure to be freed. There is a check for NULL
 *               pointer.
 */
void
clock_citytime_free(Citytime *city);

/**
 * @brief Return time information about a particular city.
 *
 * @param city City to return information for.
 *
 * @returns A newly allocated #Citytime structure or NULL if error occured, free
 *          with #clock_citytime_free
 */
Citytime *
clock_get_time_in_city(Cityinfo *city);

/**
 * @brief Get GMT offset of a #Citytime.
 *
 * @param ct #Citytime structure to return GMT offset of.
 *
 * @returns GMT offset.
 */
gint
clock_citytime_get_gmt_offset (Citytime *ct);

/**
 * @brief Gets time zone from #Citytime structure.
 *
 * @param ct pointer to #Citytime structure
 */
#define clock_citytime_get_zone(ct) (cityinfo_get_zone((ct)->city))

/**
 * @brief Gets city name from #Citytime structure.
 *
 * @param ct pointer to #Citytime structure
 */
#define clock_citytime_get_city(ct) (cityinfo_get_name((ct)->city))

/**
 * @brief Gets country name from #Citytime structure.
 *
 * @param ct pointer to #Citytime structure
 */

#define clock_citytime_get_country(ct) (cityinfo_get_country((ct)->city))

/**
 * @brief Gets time from #Citytime structure.
 *
 * @param ct pointer to #Citytime structure
 */
#define clock_citytime_get_time(ct) (ct->time)

/**
 * @brief Gets id from #Citytime structure.
 *
 * @param ct pointer to #Citytime structure
 */
#define clock_citytime_get_id(ct) (cityinfo_get_id((ct)->city))

#endif /* CLOCK_CORE_CITYTIME_H */
