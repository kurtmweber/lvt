/*  This file is part of Lavender Throne.
 *  Copyright 2016 by Kurt Weber
 *
 *  Lavender Throne is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Lavender Throne is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Lavender Throne.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CREATUREMGMT_H
#define _CREATUREMGMT_H

typedef enum wieldOutcome{
  WIELD_SUCCEEDED,
  WIELD_FAILED_TWOHANDED,	// could not wield because it is a two-handed object and creature is
				// equipped with a shield
  WIELD_FAILED_WEIGHT,
  WIELD_FAILED
} wieldOutcome;

typedef enum wearOutcome{
  WEAR_SUCCEEDED,
  WEAR_FAILED_NOT_ARMOR
} wearOutcome;

typedef enum removeOutcome{
  REMOVE_SUCCEEDED,
  REMOVE_FAILED_NOT_WORN,
  REMOVE_FAILED_NOT_ITEM
} removeOutcome;

#endif