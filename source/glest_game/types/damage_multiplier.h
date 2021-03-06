// ==============================================================
//	This file is part of Glest (www.glest.org)
//
//	Copyright (C) 2001-2008 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_DAMAGEMULTIPLIER_H_
#define _GLEST_GAME_DAMAGEMULTIPLIER_H_

#ifdef WIN32
    #include <winsock2.h>
    #include <winsock.h>
#endif

#include <string>
#include "xml_parser.h"
#include "leak_dumper.h"

using std::string;
using Shared::Xml::XmlNode;

namespace Glest{ namespace Game{

// ===============================
// 	class AttackType  
// ===============================

class AttackType {
private:
	string name;
	int id;

public:
	AttackType() {
		id = -1;
	}
	int getId() const					{return id;}
	string getName(bool translatedValue=false) const;

	void setName(const string &name)	{this->name= name;}
	void setId(int id)					{this->id= id;}

	void saveGame(XmlNode *rootNode);
};

// ===============================
// 	class ArmorType  
// ===============================

class ArmorType {
private:
	string name;
	int id;

public:
	ArmorType() {
		id = -1;
	}
	int getId() const					{return id;}
	string getName(bool translatedValue=false) const;

	void setName(const string &name)	{this->name= name;}
	void setId(int id)					{this->id= id;}

	void saveGame(XmlNode *rootNode);
};

// =====================================================
// 	class DamageMultiplierTable  
//
///	Some attack types have bonuses against some 
/// armor types and vice-versa
// =====================================================

class DamageMultiplierTable {
private:
	double *values;
	int attackTypeCount;
	int armorTypeCount;

public:
	DamageMultiplierTable();
	~DamageMultiplierTable();

	void init(int attackTypeCount, int armorTypeCount);
	double getDamageMultiplier(const AttackType *att, const ArmorType *art) const;
	void setDamageMultiplier(const AttackType *att, const ArmorType *art, double value);

	void saveGame(XmlNode *rootNode);
};

}}//end namespace

#endif
