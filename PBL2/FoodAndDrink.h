#ifndef FOOD_AND_DRINK_H_
#define FOOD_AND_DRINK_H_

#include "CommonFunc.h"


class FoodAndDrink
{
private:
	//key
	std::string name;
	std::string item;
	std::string type;
	int price;
	int quantity;

	//status
	bool status_of_menu;
	bool status_of_order;
	bool status_freeze;

	//location of menu
	int m_page;
	int x_pos_first;
	int y_pos_first;
	int x_pos_last;
	int y_pos_last;

	//location of order
	int o_page;
public:
	FoodAndDrink();
	virtual ~FoodAndDrink();

	void SetName(const std::string&);
	std::string GetName();

	void SetItem(const std::string&);
	std::string GetItem();

	void SetType(const std::string&);
	std::string GetType();

	void SetPrice(const int&);
	int GetPrice();

	void SetQuantity(const int&);
	int GetQuantity();

	void SetStatusOfMenu(const bool&);
	bool GetStatusOfMenu()const;

	void SetStatusFreeze(const bool&);
	bool GetStatusFreeze()const;

	void SetStatusOfOrder(const bool);
	bool GetStatusOfOrder()const;

	void SetLocationOfMenu(const int&, const int&, const int&, const int&, const int&);

	int GetMenuPage()const { return this->m_page; }
	int GetXFirst()const { return this->x_pos_first; }
	int GetYFirst()const { return this->y_pos_first; }
	int GetXLast()const { return this->x_pos_last; }
	int GetYLast()const { return this->y_pos_last; }

	void SetLocationOfOrder(const int&);
	int GetOrderPage()const { return this->o_page; }

	int GetTotalOrder()const { return this->quantity * this->price; }
};



#endif