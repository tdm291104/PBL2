#include "FoodAndDrink.h"

FoodAndDrink::FoodAndDrink()
{
	this->status_of_menu = false;
	this->status_of_order = false;
	this->status_freeze = false;
	this->m_page = 0;
	this->x_pos_first = 0;
	this->y_pos_first = 0;
	this->x_pos_last = 0;
	this->y_pos_last = 0;
	this->m_page = 0;
	this->o_page = 0;
	this->price = 0;
	this->quantity = 0;
}

FoodAndDrink::~FoodAndDrink()
{

}

void FoodAndDrink::SetName(const std::string& NameFood)
{
	this->name = NameFood;
}

std::string FoodAndDrink::GetName()
{
	return this->name;
}

void FoodAndDrink::SetItem(const std::string& Item)
{
	this->item = Item;
}

std::string FoodAndDrink::GetItem()
{
	return this->item;
}

void FoodAndDrink::SetType(const std::string& TypeFood)
{
	this->type = TypeFood;
}

std::string FoodAndDrink::GetType()
{
	return this->type;
}

void FoodAndDrink::SetPrice(const int& Price)
{
	this->price = Price;
}

int FoodAndDrink::GetPrice()
{
	return this->price;
}

void FoodAndDrink::SetQuantity(const int& Quantity)
{
	this->quantity = Quantity;
}

int FoodAndDrink::GetQuantity()
{
	return this->quantity;
}

void FoodAndDrink::SetStatusOfMenu(const bool& status)
{
	this->status_of_menu = status;
}

bool FoodAndDrink::GetStatusOfMenu()const
{
	return this->status_of_menu;
}

void FoodAndDrink::SetStatusFreeze(const bool& status)
{
	this->status_freeze = status;
}
bool FoodAndDrink::GetStatusFreeze()const
{
	return this->status_freeze;
}

void FoodAndDrink::SetStatusOfOrder(const bool status)
{
	this->status_of_order = status;
}

bool FoodAndDrink::GetStatusOfOrder()const
{
	return this->status_of_order;
}

void FoodAndDrink::SetLocationOfMenu(const int& page, const int& xf, const int& yf, const int& xl, const int& yl)
{
	this->m_page = page;
	this->x_pos_first = xf;
	this->y_pos_first = yf;
	this->x_pos_last = xl;
	this->y_pos_last = yl;
}

void FoodAndDrink::SetLocationOfOrder(const int& page)
{
	this->o_page = page;
}