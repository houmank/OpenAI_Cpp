#include "gtest/gtest.h"
#include "OpenAI_Cpp/model_type_map.h"

#include <string>

class model_type_map_fixture : public ::testing::Test
{
public:
	virtual void SetUp() override
	{}

	virtual void TearDown() override
	{}

	AI::ModelTypeMap model_type_map;

	// Strings
	const std::string ADA_ID = "text-ada-001";
	const std::string DAVINCI_ID = "text-davinci-002";
	const std::string CURIE_ID = "text-curie-001";
	const std::string LEGACY_ADA_ID = "ada";
};

TEST_F(model_type_map_fixture, stringToModel)
{
	AI::ModelType ada_actual = this->model_type_map.GetStringToModelMap().at(ADA_ID);
	AI::ModelType davinci_actual = this->model_type_map.GetStringToModelMap().at(DAVINCI_ID);
	AI::ModelType curie_actual = this->model_type_map.GetStringToModelMap().at(CURIE_ID);
	AI::ModelType legacy_ada_actual = this->model_type_map.GetStringToModelMap().at(LEGACY_ADA_ID);

	ASSERT_EQ(AI::ModelType::Text_Ada_001, ada_actual);
	ASSERT_EQ(AI::ModelType::Text_Davinci_002, davinci_actual);
	ASSERT_EQ(AI::ModelType::Text_Curie_001, curie_actual);
	ASSERT_EQ(AI::ModelType::Ada, legacy_ada_actual);
}

TEST_F(model_type_map_fixture, ModelToString)
{
	std::string ada_actual = this->model_type_map.GetModelToStringMap().at(AI::ModelType::Text_Ada_001);
	std::string davinci_actual = this->model_type_map.GetModelToStringMap().at(AI::ModelType::Text_Davinci_002);
	std::string curie_actual = this->model_type_map.GetModelToStringMap().at(AI::ModelType::Text_Curie_001);
	std::string legacy_ada_actual = this->model_type_map.GetModelToStringMap().at(AI::ModelType::Ada);

	ASSERT_EQ(ADA_ID, ada_actual);
	ASSERT_EQ(DAVINCI_ID, davinci_actual);
	ASSERT_EQ(CURIE_ID, curie_actual);
	ASSERT_EQ(LEGACY_ADA_ID, legacy_ada_actual);
}