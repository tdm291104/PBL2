#ifndef MENU_H_
#define MENU_H_

#include "CommonFunc.h"
#include "FoodAndDrink.h"
#include "Text.h"
#include "Geometric.h"
#include "Button.h"

class Menu
{
protected:
	List<FoodAndDrink> FoodList;
	List<Button> B_Freeze;
	List<Button> B_Remove;
	int CurrentPage;
	int AllPage;
	bool status_add_food;
	Text Page;
	Button B_left_m;
	Button B_right_m;
	Button B_AddMoreFood;
	Button B_CloseAddMoreFood;
	Button B_AddFood;
	Button B_Poiter;
	TTF_Font* font_text;
	TTF_Font* font_text1;
	TTF_Font* font_text2;
	//attribute add food
	std::string name;
	std::string item;
	std::string type;
	std::string price;
public:
	Menu();
	virtual ~Menu();

	bool Add();
	void CheckFreeze(SDL_Event);
	void CheckRemove(SDL_Event, List<FoodAndDrink>&);
	void RemoveFood(const int&);
	void SetDefaultCurrentPage();
	int GetCurrentPage()const { return this->CurrentPage; }
	List<FoodAndDrink>& GetList() { return this->FoodList; }
	void CheckPage(SDL_Event);
	void ShowPage(SDL_Renderer*);

	void ShowButtonAddFood(SDL_Renderer*);
	bool CheckAddMoreFood(SDL_Event);
	void ShowBgAddFood(BaseObject&, SDL_Renderer*);
	bool CheckCloseAddFood(SDL_Event);
	int CheckLocationAddFood(SDL_Event);
	bool AddMoreFood();
	void ClearAddFood();

	//check enter attribute
	void CheckEnter(SDL_Event, const int&);
};


#endif