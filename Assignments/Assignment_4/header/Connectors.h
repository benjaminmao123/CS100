#pragma once

#include <string>
#include <vector>
#include <memory>

struct Connectors
{
	Connectors(std::string Type) : Type(Type)
	{

	}

	std::vector<std::shared_ptr<Connectors>> SubConnectorList;
	std::string Type;
};