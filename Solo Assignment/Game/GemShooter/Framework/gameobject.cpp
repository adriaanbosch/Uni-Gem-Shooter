// COMP710 GP 2D Framework 2020 entity altered
#include "gameobject.h"
#include "backbuffer.h"
#include "sprite.h"
// Library includes:
#include <cassert>

GameObject::GameObject()
	 : object_type(0)
	 , dynamite_breakable(0)
	, m_pSprite(0)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_velocityX(0.0f)
	, m_velocityY(0.0f)
	, m_dead(false)
{
	
}
 GameObject::~GameObject() {

}
 bool
	 GameObject::Initialise(Sprite* sprite)
 {
	 assert(sprite);
	 m_pSprite = sprite;

	 return (true);
 }

 void
	 GameObject::Process(float deltaTime)
 {

	 if (this->GetVerticalVelocity() != 0)
	 {

		 this->SetPositionY(this->GetPositionY() - GetVerticalVelocity());
	 }
	 if (this->GetHorizontalVelocity() != 0)
	 {

		 this->SetPositionY(this->GetPositionX() - GetHorizontalVelocity());
	 }
	 if (this->m_pSprite->GetAngle() != 0)
	 {
		 this->m_pSprite->SetAngle(this->m_pSprite->GetAngle());
	 }
 }


 void
	 GameObject::Draw(BackBuffer& backBuffer)
 {
	 assert(m_pSprite);
	 m_pSprite->SetX(static_cast<int>(m_x));
	 m_pSprite->SetY(static_cast<int>(m_y));
	 m_pSprite->Draw(backBuffer);
 }
 void 
	 GameObject::AimAngle(int angle) 
 {
	 this->m_pSprite->SetAngle(angle);
 }
 bool
	 GameObject::IsCollidingWith(GameObject& e)
 {
	 // SS04.6: Generic Entity Collision routine.

	 // SS04.6: Does this object collide with the e object?
	 // SS04.6: Create a circle for each entity (this and e).

	 // SS04.6: Check for intersection.
	 // SS04.6: Using circle-vs-circle collision detection.

	 // SS04.6: Return result of collision.

	 return (false); // SS04.6 Change return value!
 }

 void
	 GameObject::SetDead(bool dead)
 {
	 m_dead = dead;
 }

 void
	 GameObject::SetPosition(float x, float y)
 {
	 m_x = x;
	 m_y = y;
 }

 void
	 GameObject::SetPositionX(float x)
 {
	 m_x = x;
 }

 void
	 GameObject::SetPositionY(float y)
 {
	 m_y = y;
 }

 float
	 GameObject::GetPositionX() const
 {
	 return (m_x);
 }

 float
	 GameObject::GetPositionY() const
 {
	 return (m_y);
 }

 float
	 GameObject::GetHorizontalVelocity() const
 {
	 return (m_velocityX);
 }

 float
	 GameObject::GetVerticalVelocity() const
 {
	 return (m_velocityY);
 }

 void
	 GameObject::SetHorizontalVelocity(float x)
 {
	 m_velocityX = x;
 }

 void
	 GameObject::SetVerticalVelocity(float y)
 {
	 m_velocityY = y;
 }

