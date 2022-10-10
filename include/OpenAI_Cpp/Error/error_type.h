#pragma once

#include <cstdint>

namespace AI
{
/**
* @brief ErrorType enum will hold the error codes for the different errors that could occure. This enum will be used
* in the error handling functions of the API wrapper.
*/
enum ErrorType : std::uint8_t
{
	NO_ERR = 0,
	NO_ERR_MESSAGE_IN_JSON,
	JSON_DOCUMENT_BAD_FORMAT,
	JSON_PASSED_IN_NULLPTR
};
}