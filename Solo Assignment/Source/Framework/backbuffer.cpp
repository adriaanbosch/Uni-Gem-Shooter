// COMP710 GP 2D Framework 2020

// This include:
#include "backbuffer.h"

// Local includes:
#include "logmanager.h"
#include "texturemanager.h"
#include "sprite.h"
#include "texture.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>

BackBuffer::BackBuffer()
	: m_pTextureManager(0)
	, m_pWindow(0)
	, m_pRenderer(0)
	, m_width(0)
	, m_height(0)
	, m_clearRed(0)
	, m_clearGreen(0)
	, m_clearBlue(0)
	//, m_pDebugFont(0)
	//, m_textRed(0)
	//, m_textGreen(0)
	//, m_textBlue(0)
{

}

BackBuffer::~BackBuffer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	IMG_Quit();
	SDL_Quit();
}

bool
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("Gem Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
			}
		}
	}

	SetFullscreen(false);
	SDL_Delay(1000);
	//TTF_Init();
	//TTF_OpenFont("", 16);
	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	return (true);
}

void
BackBuffer::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		//		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALWAYS_ON_TOP);
				//SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
		SDL_SetWindowSize(m_pWindow, m_width, m_height);
	}
	else
	{
		SDL_SetWindowFullscreen(m_pWindow, 0);
	}
}

void
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	double angle;
	angle = sprite.GetAngle();
	SDL_Point center;
	center.x = sprite.GetCenterX();
	center.y = sprite.GetCenterY();
	SDL_RendererFlip flip;
	flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, angle, &center, flip);
}

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	SDL_Rect fillRect;

	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2 - x1;
	fillRect.h = y2 - y1;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite*
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

void
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}
//void BackBuffer::SetTextColour(unsigned char r, unsigned char g, unsigned char b) {
//	m_textRed = r;
//	m_textGreen = g;
//	m_textBlue = b;
//}
//void BackBuffer::DrawText(int x, int y, const char* pcText) {
//	SDL_Colour colour;
//	colour.r = m_textRed;
//	colour.g = m_textGreen;
//	colour.b = m_textBlue;
//	colour.a = 255;
//	SDL_Surface* surface = TTF_RenderText_Solid(m_pDebugFont, pcText, colour);
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
//	int i_cdecl = SDL_QueryTexture(texture, 0, 0, &m_width, &m_height);
//
//	SDL_Rect destRect;
//	destRect.x = x;
//	destRect.y = y;
//	destRect.w = m_width;
//	destRect.h = m_height;
//
//	SDL_RenderCopy(m_pRenderer, texture, &destRect, &destRect);
//
//	SDL_DestroyTexture(texture);
//	SDL_FreeSurface(surface);
//}
