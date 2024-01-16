#include "Menu.h"

Menu::Menu()
{
    this->CurrentPage = 0;
    this->AllPage = 0;
    this->status_add_food = false;
    this->B_left_m.SetButtonRect(MENU_X_BUTTON_LEFT, MENU_Y_BUTTON_LEFT);
    this->B_right_m.SetButtonRect(MENU_X_BUTTON_RIGHT, MENU_Y_BUTTON_RIGHT);
    this->B_AddMoreFood.SetButtonRect(X_MENU_Add_Food, Y_MENU_Add_Food);
    this->B_CloseAddMoreFood.SetButtonRect(960, 110);
    this->B_AddFood.SetButtonRect(680, 550);
    this->font_text = TTF_OpenFont(Text_Font, 20);
    this->font_text1 = TTF_OpenFont(Text_Font, 27);
    this->font_text2 = TTF_OpenFont(Text_Font, 22);
}

Menu::~Menu()
{
    B_left_m.Free();
    B_right_m.Free();
    B_AddFood.Free();
    B_CloseAddMoreFood.Free();
    B_Poiter.Free();
    TTF_CloseFont(font_text);
    TTF_CloseFont(font_text1);
    TTF_CloseFont(font_text2);
}

bool Menu::Add()
{
    // Mở file bằn hàm ifstream và add món ăn vào FoodList
    std::ifstream inFile;
    inFile.open(CSDL);
    if (!inFile)
    {
        return false;
    }

    std::string Item; // Tên danh muc
    std::string Name; // Tên mon
    std::string Type; // Loai
    int Price;        // gia
    //Creat Button Freeze && Button Remove
    Button B_tmp;

    std::string line;
    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        // Tách thông tin dựa trên dấu ";"
        std::getline(ss, Item, ';');
        std::getline(ss, Name, ';');
        std::getline(ss, Type, ';');
        ss >> Price;

        FoodAndDrink F;
        F.SetName(Name);
        F.SetItem(Item);
        F.SetPrice(Price);
        F.SetType(Type);
        this->FoodList.Push(F);
        //Add Button Freeze
        this->B_Freeze.Push(B_tmp);
        //Add Button Freeze
        this->B_Remove.Push(B_tmp);
    }
    B_tmp.Free();
    inFile.close();
    if (FoodList.Size() % NUMBER_OF_MENU_ON_SCREEN == 0)
        AllPage = (FoodList.Size() / NUMBER_OF_MENU_ON_SCREEN) - 1;
    else AllPage = (FoodList.Size() / NUMBER_OF_MENU_ON_SCREEN);

    return true;
}

void Menu::SetDefaultCurrentPage()
{
    this->CurrentPage = 0;
}

void Menu::CheckPage(SDL_Event events)
{
    //Check Page
    if (this->B_left_m.CheckMouse(events) == true)
    {
        --CurrentPage;
        if (CurrentPage < 0)
            CurrentPage = 0;
    }
    else if (this->B_right_m.CheckMouse(events) == true)
    {
        ++CurrentPage;
        if (CurrentPage > AllPage)
            CurrentPage = AllPage;
    }

    //destroy button
    B_left_m.Free();
    B_right_m.Free();
}

void Menu::ShowPage(SDL_Renderer* des)
{
    std::string current_page = std::to_string(CurrentPage + 1);
    std::string max_page = std::to_string(AllPage + 1);
    std::string show_page = current_page + "/" + max_page;

    //make page text
    this->Page.SetText(show_page);
    this->Page.LoadFromRenderText(font_text, des);
    this->Page.RendererText(des, X_MENU_PAGE, Y_MENU_PAGE);

    //Make Button
    this->B_left_m.LoadImg(Button_Left, des);
    this->B_right_m.LoadImg(Button_Right, des);

    B_left_m.Render(des);
    B_right_m.Render(des);
}

void Menu::CheckFreeze(SDL_Event events)
{
    //Check Freeze
    for (int i = 0; i < this->FoodList.Size(); i++)
    {
        if (this->FoodList[i].GetMenuPage() == this->CurrentPage && B_Freeze[i].CheckMouseFreeze(events))
        {
            FoodList[i].SetStatusFreeze(!FoodList[i].GetStatusFreeze());
        }
        B_Freeze[i].Free();
    }
}

