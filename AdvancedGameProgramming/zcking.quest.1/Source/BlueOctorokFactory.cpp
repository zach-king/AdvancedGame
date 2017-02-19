#include "BlueOctorokFactory.h"
#include "BlueOctorok.h"

BlueOctorokFactory::BlueOctorokFactory()
{

}

BlueOctorokFactory::~BlueOctorokFactory()
{

}

std::unique_ptr<Object> BlueOctorokFactory::create()
{
	return (std::unique_ptr<Object>)(std::make_unique<BlueOctorok>());
}