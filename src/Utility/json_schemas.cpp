#include "OpenAI_Cpp/Utility/json_schemas.h"

namespace AI
{
    rapidjson::SchemaDocument schemaStringToSchemaDocument(const char* schema)
    {
        rapidjson::Document doc;
        assert(!doc.Parse(schema).HasParseError());
        return rapidjson::SchemaDocument(doc);
    }

    AI::Error validateJson(const char* schema, const rapidjson::Document& json)
    {
        rapidjson::SchemaDocument schemaDoc = schemaStringToSchemaDocument(schema);
        rapidjson::SchemaValidator validator(schemaDoc);

        // Validate, if true error occured
        if (!json.Accept(validator))
        {
            std::string errorMessage = "";
            rapidjson::StringBuffer sb;
            validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
            errorMessage += std::string("Invalid schema: ") + sb.GetString();
            errorMessage += std::string("\nInvalid keyword: ") + validator.GetInvalidSchemaKeyword();
            errorMessage += '\n';
            return { AI::ErrorType::JSON_DOCUMENT_BAD_FORMAT, std::move(errorMessage)};
        }
        return { AI::ErrorType::NO_ERR, "" };
    }

    const char* getOpenAIModelSchema()
    {
        return R"({
              "$schema": "http://json-schema.org/draft-04/schema#",
              "description": "",
              "type": "object",
              "properties": {
                "id": {
                  "type": "string",
                  "minLength": 1
                },
                "object": {
                  "type": "string",
                  "minLength": 1
                },
                "created": {
                  "type": "number"
                },
                "owned_by": {
                  "type": "string",
                  "minLength": 1
                },
                "permission": {
                  "type": "array",
                  "uniqueItems": true,
                  "minItems": 1,
                  "items": {
                    "required": [
                      "id",
                      "object",
                      "created",
                      "allow_create_engine",
                      "allow_sampling",
                      "allow_logprobs",
                      "allow_search_indices",
                      "allow_view",
                      "allow_fine_tuning",
                      "is_blocking"
                    ],
                    "properties": {
                      "id": {
                        "type": "string",
                        "minLength": 1
                      },
                      "object": {
                        "type": "string",
                        "minLength": 1
                      },
                      "created": {
                        "type": "number"
                      },
                      "allow_create_engine": {
                        "type": "boolean"
                      },
                      "allow_sampling": {
                        "type": "boolean"
                      },
                      "allow_logprobs": {
                        "type": "boolean"
                      },
                      "allow_search_indices": {
                        "type": "boolean"
                      },
                      "allow_view": {
                        "type": "boolean"
                      },
                      "allow_fine_tuning": {
                        "type": "boolean"
                      },
                      "organization": {
                        "type": "string",
                        "minLength": 1
                      },
                      "group": {},
                      "is_blocking": {
                        "type": "boolean"
                      }
                    }
                  }
                },
                "root": {
                  "type": "string",
                  "minLength": 1
                },
                "parent": {}
              },
              "required": [
                "id",
                "object",
                "created",
                "permission"
              ]
            })";
    }
}