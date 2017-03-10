#include "RedLeeverFactory.h"
#include "RedLeever.h"

RedLeeverFactory::RedLeeverFactory()
{

}

RedLeeverFactory::~RedLeeverFactory()
{

}

std::unique_ptr<Object> RedLeeverFactory::create()
{
	return (std::unique_ptr<Object>)(std::make_unique<RedLeever>());
}