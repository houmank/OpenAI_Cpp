#pragma once

#include <cstdint>

namespace AI
{

/**
* @brief ModelType is used to categorize the popular openai models available. Some are only available for certain endpoints
* so it is important we keep track of which model type is used. 
* 
* This provides access to GPT-3 Models, Codex Models, and Content filter models.
* 
* @see OpenAI API: Models
* @see https://beta.openai.com/docs/models/overview
*/
enum ModelType : std::uint8_t
{
	// Older version of GPT-3 Models
	// Often used with fine-tuning endpoints
	Davinci = 0,
	Curie, 
	Babbage,
	Ada,
	// Current Version GPT-3 Models
	// Used with text completion endpoints
	Text_Davinci_002,
	Text_Curie_001,
	Text_Babbage_001,
	Text_Ada_001,
	// Current version Codex Models
	Code_Davinci_002,
	Code_Cushman_001,
	// Content Filter Models, API suggests using moderation endpoint instead of model
	Content_Filter_Alpha
};
}