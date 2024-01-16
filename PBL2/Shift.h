#ifndef SHIFT_H_
#define SHIFT_H_

#include "CommonFunc.h"
#include "Button.h"
#include "FoodAndDrink.h"

class Shift
{
private:
	int shift_number;
	std::string CheckIn;
	std::string CheckOut;
	int TotalPriceOfShift;
	Button B_Logout;
	Button B_Current_Shift;
	Button B_Shift1_Choose;
	Button B_Shift2_Choose;
	Button B_Shift3_Choose;

public:
	enum SHIFT
	{
		Shift_1 = 1,
		Shift_2 = 2,
		Shift_3 = 3,
	};
	Shift(std::string = "");
	~Shift();

	void ShowShift(SDL_Renderer*);
	void ShowBgSelectShift(BaseObject&, SDL_Renderer*);
	bool CheckSelectShift(SDL_Event, std::string, std::string);
	bool CheckCloseSelectShift(SDL_Event, std::string, std::string);
	bool CheckLogout(SDL_Event, std::string, std::string, std::string);

	int GetShiftNumber() const { return this->shift_number; }

	void AddPrice(const int&);
	void AddToFile(std::string, std::string, std::string);
};



#endif