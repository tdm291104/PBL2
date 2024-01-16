#include "MenuOfAdmin.h"

MenuOfAdmin::MenuOfAdmin()
{
}

MenuOfAdmin::~MenuOfAdmin()
{
}

void MenuOfAdmin::SetAttribute(FoodAndDrink& F, Button& B_freeze, Button& B_remove, const int& xp, const int& yp, const int& width, const int& height, SDL_Renderer* des)
{
    Text name;
    Text item;
    Text type;
    Text price;

    //Set text
    name.SetText(F.GetName());
    item.SetText(F.GetItem());
    type.SetText(F.GetType());
    price.SetText(std::to_string(F.GetPrice()));

    //Set Button Freeze
    B_freeze.SetButtonRect(xp + 1, yp);
    //Set Button Remove
    B_remove.SetButtonRect(xp + 210, yp);

    //Draw Geometric
    GeometricFormat rectangle_size(xp, yp + 30, width, height - 30);
    ColorData color_data(159, 252, 253);
    Geometric::RenderRectangle(rectangle_size, color_data, des);

    GeometricFormat outLine_size(xp + 1, yp + 31, width, height - 30);
    ColorData color_data2(0, 0, 0);
    Geometric::RenderOutline(outLine_size, color_data2, des);

    //Draw Name
    if (name.LoadFromRenderText(font_text1, des))
        name.RendererText(des, xp + 20, yp + 70);
    //Draw Item
    if (item.LoadFromRenderText(font_text2, des))
        item.RendererText(des, xp + (width / 3), yp + 30);
    //Draw Type
    if (type.LoadFromRenderText(font_text2, des))
        type.RendererText(des, xp + 20, (yp + height) - 30);
    //Draw Price
    price.SetColor(Text::RED_TEXT);
    if (price.LoadFromRenderText(font_text2, des))
        price.RendererText(des, (xp + width) - 80, (yp + height) - 30);
    //Draw Button Freeze
    if (F.GetStatusFreeze())
    {
        B_freeze.LoadImg(Button_Freeze, des);
        B_freeze.Render(des);
    }
    else
    {
        B_freeze.LoadImg(Button_Unfreeze, des);
        B_freeze.Render(des);
    }

    //Draw Button Remove
    B_remove.LoadImg(Button_Remove, des);
    B_remove.Render(des);

}

void MenuOfAdmin::DisplayMenu(SDL_Renderer* des)
{
    int y_start = FIRST_ROW - SPACE_FOR_ROW;
    int tmp = CurrentPage * NUMBER_OF_MENU_ON_SCREEN;
    for (int i = 0; i < ROW_OF_MENU; i++)
    {
        int x_start = FIRST_COLLUM - SPACE_FOR_COLLUM;
        y_start += SPACE_FOR_ROW;
        for (int j = 0; j < COLLUM_OF_MENU; j++)
        {
            if (tmp < FoodList.Size())
            {
                x_start += SPACE_FOR_COLLUM;
                SetAttribute(FoodList[tmp], B_Freeze[tmp], B_Remove[tmp], x_start, y_start, SPACE_FOR_COLLUM - 10, SPACE_FOR_ROW - 10, des);
                FoodList[tmp].SetLocationOfMenu(this->CurrentPage, x_start, y_start, x_start + SPACE_FOR_COLLUM - 10, y_start + SPACE_FOR_ROW - 10);
            }
            else
            {
                break;
            }
            tmp++;
        }
    }
}