#include "OpenAI_Cpp/Utility/json_helper.h"

namespace AI
{

std::string serializeRapidJson(const rapidjson::Document& json)
{
	rapidjson::StringBuffer buffer;
	buffer.Clear();
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	json.Accept(writer);

	return buffer.GetString();
}

std::string serializeRapidJson(const rapidjson::Value& json)
{
	rapidjson::StringBuffer buffer;
	buffer.Clear();
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	json.Accept(writer);

	return buffer.GetString();
}

bool checkErrorInJson(const rapidjson::Document& json)
{
	return (json.FindMember("error") != json.MemberEnd());
}

std::variant<std::string, AI::Error> errorMessageInJsonResponse(rapidjson::Document& json)
{
	/* Typical error response from OpenAI expected
	* {
	*	"error": {
	*		"message": "...",
	*		"type": "...",
	*		"param": ..., "code: ...
	*	}
	* }
	*/
	if (rapidjson::Value* value = rapidjson::Pointer("/error/message").Get(json))
		if (value->IsString())
			return value->GetString();
	return AI::Error({ ErrorType::NO_ERR_MESSAGE_IN_JSON, std::string("Unexpected JSON structure when parsing //error//message: ") + serializeRapidJson(json)});
}


std::variant<std::unique_ptr<AI::Permission>, AI::Error> deserializePermissionFromJson(rapidjson::Value* permissionPtr)
{
	if (permissionPtr)
	{
		if (permissionPtr->IsArray() && permissionPtr->GetArray().Size() > 0)
		{
			using rapidjson::Pointer;
			std::unique_ptr<AI::Permission> permission = std::make_unique<AI::Permission>();
			auto& perm_obj = permissionPtr->GetArray()[0];
			
			permission->id = Pointer("/id").Get(perm_obj)->GetString();
			permission->object = Pointer("/object").Get(perm_obj)->GetString();
			permission->created = Pointer("/created").Get(perm_obj)->GetUint64();
			permission->allow_create_engine = Pointer("/allow_create_engine").Get(perm_obj)->GetBool();
			permission->allow_logprobs = Pointer("/allow_logprobs").Get(perm_obj)->GetBool();
			permission->allow_view = Pointer("/allow_view").Get(perm_obj)->GetBool();
			permission->allow_fine_tuning = Pointer("/allow_fine_tuning").Get(perm_obj)->GetBool();
			permission->is_blocking = Pointer("/is_blocking").Get(perm_obj)->GetBool();

			return permission;
		}
		return AI::Error(
			{ ErrorType::JSON_DOCUMENT_BAD_FORMAT,
			std::string("Expected permission ptr to be array with json obj inside, recieved: ") + serializeRapidJson(*permissionPtr) }
		);
	}
	return AI::Error({ ErrorType::JSON_PASSED_IN_NULLPTR, "Nullptr passed into deserializePermissionFromJson" });
}

AI::Error deserializeModelFromJson(rapidjson::Value* modelJsonPtr, std::unique_ptr<AI::Model>& modelObj)
{
	if (modelJsonPtr)
	{
		using rapidjson::Pointer;

		modelObj->setObject(Pointer("/object").Get(*modelJsonPtr)->GetString());
		modelObj->setCreated(Pointer("/created").Get(*modelJsonPtr)->GetUint64());
		modelObj->setOwnedBy(Pointer("/owned_by").Get(*modelJsonPtr)->GetString());
		auto permission_parse = AI::deserializePermissionFromJson(Pointer("/permission").Get(*modelJsonPtr));
		if (const AI::Error* error = std::get_if<AI::Error>(&permission_parse))
			return *error;

		// else permission parsed successfully
		modelObj->setPermission(std::get<std::unique_ptr<AI::Permission>>(permission_parse));

		return {ErrorType::NO_ERR, ""};
	}
	return AI::Error({ ErrorType::JSON_PASSED_IN_NULLPTR, "Nullptr passed into deserializeModelFromJson" });
}

}