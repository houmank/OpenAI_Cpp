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

TEST(deserializePermissionFromJson, BadPermissionParsed)
{
	// TODO tomorrow
	ASSERT_FALSE(true);
}

TEST(deserializePermissionFromJson, GoodPermissionParsed)
{
	// TODO tomorrow
	ASSERT_FALSE(true);
}

TEST(deserializeModelFromJson, BadModelParsed)
{
	// TODO tomorrow
	ASSERT_FALSE(true);
}

TEST(deserializeModelFromJson, GoodModelParsed)
{
	// TODO tomorrow
	ASSERT_FALSE(true);
}