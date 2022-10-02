#include "model_type_map.h"

namespace AI
{
	ModelTypeMap::ModelTypeMap()
	{
		// initialize the mappings
		this->modelToStringMap =
		{
			{Davinci, "davinci"},
			{Curie, "curie"},
			{Babbage, "babbage"},
			{Ada, "ada"},
			{Text_Davinci_002, "text-davinci-002"},
			{Text_Curie_001, "text-curie-001"},
			{Text_Babbage_001, "text-babbage-001"},
			{Text_Ada_001, "text-ada-001"},
			{Code_Davinci_002, "code-davinci-002"},
			{Code_Cushman_001, "code-cushman-001"},
			{Content_Filter_Alpha, "content-filter-alpha"}
		};

		this->stringToModelMap =
		{
			{"davinci", Davinci},
			{"curie", Curie},
			{"babbage", Babbage},
			{"ada", Ada},
			{"text-davinci-002", Text_Davinci_002},
			{"text-curie-001", Text_Curie_001},
			{"text-babbage-001", Text_Babbage_001},
			{"text-ada-001", Text_Ada_001},
			{"code-davinci-002", Code_Davinci_002},
			{"code-cushman-001", Code_Cushman_001},
			{"content-filter-alpha", Content_Filter_Alpha}
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