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

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>

#include <DataFetcher.h>
#include <DataReader.h>
#include <versions.h>

using namespace std;

bool ANSI;

void print_homescreen()
{
    cout << endl << " _            _       ______ _____   ______  "   << endl;
    cout << "| |          | |     / _____|____ \\ (____  \\ " << endl;
    cout << "| |      ___ | |    | /      _   \\ \\ ____)  )" << endl;
    cout << "| |     / _ \\| |    | |     | |   | |  __  ( "  << endl;
    cout << "| |____| |_| | |____| \\_____| |__/ /| |__)  )"  << endl;
    cout << "|_______)___/|_______)______)_____/ |______/ "   << endl << endl;

    dye(Product::name + "\tVersion: " + Product::version + "\t" + Architecture::humanReadable +
        "\n\n" + Libraries::libcurlVersion + " RapidJSON/" + Libraries::rapidJSONVersion +
        "\n\nCompiled using " + usedCompiler::name + " Version: " + usedCompiler::version + "\n" +
        "Written by " + Developer::name + "<" + Developer::email + ">\t" + Developer::domain + "\n\n\n", dim);
}

//Checks if arguments are valid before making a request
bool validateArg(const string &arg, string &patchVar, string &langVar)
{
    //Language codes have 5 characters and underscore in the middle separating between language and country code.
    if (arg.length() == 5 && arg.find('_', 2) != string::npos) langVar = arg;
    else if (strcmp(arg.c_str(), "ANSI") == 0 | strcmp(arg.c_str(), "ansi") == 0) ANSI = true;
    //All versions contain numbers even the old patches, so it's safe to only detect a number
    else if (any_of(arg.begin(), arg.end(), ::isdigit)) patchVar = arg;
    else {
        dye("The argument \"" + arg + "\" you entered doesn't make sense!.", error);
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    //Enable ANSI escape sequences if not running on Windows
    #ifndef WIN32
        ANSI = true;
    #else
        ANSI = false;
    #endif

    string champ, patch, lang("en_US");

    if (argc == 1) {
        dye("Type a champion name or \"help\" then try again.\nExample: Irelia", error);
        return -1;
    }
    if (argc > 5) {
        dye("There's too many arguments, Maximum is 4.\nExample: Kassadin 4.4.3 fr_FR", error);
        return -1;
    }
    if (argc == 2) {
        if (strcmp(argv[1], "help") == 0 |
            strcmp(argv[1], "Help") == 0 |
            strcmp(argv[1], "guide") == 0 |
            strcmp(argv[1], "Guide") == 0 |
            strcmp(argv[1], "manual") == 0 |
            strcmp(argv[1], "Manual") == 0) {

            print_homescreen();

            cout << "["; dye("Champion", bold); cout << "] ["; dye("Patch", bold); cout << "] ["; dye("Language", bold); cout << "] "; dye("ANSI", bold); cout << "\nOR: ";
            cout << "["; dye("Champion", bold); cout << "] ["; dye("Language", bold); cout << "]\nOR: ";
            cout << "["; dye("Champion", bold); cout << "] ["; dye("Patch", bold); cout << "]\nOR: ";
            cout << "["; dye("Champion", bold); cout << "] "; dye("ansi", bold); cout << "\nOR Just: ";
            cout << "["; dye("Champion", bold); cout << "]\n\n";
            cout << "You don't have to type the patch version or the language code everytime you make a request because "
                    "they will be handled automatically, But the champion name is required.\n\n";

            cout << "Keep in mind that the way you type a champion name is IMPORTANT! URLs in data dragon are case-sensitive "
                    "and do not have spaces! Example:\n";

            dye("Bad  -> lee sin\n", warn);
            dye("Bad  -> leesin\n", warn);
            dye("Bad  -> Lee sin\n", warn);
            dye("Bad  -> Lee Sin\n", warn);
            dye("Good -> LeeSin\n\n", done);

            cout << "It's OK to type one word champion names without uppercase letters, Example:\n";
            dye("Good -> teemo\n", done);
            dye("Good -> Teemo\n\n", done);
            cout << "The app will correct it for you, but other names need to be typed correctly or you're going to face errors.\n"
                    "This law also applies to language codes; "; dye("LANGUAGE_COUNTRYCODE",bold); cout << " (en_US, en_GB, fr_FR...etc).\n\n";

            cout << "For a full list of available Patches type one of the following words: ";
                    dye("versions", bold); cout << " or "; dye("patches", bold); cout << ".\n";

            cout << "For a full list of available Languages type one of the following words: ";
                    dye("langs", bold); cout << " or "; dye("codes", bold); cout << " or "; dye("languages", bold);

            cout << ".\n\nThese lists are not cached, but obtained from Riot Games servers through HTTP, "
                    "so if you don't see an item you need to wait couple days until they update it.\n"
                    "And to maximize performance you should include the patch version when you make a request.\n\n";

            cout << "On Windows, by default " << Product::shortName << " uses Windows native API to color data and on POSIX systems "
                    "it uses ANSI. If you want to enable the ANSI by force then use ";
                    dye("ANSI", bold); cout << " or "; dye("ansi", bold); cout << " after the champion name. This will color data using ANSI "
                    "escape sequences instead of using Windows native API, But please make sure that your terminal supports it "
                    "if you're using the classical \"cmd.exe\" or \"PowerShell\"..etc then it won't work! This feature was intended for "
                    "POSIX systems like Linux or Mac. You can still get it on Windows but you'll need a better terminal/console.\n\n";

            return 0;
        }
        else if (   strcmp(argv[1], "patches") == 0 |
                    strcmp(argv[1], "Patches") == 0 |
                    strcmp(argv[1], "versions") == 0 |
                    strcmp(argv[1], "Versions") == 0) {

                    DataFetcher versionsFetcher;
                    versionsFetcher.type = Patches;
                    try {
                        versionsFetcher.fetch();
                        DataReader versionsReader;
                        versionsReader.jsonData = &versionsFetcher.data;
                        versionsReader.printPatches();
                        return 0;
                    }
                    catch (int err_code) {
                        dye("LoLCDB error code: " + to_string(err_code) + ".\n", error);
                        return -1;
                    }
        }
        else if (   strcmp(argv[1], "languages") == 0 |
                    strcmp(argv[1], "Languages") == 0 |
                    strcmp(argv[1], "langs") == 0 |
                    strcmp(argv[1], "Langs") == 0 |
                    strcmp(argv[1], "codes") == 0 |
                    strcmp(argv[1], "Codes") == 0) {

                    DataFetcher langsFetcher;
                    langsFetcher.type = Languages;
                    try {
                        langsFetcher.fetch();
                        DataReader langsReader;
                        langsReader.jsonData = &langsFetcher.data;
                        langsReader.printLanguages();
                        return 0;
                    }
                    catch (int err_code) {
                        dye("LoLCDB error code: " + to_string(err_code) + ".\n", error);
                        return -1;
                    }

        }
        else {
            //Easter egg Shhhh :^)
            if (strcmp(argv[1], "rammus") == 0) {
                random_device rd; mt19937 gen(rd());
                uniform_int_distribution<> range(1, 1000); //0.10% chance
                const int OK = range(gen);
                if (OK == 666) {
                    dye("\n\n\n\n\n\t\tOK!\n\n\n\n\n", bold);
                    return 0;
                }
            }
            champ = argv[1];
        }
    }
    if (argc == 3) { //Two arguments
        champ = argv[1];
        const string secondArg(argv[2]);
        if (!validateArg(secondArg, patch, lang)) return -1;
    }
    if (argc == 4) { //Three arguments
        champ = argv[1];
        const string secondArg(argv[2]);
        const string thirdArg(argv[3]);
        if (!validateArg(secondArg, patch, lang)) return -1;
        if (!validateArg(thirdArg, patch, lang)) return -1;
    }
    if (argc == 5) { //Four arguments        
        champ = argv[1];
        const string secondArg(argv[2]);
        const string thirdArg(argv[3]);
        const string fourthArg(argv[4]);
        if (!validateArg(secondArg, patch, lang)) return -1;
        if (!validateArg(thirdArg, patch, lang)) return -1;
        if (!validateArg(fourthArg, patch, lang)) return -1;
    }

    try {
        DataFetcher champFetcher;
        champFetcher.type         = Champion;
        champFetcher.championName = champ;
        champFetcher.language     = lang; //Default is english US (en_US)

        //Only bother to retrieve versions data if no patch version is provided by user
        if (patch.empty()) {
            DataFetcher patchesFetcher;
            patchesFetcher.type = Patches;
            patchesFetcher.fetch();

            DataReader patchesReader;
            patchesReader.jsonData = &patchesFetcher.data;
            if (patchesReader.versions().size() < 1) {
                dye("Failed to get patches list, Please try again but with a patch version included. type \"help\".\n", error);
                throw (106);
            }
            champFetcher.patch = patchesReader.versions().at(0); //Latest patch
        }
        else champFetcher.patch = patch;

        champFetcher.fetch();

        //Making sure the JSON data is legit
        if (champFetcher.data.length() > 1000) {
            DataReader reader;
            reader.jsonData = &champFetcher.data;
            reader.champion = &champFetcher.championName;
            reader.printChampion();
        }
        else {
            dye("There's a response from the server but for some reason data is empty or corrupt!\n"
                "Recheck the champion name or patch version/language code then try again.", error);
            throw (107);
        }
    }
    catch (int err_code) {
        dye("\nLoLCDB error code: " + to_string(err_code) + ".\n"
            "Inputs used to try to fetch data:\n"
            "Champion name: " + champ +
            "\nPatch version: " + patch +
            "\nLanguage code: " + lang + "\n\n", error);

        return -1;
    }

    return 0;
}
