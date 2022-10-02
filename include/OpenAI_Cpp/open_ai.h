#pragma once

#include <string>

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

namespace AI
{
/**
 * @brief Client class for OpenAI_Cpp. This is what the user initializes with their API key and optional organization ID. This class will
 * also be how most OpenAI api calls can be made.
 */
class OpenAI 
{
public:
    /**
    * @brief OpenAI constructor takes in two arguments. The unique api_key assigned by OpenAI, and an optional organization identifier.
    * If you do not have a organization identifier, you can leave it blank.
    * 
    * @param api_key secret api key assigned to you by OpenAI
    * @param org_id organization identifier if available. Can be left blank if not used.
    * 
    * @see OpenAI API: Authentication
    * @see https://beta.openai.com/docs/api-reference/authentication
    */
    OpenAI(const std::string& api_key, const std::string& org_id = "");

private:
    
    const std::string api_key_auth;
    const std::string org_identifier;
};

}