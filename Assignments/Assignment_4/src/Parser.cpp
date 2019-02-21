#include "Parser.h"

Parser::Parser()
{

}

Parser::Parser(std::string &Input) : Input(Input)
{

}

/*
	This function parses the input passed in by the user.
	If input is empty, returns false.
	If an invalid input is entered at the beginning, returns false.
	This function is responsible for balancing, splitting, syntax checking, and spacing the input.
*/
bool Parser::ParseInput(std::vector<std::string> &InputVec, std::vector<std::shared_ptr<Connectors>> &ConnectorList)
{
	//check if input is empty and for invalid input
	if (Input.empty())
	{
		return false;
	}

	//check if user tries to input a connector as the first word
	if (Input[0] == ';' || Input[0] == '&' || Input[0] == '|')
	{
		if (Input.size() > 1)
		{
			std::cout << "Shell: syntax error near unexpected token `" << Input[0] << Input[1] << "'\n";
		}
		else
		{
			std::cout << "Shell: syntax error near unexpected token `" << Input[0] << "'\n";
		}
		return false;
	}

	//clear vector and queue
	Clear(InputVec, ConnectorList);

	bool Ret = true;
	auto index = 0U;
	
	//parse input
	ParseComments();
	BalanceQuotations();
	SpaceInput();
	SplitInput();
	ParseConnectors(index, ConnectorList);
	Ret = BalanceOperators(ConnectorList);
	ParseParentheses();
	InputVec.swap(InputList);
	
	return InputVec.empty() ? false : Ret; 
}

