#include <stack>

#include "../header/ParserLibrary.h"
#include "../header/Connector.h"
#include "../header/Command.h"
#include "../header/Test.h"
#include "../header/Parenthesis.h"
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
                case Token::TokenType::CHANGE_DIRECTORY:
                case Token::TokenType::TEST:
                    cmd = Token::Create(cmdType);

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
            case Token::TokenType::TEST:
            case Token::TokenType::CHANGE_DIRECTORY:
                args.emplace_back(s);
                break;
            case Token::TokenType::SEMICOLON:
            case Token::TokenType::AND:
            case Token::TokenType::OR:
            case Token::TokenType::PIPE:
            case Token::TokenType::INPUT_REDIRECTION:
            case Token::TokenType::OUTPUT_REDIRECTION:
            case Token::TokenType::OUTPUT_APPEND:
                createCommand();
                result.emplace_back(Token::Create(tokenType));
                break;
            case Token::TokenType::EXIT:
            case Token::TokenType::LEFT_PARENTHESIS:
            case Token::TokenType::LEFT_LEGACY_TEST:
                result.emplace_back(Token::Create(tokenType));
                break;
            case Token::TokenType::RIGHT_PARENTHESIS:
                createCommand();
                result.emplace_back(Token::Create(tokenType));
                break;
            case Token::TokenType::RIGHT_LEGACY_TEST:
                if (!args.empty())
                {
                    Command* cmd = Token::Create(Token::TokenType::TEST);

                    if (cmd)
                    {
                        cmd->SetArgs(args);
                        result.emplace_back(cmd);
                    }

                    args.clear();
                }

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
                    case Token::TokenType::TEST:
                    case Token::TokenType::CHANGE_DIRECTORY:
                        postfix.emplace_back(t);
                        state = ShuntingState::EXPECT_CONNECTOR;
                        break;
                    case Token::TokenType::CONNECTOR:
                    case Token::TokenType::SEMICOLON:
                    case Token::TokenType::AND:
                    case Token::TokenType::OR:
                    case Token::TokenType::PIPE:
                    case Token::TokenType::INPUT_REDIRECTION:
                    case Token::TokenType::OUTPUT_REDIRECTION:
                    case Token::TokenType::OUTPUT_APPEND:                                
                        return onError(ErrorLibrary::ErrorState::EXPECT_COMMAND);
                    case Token::TokenType::LEFT_LEGACY_TEST:
                    case Token::TokenType::LEFT_PARENTHESIS:
                        operators.push(t);
                        break;
                    case Token::TokenType::RIGHT_LEGACY_TEST:
                    case Token::TokenType::RIGHT_PARENTHESIS:
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
                    case Token::TokenType::TEST:
                    case Token::TokenType::LEFT_LEGACY_TEST:
                    case Token::TokenType::LEFT_PARENTHESIS:
                    case Token::TokenType::CHANGE_DIRECTORY:
                        return onError(ErrorLibrary::ErrorState::EXPECT_CONNECTOR);
                    case Token::TokenType::CONNECTOR:
                    case Token::TokenType::SEMICOLON:
                    case Token::TokenType::AND:
                    case Token::TokenType::OR:
                    case Token::TokenType::PIPE:
                    case Token::TokenType::INPUT_REDIRECTION:
                    case Token::TokenType::OUTPUT_REDIRECTION:
                    case Token::TokenType::OUTPUT_APPEND:                    
                        while (!operators.empty() &&
                            operators.top()->Type() != Token::TokenType::LEFT_PARENTHESIS)
                        {
                            postfix.emplace_back(operators.top());
                            operators.pop();
                        }

                        operators.push(t);
                        state = ShuntingState::EXPECT_COMMAND;
                        break;
                    case Token::TokenType::RIGHT_LEGACY_TEST:
                        while (!operators.empty() &&
                            operators.top()->Type() != Token::TokenType::LEFT_LEGACY_TEST)
                        {
                            postfix.emplace_back(operators.top());
                            operators.pop();
                        }

                        if (!operators.empty() &&
                            operators.top()->Type() == Token::TokenType::LEFT_LEGACY_TEST)
                        {
                            toDelete.emplace_back(operators.top());
                            operators.pop();
                        }

                        toDelete.emplace_back(t);
                        state = ShuntingState::EXPECT_CONNECTOR;
                        break;
                    case Token::TokenType::RIGHT_PARENTHESIS:
                        while (!operators.empty() &&
                            operators.top()->Type() != Token::TokenType::LEFT_PARENTHESIS)
                        {
                            postfix.emplace_back(operators.top());
                            operators.pop();
                        }

                        if (!operators.empty() &&
                            operators.top()->Type() == Token::TokenType::LEFT_PARENTHESIS)
                        {
                            toDelete.emplace_back(operators.top());
                            operators.pop();
                        }

                        toDelete.emplace_back(t);
                        state = ShuntingState::EXPECT_CONNECTOR;
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
            switch (operators.top()->Type())
            {
            case Token::TokenType::LEFT_PARENTHESIS:
            case Token::TokenType::RIGHT_PARENTHESIS:
            case Token::TokenType::LEFT_LEGACY_TEST:
            case Token::TokenType::RIGHT_LEGACY_TEST:
                return onError(ErrorLibrary::ErrorState::EXPECT_PARENTHESIS);
            default:
                break;
            }

            postfix.emplace_back(operators.top());
            operators.pop();
        }

        for (const auto& i : toDelete)
            delete i;

	return postfix;
    }
}
