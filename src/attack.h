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

#ifndef _ATTACK_H
#define _ATTACK_H

typedef enum attackOutcome{
  ATTACK_MISSED,
  ATTACK_NODAMAGE,
  ATTACK_SUCCEEDED,
  ATTACK_KILLED
} attackOutcome;

#ifndef _ATTACK_C
unsigned int meleeAttack(creature *attacker, creature *defender);
unsigned int throwAttack(creature *attacker, creature *defender, item *weapon, unsigned int distanceLeft);
unsigned int calcAttackVal(creature *attacker, item *weapon);
#else
unsigned int toHit(creature *attacker, item *weapon);
unsigned int toDefend(creature *defender);
unsigned int calcAttackVal(creature *attacker, item *weapon);
unsigned int calcDefenseVal(creature *defender);
unsigned int attack(creature *attacker, creature *defender, unsigned int toHitVal, unsigned int toDefendVal, unsigned int attackVal, unsigned int defenseVal);
#endif

#endif