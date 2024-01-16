#include "Order.h"

Order::Order()
{
    this->get_list = false;
    this->is_payment = false;
    this->CurrentPage = 0;
    this->AllPage = 0;
    this->CurrentPageOfBill = 0;
    this->AllPageOfBill = 0;
    this->TotalPrice = 0;
    this->font18 = TTF_OpenFont(Text_Font, 18);
    this->font20 = TTF_OpenFont(Text_Font, 20);
    this->font25 = TTF_OpenFont(Text_Font, 25);
    this->font30 = TTF_OpenFont(Text_Font, 30);
}

Order::~Order()
{
    TTF_CloseFont(font18);
    TTF_CloseFont(font20);
    TTF_CloseFont(font25);
    TTF_CloseFont(font30);
}

void Order::AddFood(SDL_Event events, List<FoodAndDrink>& MenuFood, const int& PageTemp)
{
    //Check mouse
    if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {
        int xm = events.button.x;
        int ym = events.button.y;

        for (int i = 0; i < MenuFood.Size(); i++)
        {
            if ((MenuFood[i].GetMenuPage() == PageTemp) &&
                (xm >= MenuFood[i].GetXFirst() && xm <= MenuFood[i].GetXLast()) &&
                (ym >= MenuFood[i].GetYFirst() + 30 && ym <= MenuFood[i].GetYLast()))
            {
                if ((MenuFood[i].GetStatusFreeze() == true))
                {
                    //check nếu món ăn bên menu đã hết hàng thì sẽ không chọn được
                    MessageBox(NULL, L"Món Ăn Đã Hết Hàng", L"Thông Báo", MB_OK | MB_ICONSTOP);
                }
                else
                {
                    if (MenuFood[i].GetStatusOfOrder() == false)
                    {
                        //set trạng thái order cho menufood
                        MenuFood[i].SetStatusOfOrder(true);
                        //add food từ menu vào order
                        FoodAndDrink F = MenuFood[i];
                        //set số lượng ban đầu
                        F.SetQuantity(1);
                        this->FoodItems.Push(F);
                        //set mapping cho orderfood và menufood
                        this->Mapping.Push(i);
                        //add button remove cho order
                        Button B_tmp;
                        this->B_remove.Push(B_tmp);
                        //add button change quantity cho order
                        this->B_change.Push(B_tmp);
                        B_tmp.Free();


                        //update CurentPage khi list order vượt quá số lượng hiển thị lên màn hình
                        if ((FoodItems.Size() != 1) && ((FoodItems.Size() - 1) % NUMBER_OF_ORDER_ON_SCREEN) == 0)
                        {
                            ++CurrentPage;
                        }
                        //set vị trí page for food
                        FoodItems[FoodItems.Size() - 1].SetLocationOfOrder(this->CurrentPage);
                        //Update AllPage
                        UpdateAllPage();
                    }
                    else if (MenuFood[i].GetStatusOfOrder() == true)
                    {
                        //check nếu món ăn bên menu đã được chọn thì sẽ không được chọn lại
                        MessageBox(NULL, L"Món Ăn Đã Được Order", L"Thông Báo", MB_OK | MB_ICONSTOP);
                    }
                }
            }
            else continue;
        }
    }
}

void Order::FoodOfOrder(FoodAndDrink& F, Button& B_remove, Button& B_change, const int& stt, const int& xp, const int& yp, SDL_Renderer* des)
{
    Text STT;
    Text name;
    Text quantity;
    Text price;

    std::string s_show = std::to_string(F.GetTotalOrder());
    int tmp = 0;
    for (int i = s_show.size() - 1; i > 0; i--)
    {
        ++tmp;
        if (tmp % 3 == 0)
        {
            s_show.push_back('0');
            for (int j = s_show.size() - 1; j > i; j--)
            {
                s_show[j] = s_show[j - 1];
            }
            s_show[i] = '.';
        }
    }

    STT.SetText(std::to_string(stt));
    name.SetText(F.GetName());
    quantity.SetText(std::to_string(F.GetQuantity()));
    price.SetText(s_show);
    B_remove.SetButtonRect(xp + 570, yp);
    B_change.SetButtonRect(xp + 395, yp);

    //Draw STT
    if (STT.LoadFromRenderText(font25, des))
        STT.RendererText(des, xp, yp);
    //Draw Name
    if (name.LoadFromRenderText(font25, des))
        name.RendererText(des, xp + 50, yp);
    //Draw Quantity
    if (quantity.LoadFromRenderText(font25, des))
        quantity.RendererText(des, xp + 370, yp);
    //Draw Price
    if (price.LoadFromRenderText(font25, des))
        price.RendererText(des, xp + 430, yp);
    //Draw Button Remove
    B_remove.LoadImg(Button_Remove, des);
    B_remove.Render(des);
    //Draw Button Change Quantity
    B_change.LoadImg(Button_Change, des);
    B_change.Render(des);
}

