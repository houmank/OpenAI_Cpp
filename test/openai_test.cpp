#include "gtest/gtest.h"
#include "OpenAI_Cpp/open_ai.h"

#include <fstream>
#include <memory>

static const std::string API_KEY_FP = R"(test\OpenAI_API_SK.txt)";
static std::string secret;

class OpenAI_Fixture : public ::testing::Test
{
public:

	static void SetUpTestSuite()
	{
		// Load secret key for OpenAI object creation
		std::ifstream ifstream;
		ifstream.open(API_KEY_FP);
		if (ifstream.is_open())
		{
			std::getline(ifstream, secret);
			ifstream.close();
		}
		
	}

	virtual void SetUp() override
	{
		openai = std::make_unique<AI::OpenAI>(secret);
	}

	
	std::unique_ptr<AI::OpenAI> openai = nullptr;
};

TEST_F(OpenAI_Fixture, ModelBuilder)
{
	openai->Model(AI::ModelType::Text_Davinci_002);
}