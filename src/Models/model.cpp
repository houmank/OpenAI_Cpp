#include "OpenAI_Cpp/Models/models.h"

namespace AI
{
ModelTypeMap Model::model_type_map{};

Model::Model(const std::string& id)
	: id(id), object(""), created(0), owned_by(""),
	permission(nullptr)
{
}

Model::Model(AI::ModelType model)
	: id(""), object(""), created(0), owned_by(""),
	permission(nullptr)
{
	this->id = this->model_type_map.GetModelToStringMap().at(model);
}

Model::~Model() {}

Model::Model(Model&& other) noexcept :
	id(std::move(other.id)), object(std::move(other.object)), created(other.created),
	owned_by(std::move(other.owned_by)), permission(std::move(other.permission))
{}

Model& Model::operator=(Model&& other) noexcept
{
	id = std::move(other.id);
	object = std::move(other.object);
	owned_by = std::move(other.owned_by);
	permission = std::move(other.permission);

	return *this;
}

const std::string& Model::getId() const { return this->id; }

const std::string& Model::getObject() const { return this->object; }

const std::uint64_t Model::getCreated() const { return this->created; }

const std::string& Model::getOwnedBy() const { return this->owned_by; }

const AI::Permission& Model::getPermission() const { return *(this->permission); }

void Model::setObject(std::string object) { this->object = std::move(object); }

void Model::setCreated(std::uint64_t created) { this->created = created; }

void Model::setOwnedBy(std::string owned_by) { this->object = std::move(owned_by); }

void Model::setPermission(std::unique_ptr<AI::Permission>& permission) { this->permission = std::move(permission); }

}