/*
	This function spaces the input.
	Input is spaced based on connectors.
	Iterates to the location of the connector and adds a space depending on 
	if it is under quotations or not.
*/
void Parser::SpaceInput()
{
	//save quotation index
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if (Input[i] == '\"')
		{
			for (auto j = i + 1; j < Input.size(); ++j)
			{
				if (Input[j] == '\"')
				{
					SaveQuotation.emplace_back(i, j);
					i = j + 1;
					break;
				}
			}
		}
	}

	auto j = 0U;
	//adds spaces to connectors
	for (auto i = 0U; i < Input.size(); ++i)
	{
		//check if connectors are in between two quotations
		//if they are do not add a space
		switch (Input[i])
		{
		case ';':
			if (!SaveQuotation.empty() && j < SaveQuotation.size())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					if (i > 0)
					{
						(Input[i - 1] != ' ') ? Input.insert(i, " ") : Input;
					}
					(Input[i + 1] != ' ') ? Input.insert(i + 1, " ") : Input;
					++i;
					++j;
				}
			}
			else
			{
				if (i > 0)
				{
					(Input[i - 1] != ' ') ? Input.insert(i, " ") : Input;
				}
				(Input[i + 1] != ' ') ? Input.insert(i + 1, " ") : Input;
				++i;
			}
			break;

		case '&':
			if (!SaveQuotation.empty() && j < SaveQuotation.size())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					if (i > 0)
					{
						(Input[i - 1] != ' ' && Input[i - 1] != '&') ? Input.insert(i, " ") : Input;
					}
					(Input[i + 1] != ' ' && Input[i + 1] != '&') ? Input.insert(i + 1, " ") : Input;
					++j;
					++i;
				}
			}
			else
			{
				if (i > 0)
				{
					(Input[i - 1] != ' ' && Input[i - 1] != '&') ? Input.insert(i, " ") : Input;
				}
				(Input[i + 1] != ' ' && Input[i + 1] != '&') ? Input.insert(i + 1, " ") : Input;
				++i;
			}
			break;

		case '|':
			if (!SaveQuotation.empty() && j < SaveQuotation.size())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					if (i > 0)
					{
						(Input[i - 1] != ' ' && Input[i - 1] != '|') ? Input.insert(i, " ") : Input;
					}
					(Input[i + 1] != ' ' && Input[i + 1] != '|') ? Input.insert(i + 1, " ") : Input;
					++i;
					++j;
				}
			}
			else
			{
				if (i > 0)
				{
					(Input[i - 1] != ' ' && Input[i - 1] != '|') ? Input.insert(i, " ") : Input;
				}
				(Input[i + 1] != ' ' && Input[i + 1] != '|') ? Input.insert(i + 1, " ") : Input;
				++i;
			}
			break;
			
		case '(':
			if (!SaveQuotation.empty() && j < SaveQuotation.size())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					if (i > 0)
					{
						(Input[i - 1] != ' ') ? Input.insert(i, " ") : Input;
					}
					(Input[i + 1] != ' ') ? Input.insert(i + 1, " ") : Input;
					++i;
					++j;
				}
			}
			else
			{
				if (i > 0)
				{
					(Input[i - 1] != ' ') ? Input.insert(i, " ") : Input;
				}
				(Input[i + 1] != ' ') ? Input.insert(i + 1, " ") : Input;
				++i;
			}
			break;

		case ')':
			if (!SaveQuotation.empty() && j < SaveQuotation.size())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					if (i > 0)
					{
						(Input[i - 1] != ' ') ? Input.insert(i, " ") : Input;
					}
					(Input[i + 1] != ' ') ? Input.insert(i + 1, " ") : Input;
					++i;
					++j;
				}
			}
			else
			{
				if (i > 0)
				{
					(Input[i - 1] != ' ') ? Input.insert(i, " ") : Input;
				}
				(Input[i + 1] != ' ') ? Input.insert(i + 1, " ") : Input;
				++i;
			}
			break;

		case '<':
			if (!SaveQuotation.empty() && j < SaveQuotation.size())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					if (i > 0)
					{
						(Input[i - 1] != ' ' && Input[i - 1] != '<') ? Input.insert(i, " ") : Input;
					}
					(Input[i + 1] != ' ' && Input[i + 1] != '<') ? Input.insert(i + 1, " ") : Input;
					++i;
					++j;
				}
			}
			else
			{
				if (i > 0)
				{
					(Input[i - 1] != ' ' && Input[i - 1] != '<') ? Input.insert(i, " ") : Input;
				}
				(Input[i + 1] != ' ' && Input[i + 1] != '<') ? Input.insert(i + 1, " ") : Input;
				++i;
			}
			break;
			
		case '>':
			if (!SaveQuotation.empty() && j < SaveQuotation.size())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					if (i > 0)
					{
						(Input[i - 1] != ' ' && Input[i - 1] != '>') ? Input.insert(i, " ") : Input;
					}
					(Input[i + 1] != ' ' && Input[i + 1] != '>') ? Input.insert(i + 1, " ") : Input;
					++i;
					++j;
				}
			}
			else
			{
				if (i > 0)
				{
					(Input[i - 1] != ' ' && Input[i - 1] != '>') ? Input.insert(i, " ") : Input;
				}
				(Input[i + 1] != ' ' && Input[i + 1] != '>') ? Input.insert(i + 1, " ") : Input;
				++i;
			}
			break;			

		default:
			break;
		}
	}
}

