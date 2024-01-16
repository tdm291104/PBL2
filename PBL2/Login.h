#ifndef LOGIN_H_
#define LOGIN_H_

#include "CommonFunc.h"
#include "Button.h"
#include "Text.h"

struct Account
{
    std::string Ma_NV;
    std::string Tai_Khoan;
    std::string Mat_Khau;
};


class Login
{
private:
    List<Account> A_list;

    std::string MaNV;
    std::string TaiKhoan;
    std::string MatKhau;
    std::string Hide_MatKhau;

    Button B_Login;
    Button B_Poiter;
    Button B_HideMK;

    bool status_hideMK;

    TTF_Font* font_text;
public:
    Login();
    ~Login();

    bool AddList();

    std::string getMaNV()const;

    void setTK(const std::string);

    void setMK(const std::string);

    bool CheckAcc();

    void ShowBgLogin(BaseObject&, SDL_Renderer*);
    int CheckLocationLogin(SDL_Event);
    void CheckEnter(SDL_Event, const int&);
    bool CheckLogin(SDL_Event);

    void CheckHideMk(SDL_Event);
};

#endif