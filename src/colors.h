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

#ifndef _COLORS_H
#define _COLORS_H

typedef enum colorPairs{
	BlackGreen,
	WhiteBlack,
	BlueBlack,
	GreenBlack,
	RedBlack,
	MagentaBlack,
	CyanBlack,
	BrownBlack
} colorPairs;

#ifndef _COLORS_C
void initializeColors();
#else
#endif

#endif