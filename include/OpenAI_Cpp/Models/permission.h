#pragma once

#include <cstdint>
#include <string>

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
	std::string id = "";
	std::string object = "";
	uint64_t created = 0;
	bool allow_create_engine = false;
	bool allow_sampling = false;
	bool allow_logprobs = false;
	bool allow_search_indices = false;
	bool allow_view = false;
	bool allow_fine_tuning = false;
	std::string organization = "*";
	std::string group = "*";
	bool is_blocking = false;
};
}