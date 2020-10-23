#include "../header/ErrorLibrary.h"

namespace ErrorLibrary
{
	ErrorState state = ErrorState::NONE;

	std::string GetErrorMessage()
	{
		std::string message;
	
		switch (state)
		{
		case ErrorState::NONE:
			message = "NONE";
			break;
		case ErrorState::EXPECT_COMMAND:
			message = "EXPECTED COMMAND";
			break;
		case ErrorState::EXPECT_CONNECTOR:
			message = "EXPECTED CONNECTOR";
			break;
		case ErrorState::EXPECT_PARENTHESIS:
			message = "EXPECTED PARENTHESIS";
			break;
		default:
			break;
		}
	
		return message;
	}	
}