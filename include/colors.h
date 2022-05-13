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

#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <string>

#ifdef WIN32
    #include <windows.h>
#endif

using namespace std;

enum Color {
	bold        = 0x6660,
	dim         = 0x6661,
	underline   = 0x6662,
	spell       = 0x6663,
	statName    = 0x6664,
	statValue   = 0x6665,
	warn        = 0x6666,
	done        = 0x6667,
    error       = 0x6668,
    PBLow       = 0x6669,
    PBMid       = 0x6670,
    PBHigh      = 0x6671
};

extern bool ANSI; //Global

static void dye(const string &msg, Color color)
{
    /*
    for(int k=1; k<=255;k++) {
        SetConsoleTextAttribute(commandLine, k);
        cout << k << " -> hahahahahahahahahaaha" << endl;
    }*/

    if (ANSI) {
        switch (color) {
        case bold: cout << "\e[1m" << msg << "\e[0m"; break;
        case dim: cout << "\e[2m" << msg << "\e[0m"; break;
        case underline: cout << "\e[4m" << msg << "\e[0m"; break;
        case spell: cout << "\e[45m" << msg << "\e[0m"; break;
        case statName: cout << "\e[44m" << msg << "\e[0m"; break;
        case statValue: cout << "\e[42m" << msg << "\e[0m"; break;
        case PBLow: cout << "\e[41m" << msg << "\e[0m"; break;
        case PBMid: cout << "\e[43m" << msg << "\e[0m"; break;
        case PBHigh: cout << "\e[42m" << msg << "\e[0m"; break;
        case warn: cout << "\e[33m" << msg << "\e[0m"; break;
        case done: cout << "\e[32m" << msg << "\e[0m"; break;
        case error: cout << "\e[31m" << msg << "\e[0m"; break;
        default: cout << "\e[0m" << msg << "\e[0m";
        }
    }
    else {
        #ifdef WIN32
        HANDLE commandLine = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (color) {
        case bold:
            SetConsoleTextAttribute(commandLine, 15);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case dim:
            SetConsoleTextAttribute(commandLine, 8);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case underline:
            SetConsoleTextAttribute(commandLine, 15);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case spell:
            SetConsoleTextAttribute(commandLine, 95);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case statName:
            SetConsoleTextAttribute(commandLine, 63);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case statValue:
            SetConsoleTextAttribute(commandLine, 207);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case PBLow:
            SetConsoleTextAttribute(commandLine, 207);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case PBMid:
            SetConsoleTextAttribute(commandLine, 231);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case PBHigh:
            SetConsoleTextAttribute(commandLine, 47);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case warn:
            SetConsoleTextAttribute(commandLine, 6);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case done:
            SetConsoleTextAttribute(commandLine, 10);
            cout << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        case error:
            SetConsoleTextAttribute(commandLine, 12);
            cerr << msg;
            SetConsoleTextAttribute(commandLine, 7);
            break;
        default:
            SetConsoleTextAttribute(commandLine, 7);
            cout << msg;
            break;
        }
        #else
            cout << msg;
        #endif
    }
}

#endif // COLORS_H
