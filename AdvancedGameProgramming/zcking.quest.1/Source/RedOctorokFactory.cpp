#include "RedOctorokFactory.h"
#include "RedOctorok.h"

RedOctorokFactory::RedOctorokFactory()
{

}

RedOctorokFactory::~RedOctorokFactory()
{

}

std::unique_ptr<Object> RedOctorokFactory::create()
{
	return (std::unique_ptr<Object>)(std::make_unique<RedOctorok>());
}