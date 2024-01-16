#include "Shift.h"

Shift::Shift(std::string time_check_in) : CheckIn(time_check_in)
{
	this->shift_number = 0;
	this->B_Logout.SetButtonRect(650, 755);
	this->B_Current_Shift.SetButtonRect(650, 58);
	this->B_Shift1_Choose.SetButtonRect(350, 400);
	this->B_Shift2_Choose.SetButtonRect(650, 400);
	this->B_Shift3_Choose.SetButtonRect(950, 400);
	this->CheckOut = "";
	this->TotalPriceOfShift = 0;
}

Shift::~Shift()
{

}

void Shift::ShowShift(SDL_Renderer* des)
{
	this->B_Current_Shift.LoadImg(Button_Shift + std::to_string(this->shift_number) + ".png", des);
	this->B_Current_Shift.Render(des);

	this->B_Logout.LoadImg(Button_Logout, des);
	this->B_Logout.Render(des);
}

bool Shift::CheckSelectShift(SDL_Event events, std::string time, std::string date)
{
	if (this->B_Shift1_Choose.CheckMouse(events))
	{
		MessageBox(NULL, L"Đã Chọn Ca 1", L"Thông Báo", MB_OK | MB_ICONSTOP);
		//set time check in
		this->CheckIn = time;

		return this->shift_number = SHIFT::Shift_1;
	}
	else if (this->B_Shift2_Choose.CheckMouse(events))
	{
		MessageBox(NULL, L"Đã Chọn Ca 2", L"Thông Báo", MB_OK | MB_ICONSTOP);
		//set time check in
		this->CheckIn = time;

		return this->shift_number = SHIFT::Shift_2;
	}
	else if (this->B_Shift3_Choose.CheckMouse(events))
	{
		MessageBox(NULL, L"Đã Chọn Ca 3", L"Thông Báo", MB_OK | MB_ICONSTOP);
		//set time check in
		this->CheckIn = time;

		return this->shift_number = SHIFT::Shift_3;
	}

	return false;
}

bool Shift::CheckCloseSelectShift(SDL_Event events, std::string time, std::string date)
{
	if (CheckSelectShift(events, time, date))
		return true;

	return false;
}

bool Shift::CheckLogout(SDL_Event events, std::string time, std::string date, std::string MaNV)
{
	if (this->B_Logout.CheckMouse(events))
	{
		AddToFile(time, date, MaNV);
		MessageBox(NULL, L"Đăng Xuất Thành Công!!!", L"Thông Báo", MB_OK | MB_ICONSTOP);
		return true;
	}
	else return false;
}

void Shift::ShowBgSelectShift(BaseObject& CS_bg, SDL_Renderer* des)
{
	//show background
	CS_bg.Render(des, NULL);

	//show button Shift
	this->B_Shift1_Choose.LoadImg(Button_Shift1, des);
	this->B_Shift1_Choose.Render(des);

	this->B_Shift2_Choose.LoadImg(Button_Shift2, des);
	this->B_Shift2_Choose.Render(des);

	this->B_Shift3_Choose.LoadImg(Button_Shift3, des);
	this->B_Shift3_Choose.Render(des);
}

void Shift::AddPrice(const int& price)
{
	this->TotalPriceOfShift += price;
}

void Shift::AddToFile(std::string time, std::string date, std::string MaNV)
{
	this->CheckOut = time;
	std::ofstream outFile;
	outFile.open(Payment_History + date + ".txt", std::ios::app);
	if (!outFile)
	{
		return;
	}

	outFile << "******************************************" << std::endl;
	outFile << "Ket Thuc CA: " << this->shift_number << std::endl;
	outFile << "Nhan Vien: " << MaNV << std::endl;
	outFile << "Gio Check In: " << this->CheckIn << std::endl;
	outFile << "Gio Check Out: " << this->CheckOut << std::endl;
	outFile << "Tong Tien: " << this->TotalPriceOfShift << std::endl;

	//reset
	this->TotalPriceOfShift = 0;
}