#pragma once

#include <string>

#include "OpenAI_Cpp/Error/error_type.h"

namespace AI
{
/**
* @brief AI::Error is a simple aggregate struct that holds error info.
* The class containts two member variables: AI::ErrorType and std::string for any extra details.
*/
struct Error
{
	ErrorType type;
	std::string message;
};
}