/** This file is part of Clock Core
 *
 * Copyright © 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
 * All rights reserved.
 * Contact: Qi Ouyang <qi.ouyang@nokia.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Nokia Corporation. All rights are reserved. Copying, including
 * reproducing, storing, adapting or translating, any or all of this material
 * requires the prior written consent of Nokia Corporation. This material also
 * contains confidential information which may not be disclosed to others
 * without the prior written consent of Nokia.
 */

/** \file clockcore-cities.h
 * \brief Clockcore Cities - header file.
 *
 * API for fetching and managing cities datatabase
 */

#ifndef __CLOCK_CORE_CITIES_H__
#define __CLOCK_CORE_CITIES_H__
#include <stdlib.h>
#include <glib.h>

/* header with API to the core Cities Database */
#include <cityinfo.h>
/* Time API */
#include <time.h>
/* libtime API */
#include <clockd/libtime.h>

G_BEGIN_DECLS

/** \brief Typedef for structure with all data needed by World Clock View*/
typedef struct _Citytime Citytime;

/** \brief Structure with all data needed to present in the World Clock View.*/
struct _Citytime {
	Cityinfo* city;       /**< structure with city informations */
	struct tm time;       /**< local time in city */
	gint      gmt_offset; /**< specify GMT offset in city */
	gchar*    date;       /**< string with date in city (etc. Fri 22.02) */
};

/** \brief Typedef for structure containing information about city.*/
typedef struct _CityinfoExt CityinfoExt;
/** \brief Structure with informations about city and some more extra inf.*/
struct _CityinfoExt {
	Cityinfo* city;       /**< structure with city informations */
	gint      gmt_offset; /**< specify GMT offset in the city */
};

/** \brief free allocated memory by the Citytime structure*/
void clock_citytime_free (Citytime* city);

/** \brief Function returns structure with informations about a wanted city */
Cityinfo*  clock_get_location (gint id);

/** \brief Same as get_location, but uses a timezone string (i.e. Europe/London) */
Cityinfo*  clock_get_location_from_timezone (const gchar *timezone);

/** \brief Return time infromation about particular City.
 */
Citytime*  clock_get_time_in_city(Cityinfo* city);

/** \brief Funtion returns an a array of all remote time zones*/
Citytime** clock_get_remote_locations (void);

/** \brief Function updates the time in location*/
gboolean   clock_update_time_in_location (Citytime* loc, gboolean home_city);

/**
 * \brief Function returns an array with all available time zones on a platform
 */
Cityinfo** clock_get_available_locations (void);

/** \brief Function adds to a database a new remote location*/
Citytime*  clock_add_new_remote_location (Cityinfo* loc);

/** \brief Functins remove remote location from a database*/
gboolean   clock_remove_remote_location (Citytime* loc);

/** \brief Function returns nearest to the given coordinates city informations*/
Cityinfo*  clock_find_nearest_location (gdouble x, gdouble y, gint old_id);

/** \brief Gets GMT offset of given Citytime structure. */
gint clock_citytime_get_gmt_offset (Citytime* city);


/**
 * \brief Gets time zone string from Citytime structure.
 * \param ct pointer to Citytime structure with all data needed in Clock
 * Application
 */
#define clock_citytime_get_zone(ct) (cityinfo_get_zone(ct->city))

/**
 * \brief Gets city name from Citytime structure.
 * \param ct pointer to Citytime structure with all data needed in Clock
 * Application
 */
#define clock_citytime_get_city(ct) (cityinfo_get_name(ct->city))

/**
 * \brief Gets country name from Citytime structure.
 * \param ct pointer to Citytime structure with all data needed in Clock
 * Application
 */
#define clock_citytime_get_country(ct) (cityinfo_get_country(ct->city))

/**
 * \brief Gets time from given Citytime structure.
 * \param ct pointer to Citytime structure with all data needed in Clock
 * Application
 */
#define clock_citytime_get_time(ct) (ct->time)

/**
 * \brief Gets id of given Citytime structure.
 * \param ct pointer to Citytime structure with all data needed in Clock
 * Application
 */
#define clock_citytime_get_id(ct) (cityinfo_get_id(ct->city))

G_END_DECLS

#endif
