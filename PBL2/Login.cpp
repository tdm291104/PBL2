#include "Login.h"

Login::Login()
{
    this->MaNV = "";
    this->TaiKhoan = "";
    this->MatKhau = "";
    this->Hide_MatKhau = "";
    this->B_HideMK.SetButtonRect(970, 460);
    this->B_Login.SetButtonRect(588, 539);
    this->status_hideMK = true;
    this->font_text = TTF_OpenFont(Text_Font, 30);
}

Login::~Login()
{
    B_Login.Free();
    B_Poiter.Free();
    B_HideMK.Free();
    TTF_CloseFont(font_text);
}

bool Login::AddList()
{
    // Mở file bằn hàm ifstream và add account vào A_list
    std::ifstream inFile;
    inFile.open(Account_file);
    if (!inFile.is_open())
    {
        return false;
    }

    std::string Ma;
    std::string TK;
    std::string MK;

    std::string line;
    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        if (!ss)
            return false;
        // Tách thông tin dựa trên dấu ";"
        std::getline(ss, Ma, ';');
        std::getline(ss, TK, ';');
        std::getline(ss, MK, ';');

        Account A;
        A.Ma_NV = Ma;
        A.Tai_Khoan = TK;
        A.Mat_Khau = MK;
        this->A_list.Push(A);
    }

    return true;
}

std::string Login::getMaNV()const
{
    return this->MaNV;
}

void Login::setTK(const std::string tk)
{
    this->TaiKhoan = tk;
}

void Login::setMK(const std::string mk)
{
    this->MatKhau = mk;
}

bool Login::CheckAcc()
{
    for (int i = 0; i < this->A_list.Size(); i++)
    {
        if (this->TaiKhoan == A_list[i].Tai_Khoan && this->MatKhau == A_list[i].Mat_Khau)
        {
            this->MaNV = A_list[i].Ma_NV;
            return true;
        }
    }
    return false;
}

void Login::ShowBgLogin(BaseObject& Login_bg, SDL_Renderer* des)
{
    Text TK;
    Text MK;

    //show background
    Login_bg.Render(des, NULL);

    //show button Login
    this->B_Login.LoadImg(Button_Login, des);
    this->B_Login.Render(des);

    // show button poiter
    this->B_Poiter.LoadImg(Button_Poiter, des);
    this->B_Poiter.Render(des);

    // show button Hide MK
    this->B_HideMK.LoadImg(Button_HideMK, des);
    this->B_HideMK.Render(des);

    //show text
    TK.SetText(this->TaiKhoan);
    if (TK.LoadFromRenderText(font_text, des))
        TK.RendererText(des, 400, 350);

    if (this->status_hideMK)
        MK.SetText(this->Hide_MatKhau);
    else MK.SetText(this->MatKhau);
    if (MK.LoadFromRenderText(font_text, des))
        MK.RendererText(des, 400, 465);
}

int Login::CheckLocationLogin(SDL_Event events)
{
    int xm = 0;
    int ym = 0;
    if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {
        SDL_GetMouseState(&xm, &ym);
        if ((xm >= 395 && xm <= 1025) &&
            (ym >= 340 && ym <= 400))
        {
            this->B_Poiter.SetButtonRect(370, 370);
            return 1;
        }
        else if ((xm >= 395 && xm <= 1025) &&
            (ym >= 455 && ym <= 515))
        {
            this->B_Poiter.SetButtonRect(370, 485);
            return 2;
        }
        else
        {
            this->B_Poiter.SetButtonRect(-10, -10);
            return 0;
        }
    }
    else return -1;
}

void Login::CheckEnter(SDL_Event events, const int& enter)
{
    if (events.type == SDL_KEYDOWN)
    {
        if (enter != -1 && enter != 0)
        {
            std::string& selectedText = (enter == 1) ? this->TaiKhoan : this->MatKhau;

            SDL_Keycode sym = events.key.keysym.sym;
            SDL_Keymod mod = SDL_GetModState();

            // Kiểm tra xem Shift, Caps Lock hay Num Lock có được bật không
            bool isShiftPressed = (mod & KMOD_SHIFT) != 0;
            bool isCapsLockOn = (mod & KMOD_CAPS) != 0;
            bool isNumLockOn = (mod & KMOD_NUM) != 0;

            // Xác định ký tự được nhấn dựa trên Shift và Caps Lock
            char pressedChar = 0;
            if (sym == SDLK_SPACE || sym >= SDLK_a && sym <= SDLK_z || sym >= SDLK_0 && sym <= SDLK_9)
            {
                pressedChar = static_cast<char>(isShiftPressed || isCapsLockOn ? toupper(sym) : tolower(sym));
            }

            if (pressedChar != 0)
            {
                // Trả về ký tự
                if (selectedText.size() < 10)
                {
                    selectedText += pressedChar;
                    if (enter == 2)
                        this->Hide_MatKhau.push_back('*');
                }
                else
                    MessageBox(NULL, L"Quá nhiều kí tự", L"Thông Báo", MB_OK | MB_ICONSTOP);
            }
            else if (sym == SDLK_BACKSPACE && !selectedText.empty())
            {
                selectedText.pop_back();
                if (enter == 2)
                    this->Hide_MatKhau.pop_back();
            }
        }
    }
}

void Login::CheckHideMk(SDL_Event events)
{
    if (this->B_HideMK.CheckMouse(events))
        this->status_hideMK = !this->status_hideMK;
}

bool Login::CheckLogin(SDL_Event events)
{
    if (B_Login.CheckMouse(events))
    {
        if (!CheckAcc())
        {
            this->MaNV = "";
            this->TaiKhoan = "";
            this->MatKhau = "";
            this->Hide_MatKhau = "";
            MessageBox(NULL, L"Sai Tai Khoan Hoac Mat Khau!!!", L"Thông Báo", MB_OK | MB_ICONSTOP);
            return false;
        }
        else
        {
            this->TaiKhoan = "";
            this->MatKhau = "";
            this->Hide_MatKhau = "";
            MessageBox(NULL, L"Đăng Nhập Thành Công", L"Thông Báo", MB_OK | MB_ICONSTOP);
            return true;
        }
    }
    else return false;
}