#pragma once

#include <string>

namespace ErrorLibrary
{
    enum class ErrorState
    {
    	NONE,
    	EXPECT_COMMAND,
        EXPECT_CONNECTOR,
        EXPECT_PARENTHESIS
    };

    extern ErrorState state;

	std::string GetErrorMessage();
}