void Order::ShowPage(SDL_Renderer* des)
{
    std::string current_page = std::to_string(CurrentPage + 1);
    std::string max_page = std::to_string(AllPage + 1);
    std::string show_page = current_page + "/" + max_page;

    //make page text
    Text Page;
    Page.SetText(show_page);
    Page.LoadFromRenderText(font20, des);
    Page.RendererText(des, 290, 700);

    //Make Button Left,Right
    this->B_left_o.LoadImg(Button_Left, des);
    this->B_right_o.LoadImg(Button_Right, des);

    B_left_o.SetButtonRect(ORDER_X_BUTTON_LEFT, ORDER_Y_BUTTON_LEFT);
    B_right_o.SetButtonRect(ORDER_X_BUTTON_RIGHT, ORDER_Y_BUTTON_RIGHT);

    B_left_o.Render(des);
    B_right_o.Render(des);
}

void Order::CheckPage(SDL_Event events)
{
    //Check Page
    if (this->B_left_o.CheckMouse(events))
    {
        --CurrentPage;
        if (CurrentPage < 0)
            CurrentPage = 0;
    }
    else if (this->B_right_o.CheckMouse(events))
    {
        ++CurrentPage;
        if (CurrentPage > AllPage)
            CurrentPage = AllPage;
    }

    //Destroy Button
    B_left_o.Free();
    B_right_o.Free();
}

void Order::UpdateAllPage()
{
    if ((FoodItems.Size() != 0) && (FoodItems.Size() % NUMBER_OF_ORDER_ON_SCREEN) == 0)
    {
        this->AllPage = (FoodItems.Size() / NUMBER_OF_ORDER_ON_SCREEN) - 1;
    }
    else this->AllPage = (FoodItems.Size() / NUMBER_OF_ORDER_ON_SCREEN);
}

void Order::DisplayOrder(SDL_Renderer* des)
{
    int tmp = CurrentPage * NUMBER_OF_ORDER_ON_SCREEN;

    int y_start = 50;
    int x_start = 20;
    for (int i = 0; i < NUMBER_OF_ORDER_ON_SCREEN; i++)
    {
        y_start += 50;
        if (tmp < FoodItems.Size())
        {
            FoodOfOrder(FoodItems[tmp], B_remove[tmp], B_change[tmp], tmp + 1, x_start, y_start, des);
        }
        else
        {
            break;
        }
        tmp++;
    }
}

void Order::ChangeQuantityFood(SDL_Event events)
{
    for (int i = 0; i < FoodItems.Size(); i++)
    {
        if (this->CurrentPage == FoodItems[i].GetOrderPage())
        {
            if (B_change[i].CheckMouseChangeQuantity(events) == Button::increase)
            {
                FoodItems[i].SetQuantity(FoodItems[i].GetQuantity() + 1);
            }
            else if (B_change[i].CheckMouseChangeQuantity(events) == Button::decrease)
            {
                FoodItems[i].SetQuantity(FoodItems[i].GetQuantity() - 1);
                if (FoodItems[i].GetQuantity() < 1)
                    FoodItems[i].SetQuantity(1);
            }
            else
            {
                B_change[i].Free();
            }
        }
    }

}

void Order::RemoveFood(SDL_Event events, List<FoodAndDrink>& MenuFood)
{
    for (int i = 0; i < FoodItems.Size(); i++)
    {
        if (this->CurrentPage == FoodItems[i].GetOrderPage())
        {
            if (B_remove[i].CheckMouse(events) == true)
            {
                if ((i + 1) < FoodItems.Size())
                {
                    FoodItems[i + 1].SetLocationOfOrder(FoodItems[i].GetOrderPage());
                    FoodItems.Pop(i);

                    B_remove[i + 1] = B_remove[i];
                    B_remove[i].Free();
                    B_remove.Pop(i);

                    B_change[i + 1] = B_change[i];
                    B_change[i].Free();
                    B_change.Pop(i);

                    MenuFood[Mapping[i]].SetStatusOfOrder(false);
                    Mapping.Pop(i);
                }
                else
                {
                    FoodItems.Pop(i);

                    B_remove[i].Free();
                    B_remove.Pop(i);

                    B_change[i].Free();
                    B_change.Pop(i);

                    MenuFood[Mapping[i]].SetStatusOfOrder(false);
                    Mapping.Pop(i);
                }

                //Update AllPage
                int page_tmp = this->AllPage;
                UpdateAllPage();
                if (page_tmp != this->AllPage)
                {
                    this->CurrentPage--;
                    if (this->CurrentPage < 0)
                        this->CurrentPage = 0;
                }
                break;
            }
            else
            {
                B_change[i].Free();
            }
        }
    }
}

