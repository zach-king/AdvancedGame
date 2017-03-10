#include "BlueLeeverFactory.h"
#include "BlueLeever.h"

BlueLeeverFactory::BlueLeeverFactory()
{

}

BlueLeeverFactory::~BlueLeeverFactory()
{

}

std::unique_ptr<Object> BlueLeeverFactory::create()
{
	return (std::unique_ptr<Object>)(std::make_unique<BlueLeever>());
}