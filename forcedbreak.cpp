#include <iostream>
//#include <chrono>
//#include <ctime>
#include <thread>
//#include <iomanip>
//#include <sstream>
#include <Windows.h>
//#include <string>
//#include <fstream>

bool debugging = false;
std::wstring windowTitle = L"Fidelity Active Trader Pro";
HWND consoleWindow = GetConsoleWindow();
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void bringToFront() {

	ShowWindow(consoleWindow, SW_NORMAL);
	SetForegroundWindow(consoleWindow);
}

bool marketOpen() {

	if (debugging) {
		std::cout << "Market Open. Debugging." << std::endl;
		return true;
	}

	std::time_t currentTime = std::time(nullptr);
	std::tm localTime{};
	localtime_s(&localTime, &currentTime);

	int currentDay = localTime.tm_wday;  // Sunday = 0, Monday = 1, ..., Saturday = 6
	int currentHour = localTime.tm_hour;

	// Check if it's a weekday (Monday to Friday) and between 6am and 1pm
	if (currentDay >= 1 && currentDay <= 5 && currentHour >= 6 && currentHour < 13) {
		return true;
	}

	return false;
}

BOOL CtrlHandler(DWORD fdwCtrlType) {
	if (fdwCtrlType == CTRL_CLOSE_EVENT && marketOpen()) {
		// Abort any previous shutdowns
		system("shutdown /a");

		// Perform shutdown when the user closes the console window
		system("shutdown /s /t 0");
		return TRUE;
	}
	return FALSE;
}

void clear() {
	// Clear the console screen
	if (!debugging) {
		std::system("cls");
	}
	else {
		std::cout << "Clear. Debugging." << std::endl;
	}
}

bool isTimeMatch(const std::tm& time, int targetHour, int targetMinute) {
	return (time.tm_hour == targetHour) && (time.tm_min == targetMinute);
}

void restoreFidy() {
	HWND targetWindow = FindWindow(nullptr, windowTitle.c_str());
	if (targetWindow != nullptr) {
		ShowWindow(targetWindow, SW_RESTORE);
		SetForegroundWindow(targetWindow);
	}
	else {
	}
}

void minimizeFidy() {
	HWND targetWindow = FindWindow(nullptr, windowTitle.c_str());
	if (targetWindow != nullptr) {
		ShowWindow(targetWindow, SW_MINIMIZE);
	}
	else {
	}
}

int main() {
	if (!marketOpen()) {
		std::cout << "Market is closed." << std::endl;

		return 0;
	}

	//This will shut down your computer when the window is closed.
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)) {
		std::cerr << "Error: Could not set control handler." << std::endl;

		return 1;
	}

	while (marketOpen()) {
		std::time_t now = std::time(nullptr);
		std::tm local_time = {};
		localtime_s(&local_time, &now);
		local_time.tm_sec = 0;

		//forced break
		if (local_time.tm_hour == 6 && local_time.tm_min >= 0 &&
			local_time.tm_hour == 6 && local_time.tm_min <= 59) {
			minimizeFidy();
		}
		else if (isTimeMatch(local_time, 7, 0)) {
			restoreFidy();
			std::this_thread::sleep_for(std::chrono::minutes(1));
		}


		else if (local_time.tm_hour == 8 && local_time.tm_min >= 0 &&
			local_time.tm_hour == 8 && local_time.tm_min <= 59) {
			minimizeFidy();
		}
		else if (isTimeMatch(local_time, 9, 0)) {
			restoreFidy();
			std::this_thread::sleep_for(std::chrono::minutes(1));
		}


		else if (local_time.tm_hour == 9 && local_time.tm_min >= 30 &&
			local_time.tm_hour == 9 && local_time.tm_min <= 59) {
			minimizeFidy();
		}
		else if (isTimeMatch(local_time, 10, 0)) {
			restoreFidy();
			std::this_thread::sleep_for(std::chrono::minutes(1));
		}


		else if (local_time.tm_hour == 10 && local_time.tm_min >= 30 &&
			local_time.tm_hour == 10 && local_time.tm_min <= 59) {
			minimizeFidy();
		}
		else if (isTimeMatch(local_time, 11, 0)) {
			restoreFidy();
			std::this_thread::sleep_for(std::chrono::minutes(1));
		}


		else if (local_time.tm_hour == 11 && local_time.tm_min >= 30 &&
			local_time.tm_hour == 11 && local_time.tm_min <= 59) {
			minimizeFidy();
		}
		else if (isTimeMatch(local_time, 12, 0)) {
			restoreFidy();
			std::this_thread::sleep_for(std::chrono::minutes(1));
		}


		else if (local_time.tm_hour == 12 && local_time.tm_min >= 30 &&
			local_time.tm_hour == 12 && local_time.tm_min <= 59) {
			minimizeFidy();
		}
		else if (isTimeMatch(local_time, 13, 0)) {
			restoreFidy();
			std::this_thread::sleep_for(std::chrono::minutes(1));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	clear();
	std::cout << "Market is closed." << std::endl;

	return 0;
}