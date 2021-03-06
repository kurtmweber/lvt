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

#ifndef _SAVE_H
#define _SAVE_H

typedef enum encapsulatedTypes{
	ENCAP_TYPE_STRING,
	ENCAP_TYPE_PLAYER,
	ENCAP_TYPE_CREATURE,
	ENCAP_TYPE_ITEM,
	ENCAP_TYPE_GLOBALSTATUS,
	ENCAP_TYPE_MAPSPACE,
	ENCAP_TYPE_PLANT,
} encapsulatedTypes;

typedef struct readObjectList{
	uintptr_t id;
	void *ptr;
	encapsulatedTypes type;
	size_t size;
} readObjectList;

typedef struct fileObjectInfo{
	uintptr_t id;
	encapsulatedTypes type;
	size_t size;
} fileObjectInfo;

#define CHECK_ALREADY_STORED \
localId = getObjectId((void *)object);\
\
if (alreadyStored((void *)object)){\
	return localId;\
	}\
	
	#endif