void Order::ShowTotalPrice(const int& xp, const int& yp, SDL_Renderer* des)
{
    //get totalPrice
    int TotalTmp = 0;
    for (int i = 0; i < FoodItems.Size(); i++)
    {
        TotalTmp += FoodItems[i].GetTotalOrder();
    }
    if (this->TotalPrice != TotalTmp)
        this->TotalPrice = TotalTmp;

    //show totalPrice
    Text total_price;
    std::string s_show = std::to_string(this->TotalPrice);
    int tmp = 0;
    for (int i = s_show.size() - 1; i > 0; i--)
    {
        ++tmp;
        if (tmp % 3 == 0)
        {
            s_show.push_back('0');
            for (int j = s_show.size() - 1; j > i; j--)
            {
                s_show[j] = s_show[j - 1];
            }
            s_show[i] = '.';
        }
    }
    total_price.SetText(s_show + " VND");

    //draw total
    total_price.LoadFromRenderText(font30, des);
    total_price.RendererText(des, xp, yp);
}

void Order::RemoveOrder(List<FoodAndDrink>& MenuFood)
{
    for (int i = 0; i < FoodItems.Size(); i++)
    {
        MenuFood[Mapping[i]].SetStatusOfOrder(false);
    }
    this->CurrentPage = 0;
    this->AllPage = 0;
    this->Mapping.Clear();
    this->B_change.Clear();
    this->B_remove.Clear();
    this->FoodItems.Clear();
}

bool Order::CheckPayment(SDL_Event events, SDL_Renderer* des, std::string Payment_time, const int& shift_number, Shift& shift, std::string date, std::string MaNV)
{
    //Check Payment
    if (this->B_Payment.CheckMouse(events))
    {
        if (this->FoodItems.Size() == 0)
        {
            MessageBox(NULL, L"Đơn hàng của bạn chưa có món ăn nào!!!", L"Thông Báo", MB_OK | MB_ICONSTOP);
        }
        else
        {
            Invoicing(Payment_time, shift_number, shift, date, MaNV);
            this->is_payment = true;
        }
        //Destroy Button
        B_Payment.Free();
        return true;
    }
    else
    {
        //Destroy Button
        B_Payment.Free();
        return false;
    }
}

void Order::ShowPayment(SDL_Renderer* des)
{
    //Make Button Payment
    this->B_Payment.LoadImg(Button_In_Bill, des);

    B_Payment.SetButtonRect(420, 748);

    B_Payment.Render(des);
}

void Order::FoodOfBill(FoodAndDrink& F, const int& stt, const int& xp, const int& yp, SDL_Renderer* des)
{
    Text STT;
    Text name;
    Text quantity;
    Text price;
    Text TotalPrice;

    std::string price_show = std::to_string(F.GetPrice());
    int tmp = 0;
    for (int i = price_show.size() - 1; i > 0; i--)
    {
        ++tmp;
        if (tmp % 3 == 0)
        {
            price_show.push_back('0');
            for (int j = price_show.size() - 1; j > i; j--)
            {
                price_show[j] = price_show[j - 1];
            }
            price_show[i] = '.';
        }
    }

    std::string priceTotal_show = std::to_string(F.GetTotalOrder());
    tmp = 0;
    for (int i = priceTotal_show.size() - 1; i > 0; i--)
    {
        ++tmp;
        if (tmp % 3 == 0)
        {
            priceTotal_show.push_back('0');
            for (int j = priceTotal_show.size() - 1; j > i; j--)
            {
                priceTotal_show[j] = priceTotal_show[j - 1];
            }
            priceTotal_show[i] = '.';
        }
    }

    STT.SetText(std::to_string(stt));
    name.SetText(F.GetName());
    quantity.SetText(std::to_string(F.GetQuantity()));
    price.SetText(price_show);
    TotalPrice.SetText(priceTotal_show);

    //Draw STT
    if (STT.LoadFromRenderText(font18, des))
        STT.RendererText(des, xp, yp);
    //Draw Name
    if (name.LoadFromRenderText(font18, des))
        name.RendererText(des, xp + 35, yp);
    //Draw Quantity
    if (quantity.LoadFromRenderText(font18, des))
        quantity.RendererText(des, xp + 230, yp);
    //Draw Price
    if (price.LoadFromRenderText(font18, des))
        price.RendererText(des, xp + 270, yp);
    //Draw PriceTotal
    if (TotalPrice.LoadFromRenderText(font18, des))
        TotalPrice.RendererText(des, xp + 340, yp);
}