/*
	Iterates through string and parses the connectors.
	If a connector is found between two quotations it will not be counted.
	Connectors will be pushed into a queue of strings for tree building
*/
std::vector<std::shared_ptr<Connectors>> Parser::ParseConnectors(unsigned int index, std::vector<std::shared_ptr<Connectors>> &ConnectorList)
{
	std::shared_ptr<Connectors> Connector;

	for (auto i = index; i < InputList.size(); ++i)
	{
		index = i;

		if ((i + 1) < InputList.size())
		{
			if (!ParenthesesStack.empty())
			{
				if (InputList[i] == ")")
				{
					if (!ParenthesesStack.empty())
					{
						ParenthesesStack.pop();
					}

					IndexVector.emplace_back(i);
					break;
				}
				if (InputList[i + 1] != "(")
				{
					if (InputList[i] == ";")
					{
						Connector = std::make_shared<Connectors>(";");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == "&&")
					{
						Connector = std::make_shared<Connectors>("&&");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == "||")
					{
						Connector = std::make_shared<Connectors>("||");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == "|")
					{
						Connector = std::make_shared<Connectors>("|");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == "<")
					{
						Connector = std::make_shared<Connectors>("<");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == ">")
					{
						Connector = std::make_shared<Connectors>(">");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == ">>")
					{
						Connector = std::make_shared<Connectors>(">>");
						ConnectorList.emplace_back(Connector);
					}					
				}
				else if (InputList[i + 1] == "(")
				{
					if (InputList[i] == ";")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>(";");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "&&")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("&&");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "||")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("||");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "|")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("|");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "<")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("<");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == ">")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>(">");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == ">>")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>(">>");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}					
				}
			}
			else
			{
				if (InputList[i + 1] == "(")
				{
					if (InputList[i] == ";")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>(";");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "&&")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("&&");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "||")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("||");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "|")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("|");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == "<")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>("<");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == ">")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>(">");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}
					else if (InputList[i] == ">>")
					{
						ParenthesesStack.push("(");
						Connector = std::make_shared<Connectors>(">>");
						ParseConnectors(++index, Connector->SubConnectorList);
						ConnectorList.emplace_back(Connector);
						index = IndexVector.back();
					}					
				}
				else if (InputList[i + 1] != "(")
				{
					if (InputList[i] == ";")
					{
						Connector = std::make_shared<Connectors>(";");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == "&&")
					{
						Connector = std::make_shared<Connectors>("&&");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == "||")
					{
						Connector = std::make_shared<Connectors>("||");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == "|")
					{
						Connector = std::make_shared<Connectors>("|");
						ConnectorList.emplace_back(Connector);
					}			
					else if (InputList[i] == "<")
					{
						Connector = std::make_shared<Connectors>("<");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == ">")
					{
						Connector = std::make_shared<Connectors>(">");
						ConnectorList.emplace_back(Connector);
					}
					else if (InputList[i] == ">>")
					{
						Connector = std::make_shared<Connectors>(">>");
						ConnectorList.emplace_back(Connector);
					}					
				}
			}
		}
		else
		{
			if (InputList[i] == ")")
			{
				if (!ParenthesesStack.empty())
				{
					ParenthesesStack.pop();
				}

				IndexVector.emplace_back(i);
				break;
			}
			if (InputList[i] == ";")
			{
				Connector = std::make_shared<Connectors>(";");
				ConnectorList.emplace_back(Connector);
			}
			else if (InputList[i] == "&&")
			{
				Connector = std::make_shared<Connectors>("&&");
				ConnectorList.emplace_back(Connector);
			}
			else if (InputList[i] == "||")
			{
				Connector = std::make_shared<Connectors>("||");
				ConnectorList.emplace_back(Connector);
			}
			else if (InputList[i] == "|")
			{
				Connector = std::make_shared<Connectors>("|");
				ConnectorList.emplace_back(Connector);
			}
			else if (InputList[i] == "<")
			{
				Connector = std::make_shared<Connectors>("<");
				ConnectorList.emplace_back(Connector);
			}
			else if (InputList[i] == ">")
			{
				Connector = std::make_shared<Connectors>(">");
				ConnectorList.emplace_back(Connector);
			}
			else if (InputList[i] == ">>")
			{
				Connector = std::make_shared<Connectors>(">>");
				ConnectorList.emplace_back(Connector);
			}			
		}

		i = index;
	}

	return ConnectorList;
}
/*
	Tokenizes string. 
	Utilizes an std stringstream to split the input into tokens.
	The tokens will be pushed back into a vector of strings
*/
void Parser::SplitInput()
{
	std::istringstream iss(Input);
	std::string Token;
	//splits input into tokens which get pushed into string a vector
	while (iss >> Token)
	{
		InputList.emplace_back(Token);
	}
}

void Parser::ParseParentheses()
{
	for (auto i = 0U; i < InputList.size(); ++i)
	{
		if (InputList[i] == "(" || InputList[i] == ")")
		{
			InputList.erase(InputList.begin() + i);
			--i;
		}
	}
}

