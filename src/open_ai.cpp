#include "OpenAI_Cpp/open_ai.h"
#include <iostream>

namespace AI 
{
	static const std::string OPENAI_API_URL = R"(https://api.openai.com/v1/)";
	static const std::string OPENAI_API_ORG_HEADER = "OpenAI-Organization";

OpenAI::OpenAI(const std::string& api_key, const std::string& org_id)
	: api_key_auth(api_key), org_identifier(org_id), currentModel(nullptr)
{}

const Model& OpenAI::Model(const std::string& id)
{
	this->currentModel = std::make_unique<AI::Model>(id);
	initModel();

	return *this->currentModel;
}

const AI::Model& OpenAI::Model(AI::ModelType model)
{
	this->currentModel = std::make_unique<AI::Model>(model);
	initModel();

	return *this->currentModel;
}

void OpenAI::initModel()
{
	std::string url = OPENAI_API_URL + R"(models/)" + this->currentModel->id;
	cpr::Response modelResponse = cpr::Get(cpr::Url(url),
		                          cpr::Bearer(this->api_key_auth));

	std::cout << modelResponse.text << std::endl;
}

}
