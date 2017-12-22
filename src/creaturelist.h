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

#ifndef _CREATURELIST_H
#define _CREATURELIST_H

#ifndef _CREATURELIST_C
creatureList *findCreatureListEntry(creatureList *list, creature *creature);
creatureList *insertNewCreatureNode(creatureList *list, creatureList *node);
creatureList *removeCreatureNode(creatureList *list, creatureList *node);
#endif

#endif