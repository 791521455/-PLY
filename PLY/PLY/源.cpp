#include <iostream>
#include <windows.h>

using namespace std;

#define FONT_SIZE 30
#define FONT_FAMILY L"Consolas"

int main(void) {
	//******************������ɫΪ��ɫ�ı�����ɫ����
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | BACKGROUND_GREEN); // ������ɫΪ��ɫ�ı�����ɫ����
	//******************
	int mou_x, mou_y;
	float time_stop, time_stay, time_times;
	char mod_click;
	unsigned int sleepTime=1;
	//******************
	cout << "v1.10������־��" << endl << " 1.LW�޸�" << endl << " 2.�޸����ʱ�䣨s������ΪС��������" << endl << " 3.Ĭ�ϵ��ʱ�䣨s��Ϊ100" << endl << " 4.������ģʽ���£�" << endl << "      a.����aΪĬ�ϵ��ʱ��0.1s=100ms" << endl << "      b.����bΪ�Զ�����ʱ��/s"<<endl;
	//******************
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	cout << "v1.10    ����� ר �� �� �� ��" << endl;
	//cout << "���� ���ʱ�� ����Ϊ0.1"<<endl;
	cout << "����ģʽ a.Ĭ�� b.�Զ���" << endl;
	cin >> mod_click;
	//******************
	if (mod_click == 'A' || mod_click == 'a') {
		cout << "������ʱ�� (s)��";
		cin >> time_stop;
		cout << "�������������";
		cin >> time_times;
		time_stay = 100;
		unsigned int sleepTime = 1000 * time_stop;
	}
	else if (mod_click == 'B' || mod_click == 'b') {
		cout << "������ʱ�� (s)��";
		cin >> time_stop;
		cout << "������ʱ�䣨ms)��";
		cin >> time_stay;
		cout << "�������������";
		cin >> time_times;
		unsigned int sleepTime = 1000 * time_stop; // ����t/ms
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