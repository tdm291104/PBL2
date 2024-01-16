#include "BaseObject.h"
#include "CommonFunc.h"
#include "FoodAndDrink.h"
#include "Text.h"
#include "MenuOfAdmin.h"
#include "Order.h"
#include "Shift.h"
#include "Login.h"
#undef main

BaseObject PBL2_background;
BaseObject Login_Background;
BaseObject g_background;
BaseObject Bill_Background;
BaseObject Add_Food_Background;
BaseObject Choose_Shift_Background;
TTF_Font* font = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);

    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("PBL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }

    if (TTF_Init() == -1)
        success = false;

    font = TTF_OpenFont(Text_Font, 25);
    if (font == NULL)
        success = false;

    return success;
}

bool LoadBackground()
{
    bool ret1 = g_background.LoadImg(Background_name, g_screen);
    bool ret2 = Bill_Background.LoadImg(Background_Bill, g_screen);
    Bill_Background.SetRect(500, 40);
    bool ret3 = Add_Food_Background.LoadImg(Background_AddFood, g_screen);
    Add_Food_Background.SetRect(500, 100);
    bool ret4 = Choose_Shift_Background.LoadImg(Background_ChooseShift, g_screen);
    bool ret5 = PBL2_background.LoadImg(Background_Pbl2, g_screen);
    bool ret6 = Login_Background.LoadImg(Background_Login, g_screen);

    return (ret1 && ret2 && ret3 && ret5 && ret6);
}

void CreatNewFile(std::string name_file)
{
    std::ofstream outfile(Payment_History + name_file + ".txt");
    if (outfile.is_open()) {
        std::cout << "File created successfully." << std::endl;
        outfile.close();
    }
    else {
        std::cout << "Error creating file." << std::endl;
    }
}

bool CheckFile(std::string name_file)
{
    std::string file_name = Payment_History + name_file + ".txt";
    std::ifstream infile(file_name);
    if (infile.good())
        return true;
    else return false;
}

std::string GetRealTime()
{
    std::locale::global(std::locale("vi_VN.UTF-8"));
    auto currentTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);

    // Sử dụng struct tm để trích xuất ngày và giờ
    struct std::tm now;
    localtime_s(&now, &time);

    // Lấy ngày
    std::string year = std::to_string(now.tm_year + 1900);  // Năm hiện tại
    std::string month; // Tháng hiện tại
    if (now.tm_mon + 1 < 10)
        month = '0' + std::to_string(now.tm_mon + 1);
    else month = std::to_string(now.tm_mon + 1);

    std::string day; // Ngày hiện tại
    if (now.tm_mday < 10)
        day = '0' + std::to_string(now.tm_mday);
    else day = std::to_string(now.tm_mday);

    // Lấy giờ
    std::string hour; // Giờ hiện tại
    if (now.tm_hour < 10)
        hour = '0' + std::to_string(now.tm_hour);
    else  hour = std::to_string(now.tm_hour);

    std::string minute;        // Phút hiện tại
    if (now.tm_min < 10)
        minute = '0' + std::to_string(now.tm_min);
    else minute = std::to_string(now.tm_min);

    std::string second;        // Giây hiện tại
    if (now.tm_sec < 10)
        second = '0' + std::to_string(now.tm_sec);
    else second = std::to_string(now.tm_sec);

    std::string D_M_Y = day + '/' + month + '/' + year;
    std::string H_M_S = hour + ':' + minute + ':' + second;

    return D_M_Y + ' ' + H_M_S;
}

std::string GetRealDate()
{
    std::locale::global(std::locale("vi_VN.UTF-8"));
    auto currentTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);

    // Sử dụng struct tm để trích xuất ngày và giờ
    struct std::tm now;
    localtime_s(&now, &time);

    // Lấy ngày
    std::string year = std::to_string(now.tm_year + 1900);  // Năm hiện tại
    std::string month; // Tháng hiện tại
    if (now.tm_mon + 1 < 10)
        month = '0' + std::to_string(now.tm_mon + 1);
    else month = std::to_string(now.tm_mon + 1);

    std::string day; // Ngày hiện tại
    if (now.tm_mday < 10)
        day = '0' + std::to_string(now.tm_mday);
    else day = std::to_string(now.tm_mday);

    std::string D_M_Y = day + '_' + month + '_' + year;
    return D_M_Y;
}

