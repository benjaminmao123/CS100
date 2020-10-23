#include <stack>

#include "../header/ParserLibrary.h"
#include "../header/Connector.h"
#include "../header/Command.h"
#include "../header/ErrorLibrary.h"

namespace ParserLibrary
{
    std::vector<std::string> Tokenize(const std::string& input)
    {
        std::istringstream iss(input);
        
        std::string token;
        std::vector<std::string> tokens;
        
        while (iss >> token)
            tokens.emplace_back(token);
            
        return tokens;
    }    
    
    std::vector<Command*> Tokenize(const std::vector<std::string>& input)
    {
        std::vector<Command*> result;
        std::vector<std::string> args;
        
        auto createCommand = [&]()
        {
            if (!args.empty())
            {
                Token::TokenType cmdType = Token::GetEnum(args.front());
                Command* cmd = nullptr;

                switch (cmdType)
                {
                case Token::TokenType::NONE:
                    cmd = Token::Create(Token::TokenType::COMMAND);

                    if (cmd)
                    {
                        cmd->SetArgs(args);
                        result.emplace_back(cmd);
                    }
                    break;
                default:
                    break;
                }

                args.clear();
            }
        };

        for (const auto& s : input)
        {
            Token::TokenType tokenType = Token::GetEnum(s);

            switch (tokenType)
            {
            case Token::TokenType::NONE:
                args.emplace_back(s);
                break;
            case Token::TokenType::SEMICOLON:
            case Token::TokenType::AND:
            case Token::TokenType::OR:
                createCommand();
                result.emplace_back(Token::Create(tokenType));
                break;
            case Token::TokenType::EXIT:
                result.emplace_back(Token::Create(tokenType));
                break;
            default:
                break;
            }
        }

        createCommand();
        
        return result;
    }
    
    std::string ParseComment(const std::string& input, const std::string& comment)
    {
        std::string result = input;
        
        std::size_t first = result.find(comment);
        std::size_t last = result.find_last_of(comment);
        
        if (!last)
            ++last;
        
        if (first != std::string::npos)
            result.erase(result.begin() + first, result.end());
        
        return result;
    }

    std::vector<Command*> GeneratePostfix(std::vector<Command*>& infix)
    {
		ShuntingState state = ShuntingState::EXPECT_COMMAND;
		ErrorLibrary::state = ErrorLibrary::ErrorState::NONE;

        auto onError = [&](ErrorLibrary::ErrorState state)
        {
            ErrorLibrary::state = state;

            for (const auto& i : infix)
                delete i;

            return std::vector<Command*>();
        };

		std::stack<Command*> operators;
		std::vector<Command*> postfix;
        std::vector<Command*> toDelete;

        for (auto& t : infix)
        {
            if (t)
            {
                switch (state)
                {
                case ShuntingState::EXPECT_COMMAND:
                {
                    switch (t->Type())
                    {
                    case Token::TokenType::COMMAND:
                    case Token::TokenType::EXIT:
                        postfix.emplace_back(t);
                        state = ShuntingState::EXPECT_CONNECTOR;
                        break;
                    case Token::TokenType::CONNECTOR:
                    case Token::TokenType::SEMICOLON:
                    case Token::TokenType::AND:
                    case Token::TokenType::OR:
                        return onError(ErrorLibrary::ErrorState::EXPECT_COMMAND);
                    default:
                        break;
                    }
                }
                break;
                case ShuntingState::EXPECT_CONNECTOR:
                {
                    switch (t->Type())
                    {
                    case Token::TokenType::COMMAND:
                    case Token::TokenType::EXIT:
                        return onError(ErrorLibrary::ErrorState::EXPECT_CONNECTOR);
                    case Token::TokenType::CONNECTOR:
                    case Token::TokenType::SEMICOLON:
                    case Token::TokenType::AND:
                    case Token::TokenType::OR:
                        while (!operators.empty())
                        {
                            postfix.emplace_back(operators.top());
                            operators.pop();
                        }

                        operators.push(t);
                        state = ShuntingState::EXPECT_COMMAND;
                        break;
                    default:
                        break;
                    }
                }
                break;
                default:
                    break;
                }
            }
        }

        if (state == ShuntingState::EXPECT_COMMAND)
            return onError(ErrorLibrary::ErrorState::EXPECT_COMMAND);

        while (!operators.empty())
        {
            postfix.emplace_back(operators.top());
            operators.pop();
        }

        for (const auto& i : toDelete)
            delete i;

		return postfix;
    }
}