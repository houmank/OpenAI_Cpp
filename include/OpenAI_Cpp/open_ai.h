#pragma once

#include <string>

#include "cpr/cpr.h"
#include "rapidjson/rapidjson.h"

#include "OpenAI_Cpp/Models/models.h"

namespace AI
{
/**
 * @brief Client class for OpenAI_Cpp. This is what the user initializes with their API key and optional organization ID. This class will
 * also be how most OpenAI api calls can be made.
 */
class OpenAI 
{
public:
    /**
    * @brief OpenAI constructor takes in two arguments. The unique api_key assigned by OpenAI, and an optional organization identifier.
    * If you do not have a organization identifier, you can leave it blank.
    * 
    * @param api_key secret api key assigned to you by OpenAI
    * @param org_id organization identifier if available. Can be left blank if not used.
    * 
    * @see OpenAI API: Authentication
    * @see https://beta.openai.com/docs/api-reference/authentication
    */
    OpenAI(const std::string& api_key, const std::string& org_id = "");

    /**
    * Model is a builder function that returns a Model&, this model is what is currently used when calling different endpoints.
    * This method accepts two overloads. this method accepts an id string which dictates what openai model is used. User can also use 
    * the ModelType enum to indicate the id. If an invalid id was passed, the method throws InvalidArgumentException.
    * 
    * @param id the id of the model which will be used.
    * @return const referrence to the current model. referrence used so builder pattern can be used.
    * @throws InvalidArgumentException
    */
    const AI::Model& Model(const std::string& id);

    /**
    * Model is a builder function that returns a Model&, this model is what is currently used when calling different endpoints.
    * This method accepts two overloads. this method accepts a ModelType enum to indicate the id. There is also an overload for
    * passing the id in directly using a string. If an invalid modeltype was passed, the method throws InvalidArgumentException.
    * 
    * @param id the id of the model which will be used.
    * @return const referrence to the current model. referrence used so builder pattern can be used.
    * @throws InvalidArgumentException
    */
    const AI::Model& Model(AI::ModelType model);

private:
	/**
	* @brief initModel is a private initializer function that will fill out the necessary information for a given model using
	* openai's GET model/{model}. If an error occures such as not being able to find a named model using its id, the function will return false
	* else it will return true.
	* 
	* @return boolean indicates if the initialization of this object was successful
	*/
	void initModel();

private:
    
    const std::string api_key_auth;
    const std::string org_identifier;

    std::unique_ptr<AI::Model> currentModel;
};

}