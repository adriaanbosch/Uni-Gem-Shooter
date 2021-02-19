#include "shootGem.h"
#include <vector>

ShootGem::ShootGem()
{
	GameObject();
}
ShootGem::~ShootGem()
{
	
}
bool ShootGem::Initialise(Sprite* sprite)
{
	return GameObject::Initialise(sprite);
}

