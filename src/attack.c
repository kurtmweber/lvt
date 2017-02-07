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

#define _ATTACK_C

#include "attack.h"
#include "lvt.h"
#include "messages.h"

unsigned int attack(creature *attacker, creature *defender){
  
  unsigned int toHitVal, toDefendVal;
  unsigned int toHitRoll, toDefendRoll;
  unsigned int attackVal, defenseVal;
  unsigned int attackRoll, defenseRoll;
  unsigned int damage;
  unsigned int defenderCurHp;
  unsigned int attackerXp, defenderXp;
  static rng localRng;
  static bool rngInitd = false;
  
#ifndef _D_DEBUG
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
    }
  
  toHitVal = toHit(attacker);
  toDefendVal = toDefend(defender);
  
  toHitRoll = uniformRandomRangeInt(&localRng, 0, toHitVal);
  toDefendRoll = uniformRandomRangeInt(&localRng, 0, toDefendVal);
  
  if (toHitRoll <= toDefendRoll){
    return ATTACK_MISSED;
  }
  
  attackVal = calcAttackVal(attacker);
  defenseVal = calcDefenseVal(defender);
  
  attackRoll = uniformRandomRangeInt(&localRng, 0, attackVal);
  defenseRoll = uniformRandomRangeInt(&localRng, 0, defenseVal);

  if (attackRoll <= defenseRoll){
    return ATTACK_NODAMAGE;
  }
  
  damage = attackRoll - defenseRoll;
  
  defenderCurHp = getCreatureCurHp(defender);
  
  if (damage < defenderCurHp){
    setCreatureCurHp(defender, defenderCurHp - damage);
    return ATTACK_SUCCEEDED;
  } else {
#endif
    defenderXp = MAX(getCreatureXp(defender), 1);	// always get at least 1 xp for a kill
    attackerXp = getCreatureXp(attacker);
    setCreatureLevelHpXp(attacker, attackerXp + defenderXp);
    killCreature(defender);	// can't kill the defender before we get the data we need from them
    return ATTACK_KILLED;
#ifndef _D_DEBUG
  }
#endif
}

unsigned int calcAttackVal(creature *attacker){
  unsigned int weaponDamage;
  statList stats;
  
  if (attacker->weapon){
    weaponDamage = attacker->weapon->itemData.baseDamage + attacker->weapon->damageModifier;
  } else {
    weaponDamage = 1;	// bare-handed combat
  }
  
  getCreatureCurStats(attacker, &stats);
  
  return weaponDamage * stats.strength;
}

unsigned int calcDefenseVal(creature *defender){
  unsigned int armorClass;
  statList stats;
  
  armorClass = getCreatureArmorClass(defender);
  
  getCreatureCurStats(defender, &stats);
  
  return armorClass + stats.constitution;
}

unsigned int toDefend(creature *defender){
  unsigned int armorClass;
  statList stats;

  armorClass = getCreatureArmorClass(defender);
  
  getCreatureCurStats(defender, &stats);
  
  return armorClass + stats.dexterity + stats.intelligence + stats.wisdom + getCreatureXp(defender);
}

unsigned int toHit(creature *attacker){
  unsigned int weaponToHit;
  statList stats;

  if (attacker->weapon){
    weaponToHit = attacker->weapon->itemData.baseToHit + attacker->weapon->toHitModifier;
  } else {
    weaponToHit = 1;	// bare-handed combat
  }
  
  getCreatureCurStats(attacker, &stats);
  
  return weaponToHit * (stats.dexterity + stats.intelligence + stats.wisdom + getCreatureXp(attacker));
}