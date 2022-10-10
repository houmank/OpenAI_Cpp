#include "gtest/gtest.h"
#include "OpenAI_Cpp/Utility/json_schemas.h"

TEST(schemaValidator, testBadModelValidator)
{
    using namespace rapidjson;
    const char* raw_json = R"({
          "id": "text-davinci-002",
          "created": 1649880484,
          "permission" : "Not an array",
          "root": "text-davinci-002",
          "parent": null
        })";

    // parse json
    rapidjson::Document json;
    json.Parse(raw_json);
    ASSERT_TRUE(!json.HasParseError());

    auto validated_json = AI::validateJson(AI::getOpenAIModelSchema(), json);
    ASSERT_TRUE(validated_json.type != AI::ErrorType::NO_ERR);
    //std::cout << validated_json.message << '\n';
}

TEST(schemaValidator, testCorrectModelValidator)
{
    const char* raw_json = R"({
          "id": "text-davinci-002",
          "object": "model",
          "created": 1649880484,
          "owned_by": "openai",
          "permission": [
            {
              "id": "modelperm-7E53j9OtnMZggjqlwMxW4QG7",
              "object": "model_permission",
              "created": 1664307523,
              "allow_create_engine": false,
              "allow_sampling": true,
              "allow_logprobs": true,
              "allow_search_indices": false,
              "allow_view": true,
              "allow_fine_tuning": false,
              "organization": "*",
              "group": null,
              "is_blocking": false
            }
          ],
          "root": "text-davinci-002",
          "parent": null
        })";
    
    // parse json
    rapidjson::Document json;
    json.Parse(raw_json);
    ASSERT_TRUE(!json.HasParseError());

    auto validated_json = AI::validateJson(AI::getOpenAIModelSchema(), json);
    ASSERT_TRUE(validated_json.type == AI::ErrorType::NO_ERR);
}