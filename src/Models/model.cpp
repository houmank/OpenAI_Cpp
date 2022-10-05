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
}