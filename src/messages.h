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

#ifndef _MESSAGES_H
#define _MESSAGES_H

#define MSGLEN(a) (strlen(a) - 2)

#define WELCOME_MSG "Welcome to Lavender Throne, %s!"
#define MOVE_WALL_MSG "There is a wall there!"
#define MOVE_CREATURE_MSG "Someone else is already there!"
#define MOVE_DOOR_MSG "There is a closed door there!"
#define NO_DOOR_THERE_MSG "There is no door to open there!"
#define DOOR_ALREADY_OPEN_MSG "That door is already open!"
#define DOOR_ALREADY_CLOSED_MSG "That door is already closed!"
#define WHICH_DIRECTION_MSG "Which direction?"
#define NEVER_MIND_MSG "Never mind..."
#define CANNOT_UP_HERE_MSG "You cannot go up here."
#define CANNOT_DOWN_HERE_MSG "You cannot go down here."
#define UP_IS_EXIT_MSG "To go up from here is to exit."
#define DIED_OLD_AGE_MSG "You have died of old age..."
#define SELECT_LOCATION_MSG "Please select a location."
#define NOTHING_THERE_MSG "I see nothing there"
#define ATTACK_MISSED_MSG "Your attack missed!"
#define ATTACK_NODAMAGE_MSG "Your attack landed, but did no damage."
#define ATTACK_SUCCEEDED_MSG "Your attack succeeded!"
#define ATTACK_KILLED_MSG "You killed your opponent!"
#define INVENTORY_FULL_MSG "Your inventory is full!"
#define WIELD_FAILED_TWOHANDED_SHIELD_MSG "You cannot wield a two-handed weapon while equipped with a shield!"

#define ATTACK_ALLIED_Q "The creature there is allied.  Do you wish to attack?"

#endif