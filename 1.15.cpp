
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//cmd窗口配置
#define FONT_SIZE 30
#define FONT_FAMILY L"Consolas"
//cmd_size
bool SetSize(int width, int height)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出句柄
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; //设置宽高
	bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // 设置窗体尺寸
	if (!ret) return false;
	COORD coord = { width, height };
	ret = SetConsoleScreenBufferSize(hOutput, coord); // 设置缓冲尺寸
	return ret;
}

void cmd_ctrl() {
	HWND hWnd = GetConsoleWindow(); //获取窗口句柄
	LONG_PTR sty = GetWindowLongPtrA(hWnd, GWL_STYLE); //获取窗口样式
	sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; //去除可变化大小,最大,最小化按钮,~是取反,&是与,这是位运算相关的知识了
	SetWindowLongPtrA(hWnd, GWL_STYLE, sty); //设置窗体不可更改大小,不可最大化
}

void cmd_color(int i) {
	//0.默认//1.设置颜色为蓝色文本，红色背景//2.new
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (i == 1) {
		//设置颜色为蓝色文本，红色背景
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | BACKGROUND_GREEN);
	}
	else if (i == 0) {
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else if (i == 2) {
		system("color 0D"); //设置背景为黑色,字体为淡红色
	}
}

void note_cout() {
	SetConsoleTitleA("鼠标模拟器");
	//Sleep(300);
	//system("title 标题"); //设置一个新标题
	cout << "v1.15更新日志：" << endl 
		<< " 1.NAME" << endl 
		<< " 2.修复间隔时间错误" << endl 
		<< " 3.修复点击时间错误" << endl 
		<< " 4.增加了模式如下：" << endl
		<< "     a.输入a为默认点击时间" << endl 
		<< "     b.输入b为自定义点击时间" << endl
		<< "     c.输入3为DEBUG"<<endl
		<< "     d.输入4.5体验测试功能" << endl
		<< "5.自己看吧"<<endl;
}

void title_cout(int i) {
	//0.title
	if (i == 0) {
		cout << "v1.10 MOUSE_BOSS" << endl;
	}
}

int mode_cin() {
	char mode;
	//cout << "建议 点击时间 设置为0.1"<<endl;
	cout << "输入模式 a.默认 b.自定义" << endl;
	cin >> mode;
	return mode;
}

/*struct IMFOO {
	int t_w;//time_wait
	int t_s;//time_stay
	int t_s;//time_times
	unsigned int sleepTime = 1000 * t_s; // 休眠t/ms
};*/

int main(void) {
	int mou_x, mou_y;
	//float time_stop, time_stay, time_times;
	int time_stop;
	int time_times;
	int time_stay;
	char mode;
	unsigned int sleepTime = 1;
	SetSize(40, 20);//50.40

	cmd_color(2);
	note_cout();
	cmd_color(0);
	title_cout(0);
here:
	mode = mode_cin();
	
	if (mode == 'A' || mode == 'a') {
		cout << "输入间隔时间 (s)：";
		cin >> time_stop;
		cout << "输入连点次数：";
		cin >> time_times;
		time_stay = 100;
		//unsigned int sleepTime = 1000 * time_stop;
	}
	else if (mode == 'B' || mode == 'b') {
		cout << "输入间隔时间 (s)：";
		cin >> time_stop;
		cout << "输入点击时间（ms)：";
		cin >> time_stay;
		cout << "输入连点次数：";
		cin >> time_times;
		//unsigned int sleepTime = 1000 * time_stop; // 休眠t/ms
	}
	else if (mode == '3') {
		time_stop=3;
		time_times = 5;
		time_stay = 100;
	}
	else if (mode == '4') {
		cmd_ctrl();
		cout << "去除可变化大小,最大,最小化按钮,设置窗体不可更改大小,不可最大化";
		goto here;
	}
	else if (mode == '5') {
		while (1) {
			Sleep(3000);
			POINT mou_p;
			GetCursorPos(&mou_p);
			mou_x = mou_p.x;
			mou_y = mou_p.y;
			std::cout << "Current mouse position: (" << mou_x << ", " << mou_y << ")" << std::endl;
		}
		goto here;
	}
	else if (mode == '6') {
		cmd_ctrl();
		cout << "去除可变化大小,最大,最小化按钮,设置窗体不可更改大小,不可最大化";
		goto here;
	}
	sleepTime = 1000 * time_stop;

	//printf("time_stop=%d,time_times=%d,time_stay=%d,sleepTime=%d\n", time_stop, time_times, time_stay, sleepTime);

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
	//goto here;
	system("pause");//stop cmd to exchange return 0
	//return 0;
}