void Menu::CheckRemove(SDL_Event events, List<FoodAndDrink>& MenuFood)
{
    //Check Remove
    for (int i = 0; i < this->FoodList.Size(); i++)
    {
        if (this->FoodList[i].GetMenuPage() == this->CurrentPage && B_Remove[i].CheckMouse(events))
        {
            if (MenuFood.isEmpty())
                RemoveFood(i);
            else MessageBox(NULL, L"Hãy Reset Order Trước Khi Xoá Món Ăn", L"Thông Báo", MB_OK | MB_ICONSTOP);
            break;
        }
        else B_Remove[i].Free();
    }
}

void Menu::RemoveFood(const int& index)
{
    //Remove trên Lists
    this->FoodList.Pop(index);
    this->B_Freeze.Pop(index);
    this->B_Remove.Pop(index);

    //Remove trên CSDL
    std::ofstream outFile;
    outFile.open(CSDL, std::ios::trunc);
    if (!outFile)
    {
        return;
    }

    for (int i = 0; i < this->FoodList.Size(); i++)
        outFile << this->FoodList[i].GetItem() << ';' << this->FoodList[i].GetName() << ';' << this->FoodList[i].GetType() << ';' << this->FoodList[i].GetPrice() << std::endl;
    outFile.close();
}

void Menu::ShowButtonAddFood(SDL_Renderer* des)
{
    this->B_AddMoreFood.LoadImg(Button_Add_Food, des);
    this->B_AddMoreFood.Render(des);
}

bool Menu::CheckAddMoreFood(SDL_Event events)
{
    if (this->B_AddMoreFood.CheckMouse(events))
        this->status_add_food = true;

    return this->status_add_food;
}

void Menu::ShowBgAddFood(BaseObject& Add_bg, SDL_Renderer* des)
{
    if (this->status_add_food)
    {
        Text Name;
        Text Item;
        Text Type;
        Text Price;

        //show background
        Add_bg.Render(des, NULL);

        //show button close
        this->B_CloseAddMoreFood.LoadImg(Button_Remove, des);
        this->B_CloseAddMoreFood.Render(des);

        //show button addFood
        this->B_AddFood.LoadImg(Button_Add_Food, des);
        this->B_AddFood.Render(des);

        // show button poiter
        this->B_Poiter.LoadImg(Button_Poiter, des);
        this->B_Poiter.Render(des);

        //show text
        Name.SetText(this->name);
        if (Name.LoadFromRenderText(font_text1, des))
            Name.RendererText(des, 535, 175);
        Item.SetText(this->item);
        if (Item.LoadFromRenderText(font_text1, des))
            Item.RendererText(des, 535, 280);
        Type.SetText(this->type);
        if (Type.LoadFromRenderText(font_text1, des))
            Type.RendererText(des, 535, 384);
        Price.SetText(this->price);
        if (Price.LoadFromRenderText(font_text1, des))
            Price.RendererText(des, 535, 490);
    }
}

bool Menu::CheckCloseAddFood(SDL_Event events)
{
    if (this->B_CloseAddMoreFood.CheckMouse(events))
    {
        this->status_add_food = false;
        ClearAddFood();
        return true;
    }
    else if (this->B_AddFood.CheckMouse(events))
    {
        if (AddMoreFood())
        {
            this->status_add_food = false;
            return true;
        }
        else return false;
    }
    else return false;
}

