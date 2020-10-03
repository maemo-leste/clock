/*
 * clockcore-cities.c
 *
 * Copyright (C) 2020 Ivaylo Dimitrov <ivo.g.dimitrov.75@gmail.com>
 *
 * This library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <https://www.gnu.org/licenses/>.
 */

#include "clockcore-cities.h"

static Cityinfo **cities = NULL;

Cityinfo *
clock_find_nearest_location(gdouble x, gdouble y, gint old_id)
{
  Cityinfo **_cities;
  Cityinfo *city;
  double sigma = 2.0;

  if (!cities)
    cities = cityinfo_get_all();

  if (!cities)
    return cityinfo_find_closest(x, y);


  for (_cities = cities; _cities; _cities++)
  {
    Cityinfo *c = *_cities;
    double new_sigma = (y - c->y) * (y - c->y) + (x - c->x) * (x - c->x);

    if (sigma > new_sigma)
    {
      sigma = new_sigma;
      city = c;
    }
  }

  if (old_id == cityinfo_get_id(city))
    return NULL;

  return cityinfo_clone(city);
}
