#include "UIElement.h"

UIElement::UIElement(Vector position, SDL_Renderer* renderer, const char* fileName, ID identifier)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	if (!tempSurface)
	{
		printf("Failed to load image. Error: %s", IMG_GetError());

		__debugbreak;
	}
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	this->identifier = identifier;
	this->position = position;
	this->isSelected = false;
	this->destRect.h = 32;
	this->destRect.w = 32;
}

UIElement::UIElement(Vector position, SDL_Renderer* renderer, SDL_Texture* texture, ID identifier)
{
	this->texture = texture;
	this->identifier = identifier;
	this->position = position;
	this->isSelected = false;
	this->destRect.h = 32;
	this->destRect.w = 32;
}

void UIElement::update(Vector mousePos)
{
	bool collision;
	if (isSelected) collision = this->position.x < mousePos.x&& this->position.x + this->destRect.h > mousePos.x && this->position.y < mousePos.y&& this->destRect.h + this->position.y > mousePos.y;
	else collision = this->position.x + 2 < mousePos.x&& this->position.x + 2 + this->destRect.h - 4 > mousePos.x && this->position.y + 2 < mousePos.y&& this->destRect.h - 4 + this->position.y  + 2 > mousePos.y;

	if (collision)
	{
		if (!isSelected)
		{
			this->destRect.h -= 4;
			this->destRect.w -= 4;
			this->position.x += 2;
			this->position.y += 2;
			isSelected = true;
		}
	}
	else
	{
		if (isSelected)
		{
			this->destRect.h += 4;
			this->destRect.w += 4;
			this->position.x -= 2;
			this->position.y -= 2;
			isSelected = false;
		}
	}
}

void UIElement::render(SDL_Renderer* renderer)
{
	this->destRect.x = this->position.x;
	this->destRect.y = this->position.y;
	SDL_RenderCopy(renderer, this->texture, NULL, &this->destRect);
}

void UIElement::updateTexture(SDL_Texture* texture)
{
	this->texture = texture;
}
