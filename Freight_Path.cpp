//
// Created by agla on 2021-06-22.
//

#include "Freight_Path.h"
//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

#include <curl/curl.h>

Freight_Path::Freight_Path(int missionId) : mission_id(missionId)
{
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

string Freight_Path::find_route() {
    string json_data = this->get_points();

    if (json_data.find("error"))
        return json_data;

//    json::parse($json_data);
}

string Freight_Path::get_points()
{
//    sql::Driver *driver;
//    sql::Connection *con;
//    sql::Statement *stmt;
//    sql::ResultSet *res;
//
//    driver = get_driver_instance();
//    con = driver->connect("tcp://127.0.0.1:3306", "develop", "Nopass1!");
//    con->setSchema("develop");
//
//    stmt = con->createStatement();
//    res = stmt->executeQuery("select info_data from im_info where info_key='mission_" + std::to_string(mission_id) + "'");
//    res->next();
//    std::istream *data = res->getBlob("info_data");
//
//
//    delete res;
//    delete stmt;
//    delete con;

    string url("http://127.0.0.1/wp-json/freight/v1/freight?mission_ids=");
    url += std::to_string(mission_id);

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        /* always cleanup */
        curl_easy_cleanup(curl);

        return response_string;
    }

    return "error: can't get path";


}

