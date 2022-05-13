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

#include <DataReader.h>

void DataReader::printChampion()
{
	Document document;
    document.Parse(jsonData->c_str());
    if (document.HasParseError()) {
        dye("JSON data was retrieved but parsing process failed, Here's the error:\n", error);
        dye("Code: " + to_string(document.GetParseError()) +
            "\tOffset: " + to_string(document.GetErrorOffset()) +
            "\nMessage: " + GetParseError_En(document.GetParseError()) + "\n", error);
        throw (102);
    }

    const string patchVersion(document["version"].GetString());
    const string champName(document["data"][champion->c_str()]["name"].GetString());
    const string champTitle(document["data"][champion->c_str()]["title"].GetString());
    const string champPartype(document["data"][champion->c_str()]["partype"].GetString());
    const int numOfSkins(document["data"][champion->c_str()]["skins"].Size()-1);
    const string champLore(document["data"][champion->c_str()]["lore"].GetString());

    dye("\n\n\t\t" + champName + ": ", bold); cout << champTitle;
    dye("\n\n\tClass: ", bold);
    for (const auto &champTag : document["data"][champion->c_str()]["tags"].GetArray()) {
        cout << champTag.GetString() << " ";
    }
    dye(" | ", dim); dye("Resource: ", bold); cout << champPartype; dye(" | ", dim); dye("Skins: ", bold); cout << numOfSkins << endl << endl;

    for (const auto &champInfo : document["data"][champion->c_str()]["info"].GetObj()) {
        const int infoValue = champInfo.value.GetInt();
        if (strcmp(&champInfo.name.GetString()[0], "attack") == 0) {
            dye("\t\tAttack \t\t-> ", dim); cout << "[";
            for(int a = 1; a <= 10; a++) {
                if (a <= infoValue) {
                    if (infoValue < 4) dye("|", PBLow);
                    else if (infoValue >= 4 && infoValue <=6) dye("|", PBMid);
                    else if (infoValue > 6) dye("|", PBHigh);
                }
                else cout << "-";
            }
            cout << "] "; dye(to_string(infoValue), dim); cout << "/10\n";
        }
        if (strcmp(&champInfo.name.GetString()[0], "defense") == 0) {
            dye("\t\tDefense \t-> ", dim); cout << "[";
            for(int d = 1; d <= 10; d++) {
                if (d <= champInfo.value.GetInt()) {
                    if (infoValue < 4) dye("|", PBLow);
                    else if (infoValue >= 4 && infoValue <=6) dye("|", PBMid);
                    else if (infoValue > 6) dye("|", PBHigh);
                }
                else cout << "-";
            }
            cout << "] "; dye(to_string(champInfo.value.GetInt()), dim); cout << "/10\n";
        }
        if (strcmp(&champInfo.name.GetString()[0], "magic") == 0) {
            dye("\t\tMagic \t\t-> ", dim); cout << "[";
            for(int m = 1; m <= 10; m++) {
                if (m <= champInfo.value.GetInt()) {
                    if (infoValue < 4) dye("|", PBLow);
                    else if (infoValue >= 4 && infoValue <=6) dye("|", PBMid);
                    else if (infoValue > 6) dye("|", PBHigh);
                }
                else cout << "-";
            }
            cout << "] "; dye(to_string(champInfo.value.GetInt()), dim); cout << "/10\n";
        }
        if (strcmp(&champInfo.name.GetString()[0], "difficulty") == 0) {
            dye("\t\tDifficulty \t-> ", dim); cout << "[";
            for(int d = 1; d <= 10; d++) {
                if (d <= infoValue) {
                    if (infoValue < 4) dye("|", PBHigh);
                    else if (infoValue >= 4 && infoValue <=6) dye("|", PBMid);
                    else if (infoValue > 6) dye("|", PBLow);
                }
                else cout << "-";
            }
            cout << "] "; dye(to_string(champInfo.value.GetInt()), dim); cout << "/10\n";
        }
    }

    cout << endl;

    for (const auto &champPassive : document["data"][champion->c_str()]["passive"].GetObj()) {
        if (strcmp(&champPassive.name.GetString()[0], "name") == 0) {
            dye(champPassive.value.GetString(), bold); cout << ": ";
        }
        if (strcmp(&champPassive.name.GetString()[0], "description") == 0) {
            cout << champPassive.value.GetString() << endl << endl;
        }
    }

    int spellKey(1);
    for (const auto &champSpells : document["data"][champion->c_str()]["spells"].GetArray()) {
        for (const auto &champSpell : champSpells.GetObj()) {
            if (strcmp(&champSpell.name.GetString()[0], "name") == 0) {
                switch (spellKey) {
                    case 1:
                        dye("Q ->", spell); cout << " "; dye(champSpell.value.GetString(), bold); cout << ": ";
                        break;
                    case 2:
                        dye("W ->", spell); cout << " "; dye(champSpell.value.GetString(), bold); cout << ": ";
                        break;
                    case 3:
                        dye("E ->", spell); cout << " "; dye(champSpell.value.GetString(), bold); cout << ": ";
                        break;
                    case 4:
                        dye("R ->", spell); cout << " "; dye(champSpell.value.GetString(), bold); cout << ": ";
                        break;
                }
            }
            if (strcmp(&champSpell.name.GetString()[0], "description") == 0) {
                cout << champSpell.value.GetString() << endl;
            }
            if (strcmp(&champSpell.name.GetString()[0], "maxrank") == 0) {
                dye("Max Rank: ", bold); cout << champSpell.value.GetInt(); dye(" | ", dim);
            }
            if (strcmp(&champSpell.name.GetString()[0], "cooldownBurn") == 0) {
                dye("Cooldowns: ", bold); cout << champSpell.value.GetString(); dye(" | ", dim);
            }
            if (strcmp(&champSpell.name.GetString()[0], "costBurn") == 0) {
                dye("Cost: ", bold); cout << champSpell.value.GetString(); dye(" | ", dim);
            }
            if (strcmp(&champSpell.name.GetString()[0], "effectBurn") == 0) {
                dye("Damage: ", bold); cout << champSpell.value.GetArray()[1].GetString(); dye(" | ", dim);
            }
            if (strcmp(&champSpell.name.GetString()[0], "rangeBurn") == 0) {
                dye("Range: ", bold); cout << champSpell.value.GetString(); cout << endl << endl;
            }
        }
        spellKey++;
    }

    cout << endl;

    int cols(0);
    for (auto &champStat: document["data"][champion->c_str()]["stats"].GetObj()) {
        if (strcmp(&champStat.name.GetString()[0], "hp") == 0) {
            dye("HP", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "hpperlevel") == 0) {
            dye("HP Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "mp") == 0) {
            dye("MP", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "mpperlevel") == 0) {
            dye("MP Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "movespeed") == 0) {
            dye("Movement Speed", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "armor") == 0) {
            dye("Armor", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "armorperlevel") == 0) {
            dye("Armor Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "spellblock") == 0) {
            dye("Spell Block", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "spellblockperlevel") == 0) {
            dye("SB Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "attackrange") == 0) {
            dye("Attack Range", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "hpregen") == 0) {
            dye("HP Regen", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "hpregenperlevel") == 0) {
            dye("HP Regen Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "mpregen") == 0) {
            dye("MP Regen", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "mpregenperlevel") == 0) {
            dye("MP Regen Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "crit") == 0) {
            dye("Critical Strike Chance", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "critperlevel") == 0) {
            dye("CSC Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "attackdamage") == 0) {
            dye("Attack Damage", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "attackdamageperlevel") == 0) {
            dye("AD Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "attackspeedperlevel") == 0) {
            dye("AS Per Level", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }
        if (strcmp(&champStat.name.GetString()[0], "attackspeed") == 0) {
            dye("Attack Speed", statName); dye(to_string(champStat.value.GetFloat()), statValue); cout << "\t";
        }

        cols++;
        if (cols == 2) { cout << endl << endl; cols = 0; }
    }

    int tips_count(1);

    dye("\nTips on how to play this champion:\n", bold);
    if (!document["data"][champion->c_str()]["allytips"].GetArray().Empty()) {
        for (const auto &champAllyTip : document["data"][champion->c_str()]["allytips"].GetArray()) {
            dye(to_string(tips_count), bold); cout << ". " << champAllyTip.GetString() << endl; tips_count++;
        }
    }
    else dye("There's no ally tips available.\n", warn);

    dye("\nTips on how to play against this champion:\n", bold);
    if (!document["data"][champion->c_str()]["enemytips"].GetArray().Empty()) {
        tips_count = 1;
        for (const auto &champEnemyTip : document["data"][champion->c_str()]["enemytips"].GetArray()) {
            dye(to_string(tips_count), bold); cout << ". " << champEnemyTip.GetString() << endl; tips_count++;
        }
    }
    else dye("There's no enemy tips available.\n", warn);


    dye("\n\nWho's " + champName + "\n", underline);
    if (!champLore.empty()) cout << champLore;
    else dye("There's no lore available.", warn);
    cout << endl << endl << endl;

    dye("This info was retrieved from Riot Games servers using Data Dragon LoL Patch \"" + patchVersion + "\".\n", dim);
    dye("If you want some info on this champion from a specific patch from the past then make sure to include the version or type \"help\".\n", dim);
    dye("Disclaimer: This software was NOT made nor affiliated by Riot Games. I just made it for fun --Xen <3 \n", warn);

}

void DataReader::printPatches()
{
    Document document;
    document.Parse(jsonData->c_str());
    if (document.HasParseError()) {
        dye("JSON data was retrieved but parsing process failed, Here's the error:\n", error);
        dye("Code: " + to_string(document.GetParseError()) +
            "\tOffset: " + to_string(document.GetErrorOffset()) +
            "\nMessage: " + GetParseError_En(document.GetParseError()) + "\n", error);
        throw (103);
    }

    for (const auto &patch : document.GetArray()) {
        cout << patch.GetString() << endl;
    }
}
void DataReader::printLanguages()
{
    Document document;
    document.Parse(jsonData->c_str());
    if (document.HasParseError()) {
        dye("JSON data was retrieved but parsing process failed, Here's the error:\n", error);
        dye("Code: " + to_string(document.GetParseError()) +
            "\tOffset: " + to_string(document.GetErrorOffset()) +
            "\nMessage: " + GetParseError_En(document.GetParseError()) + "\n", error);
        throw (104);
    }

    for (const auto &language : document.GetArray()) {
        cout << language.GetString() << endl;
    }
}
const vector<string> DataReader::versions()
{
    Document document;
    document.Parse(jsonData->c_str());
    if (document.HasParseError()) {
        dye("JSON data was retrieved but parsing process failed, Here's the error:\n", error);
        dye("Code: " + to_string(document.GetParseError()) +
            "\tOffset: " + to_string(document.GetErrorOffset()) +
            "\nMessage: " + GetParseError_En(document.GetParseError()) + "\n", error);
        throw (105);
    }
    vector<string> v;
    for (const auto &patch : document.GetArray()) {
        v.push_back(patch.GetString());
    }
    return v;
}