/*	
	Parses quotations in the string.
	If user inputs echo "a" it will print: a.
	If user inputs echo \"a\" it will remove the backslashes and output: "a".
*/
bool Parser::ParseQuotations(std::string &TempInput, std::string &Input)
{
	bool HasConnector = false;
	
	//saves the position of quotation marks that will be erased
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if (Input[i] == '\"')
		{
			if ((i > 0) && (Input[i - 1] != '\\'))
			{
				SavePosition.emplace_back(i);
			}
			else
			{
				SavePosition.emplace_back(i);
			}
		}
	}

	bool Saved = false;

	//saves the start and end range for quotation marks
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if (Input[i] == '\"')
		{
			for (auto j = i + 1; j < Input.size(); ++j)
			{
				if (Input[j] == '\"')
				{
					SaveQuotation.emplace_back(i, j);
					Saved = true;
					i = j + 1;
					break;
				}
				else
				{
					Saved = false;
				}
			}

			if (!Saved)
			{
				SaveQuotation.emplace_back(i, UINT16_MAX);
			}
		}
	}

	auto j = 0U;

	//check if connector is in between two quotation marks
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if ((Input[i] == '&') || (Input[i] == ';') || (Input[i] == '|'))
		{
			if (!SaveQuotation.empty())
			{
				if (!(i > SaveQuotation[j].first && i < SaveQuotation[j].second))
				{
					++j;
				}
				else
				{
					HasConnector = true;
				}
			}
		}
	}

	//erase quotation marks
	for (auto i = 0U; i < SavePosition.size(); ++i)
	{
		Input.erase(SavePosition[i], 1);
		if (i < SavePosition.size() - 1)
		{
			SavePosition[i + 1] = SavePosition[i + 1] - (1 + i);
		}
	}
	//erase backlashes
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if (Input[i] == '\\')
		{
			Input.erase(i, 1);
		}
	}
	
	//assign tempinput to input
	TempInput = Input;

	return HasConnector;
}

/*
	This function should balance quotations.
	It parses the input and if an uneven amount of quotations are entered,
	prompts the user for a closing quotation.
*/
void Parser::BalanceQuotations()
{
	//balances unclosed '"', '&&', and '||'
	int QuoteCount = 0;

	//count number of quotes in input
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if ((i > 0) && (Input[i] == '\"'))
		{
			if (Input[i - 1] != '\\')
			{
				++QuoteCount;
			}
		}
		else if (!i && Input[i] == '\"')
		{
			++QuoteCount;
		}
	}

	//check for even quote count
	while ((QuoteCount % 2))
	{
		std::cout << "> ";

		//if quote count is not even ask for input
		std::string temp;
		getline(std::cin, temp);

		for (auto i = 0U; i < temp.size(); ++i)
		{
			if (temp[i] == '"')
			{
				++QuoteCount;
			}
		}

		//add newline after input
		if (temp == "\"")
		{
			Input += temp;
		}
		else
		{
			Input += " " + temp;
		}
	}
}

/*
	Balances inputs if input is missing rhs value with connector.
	If rhs value is missing, prompts user for input, parses it, and adds it to the input vector
*/
bool Parser::BalanceOperators(std::vector<std::shared_ptr<Connectors>> &ConnectorList)
{
	//check for syntax errors
	if (!CheckSyntax())
	{
		return false;
	}
	
	std::string Temp;
	bool HasNext = false;

	//initiate loop if there is a next element in the vector else break out of loop
	while (!HasNext)
	{
		if (InputList.empty())
		{
			return false;
		}
		for (auto i = 0U; i < InputList.size(); ++i)
		{
			Parser parse;
			
			//parses string to check if connector is under quotations
			bool HasConnector = parse.ParseQuotations(Temp, InputList[i]);
			InputList[i] = Temp;

			if ((InputList[i] == "||" || InputList[i] == "&&") && !HasConnector)
			{
				//if i + 1 >= InputList.size() there is no next element to be parsed
				if ((i + 1) >= InputList.size())
				{
					HasNext = false;
				}
				else
				{
					HasNext = true;
				}
			}
			else
			{
				HasNext = true;
			}
		}
		
		//continue parsing if a next element exists
		if (!HasNext)
		{
			//prompt the user to enter the rhs element
			std::cout << "> ";
			getline(std::cin, Input);
			
			//parse the input for comments
			ParseComments();
			
			//check if there are quotations that need to be balanced
			BalanceQuotations();
			
			//space the connectors
			SpaceInput();
			
			//parse connectors
			auto index = 0U;
			ParseConnectors(index, ConnectorList);
			
			//split the token and place them into the input vector
			std::istringstream iss(Input);
			std::string Token;
			while (iss >> Token)
			{
				InputList.emplace_back(Token);
			}
			
			//do a final syntax check after everything has been pushed into vector
			if (!CheckSyntax())
			{
				return false;
			}
		}
	}
	
	return true;
}

