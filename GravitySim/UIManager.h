#pragma once

#include <vector>

#include "UIElement.h"
#include "Vector.h"

class UIManager
{
public:
	std::vector<UIElement*> buttons = {};

	void update(Vector mousePos);
	void render(SDL_Renderer* renderer);

};