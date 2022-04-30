#include "UIManager.h"

void UIManager::update(Vector mousePos)
{
	for (auto& button : this->buttons)
	{
		button->update(mousePos);
	}
}

void UIManager::render(SDL_Renderer* renderer)
{
	for (auto& button : this->buttons)
	{
		button->render(renderer);
	}
}
