#pragma once

#include "CommandBase.h"
#include "Connectors.h"

#include <utility>
#include <sstream>
#include <iostream>
#include <stack>

class Parser
{
public:
    Parser();
    Parser(std::string &Input);
    bool ParseInput(std::vector<std::string> &InputVec, std::vector<std::shared_ptr<Connectors>> &ConnectorList);
	std::vector<std::shared_ptr<Connectors>> ParseConnectors(unsigned int index, std::vector<std::shared_ptr<Connectors>> &ConnectorList);
    void SpaceInput();
    void SplitInput();
    bool ParseQuotations(std::string &TempInput, std::string &Input);
    void BalanceQuotations();
    bool BalanceOperators(std::vector<std::shared_ptr<Connectors>> &ConnectorList);
    bool CheckSyntax();
    void Clear(std::vector<std::string> &InputVec, std::vector<std::shared_ptr<Connectors>> &ConnectorList);
    void ParseComments();
    void ParseParentheses();
    bool isBalanced(std::string open, std::string close);
    
private:
    std::string Input;
    std::string SaveInput;
    std::vector<std::string> InputList;
    std::vector<unsigned int> SavePosition;
    std::vector<std::pair<unsigned int, unsigned int>> SaveQuotation;
	std::vector<unsigned int> IndexVector;
	std::vector<std::pair<unsigned int, unsigned int>> ParenthesesLocation;
	std::stack<std::string> ParenthesesStack;
};