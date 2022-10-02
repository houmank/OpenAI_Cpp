#pragma once

#include <cstdint>

namespace AI
{

/**
* @brief permission struct that contains all of the permissions allowed to the attached model. This will be used to determine what actions can be done 
* through the API with the users permission level and model type.
* 
* 
* @see OpenAI API
* @see https://beta.openai.com/docs/api-reference/models
*/
struct Permission
{
	std::string id;
	std::string object;
	uint64_t created;
	bool allow_create_engine;
	bool allow_sampling;
	bool allow_logprobs;
	bool allow_search_indices;
	bool allow_view;
	bool allow_fine_tuning;
	std::string organization;
	std::string group;
	bool is_blocking;
};
}