/************************************************************************************
*  Copyright (c) 2022 Xen <xen-dev@pm.me>                                           *
*  This file is part of the League of Legends Champion Database project, AKA LoLCDB *
*  LoLCDB is free software; you can redistribute it and/or modify it under          *
*  the terms of the GNU Lesser General Public License (LGPL) as published           *
*  by the Free Software Foundation; either version 3 of the License, or             *
*  (at your option) any later version.                                              *
*  LoLCDB is distributed in the hope that it will be useful, but WITHOUT            *
*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or            *
*  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public              *
*  License for more details.                                                        *
*  You should have received a copy of the GNU Lesser General Public License         *
*  along with this program. If not, see <https://www.gnu.org/licenses>.             *
*  THIS SOFTWARE IS NOT MADE BY RIOT GAMES NOR AFFILIATED WITH RIOT GAMES.          *
************************************************************************************/

#ifndef DATAREADER_H
#define DATAREADER_H

#include <iostream>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/error/error.h>
#include <rapidjson/error/en.h>

#include <colors.h>

using namespace std;
using namespace rapidjson;

class DataReader {
    public:
        string *jsonData, *champion;

        void printChampion();
        void printPatches();
        void printLanguages();
        const vector<string> versions();
};

#endif // DATAREADER_H
