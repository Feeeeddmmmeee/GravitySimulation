#include "UIManager.h"

UIManager::~UIManager()
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		UIElement* p = this->buttons[i];
		delete p;
	}
	this->buttons.clear();

	TTF_CloseFont(this->font);
}

void UIManager::update(Vector mousePos)
{
	for (auto& button : this->buttons)
	{
		button->update(mousePos);
	}
}

void UIManager::render(SDL_Renderer* renderer, std::string* texts, int size)
{
	for (auto& button : this->buttons)
	{
		button->render(renderer);
	}

	if (this->font)
	{
		for (int i = 0; i < size; i++)
		{
			SDL_Surface* tempSurface = TTF_RenderText_Solid(this->font, texts[i].c_str(), this->color);
			SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

			int w = 0, h = 0;
			SDL_QueryTexture(tempTexture, NULL, NULL, &w, &h);

			SDL_Rect rect;
			rect.x = 4;
			rect.y = i * 20;
			rect.w = w/ 1.5;
			rect.h = h/ 1.5;

			SDL_RenderCopy(renderer, tempTexture, NULL, &rect);

			SDL_FreeSurface(tempSurface);
			SDL_DestroyTexture(tempTexture);
		}
	}
}

void UIManager::textInit(TTF_Font* font, SDL_Color color)
{
	this->font = font;
	this->color = color;
}
