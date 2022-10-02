#pragma once

#include <unordered_map>
#include "model_type.h"

namespace AI
{
/**
* @brief This class is a simple bidirectional map for the ModelType enum. This is the recieved model string 
* can be mapped correctly to the internal ModelType enum used by the library.
*/
class ModelTypeMap
{
public:
	/**
	* @brief default constructor. This initializes the bidirectional mapping. Once created user
	* can call the appropriate getter to access the mapping.
	*/
	ModelTypeMap();
	
	/**
	* @brief GetModelToStringMap returns a reference to an unordered_map between 
	* AI::ModelType to std::string returned by the OpenAI API.
	* 
	* @return Reference to unordered_map
	*/
	const std::unordered_map<AI::ModelType, std::string>& GetModelToStringMap();

	/**
	* @brief GetStringToModelMap returns a reference to an unordered_map between
	* std::string (which is returned by OpenAI API) to AI::ModelType.
	*
	* @return Reference to unordered_map
	*/
	const std::unordered_map<std::string, AI::ModelType>& GetStringToModelMap();

private:
	const std::unordered_map<AI::ModelType, std::string> modelToStringMap;
	const std::unordered_map<std::string, AI::ModelType> stringToModelMap;
};
}