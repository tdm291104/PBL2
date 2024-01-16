#ifndef MENU_OF_ADMIN_
#define MENU_OF_ADMIN_

#include "Menu.h"

class MenuOfAdmin : public Menu
{
public:
	MenuOfAdmin();
	virtual ~MenuOfAdmin();

	void SetAttribute(FoodAndDrink&, Button&, Button&, const int&, const int&, const int&, const int&, SDL_Renderer*);

	void DisplayMenu(SDL_Renderer* des);
};

#endif