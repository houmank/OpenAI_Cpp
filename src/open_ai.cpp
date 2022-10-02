#include "OpenAI_Cpp/open_ai.h"

namespace AI 
{
	const std::string OPENAI_API_URL = R"(https://api.openai.com/v1/)";
	const std::string OPENAI_API_ORG_HEADER = "OpenAI-Organization";

OpenAI::OpenAI(const std::string& api_key, const std::string& org_id)
	: api_key_auth(api_key), org_identifier(org_id)
{}

}
