#include "gtest/gtest.h"
#include "OpenAI_Cpp/Utility/json_helper.h"

TEST(checkErrorInJson, ErrorInJsonRoot)
{
	std::string raw_json = R"({"error":{"testing":5 }})";
	rapidjson::Document json;
	json.Parse(raw_json.c_str());

	ASSERT_TRUE(AI::checkErrorInJson(json));
}

TEST(errorMessageInJsonResponse, BadErrorJsonPassedIn)
{
	std::string raw_json = R"({"Foo":{"Bar":"Bad Json"}})";
	rapidjson::Document json;
	json.Parse(raw_json.c_str());
	
	std::variant<std::string, AI::Error> result = AI::errorMessageInJsonResponse(json);
	ASSERT_TRUE(result.index() == 1);
	const AI::Error& error = std::get<AI::Error>(result);
	ASSERT_TRUE(error.message.find("Unexpected JSON structure") != std::string::npos);
}

TEST(errorMessageInJsonResponse, GoodErrorJsonPassedIn)
{
	std::string raw_json = 
		R"({
			"error": {
				 "message": "You didn't provide an API key. You need to provide your API key in an Authorization header using Bearer auth key from https://beta.openai.com.",
				 "type": "invalid_request_error",
				 "param": null,
				 "code": null
				 }
			})";
	rapidjson::Document json;
	json.Parse(raw_json.c_str());

	std::variant<std::string, AI::Error> result = AI::errorMessageInJsonResponse(json);
	ASSERT_TRUE(result.index() == 0);
	const std::string& message = std::get<std::string>(result);
	ASSERT_TRUE(message.find("need to provide your API key") != std::string::npos);
}

TEST(deserializePermissionFromJson, GoodPermissionParsed)
{
	// User should check for bad input with JSON schemas in json_schemas.h
	const char* raw_json =
		R"({
          "permission": [
            {
              "id": "modelperm-id123",
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
          ]
        })";

	rapidjson::Document json;
	json.Parse(raw_json);
	rapidjson::Value* permission = rapidjson::GetValueByPointer(json, "/permission");

	std::variant<std::unique_ptr<AI::Permission>, AI::Error> result = AI::deserializePermissionFromJson(permission);
	std::unique_ptr<AI::Permission>* myPerm = std::get_if <std::unique_ptr<AI::Permission>>(&result);
	ASSERT_TRUE(myPerm != nullptr);
	ASSERT_TRUE((*myPerm)->created == 1664307523);
}

TEST(deserializeModelFromJson, GoodModelParsed)
{
	// User should check for bad input with JSON schemas in json_schemas.h
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

	rapidjson::Document json;
	json.Parse(raw_json);

	std::unique_ptr<AI::Model> modelObj = std::make_unique<AI::Model>("text-davinci-002");
	AI::Error possibleError = AI::deserializeModelFromJson(&json, modelObj);
	ASSERT_TRUE(possibleError.type == AI::ErrorType::NO_ERR);
	ASSERT_TRUE(modelObj->getCreated() == 1649880484);
}