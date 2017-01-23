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

#define _COLORS_C

#include <ncurses.h>
#include <stdlib.h>
#include "colors.h"
#include "lvt.h"

void initializeColors(){
  if (!has_colors()){
    destroyNcurses();
    exit(0);
  }
  
  start_color();
  
  init_pair(BlackGreen, COLOR_BLACK, COLOR_GREEN);
  init_pair(WhiteBlack, COLOR_WHITE, COLOR_BLACK);
  init_pair(BlueBlack, COLOR_BLUE, COLOR_BLACK);
  init_pair(GreenBlack, COLOR_GREEN, COLOR_BLACK);
  init_pair(RedBlack, COLOR_RED, COLOR_BLACK);
  init_pair(MagentaBlack, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(CyanBlack, COLOR_CYAN, COLOR_BLACK);
  
  return;
}