// COMP710 GP 2D Framework 2020

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "gameobject.h"
#include "gem.h"



// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
// Static Members:
Game* Game::sm_pInstance = 0;
Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}
void Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}
Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_pSprite(0)
	, pSprite(0)
	, wallSprite1(0)
	, wallSprite2(0)
	, wallPlate1(0)
	, wallPlate2(0)
	, deadZone(0)
	, roof(0)
	, object1(0)
	, objectlist(0)
	, gem(0)
	, aimLine(0)
	, shootingGem(0)
	, movingGem(0)
	, swapGem(0)
	, currentGem(0)
	, nextGem(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
	, movingGemBool(0)
	, roofCount(0)
	, rock1(0)
	, rock2(0)
	, rock3(0)
	, rock4(0)
	, onStartup(true)
	, menu(true)
	, logo(0)
	, button1(0)
	, button2(0)
	, buttonSelect(0)
	, isPaused(false)
	, gameActive(false)
{
	std::vector<Gem*> objectlist();
	std::vector<float> hexGridX; // had to much trouble creating a 2D vector
	//std::vector<float> hexGridY;
}
Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

void Game::SplashScreen(BackBuffer& backBuffer) {
	if (onStartup == true)
	{
		onStartup = false;
		logo = new Sprite();
		logo = m_pBackBuffer->CreateSprite("AUTlogo.png");
		logo->Draw(*m_pBackBuffer);
		backBuffer.Present();
		SDL_Delay(3000);
		backBuffer.Clear();
		backBuffer.Present();
	}
	
}
void Game::MainMenu(BackBuffer& backBuffer) {
	
	if (menu == true)
	{
		if (buttonSelect == NULL)
		{
			buttonSelect = new Sprite();
			buttonSelect = m_pBackBuffer->CreateSprite("ButtonSelect.png");
			buttonSelect->SetX(290); buttonSelect->SetY(600);
		}
		button1 = new Sprite();
		button1 = m_pBackBuffer->CreateSprite("Button1.png");
		button2 = new Sprite();
		button2 = m_pBackBuffer->CreateSprite("Button2.png"); // reusing 
		button1->SetX(300); button1->SetY(500);
		button2->SetX(300); button2->SetY(800);
		button1->Draw(*m_pBackBuffer);
		button2->Draw(*m_pBackBuffer);
		buttonSelect->Draw(*m_pBackBuffer);
	}
	
}
void Game::PauseMenu(BackBuffer& backBuffer) {
	
	if (isPaused == true)
	{

		button1 = new Sprite();
		button1 = m_pBackBuffer->CreateSprite("Button1.png");
		button2 = new Sprite();
		button2 = m_pBackBuffer->CreateSprite("Button2.png");
		button1->SetX(300); button1->SetY(500);
		button2->SetX(300); button2->SetY(800);
		button1->Draw(*m_pBackBuffer);
		button2->Draw(*m_pBackBuffer);
		buttonSelect->Draw(*m_pBackBuffer);
	}
}
void Game::MenuInput(int input) { // 1 up, 2 down , 3 enter
		switch (input)
		{
		case 1:
			buttonSelect->SetX(290); buttonSelect->SetY(600); // new game
			
			break;
		case 2:
			buttonSelect->SetX(290); buttonSelect->SetY(900); // exit
			break;
		case 3:
			if (buttonSelect->GetY() == 600) //enter on new game
			{
				gameActive = true;
				menu = false;
			}
			else 
			{
				Quit(); //enter on quit
			}
			break;
		case 4:
			if (menu == false) //brings up pause menu
			{
				if (gameActive == true)
				{
					isPaused = !isPaused;
					buttonSelect->SetX(290); buttonSelect->SetY(600);
				}
			}
			break;
		default:
			break;
		}
		
}
bool Game::Initialise()
{
	const int width = 1920;
	const int height = 1080;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	m_pBackBuffer->SetClearColour(64, 58, 58);
	GameSprites();

	
	return (true);
}
void Game::GameSprites() { // creates all the still sprites for the game
	wallSprite1, wallSprite2, wallPlate1, wallPlate2, deadZone, roof = new Sprite();
	wallSprite1 = m_pBackBuffer->CreateSprite("wall.png");
	wallSprite2 = m_pBackBuffer->CreateSprite("wall.png");
	wallPlate1 = m_pBackBuffer->CreateSprite("wallplate.png");
	wallPlate2 = m_pBackBuffer->CreateSprite("wallplate.png");
	deadZone = m_pBackBuffer->CreateSprite("deadzone.png");
	roof = m_pBackBuffer->CreateSprite("roof.png");

	roof->SetX(325);
	wallSprite1->SetX(0); wallSprite2->SetX(1620);
	wallPlate1->SetX(300); wallPlate2->SetX(1610);
	deadZone->SetX(320); deadZone->SetY(950);
	HexGrid();
	GameObjectListed();
	GameObjectShootingGems();
}
void Game::HexGrid() { // this list will hold the fixed grid positions which gems will be placed and where gems can land

	//hexGrid(r, std::vector<int>(c, 0));
	int r = 1; //row
	int c = 1; //column
	int d = 0; 
	float w = 320; 
	float h = 70;
	int i = 0;
	while (r <= 60) //rows
	{
		while (c <= 14) // columns
		{
			//hexGrid

			hexGridX.push_back(w + d);
			hexGridX.push_back(h);
			//hexGrid.push_back(hexGridX);
			//hexGrid.push_back(hexGridY);
			c++;
			w = w + 90;
			i++;
		}
		//hexGrid.push_back(hexGridX);
		if (c = 14) {
			r++;
			c = 1;
			h = h + 25;
			w = 320;
			if (r % 2 == 0) d = 45;
			else d = 0;
		}
	}
	
}
void Game::GameObjectShootingGems() { 
	//make aim line here
	aimLine = new GameObject();
	pSprite = new Sprite();
	pSprite = m_pBackBuffer->CreateSprite("aimline.png");
	pSprite->SetCenter(2.5, 1040);
	aimLine->Initialise(pSprite);
	aimLine->SetPositionY(40);
	aimLine->SetPositionX(960);
	
	//make the two objects

		currentGem = new Gem();
		pSprite = new Sprite();
		pSprite = m_pBackBuffer->CreateSprite(currentGem->GemRandom());
		currentGem->Initialise(pSprite);
		movingGem = new Gem();
		movingGem = currentGem;
		nextGem = new Gem();
		pSprite = new Sprite();
		pSprite = m_pBackBuffer->CreateSprite(nextGem->GemRandom());
		nextGem->Initialise(pSprite);


		currentGem->SetPosition(931, 1000);
		nextGem->SetPosition(1031, 1000);
}
void Game::GemShot() { // will deal with shooting gems, and the list
	if (movingGemBool == false)
	{
		movingGem = currentGem;
		movingGem->Draw(*m_pBackBuffer);
		movingGem->SetHorizontalVelocity(CalcAngleVel());
		movingGem->SetVerticalVelocity(2);
		movingGemBool = true;

		currentGem = nextGem;
		currentGem->SetPosition(931, 1000);
		nextGem = new Gem();
		pSprite = new Sprite();
		pSprite = m_pBackBuffer->CreateSprite(nextGem->GemRandom());
		nextGem->Initialise(pSprite);
		nextGem->SetPosition(1031, 1000);
		nextGem->Draw(*m_pBackBuffer);
	}
}
void Game::PlayerLoss(int i) { // checks if a gem in objectlist is touching the deadzone
	if (objectlist[i]->GetPositionY() >= 950)
	{
		menu = true;
		gameActive = false;
	}
}
void Game::RoofLower() {
	if (roofCount >= 3)
	{
		roof->SetY(roof->GetY() + 50);
		roofCount = 0;
		ForListLoop(5, 0);// loops to move gem locations down 60 pixels
		rock1, rock2, rock3, rock4 = new Sprite();
		rock1 = m_pBackBuffer->CreateSprite("rock.png"); rock2 = m_pBackBuffer->CreateSprite("rock.png"); rock3 = m_pBackBuffer->CreateSprite("rock.png"); rock4 = m_pBackBuffer->CreateSprite("rock.png");
		rock1->SetX(420); rock1->SetY(20); rock2->SetX(1100); rock2->SetY(10); rock3->SetX(850); rock3->SetY(40); rock4->SetX(1520); rock4->SetY(90);
	}
}
void Game::GemLower(int i) {
	
 		objectlist[i]->SetPositionY(objectlist[i]->GetPositionY() + 50);
}
float Game::CalcAngleVel() // this method will calculate how much y velocity the movingGem should have
{
	if (aimLine->GetAngle() == 0)
	{
		return 0;
	}
	else 
	{
		double vel = 0;
		double b = 10;
		double aimAngle = static_cast<double>(aimLine->GetAngle());
		if (aimAngle > 0)
		{
			vel = b / cos(aimAngle);
			vel = sqrt((vel * vel) - (b * b));
			vel = vel / 10;
			return vel;
		}
		else 
		{
			aimAngle = fabs(aimAngle); // makes the number positive for calc
			vel = b / cos(aimAngle);
			vel = sqrt((vel * vel) - (b * b));
			vel = vel / 10;
			return static_cast<float>(-vel);
		}
	}
}
void Game::Aim(int angle) 
{
	if (angle == 1) aimLine->AimAngle(-1);
	if (angle == 2) aimLine->AimAngle(1);
}
void Game::SwitchGems() { //allows the user to switch between the current and next gem to shoot
	swapGem = currentGem;
	currentGem = nextGem;
	nextGem = swapGem;
	nextGem->SetPosition(1031, 1000);
	currentGem->SetPosition(931, 1000);
	movingGem = currentGem;
	swapGem = NULL;
}
void Game::GameObjectListed() { // this method creates gems, places them in a list based on hexgrid x & y
	int i = 0;
	while (objectlist.size() < 112)
	{
		gem = new Gem();
		pSprite = new Sprite();
		pSprite = m_pBackBuffer->CreateSprite(gem->GemRandom()); // assigns a random gem colour
		pSprite->SetCenter(30, 30);
		gem->Initialise(pSprite);
		gem->SetPosition(hexGridX[i], hexGridX[i+1]);
		objectlist.push_back(gem);
		i++; i++;
	}
}
void Game::EmptySpot() {
	movingGem->SetHorizontalVelocity(0);
	movingGem->SetVerticalVelocity(0);
	//this loop will clone hexGrid and remove all object filled positions from it, leaving only free spots for the movinggem to be placed.
	std::vector<float> emptyspots(hexGridX);
	int xy = 0;
	for (int x = 0; x < objectlist.size(); x++)
	{
		if (objectlist[x]->GetPosition() == emptyspots[xy], emptyspots[xy + 1])
		{
			emptyspots.erase(emptyspots.begin() + xy);
			emptyspots.erase(emptyspots.begin() + xy);
		}
		else 
		{
			xy++; xy++;
		}
	}
	for (int z = 0; z < emptyspots.size();)
	{
		if ((movingGem->GetPositionX() - emptyspots[z]) < 45 && (movingGem->GetPositionX() - emptyspots[z]) > - 45)
		{
			if ((movingGem->GetPositionY() - emptyspots[z + 1]) < 45 && (movingGem->GetPositionY() - emptyspots[z + 1]) > -45)
			{
				movingGem->SetPosition(emptyspots[z], emptyspots[z + 1]);
			}
		}
		z++; z++;
	}
}
void Game::CheckCollision(int i) 
{ // this function will check if shooting object position collides with the gem list
	bool removeShot = false;
	bool removeGem = false;
	if (movingGemBool == true)
	{
		if (movingGem->IsCollidingWith(objectlist[i]->GetPositionX(), objectlist[i]->GetPositionY()) == true)
		{
			EmptySpot();
			if (movingGem->IsSameColour(objectlist[i]->GetGemColour()) == true)
			{
				movingGem->SetPosition(-60, -60);//hides offscreen // animation here
				removeShot = true;
				removeGem = true;
				movingGemBool = false;
			}
			else
			{
				gem = new Gem();
				gem = movingGem;
				objectlist.push_back(gem);
				gem->Draw(*m_pBackBuffer);
				movingGemBool = false;
				roofCount++;
			}
		}
		if (removeGem == true)
		{
			/*for (int x = 0; x < objectlist.size(); x++)
			{
				if (objectlist[i]->IsCollidingWith(objectlist[x]->GetPositionX(), objectlist[x]->GetPositionY()) == true)
				{
					if (objectlist[i]->IsSameColour(objectlist[x]->GetGemColour()) == true)
					{
						objectlist.erase(objectlist.begin() + x);
					}
				}
			}*/
			objectlist.erase(objectlist.begin() + i); //remove gems hit
		}
	}
}
void Game::ForListLoop(int switchNumber, float deltaTimeCopy) { // this function saves the need for multiple for loops for this list everywhere
	for (int i = 0; i < objectlist.size(); i++) {
		
		switch (switchNumber)
		{
		case 1: //draw list
			objectlist[i]->Draw(*m_pBackBuffer);
			break;
		case 2: //process list
			objectlist[i]->Process(deltaTimeCopy);
			break;
		case 3: //collision check of objects
			CheckCollision(i);
			break;
		case 4:
			PlayerLoss(i);
			break;
		case 5: 
			GemLower(i);
			break;
		default:
			break;
		}
	}
	
	
}
void Game::GameActive(BackBuffer& backBuffer) {
	if (gameActive == true)
	{
		backBuffer.Clear();
		deadZone->Draw(*m_pBackBuffer); aimLine->Draw(*m_pBackBuffer); wallSprite1->Draw(*m_pBackBuffer); wallSprite2->Draw(*m_pBackBuffer);
		wallPlate1->Draw(*m_pBackBuffer); wallPlate2->Draw(*m_pBackBuffer); roof->Draw(*m_pBackBuffer);
		movingGem->Draw(*m_pBackBuffer); currentGem->Draw(*m_pBackBuffer); nextGem->Draw(*m_pBackBuffer);
		ForListLoop(1, 0);
		if (rock1 != NULL)
		{
			rock1->Draw(*m_pBackBuffer); rock2->Draw(*m_pBackBuffer); rock3->Draw(*m_pBackBuffer); rock4->Draw(*m_pBackBuffer);
		}
	}
}
bool Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		float deltaTime = (current - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_lastTime = current;

		m_executionTime += deltaTime;

		Process(deltaTime);

		m_lag += deltaTime;

		int innerLag = 0;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
			++innerLag;
		}


		Draw(*m_pBackBuffer);
	}

	return (m_looping);
}
void Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}
	m_pSprite->Process(deltaTime);
	aimLine->Process(deltaTime);
	movingGem->Process(deltaTime);
	currentGem->Process(deltaTime);
	nextGem->Process(deltaTime);
	ForListLoop(2, deltaTime);
	ForListLoop(3, 0);
	RoofLower();
	rock1->Process(deltaTime);
	rock2->Process(deltaTime);
	rock3->Process(deltaTime);
	rock4->Process(deltaTime);
	ForListLoop(4, 0);
	if (buttonSelect != NULL) buttonSelect->Process(deltaTime);

}
void Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;
	backBuffer.Clear();
	SplashScreen(backBuffer);
	MainMenu(backBuffer);
	GameActive(backBuffer);
	PauseMenu(backBuffer);
	
	//backBuffer.SetTextColour(255, 0, 0);
	//backBuffer.DrawText(50, 50, "hello");
	backBuffer.Present();
}
void Game::Quit()
{
	m_looping = false;
}
