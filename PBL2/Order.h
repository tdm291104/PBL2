#ifndef ORDER_H_
#define ORDER_H_

#include "CommonFunc.h"
#include "FoodAndDrink.h"
#include "Menu.h"
#include "Shift.h"

class Order
{
private:
	List<FoodAndDrink> FoodItems;
	List<Button> B_remove;
	List<Button> B_change;
	List<int> Mapping;
	bool get_list;
	bool is_payment;
	int CurrentPage;
	int AllPage;
	int CurrentPageOfBill;
	int AllPageOfBill;
	int TotalPrice;
	Button B_left_o;
	Button B_right_o;
	Button B_left_b;
	Button B_right_b;
	Button B_Payment;
	Button B_Close_Bill;
	TTF_Font* font18;
	TTF_Font* font20;
	TTF_Font* font25;
	TTF_Font* font30;
public:
	Order();
	virtual ~Order();

	void DisplayOrder(SDL_Renderer*);
	void RemoveOrder(List<FoodAndDrink>&);
	void AddFood(SDL_Event, List<FoodAndDrink>&, const int& PageTemp);

	void FoodOfOrder(FoodAndDrink&, Button&, Button&, const int&, const int&, const int&, SDL_Renderer*);

	List<FoodAndDrink>& GetList() { return this->FoodItems; }

	//check, show, update PAGE
	void CheckPage(SDL_Event);
	void ShowPage(SDL_Renderer*);
	void UpdateAllPage();


	void ChangeQuantityFood(SDL_Event);
	void RemoveFood(SDL_Event, List<FoodAndDrink>&);
	void ShowTotalPrice(const int&, const int&, SDL_Renderer*);
	int GetTotalPrice()const { return this->TotalPrice; }

	bool CheckPayment(SDL_Event, SDL_Renderer*, std::string Payment_time, const int&, Shift&, std::string, std::string);
	void ShowPayment(SDL_Renderer*);

	bool Get_is_Payment()const { return is_payment; }
	void FoodOfBill(FoodAndDrink&, const int&, const int&, const int&, SDL_Renderer*);
	void ShowBill(BaseObject&, SDL_Renderer*, std::string);
	bool Check_Close(SDL_Event, List<FoodAndDrink>&);
	void CheckPageOfBill(SDL_Event);
	void ShowPageOfBill(SDL_Renderer*);

	void Invoicing(std::string, const int&, Shift&, std::string, std::string);
};

#endif