void Close()
{
    g_background.Free();
    Bill_Background.Free();
    Add_Food_Background.Free();
    Choose_Shift_Background.Free();
    PBL2_background.Free();
    Login_Background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{

    if (InitData() == false)
        return -1;

    if (LoadBackground() == false)
        return -1;

    //make Account
    Login Account;
    if (!Account.AddList())
        return -1;

    //make Menu
    MenuOfAdmin menu;
    if (!menu.Add())
        return -1;
    //make Order
    Order order;

    //make Folder để lưu lịch sử thanh toán
    if (!CheckFile(GetRealDate()))
        CreatNewFile(GetRealDate());

    //make Shift
    Shift shift(GetRealTime());

    //make Real Time
    Text RealTime;
    RealTime.SetColor(Text::RED_TEXT);

    int paused = PAUSE::not_pause;
    int status = STATUS::background;
    bool is_quit = false;
    int enter_addfood = 0;
    int enter_login = 0;
    Uint32 frame_start = 0;
    int frame_time = 0;
    std::string Payment_time;
    while (!is_quit)
    {
        frame_start = SDL_GetTicks();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            if (status == STATUS::background)
            {
                if (g_event.type == SDL_KEYDOWN)
                    status = STATUS::login;
            }
            else if (status == STATUS::login)
            {
                if (paused == PAUSE::not_pause)
                {
                    if (Account.CheckLocationLogin(g_event) != -1)
                        enter_login = Account.CheckLocationLogin(g_event);
                    Account.CheckEnter(g_event, enter_login);
                    Account.CheckHideMk(g_event);
                    if (Account.CheckLogin(g_event))
                        paused = PAUSE::pause_choose_shift;
                }
                else if (paused == PAUSE::pause_choose_shift)
                {
                    if (shift.CheckCloseSelectShift(g_event, GetRealTime(), GetRealDate()))
                    {
                        paused = PAUSE::not_pause;
                        status = STATUS::runApp;
                    }
                }
            }
            else
            {
                List<FoodAndDrink>& MenuFood = menu.GetList();
                List<FoodAndDrink>& OrderFood = order.GetList();

                if (paused == PAUSE::not_pause)
                {
                    menu.CheckPage(g_event);
                    menu.CheckFreeze(g_event);
                    if (menu.CheckAddMoreFood(g_event))
                        paused = PAUSE::pause_add_food;
                    menu.CheckRemove(g_event, OrderFood);

                    order.CheckPage(g_event);
                    order.ChangeQuantityFood(g_event);
                    order.RemoveFood(g_event, MenuFood);
                    order.AddFood(g_event, MenuFood, menu.GetCurrentPage());
                    Payment_time = GetRealTime();
                    if (order.CheckPayment(g_event, g_screen, Payment_time, shift.GetShiftNumber(), shift, GetRealDate(), Account.getMaNV()))
                        paused = PAUSE::pause_payment;

                    if (shift.CheckLogout(g_event, GetRealTime(), GetRealDate(), Account.getMaNV()))
                    {
                        menu.SetDefaultCurrentPage();
                        status = STATUS::login;
                    }
                }
                else if (paused == PAUSE::pause_payment)
                {
                    order.CheckPageOfBill(g_event);
                    if (order.Check_Close(g_event, MenuFood))
                        paused = PAUSE::not_pause;
                }
                else if (paused == PAUSE::pause_add_food)
                {
                    if (menu.CheckLocationAddFood(g_event) != -1)
                        enter_addfood = menu.CheckLocationAddFood(g_event);
                    menu.CheckEnter(g_event, enter_addfood);
                    if (menu.CheckCloseAddFood(g_event))
                        paused = PAUSE::not_pause;
                }
            }
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        if (status == STATUS::background)
        {
            PBL2_background.Render(g_screen, NULL);
            SDL_RenderPresent(g_screen);
        }
        else if (status == STATUS::login)
        {
            Account.ShowBgLogin(Login_Background, g_screen);
            if (paused == PAUSE::pause_choose_shift)
                shift.ShowBgSelectShift(Choose_Shift_Background, g_screen);
            SDL_RenderPresent(g_screen);
        }
        else
        {
            g_background.Render(g_screen, NULL);

            shift.ShowShift(g_screen);

            menu.ShowPage(g_screen);
            menu.DisplayMenu(g_screen);
            menu.ShowButtonAddFood(g_screen);

            order.ShowTotalPrice(160, 752, g_screen);
            order.ShowPage(g_screen);
            order.ShowPayment(g_screen);
            order.DisplayOrder(g_screen);
            order.ShowBill(Bill_Background, g_screen, Payment_time);

            menu.ShowBgAddFood(Add_Food_Background, g_screen);

            //Show Real Time
            std::string Real_time = GetRealTime();
            RealTime.SetText(Real_time);
            RealTime.LoadFromRenderText(font, g_screen);
            RealTime.RendererText(g_screen, SCREEN_WIDTH - 230, 10);

            SDL_RenderPresent(g_screen);

            //kiểm soát tốc độ cập nhật
            frame_time = SDL_GetTicks() - frame_start;
            if (frame_time < FRAME_DELAY)
            {
                SDL_Delay(FRAME_DELAY - frame_time);
            }
        }
    }

    //Check out ca làm việc cuối khi chưa đăng xuất
    if (status == STATUS::runApp)
        shift.AddToFile(GetRealTime(), GetRealDate(), Account.getMaNV());

    Close();

    return 0;
}