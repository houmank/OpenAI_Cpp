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
	friend class OpenAI;

	/**
	* Default ctro, shouldn't be used as the id is necessary for initialization by OpenAI class.
	* Only included so json can deserialize. This ctor should never be called by the user.
	*/
	Model() = default;

	/**
	* @brief Model constructor takes in the id of the model. If a user wants a well-known model
	* they can use the overloaded constructor which takes in a ModelType enum. Users shouldnt call this
	* constructor, instead they should use OpenAI.Model to get model referrence.
	* 
	* @param id the id assigned by openai to the model.
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

	/**
	* @brief Model destructor
	*/
	~Model();

	/**
	* @brief copy constructor, deleted as the Model objects shouldn't be copied once constructed.
	*/
	Model(const Model&) = delete;

	/**
	* @brief simple move constructor for Model class.
	*/
	Model(Model&& other) noexcept;

	/**
	* @brief copy assingment operator, deleted as the Model objects shouldn't be copied once constructed.
	*/
	Model& operator=(const Model&) = delete;

	/**
	* @brief simple move assignment operator for Model class.
	*/
	Model& operator=(Model&& other) noexcept;

	// Getters and setters
	// -------------------------

	/**
	* @brief getId is a getter for the id field.
	*
	* @return object const& to id string
	*/
	const std::string& getId() const;

	/**
	* @brief getObject is a getter for the object field.
	* 
	* @return object const& to object string
	*/
	const std::string& getObject() const;

	/**
	* @brief getCreated is a getter for the created time field.
	* 
	* @return created const unit64_t representing unix time
	*/
	const std::uint64_t getCreated() const;

	/**
	* @brief getOwnedBy is a getter for the owned_by field
	* 
	* @return owned_by const& to owned_by string
	*/
	const std::string& getOwnedBy() const;

	/**
	* @brief getPermission is a getter for the permission field
	* 
	* @return permission const& to AI::Permission object
	*/
	const AI::Permission& getPermission() const;

	/**
	* @brief setObject is a setter for object field
	* 
	* @param object copy of the object which will be assigned
	*/
	void setObject(std::string object);

	/**
	* @brief setCreated is a setter for the created field
	* 
	* @param created uint64_t unix time which will be assigned to created field
	*/
	void setCreated(std::uint64_t created);

	/**
	* @brief setOwnedBy is a setter for owned_by field
	* 
	* @param owned_by copy of owned_by string which will be assigned
	*/
	void setOwnedBy(std::string owned_by);

	/**
	* @brief setPermission is a stter for permission field. Note that ownership of 
	* the permission object will be transfered to model, passed in permission pointer will be 
	* invalid after setter is called.
	* 
	* @param permission referrence to permission object which will be moved into this model.
	*/
	void setPermission(std::unique_ptr<AI::Permission>& permission);

private:
	std::string id;
	std::string object;
	std::uint64_t created;
	std::string owned_by;
	std::unique_ptr<AI::Permission> permission;

	static AI::ModelTypeMap model_type_map;
};
}