/*
	Iterates through the InputList vector and checks if there are any invalid inputs
*/
bool Parser::CheckSyntax()
{
	for (auto i = 0U; i < InputList.size(); ++i)
	{
		if (i >= InputList.size() - 1)
		{
			break;
		}
		if (InputList[i] == ";" || InputList[i] == "||" || InputList[i] == "&&")
		{
			if (InputList[i + 1] == ";" || InputList[i + 1] == "||" || InputList[i + 1] == "&&")
			{
				std::cout << "Shell: syntax error near unexpected token `" << InputList[i + 1] << "'\n";
				return false;
			}
			else if (i > 0)
			{
				if (InputList[i - 1] == ";" || InputList[i - 1] == "||" || InputList[i - 1] == "&&")
				{
					std::cout << "Shell: syntax error near unexpected token `" << InputList[i] << "'\n";
					return false;
				}
			}
		}
	}
	
	if (!isBalanced("(", ")") || !isBalanced("[", "]"))
	{
		std::cout << "Shell: syntax error: unbalanced grouping operators\n";
		return false;
	}

	return true;
}

/* 
	Clears the containers used to store input to discard input from previous iteration
*/
void Parser::Clear(std::vector<std::string> &InputVec, std::vector<std::shared_ptr<Connectors>> &ConnectorList)
{
	InputList.clear();
	SavePosition.clear();
	SaveQuotation.clear();
	IndexVector.clear();
	InputVec.clear();
	ConnectorList.clear();
	if (!ParenthesesStack.empty())
	{
		std::stack<std::string>().swap(ParenthesesStack);
	}
}

/*
	Checks if input contains comments.
	If input contains comments, erases the current value the iterator is on and
	erases the rest of the line from starting from that position.
*/
void Parser::ParseComments()
{
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if (Input[i] == '(')
		{
			for (auto j = i; j < Input.size(); ++j)
			{
				if (Input[j] == ')')
				{
					ParenthesesLocation.emplace_back(std::make_pair(i, j));
				}
			}
		}
	}
	
	for (auto i = 0U; i < Input.size(); ++i)
	{
		if (Input[i] == '#')
		{
			if (i > 0)
			{
				if (!ParenthesesLocation.empty())
				{
					for (auto j = 0U; j < ParenthesesLocation.size(); ++j)
					{
						if (!(i >= ParenthesesLocation[j].first && i <= ParenthesesLocation[j].second))
						{
							Input.erase(Input.begin() + i, Input.end());
							break;
						}
						else
						{
							Input.erase(Input.begin() + i, Input.begin() + ParenthesesLocation[j].second);
							break;
						}
					}
				}
			}
			else
			{
				Input.erase(0, 1);
			}
			break;
		}
	}
}

bool Parser::isBalanced(std::string open, std::string close)
{
	std::stack<std::string> openstack;
	std::stack<std::string> closestack;

	for (auto i = 0U; i < InputList.size(); ++i)
	{
		for (auto j = 0U; j < InputList[i].size(); ++j)
		{
			if (InputList[i] == open)
			{
				openstack.push(open);
			}
			else if (InputList[i] == close)
			{
				closestack.push(close);
			}
		}
	}

	if (openstack.size() != closestack.size())
	{
		return false;
	}

	return true;
}
