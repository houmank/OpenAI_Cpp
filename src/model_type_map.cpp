#include "OpenAI_Cpp/model_type_map.h"

namespace AI
{
	ModelTypeMap::ModelTypeMap()
	{
		// initialize the mappings
		this->modelToStringMap =
		{
			{ModelType::Davinci, "davinci"},
			{ModelType::Curie, "curie"},
			{ModelType::Babbage, "babbage"},
			{ModelType::Ada, "ada"},
			{ModelType::Text_Davinci_002, "text-davinci-002"},
			{ModelType::Text_Curie_001, "text-curie-001"},
			{ModelType::Text_Babbage_001, "text-babbage-001"},
			{ModelType::Text_Ada_001, "text-ada-001"},
			{ModelType::Code_Davinci_002, "code-davinci-002"},
			{ModelType::Code_Cushman_001, "code-cushman-001"},
			{ModelType::Content_Filter_Alpha, "content-filter-alpha"}
		};

		this->stringToModelMap =
		{
			{"davinci", ModelType::Davinci},
			{"curie", ModelType::Curie},
			{"babbage", ModelType::Babbage},
			{"ada", ModelType::Ada},
			{"text-davinci-002", ModelType::Text_Davinci_002},
			{"text-curie-001", ModelType::Text_Curie_001},
			{"text-babbage-001", ModelType::Text_Babbage_001},
			{"text-ada-001", ModelType::Text_Ada_001},
			{"code-davinci-002", ModelType::Code_Davinci_002},
			{"code-cushman-001", ModelType::Code_Cushman_001},
			{"content-filter-alpha", ModelType::Content_Filter_Alpha}
		};
	}

	const std::unordered_map<AI::ModelType, std::string>& ModelTypeMap::GetModelToStringMap()
	{
		return this->modelToStringMap;
	}

	const std::unordered_map<std::string, AI::ModelType>& ModelTypeMap::GetStringToModelMap()
	{
		return this->stringToModelMap;
	}
}