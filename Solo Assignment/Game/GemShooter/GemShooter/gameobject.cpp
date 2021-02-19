#include "gameobject.h"
#include "backbuffer.h"
#include "sprite.h"

 gameobject::gameobject() 
	 : object_type(0)
	 , dynamite_breakable(0) 
{
	
}
 gameobject::~gameobject() {

}
bool gameobject::Initialise() {

	return (true);
}
void gameobject::Draw(BackBuffer& backBuffer) {

}

