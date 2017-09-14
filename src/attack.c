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

#include "lvt.h"

#include "attack.h"
#include "messages.h"

unsigned int attack(creature *attacker, creature *defender, unsigned int toHitVal, unsigned int toDefendVal, unsigned int attackVal, unsigned int defenseVal){
  unsigned int toHitRoll, toDefendRoll;
  unsigned int attackRoll, defenseRoll;
  unsigned int damage;
  unsigned int defenderCurHp;
  unsigned int attackerXp, defenderXp;
  static rng localRng;
  static bool rngInitd = false;  
  
  setInCombat(defender, true);
  setInCombat(attacker, true);
  
//#ifndef _D_DEBUG
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
    }
    
  toHitRoll = uniformRandomRangeInt(&localRng, 0, toHitVal);
  toDefendRoll = uniformRandomRangeInt(&localRng, 0, toDefendVal);
  
  if (toHitRoll <= toDefendRoll){
    return ATTACK_MISSED;
  }
  
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
//#endif
    defenderXp = MAX(getCreatureXp(defender), 1);       // always get at least 1 xp for a kill
    attackerXp = getCreatureXp(attacker);
    setCreatureLevelHpXp(attacker, attackerXp + defenderXp);
    killCreature(defender);     // can't kill the defender before we get the data we need from them
    return ATTACK_KILLED;
//#ifndef _D_DEBUG
  }
//#endif
}

unsigned int calcAttackVal(creature *attacker, item *weapon){
  unsigned int weaponDamage;
  statList stats;
  
  if (weapon){
    weaponDamage = weapon->itemData.baseDamage + weapon->damageModifier;
  } else {
    weaponDamage = 1;   // bare-handed combat
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

unsigned int meleeAttack(creature *attacker, creature *defender){
  unsigned int toHitVal, toDefendVal;
  unsigned int attackVal, defenseVal;

  toHitVal = toHit(attacker, attacker->weapon);
  toDefendVal = toDefend(defender);
  
  attackVal = calcAttackVal(attacker, attacker->weapon);
  defenseVal = calcDefenseVal(defender);
  
  return attack(attacker, defender, toHitVal, toDefendVal, attackVal, defenseVal);
}

unsigned int throwAttack(creature *attacker, creature *defender, item *weapon, unsigned int distanceLeft){
  unsigned int toHitVal, toDefendVal;
  unsigned int attackVal, defenseVal;
  
  toHitVal = toHit(attacker, weapon);
  
  if (weapon->itemData.throwable){
    attackVal = calcAttackVal(attacker, weapon);
  } else {
    attackVal = distanceLeft * weapon->itemData.weight;
  }
  
  toDefendVal = toDefend(defender);
  defenseVal = calcDefenseVal(defender);
  
  return attack(attacker, defender, toHitVal, toDefendVal, attackVal, defenseVal);
}

unsigned int toDefend(creature *defender){
  unsigned int armorClass;
  statList stats;

  armorClass = getCreatureArmorClass(defender);
  
  getCreatureCurStats(defender, &stats);
  
  return armorClass + stats.dexterity + stats.intelligence + stats.wisdom + getCreatureXp(defender);
}

unsigned int toHit(creature *attacker, item *weapon){
  unsigned int weaponToHit;
  statList stats;

  if (weapon){
    weaponToHit = weapon->itemData.baseToHit + weapon->toHitModifier;
  } else {
    weaponToHit = 1;	// bare-handed combat
  }
  
  getCreatureCurStats(attacker, &stats);
  
  return weaponToHit * (stats.dexterity + stats.intelligence + stats.wisdom + getCreatureXp(attacker));
}