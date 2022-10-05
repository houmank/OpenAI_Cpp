#pragma once

#include <memory>

#include "permission.h"
#include "model_type.h"
#include "model_type_map.h"

namespace AI
{
/**
* @brief Model is the new version of OpenAI engines.This class is how the library dictates what model to use when calling different endpoints.
* Well known models will be accessible through static factory methods. More info can be seen at OpenAI's api documentation.
*
* @see OpenAI API: Models
* @see https://beta.openai.com/docs/models/overview
* @see https://beta.openai.com/docs/api-reference/models
*/

class Model
{
public:
	// Friend classes
	friend class OpenAI;
	

	/**
	* @brief Model constructor takes in the id of the model. If a user wants a well-known model
	* they can use the overloaded constructor which takes in a ModelType enum. Users shouldnt call this
	* constructor, instead they should use OpenAI.Model to get model referrence.
	* 
	* @param id the id assigned by openai to the model..
	*/
	Model(const std::string& id);



	/**
	* @brief Model constructor accepts a ModelType enum. These modeltype enums are availble for the
	* most of the popular models available currently. See https://beta.openai.com/docs/models/overview.
	* Users shouldnt call this constructor, instead they should use OpenAI.Model() to get model referrence.
	* 
	* @param modelType is the enum indicating which well known model to use
	*/
	Model(AI::ModelType modelType);

private:
	std::string id;
	std::string object;
	std::string owned_by;
	std::unique_ptr<AI::Permission> permission;

	static AI::ModelTypeMap model_type_map;
};
}