#pragma once

#include <string>
#include <assert.h>

#include "rapidjson/document.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"

#include "OpenAI_Cpp/Error/error.h"

namespace AI
{
    /**
    * schemaStringToSchemaDocument is a quick helper function that converts schema string first into a json document,
    * then will convert document to a schemadocument which is then returned.
    * 
    * @param schema schema as const char*
    * @return SchemaDocument
    */
    rapidjson::SchemaDocument schemaStringToSchemaDocument(const char* schema);
    

    /**
    * validateJson will accept a schema, and an input json document to validate. The function will
    * return a AI::Error, The AI::Error.type will be set to NO_ERR if the validation was done successfully, else
    * error type will be set to JSON_DOCUMENT_BAD_FORMAT.The AI::Error.message will be set to a detailed error message
    * indicating where the validation failed.
    * 
    * @param schema schema as const char*
    * @param inputJson input json as rapidjson::document
    * @return AI::Error, if json is valid Error.type == ErrorType::NO_ERR
    */
    AI::Error validateJson(const char* schema, const rapidjson::Document& json);

    /**
    * getOpenAIModelSchema is a function that returns string literal of model object schema.
    * 
    * @return const char* of model schema
    */
    const char* getOpenAIModelSchema();

}