void Menu::CheckEnter(SDL_Event events, const int& enter)
{
    if (events.type == SDL_KEYDOWN)
    {
        if (enter != -1 && enter != 0 && enter != 4)
        {
            std::string& selectedText = (enter == 1) ? this->name : (enter == 2) ? this->item : this->type;

            SDL_Keycode sym = events.key.keysym.sym;
            SDL_Keymod mod = SDL_GetModState();

            // Kiểm tra xem Shift, Caps Lock hay Num Lock có được bật không
            bool isShiftPressed = (mod & KMOD_SHIFT) != 0;
            bool isCapsLockOn = (mod & KMOD_CAPS) != 0;
            bool isNumLockOn = (mod & KMOD_NUM) != 0;

            // Xác định ký tự được nhấn dựa trên Shift và Caps Lock
            char pressedChar = 0;
            if (sym == SDLK_SPACE || sym >= SDLK_a && sym <= SDLK_z)
            {
                pressedChar = static_cast<char>(isShiftPressed || isCapsLockOn ? toupper(sym) : tolower(sym));
            }

            if (pressedChar != 0)
            {
                // Trả về ký tự
                if (selectedText.size() < 10)
                    selectedText += pressedChar;
                else
                    MessageBox(NULL, L"Quá nhiều kí tự", L"Thông Báo", MB_OK | MB_ICONSTOP);
            }
            else if (sym == SDLK_BACKSPACE && !selectedText.empty())
            {
                selectedText.pop_back();
            }
        }
        else if (enter == 4)
        {
            SDL_Keycode sym = events.key.keysym.sym;
            if (sym >= SDLK_0 && sym <= SDLK_9)
            {
                if (this->price.size() < 7)
                    this->price += static_cast<char>(sym);
                else MessageBox(NULL, L"Quá nhiều kí tự", L"Thông Báo", MB_OK | MB_ICONSTOP);
            }
            else if (sym == SDLK_BACKSPACE && !this->price.empty())
            {
                this->price.pop_back();
            }
            else
            {
                MessageBox(NULL, L"Hãy Nhập Số!!!!", L"Thông Báo", MB_OK | MB_ICONSTOP);
            }
        }
    }
}

int Menu::CheckLocationAddFood(SDL_Event events)
{
    int xm = 0;
    int ym = 0;
    if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {
        SDL_GetMouseState(&xm, &ym);
        if ((xm >= 530 && xm <= 965) &&
            (ym >= 175 && ym <= 214))
        {
            this->B_Poiter.SetButtonRect(510, 185);
            return 1;
        }
        else if ((xm >= 530 && xm <= 965) &&
            (ym >= 280 && ym <= 318))
        {
            this->B_Poiter.SetButtonRect(510, 290);
            return 2;
        }
        else if ((xm >= 530 && xm <= 965) &&
            (ym >= 384 && ym <= 423))
        {
            this->B_Poiter.SetButtonRect(510, 394);
            return 3;
        }
        else if ((xm >= 530 && xm <= 965) &&
            (ym >= 490 && ym <= 530))
        {
            this->B_Poiter.SetButtonRect(510, 500);
            return 4;
        }
        else
        {
            this->B_Poiter.SetButtonRect(-10, -10);
            return 0;
        }
    }
    else return -1;
}

void Menu::ClearAddFood()
{
    this->name.clear();
    this->item.clear();
    this->type.clear();
    this->price.clear();
}

bool Menu::AddMoreFood()
{
    if (this->name.empty() || this->item.empty() || this->type.empty() || this->price.empty())
    {
        MessageBox(NULL, L"Dữ Liệu Sai!!!", L"Thông Báo", MB_OK | MB_ICONSTOP);
        return false;
    }
    else
    {
        // Mở file bằn hàm ofstream và add món ăn vào FoodList
        std::ofstream outFile;
        outFile.open(CSDL, std::ios::app);
        if (!outFile)
        {
            return false;
        }
        outFile << std::endl << this->item << ';' << this->name << ';' << this->type << ';' << this->price;
        outFile.close();

        //add vào vector foodlist
        FoodAndDrink F;
        Button B_tmp;
        F.SetName(this->name);
        F.SetItem(this->item);
        int p_tmp = std::stoi(this->price);
        F.SetPrice(p_tmp);
        F.SetType(this->type);
        this->FoodList.Push(F);
        //Add Button Freeze
        this->B_Freeze.Push(B_tmp);
        //Add Button Remove
        this->B_Remove.Push(B_tmp);
        B_tmp.Free();
        if (FoodList.Size() % NUMBER_OF_MENU_ON_SCREEN == 0)
            AllPage = (FoodList.Size() / NUMBER_OF_MENU_ON_SCREEN) - 1;
        else AllPage = (FoodList.Size() / NUMBER_OF_MENU_ON_SCREEN);

        //Clear
        ClearAddFood();

        return true;
    }

}