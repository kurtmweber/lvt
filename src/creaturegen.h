/*  This file is part of Lavender Throne.
 *  Copyright 2017 by Kurt Weber
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

#define _CREATUREGEN_H

#ifndef _CREATUREGEN_C
creatureList *generateStartingCreatures();
#else
bool decidePlaceCreature(coord2D floor, unsigned int level);
creature *newRandomOrphanCreature(coord2D floor, unsigned int level);
void placeNewCreature(creature *creature, coord3D location);
creature *spawnOrphanCreature(creatureSpecies species, creatureClass class);
#endif