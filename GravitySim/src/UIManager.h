#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <vector>

#include "SDL_ttf.h"

#include "UIElement.h"

class UIManager
{
public:
	~UIManager();

	void update(Vector mousePos);
	void render(SDL_Renderer* renderer, std::string* texts, int size);

	void textInit(TTF_Font* font, SDL_Color color);

	UIElement* getElementByID(ID identifier);

	std::vector<UIElement*> buttons = {};

private:
	TTF_Font* font;
	SDL_Color color;

};

#endif