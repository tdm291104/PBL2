#ifndef BUTTON_H_
#define BUTTON_H_

#include "CommonFunc.h"
#include "BaseObject.h"


class Button : public BaseObject
{
private:

public:
	Button();
	virtual ~Button();
	enum CHANGE
	{
		remain = -1,
		increase = 0,
		decrease = 1,
	};

	void SetButtonRect(const int&, const int&);
	bool CheckMouse(SDL_Event);
	int CheckMouseChangeQuantity(SDL_Event events);
	bool CheckMouseFreeze(SDL_Event events);
};


#endif