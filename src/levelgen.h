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

#ifndef _LEVELGEN_H
#define _LEVELGEN_H

#ifndef _LEVELGEN_C
extern const unsigned int roomCoverageMu;
extern const unsigned int roomCoverageSigma;
extern const unsigned int roomCoverageFloor;
extern const unsigned int roomCoverageCeiling;
extern const unsigned int straightness;  // likelihood (out of 1000) that the next space dug out for a tunnel
                                        // will be towards the target

extern const unsigned int minRoomX;        // max and min sizes of a room
extern const unsigned int minRoomY;
extern const unsigned int maxRoomX;
extern const unsigned int maxRoomY;

extern const unsigned int doorLikelihood;        // likelihood (out of 1000) that a door-eligible floor will
                                                // become a door
extern const unsigned int hiddenDoorLikelihood;  // likelihood (out of 1000) that a door will be hidden

extern const unsigned int numLevels;

extern const unsigned int dimMapX;       // map dimensions
extern const unsigned int dimMapY;

# else

// some tuning constants
const unsigned int roomCoverageMu = 1000;
const unsigned int roomCoverageSigma = 500;
const unsigned int roomCoverageFloor = 500;
const unsigned int roomCoverageCeiling = 5000;
const unsigned int straightness = 850;  // likelihood (out of 1000) that the next space dug out for a tunnel
                                        // will be towards the target

const unsigned int minRoomX = 2;        // max and min sizes of a room
const unsigned int minRoomY = 2;
const unsigned int maxRoomX = 10;
const unsigned int maxRoomY = 10;

const unsigned int doorLikelihood = 500;        // likelihood (out of 1000) that a door-eligible floor will
                                                // become a door
const unsigned int hiddenDoorLikelihood = 100;  // likelihood (out of 1000) that a door will be hidden

const unsigned int numLevels = 100;

const unsigned int dimMapX = 100;       // map dimensions
const unsigned int dimMapY = 100;

#endif

#endif