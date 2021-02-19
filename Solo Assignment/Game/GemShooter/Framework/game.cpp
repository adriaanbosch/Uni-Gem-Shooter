// COMP710 GP 2D Framework 2020

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include"gameobject.h"
#include"gem.h"
#include "shootGem.h"



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

void
Game::DestroyInstance()
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
	, deadZone(0)
	, roof(0)
	, object1(0)
	, objectlist(0)
	, gem1(0)
	, aimLine(0)
	, shootingGem(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
{
	std::vector<GameObject*> objectlist();
	std::vector<GameObject*> shootingList();
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool
Game::Initialise()
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
	//sprite setup for start of game
	wallSprite1, wallSprite2, deadZone, roof = new Sprite();
	wallSprite1 = m_pBackBuffer->CreateSprite("wall.png");
	wallSprite2 = m_pBackBuffer->CreateSprite("wall.png");
	deadZone = m_pBackBuffer->CreateSprite("deadzone.png");
	roof = m_pBackBuffer->CreateSprite("roof.png");
	
	roof->SetX(325);
	wallSprite1->SetX(300);
	wallSprite2->SetX(1600);
	deadZone->SetX(320);
	deadZone->SetY(900);
	
	GameObjectListed();
	GameObjectShootingList();
	return (true);
}
void Game::GameObjectShootingList() { 
	//make aim line here
	aimLine = new GameObject();
	pSprite = new Sprite();
	pSprite = m_pBackBuffer->CreateSprite("aimline.png");
	aimLine->Initialise(pSprite);
	aimLine->SetPositionY(40);
	aimLine->SetPositionX(960);
	
	//make the two objects
	int i = 1;
	while (i <= 2)
	{
		shootingGem = new ShootGem();
		pSprite = new Sprite();
		pSprite = m_pBackBuffer->CreateSprite(shootingGem->GemRandom());
		shootingGem->Initialise(pSprite);
		shootingList.push_back(shootingGem);
		i++;
	}
	shootingList[0]->SetPositionX(925);
	shootingList[0]->SetPositionY(1000);

	shootingList[1]->SetPositionX(1050);
	shootingList[1]->SetPositionY(1000);
}
void Game::GemShot() { // will deal with shooting gems, and the list
	shootingList[0]->SetVerticalVelocity(5);
	//shootingList.erase(0);
	//add another gem

	shootingGem = new ShootGem();
	pSprite = new Sprite();
	pSprite = m_pBackBuffer->CreateSprite(shootingGem->GemRandom());
	shootingGem->Initialise(pSprite);
	shootingList.push_back(shootingGem);
	shootingList[1]->Draw(*m_pBackBuffer);
}
void Game::Aim(int angle) {
	if (angle == 1)
	{
		aimLine->AimAngle(10);
	}
	if (angle == 2)
	{
		aimLine->AimAngle(-10);
	}
	
}
void Game::SwitchGems() { //allows the user to switch between the current and next gem to shoot using <algorithm> and iter_swap 
	shootingList[0]->SetPositionX(925);
	shootingList[0]->SetPositionY(1000);
	shootingList[1]->SetPositionX(1050);
	shootingList[1]->SetPositionY(1000);
	iter_swap(shootingList.begin(), shootingList.begin() + 1);
	

	
}

void Game::GameObjectListed() { // this method creates gems, places them in a list etc
	int r = 1; //row
	int c = 1; //column
	float w = 300; // width screen
	float h = 1080; // height screen
	while (r <= 4) //rows
	{
		while (c <= 26) // columns
		{
			gem1 = new Gem();
			pSprite = new Sprite();
			pSprite = m_pBackBuffer->CreateSprite(gem1->GemRandom()); // assigns a random gem colour
			gem1->Initialise(pSprite);
			gem1->SetPositionX(w);
			gem1->SetPositionY(h);
			objectlist.push_back(gem1);
			c++;
			w = w + 40;
		}
		if (c = 26) {
			r++;
			c = 1;
			h = 1080;
			w = 300;
		}
	}
}

bool
Game::DoGameLoop()
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

void
Game::Process(float deltaTime)
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
	shootingList[0]->Process(deltaTime);
	shootingList[1]->Process(deltaTime);
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();
	wallSprite1->Draw(*m_pBackBuffer); wallSprite2->Draw(*m_pBackBuffer); deadZone->Draw(*m_pBackBuffer); roof->Draw(*m_pBackBuffer); aimLine->Draw(*m_pBackBuffer);
	shootingList[0]->Draw(*m_pBackBuffer); shootingList[1]->Draw(*m_pBackBuffer);
	//testing
	objectlist[0]->Draw(*m_pBackBuffer);
	objectlist[1]->Draw(*m_pBackBuffer);
	objectlist[20]->Draw(*m_pBackBuffer);
	//
	
	/*for (int i = 0; i < objectlist.size(); i++) {
		objectlist[1]->Draw(*m_pBackBuffer);
	}*/
	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}
