#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::SetButtonRect(const int& x, const int& y)
{
    SetRect(x, y);
}

int Button::CheckMouseChangeQuantity(SDL_Event events)
{
    int xm = 0;
    int ym = 0;
    if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {
        xm = events.button.x;
        ym = events.button.y;
        if ((xm >= rect_.x && xm <= rect_.x + rect_.w) &&
            (ym >= rect_.y && ym <= rect_.y + rect_.h / 2))
        {
            return increase;
        }
        else if ((xm >= rect_.x && xm <= rect_.x + rect_.w) &&
            (ym >= rect_.y + rect_.h / 2 && ym <= rect_.y + rect_.h))
        {
            return decrease;
        }
    }

    return remain;
}

bool Button::CheckMouse(SDL_Event events)
{
    int xm = 0;
    int ym = 0;
    if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {
        xm = events.button.x;
        ym = events.button.y;
        if ((xm >= rect_.x && xm <= rect_.x + rect_.w) &&
            (ym >= rect_.y && ym <= rect_.y + rect_.h))
        {
            return true;
        }
    }

    return false;
}

bool Button::CheckMouseFreeze(SDL_Event events)
{
    int xm = 0;
    int ym = 0;
    if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {
        xm = events.button.x;
        ym = events.button.y;
        if ((xm >= rect_.x + 134 && xm <= rect_.x + rect_.w) &&
            (ym >= rect_.y && ym <= rect_.y + rect_.h))
        {
            return true;
        }
    }

    return false;
}