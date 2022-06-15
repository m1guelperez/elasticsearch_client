//
// Created by miguel on 6/11/22.
//

#pragma once
#include <curl/curl.h>

//Check if the query to elasticsearch was successfully
bool responseCheck(CURLcode res);