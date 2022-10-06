#include "OpenAI_Cpp/Models/models.h"

namespace AI
{
ModelTypeMap Model::model_type_map{};

Model::Model(const std::string& id)
	: id(id), object(""), owned_by(""),
	permission(nullptr)
{
}


Model::Model(AI::ModelType model)
	: id(""), object(""), owned_by(""),
	permission(nullptr)
{
	this->id = this->model_type_map.GetModelToStringMap().at(model);
}

Model::~Model() {}

Model::Model(Model&& other) noexcept :
	id(std::move(other.id)), object(std::move(other.object)),
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

}