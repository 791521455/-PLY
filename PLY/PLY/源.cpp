#include <iostream>
#include <windows.h>

using namespace std;

#define FONT_SIZE 30
#define FONT_FAMILY L"Consolas"

int main(void) {
	//******************设置颜色为蓝色文本，红色背景
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | BACKGROUND_GREEN); // 设置颜色为蓝色文本，红色背景
	//******************
	int mou_x, mou_y;
	float time_stop, time_stay, time_times;
	char mod_click;
	unsigned int sleepTime=1;
	//******************
	cout << "v1.10更新日志：" << endl << " 1.LW修复" << endl << " 2.修复间隔时间（s）不能为小数的问题" << endl << " 3.默认点击时间（s）为100" << endl << " 4.增加了模式如下：" << endl << "      a.输入a为默认点击时间0.1s=100ms" << endl << "      b.输入b为自定义点击时间/s"<<endl;
	//******************
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	cout << "v1.10    翁培杰 专 用 连 点 器" << endl;
	//cout << "建议 点击时间 设置为0.1"<<endl;
	cout << "输入模式 a.默认 b.自定义" << endl;
	cin >> mod_click;
	//******************
	if (mod_click == 'A' || mod_click == 'a') {
		cout << "输入间隔时间 (s)：";
		cin >> time_stop;
		cout << "输入连点次数：";
		cin >> time_times;
		time_stay = 100;
		unsigned int sleepTime = 1000 * time_stop;
	}
	else if (mod_click == 'B' || mod_click == 'b') {
		cout << "输入间隔时间 (s)：";
		cin >> time_stop;
		cout << "输入点击时间（ms)：";
		cin >> time_stay;
		cout << "输入连点次数：";
		cin >> time_times;
		unsigned int sleepTime = 1000 * time_stop; // 休眠t/ms
	}
	//******************
	POINT mou_p;
	for (int i = 0;i < time_times;i++) {
		Sleep(static_cast<DWORD>(sleepTime));
		GetCursorPos(&mou_p);
		mou_x = mou_p.x;
		mou_y = mou_p.y;
		std::cout << "Current mouse position: (" << mou_x << ", " << mou_y << ")" << std::endl;

		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(static_cast<DWORD>(time_stay));
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

	//SetCursorPos(mou_x, mou_y);
	
	cin >> time_times;
	return 0;
}