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

	 if (this->GetVerticalVelocity() != 0) this->SetPositionY(this->GetPositionY() - GetVerticalVelocity());
	 if (this->GetHorizontalVelocity() != 0)
	 {
		 //left hand side of the screen aimline
		 if (this->GetAngle() < 0) this->SetPositionX(this->GetPositionX() - GetHorizontalVelocity());
		 //right hand side
		 else this->SetPositionX(this->GetPositionX() + GetHorizontalVelocity());
	 }
	 //if the moving gem hits one of the walls reflect
	 if (this->GetPositionX() <= 310 || this->GetPositionX() >= 1600)
	 {
		 this->SetHorizontalVelocity(-GetHorizontalVelocity());
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
	 GameObject::AimAngle(float angle) // if angle goes to low dont
 {
	 m_pSprite->SetAngle(m_pSprite->GetAngle() + angle);
	 if (m_pSprite->GetAngle() <= -75)
	 {
		 m_pSprite->SetAngle(-75);
	 }
	 if (m_pSprite->GetAngle() >= 75)
	 {
		 m_pSprite->SetAngle(75);
	 }
	
 }
 bool
	 GameObject::IsCollidingWith(float x, float y) // checks if the y and x values of both objects are within 60 pixels of each other if so they have hit each others sprite on screen
 {
	 if (this->GetPositionX() - x < 30 && this->GetPositionX() - x > - 30)
	 { 
		 if (this->GetPositionY() - y < 30 && this->GetPositionY() - y > -30)
		 {
			 return true;
		 }
	 }
	 
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
 float GameObject::GetAngle() const 
 {
	 return  m_pSprite->GetAngle();
 }
 float
	 GameObject::GetPosition() const
 {
	 return m_x , m_y;
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

