#include <stack>

#include "../header/Executor.h"
#include "../header/Connector.h"
#include "../header/ErrorLibrary.h"
#include "../header/Command.h"

bool Executor::operator()(const std::vector<Command*>& postfix)
{
	std::stack<Command*> result;
	
	for (const auto& t : postfix)
	{
		if (t)
		{
			const Connector* tempConn = dynamic_cast<Connector*>(t);

			if (tempConn)
			{
				switch (t->Type())
				{
				case Token::TokenType::SEMICOLON:
				case Token::TokenType::AND:
				case Token::TokenType::OR:
				case Token::TokenType::PIPE:
				case Token::TokenType::INPUT_REDIRECTION:
				case Token::TokenType::OUTPUT_REDIRECTION:
				case Token::TokenType::OUTPUT_APPEND:
				{
					Command* rhs = result.top();
					result.pop();

					Command* lhs = result.top();
					result.pop();

					Command* conn = Token::Create(t->Type());

					conn->Left(lhs);
					conn->Right(rhs);
					
					ptrs.emplace_back(conn);
					result.push(conn);
					break;
				}
				default:
					break;
				}
			}
			else
				result.push(t);
		}
	}

	bool ret = false;

	if (!result.empty() && result.top())
	{
                ret = result.top()->Execute();
		
		for (const auto& i : ptrs)
			delete i;
	}

	ptrs.clear();
	std::stack<Command*>().swap(result);

	return ret;
}
