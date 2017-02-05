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

#define _SPAWNITEM_C


#include "lvt.h"
#include "item.h"

item *spawnItem(itemClassId class, int subClass){
  item *item;
  
  switch(class){
    case ITEM_TYPE_CORPSE:
      item =  spawnCorpse(subClass);
      break;
    case ITEM_TYPE_LONGSWORD:
      item = spawnLongsword(subClass);
      break;
    case ITEM_TYPE_AXE:
      item = spawnAxe(subClass);
      break;
    case ITEM_TYPE_DAGGER:
      item = spawnDagger(subClass);
      break;
    default:
      return 0;
  }
  
  item->name = 0;
  
  return item;
}

item *spawnAxe(int subClass){
  item *axe;
  
  axe = allocateItem();
  setItemClass(axe, ITEM_TYPE_AXE);
  axe->axeSubClass = subClass;
  axe->itemData = itemTypes[ITEM_TYPE_AXE][subClass];
  
  return axe;
}

item *spawnDagger(int subClass){
  item *dagger;
  
  dagger = allocateItem();
  setItemClass(dagger, ITEM_TYPE_DAGGER);
  dagger->daggerSubClass = subClass;
  dagger->itemData = itemTypes[ITEM_TYPE_DAGGER][subClass];
  
  return dagger;
}

item *spawnLongsword(int subClass){
  item *longsword;
  
  longsword = allocateItem();
  setItemClass(longsword, ITEM_TYPE_LONGSWORD);
  longsword->longswordSubClass = subClass;
  longsword->itemData = itemTypes[ITEM_TYPE_LONGSWORD][subClass];
  
  return longsword;
}

item *spawnCorpse(int subClass){
  item *corpse;
  
  corpse = allocateItem();
  
  setItemClass(corpse, ITEM_TYPE_CORPSE);
  corpse->corpseSubClass = subClass;
  corpse->itemData = itemTypes[ITEM_TYPE_CORPSE][subClass];
  
  return corpse;
}