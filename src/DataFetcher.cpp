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

#include <DataFetcher.h>

size_t DataFetcher::WriteCallback(const char *in, size_t size, size_t num, string *out)
{
    const size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

void DataFetcher::fetch()
{
    CURL *curl;
    CURLcode res_code;

    string URL;
    long http_code;

    switch (type) {
        case Champion:
            //Making sure first letter is uppercase
            championName[0] = toupper(championName[0]);

            //Remove any white spaces
            championName.erase(remove(championName.begin(), championName.end(), ' '), championName.end());

            URL = "http://ddragon.leagueoflegends.com/cdn/"+patch+"/data/"+language+"/champion/"+championName+".json";
            break;
        case Patches:
            URL = "http://ddragon.leagueoflegends.com/api/versions.json";
            break;
        case Languages:
            URL = "http://ddragon.leagueoflegends.com/cdn/languages.json";
            break;
    }

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

        //Time out in seconds
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

        //Follow HTTP redirects if necessary, by default it's disabled
        if (followRedirects)
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, maxRedirects);

        //IPv4 is much faster than IPv6 when it comes to DNS resolution time
        if (ipv6)
            curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V6);
        else
            curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

        //Handles content writing, most be static function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        res_code = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(curl);

        if (res_code != CURLE_OK || http_code != 200) {
            dye("Failed to perform a http request to Riot Games servers.\n"
                "HTTP response code: " + to_string(http_code) +
                "\nCURL code: " + to_string(res_code) +
                "\nCURL message: " + curl_easy_strerror(res_code) + "\n", error);

            throw (101);
        }
    }
}
