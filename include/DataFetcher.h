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

#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include <iostream>
#include <algorithm>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <colors.h>

using namespace std;

enum FetchType {
    Champion  = 0x0001,
    Patches   = 0x0002,
    Languages = 0x0003
};

class DataFetcher
{
private:
    static size_t WriteCallback(const char *in, size_t size, size_t num, string *out);

public:
    string data, championName, patch, language = "en_US";
    FetchType type;

    int timeout          = 10; //sec
    bool ipv6            = false; //Forces IPv6
    bool followRedirects = true; //Follow HTTP redirects?
    long maxRedirects    = -1; //-1 = infinite | 0 = no redirects.

	void fetch();
};



#endif // DATAFETCHER_H
