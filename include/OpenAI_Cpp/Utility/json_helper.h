#pragma once

#include <string>
#include <memory>
#include <variant>

#include "OpenAI_Cpp/Models/permission.h"
#include "OpenAI_Cpp/Models/models.h"
#include "OpenAI_Cpp/Error/error.h"
#include "OpenAI_Cpp/Utility/json_schemas.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/pointer.h"

namespace AI
{
	/**
	* @brief serializeRapidJson is a simple function that uses a StringBuffer and writer to serialize the DOM style document.
	* It will return a std::string with the serialized JSON document's data. There is an overloaded function for
	* rapidjson::Value
	* 
	* @see https://rapidjson.org/classrapidjson_1_1_pretty_writer.html
	* 
	* @param rapidjson json object passed in as const referrence
	* @return serialized serialized string
	*/
	std::string serializeRapidJson(const rapidjson::Document& json);

	/**
	* @brief serializeRapidJson is a simple function that uses a StringBuffer and writer to serialize a rapidjson value object.
	* It will return a std::string with the value's data serialized. There is an overloaded function for rapidjson::Document as well.
	* 
	* @see https://rapidjson.org/classrapidjson_1_1_pretty_writer.html
	* 
	* @param rapidjson json object passed in as const referrence
	* @return serialized serialized string
	*/
	std::string serializeRapidJson(const rapidjson::Value& json);

	/**
	* @brief checkErrorInJson is a helper function that checks root document for an "error" object.
	* If one is found, user can call errorMessageInJsonResponse to try and get the error message.
	* 
	* @param json rapidjson::document object which will be parsed
	* @return boolean that tells caller if an error json object is present
	*/
	bool checkErrorInJson(const rapidjson::Document& json);

	/**
	* @brief errorMessageInJsonResponse is a function that parses the top level json document for an OpenAI error, if
	* one occured then the function returns the error message that openai provided. This function will assume there is
	* an "error" object, if one doesn't exist or a bad json format was parsed, the variant will be set to type: AI:ErrorType.
	* 
	* @param json rapidjson document object to parse
	* @return errorMessage std::variant<string, AI::ErrorType>, if message was parsed successful it will be string else errortype enum
	*/
	std::variant<std::string, AI::Error> errorMessageInJsonResponse(rapidjson::Document& json);

	/**
	* @brief deserializePermissionFromJson is a function that will take a rapidjson::value pointer to a permission object
	* within a json structure.The function will assume the json has been validated against permission schema before calling the function.
	* The function will return a variant of unique_ptr to a permission object that was parsed successfully, or 
	* AI::Error if an error occured during parsing.
	* 
	* @param permission Value* to permission object with json root
	* @return unique_ptr<permission> if successful, else AI::Error. Both inside of std::variant<>
	*/
	std::variant<std::unique_ptr<AI::Permission>, AI::Error> deserializePermissionFromJson(rapidjson::Value* permissionPtr);

	/**
	* @brief deserializeModelFromJson will parse a model json object into a AI::Model object. The function 
	* will check the given json against a model schema located inside json_schema.h, if schema does not match
	* model an error will be returned in the form of AI::Error. The user will
	* pass in a constructed unique_ptr to a model where the parsed data will be loaded into.
	* If the function deserialized successfully the AI::Error will return NO_ERR
	* 
	* @param json json of the model object which is going to be deserialized
	* @return model on success the AI::Error will have error.type == NO_ERR, else error will be set w/ error.message
	*/
	AI::Error deserializeModelFromJson(rapidjson::Value* modelJsonPtr, std::unique_ptr<AI::Model>& modelObj);
}