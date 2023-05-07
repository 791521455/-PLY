
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//cmd��������
#define FONT_SIZE 30
#define FONT_FAMILY L"Consolas"
//cmd_size
bool SetSize(int width, int height)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ������
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; //���ÿ��
	bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // ���ô���ߴ�
	if (!ret) return false;
	COORD coord = { width, height };
	ret = SetConsoleScreenBufferSize(hOutput, coord); // ���û���ߴ�
	return ret;
}

void cmd_ctrl() {
	HWND hWnd = GetConsoleWindow(); //��ȡ���ھ��
	LONG_PTR sty = GetWindowLongPtrA(hWnd, GWL_STYLE); //��ȡ������ʽ
	sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; //ȥ���ɱ仯��С,���,��С����ť,~��ȡ��,&����,����λ������ص�֪ʶ��
	SetWindowLongPtrA(hWnd, GWL_STYLE, sty); //���ô��岻�ɸ��Ĵ�С,�������
}

void cmd_color(int i) {
	//0.Ĭ��//1.������ɫΪ��ɫ�ı�����ɫ����//2.new
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (i == 1) {
		//������ɫΪ��ɫ�ı�����ɫ����
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | BACKGROUND_GREEN);
	}
	else if (i == 0) {
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else if (i == 2) {
		system("color 0D"); //���ñ���Ϊ��ɫ,����Ϊ����ɫ
	}
}

void note_cout() {
	SetConsoleTitleA("���ģ����");
	//Sleep(300);
	//system("title ����"); //����һ���±���
	cout << "v1.15������־��" << endl 
		<< " 1.NAME" << endl 
		<< " 2.�޸����ʱ�����" << endl 
		<< " 3.�޸����ʱ�����" << endl 
		<< " 4.������ģʽ���£�" << endl
		<< "     a.����aΪĬ�ϵ��ʱ��" << endl 
		<< "     b.����bΪ�Զ�����ʱ��" << endl
		<< "     c.����3ΪDEBUG"<<endl
		<< "     d.����4.5������Թ���" << endl
		<< "5.�Լ�����"<<endl;
}

void title_cout(int i) {
	//0.title
	if (i == 0) {
		cout << "v1.10 MOUSE_BOSS" << endl;
	}
}

int mode_cin() {
	char mode;
	//cout << "���� ���ʱ�� ����Ϊ0.1"<<endl;
	cout << "����ģʽ a.Ĭ�� b.�Զ���" << endl;
	cin >> mode;
	return mode;
}

/*struct IMFOO {
	int t_w;//time_wait
	int t_s;//time_stay
	int t_s;//time_times
	unsigned int sleepTime = 1000 * t_s; // ����t/ms
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
		cout << "������ʱ�� (s)��";
		cin >> time_stop;
		cout << "�������������";
		cin >> time_times;
		time_stay = 100;
		//unsigned int sleepTime = 1000 * time_stop;
	}
	else if (mode == 'B' || mode == 'b') {
		cout << "������ʱ�� (s)��";
		cin >> time_stop;
		cout << "������ʱ�䣨ms)��";
		cin >> time_stay;
		cout << "�������������";
		cin >> time_times;
		//unsigned int sleepTime = 1000 * time_stop; // ����t/ms
	}
	else if (mode == '3') {
		time_stop=3;
		time_times = 5;
		time_stay = 100;
	}
	else if (mode == '4') {
		cmd_ctrl();
		cout << "ȥ���ɱ仯��С,���,��С����ť,���ô��岻�ɸ��Ĵ�С,�������";
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
		cout << "ȥ���ɱ仯��С,���,��С����ť,���ô��岻�ɸ��Ĵ�С,�������";
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