void Order::ShowBill(BaseObject& Bill_bg, SDL_Renderer* des, std::string Payment_time)
{
    if (this->is_payment)
    {
        if (this->FoodItems.Size() % NUMBER_OF_BILL_ON_SCREEN == 0)
        {
            this->AllPageOfBill = (this->FoodItems.Size() / NUMBER_OF_BILL_ON_SCREEN) - 1;
        }
        else
            this->AllPageOfBill = this->FoodItems.Size() / NUMBER_OF_BILL_ON_SCREEN;

        Bill_bg.Render(des, NULL);
        int tmp = CurrentPageOfBill * NUMBER_OF_BILL_ON_SCREEN;

        //Make And Show Button Close Bill
        this->B_Close_Bill.LoadImg(Button_Remove, des);
        B_Close_Bill.SetButtonRect(ORDER_X_BUTTON_CLOSE_BILL, ORDER_Y_BUTTON_CLOSE_BILL);
        B_Close_Bill.Render(des);

        //Show Button Page
        ShowPageOfBill(des);

        int y_start = 216;
        int x_start = 540;
        for (int i = 0; i < NUMBER_OF_BILL_ON_SCREEN; i++)
        {
            y_start += 20;
            if (tmp < FoodItems.Size())
            {
                FoodOfBill(FoodItems[tmp], tmp + 1, x_start, y_start, des);
            }
            else
            {
                break;
            }
            tmp++;
        }

        //Show Total Price
        ShowTotalPrice(780, 663, des);

        //Show Order Time
        Text PaymentTime;
        PaymentTime.SetText(Payment_time);
        //Draw Real Time
        PaymentTime.LoadFromRenderText(font18, des);
        PaymentTime.RendererText(des, 660, 153);
    }
}

void Order::ShowPageOfBill(SDL_Renderer* des)
{
    std::string current_page = std::to_string(CurrentPageOfBill + 1);
    std::string max_page = std::to_string(AllPageOfBill + 1);
    std::string show_page = current_page + "/" + max_page;

    //make page text
    Text Page;
    Page.SetText(show_page);
    Page.LoadFromRenderText(font18, des);
    Page.RendererText(des, 745, 635);

    //Make Button Left,Right
    this->B_left_b.LoadImg(Button_Left_Of_Bill, des);
    this->B_right_b.LoadImg(Button_Right_Of_Bill, des);

    B_left_b.SetButtonRect(BILL_X_BUTTON_LEFT, BILL_Y_BUTTON_LEFT);
    B_right_b.SetButtonRect(BILL_X_BUTTON_RIGHT, BILL_Y_BUTTON_RIGHT);

    B_left_b.Render(des);
    B_right_b.Render(des);
}

void Order::CheckPageOfBill(SDL_Event events)
{
    //Check Page
    if (this->B_left_b.CheckMouse(events))
    {
        --CurrentPageOfBill;
        if (CurrentPageOfBill < 0)
            CurrentPageOfBill = 0;
    }
    else if (this->B_right_b.CheckMouse(events))
    {
        ++CurrentPageOfBill;
        if (CurrentPageOfBill > AllPageOfBill)
            CurrentPageOfBill = AllPageOfBill;
    }

    //Destroy Button
    B_left_b.Free();
    B_right_b.Free();
}

bool Order::Check_Close(SDL_Event events, List<FoodAndDrink>& MenuFood)
{
    //Check Close
    if (this->B_Close_Bill.CheckMouse(events))
    {
        this->is_payment = false;
        RemoveOrder(MenuFood);
        return true;
    }
    else
    {
        //Destroy Button
        B_Close_Bill.Free();
        return false;
    }
}

void Order::Invoicing(std::string Payment_time, const int& shift_number, Shift& shift, std::string date, std::string MaNV)
{
    // Mở file bằn hàm ofstream và add món ăn vào FoodList
    std::ofstream outFile;
    outFile.open(Payment_History + date + ".txt", std::ios::app);
    if (!outFile)
    {
        return;
    }

    std::string Item;           // Tên danh muc
    std::string Name;           // Tên mon
    std::string Type;           // Loại
    int Quantity;               // Số Lượng
    int Price;                  // Giá
    int TotalPriceOfFood;       // Tổng Giá

    outFile << "******************************************" << std::endl;
    outFile << "CA: " << shift_number << std::endl;
    outFile << "Nhan Vien: " << MaNV << std::endl;
    outFile << Payment_time << std::endl;
    for (int i = 0; i < this->FoodItems.Size(); i++)
    {
        Name = this->FoodItems[i].GetName();
        Item = this->FoodItems[i].GetItem();
        Type = this->FoodItems[i].GetType();
        Quantity = this->FoodItems[i].GetQuantity();
        Price = this->FoodItems[i].GetPrice();
        TotalPriceOfFood = Quantity * Price;
        shift.AddPrice(TotalPriceOfFood);

        outFile << Name << ';' << Item << ';' << Type << ';' << Quantity << ';' << Price << ';' << TotalPriceOfFood << std::endl;
    }
    outFile << this->TotalPrice << std::endl;
    outFile.close();
}