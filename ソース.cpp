#include "DxLib.h"
#include <math.h>
#include <string>
#include <vector>

int window_x, window_y, color;
int x, y;
int mouseX, mouseY;
int gamestep = 0;
int skillbt = 0;
int dx = 0;
int eriaX, eriaY;
//プログラム内の「位置」のクラス
//位置とサイズをウィンドウ比で計算
bool mouse_in_area(int startX,int startY, int endX, int endY) {
	int mouseX = 0, mouseY = 0;
	GetMousePoint(&mouseX, &mouseY);
	return (mouseX >= startX && mouseX <= endX && mouseY >= startY && mouseY <= endY);
}
class WindowArea {
public:
	int startX, startY, endX, endY;
	WindowArea(float posX, float posY, float sizeX, float sizeY) {
		this->startX = (float)window_x * posX;
		this->startY = (float)window_y * posY;
		this->endX = this->startX + (float)window_x * sizeX;
		this->endY = this->startY + (float)window_y * sizeY;
	}
	// マウスのクリック位置判定関数
	bool mouse_in() {
		return mouse_in_area(this->startX, this->startY, this->endX, this->endY);
	}
	void DrawExtend(const TCHAR* path) {
		DrawExtendGraph(this->startX, this->startY, this->endX, this->endY, LoadGraph(path), true);
	}
	void DrawRota(double exRate, const TCHAR* path) {
		DrawRotaGraph((this->startX + this->endX) / 2, (this->startY + this->endY) / 2, exRate, 0, LoadGraph(path), true);
	}

};
class WindowArea2 {
public:
	int startX, startY, endX, endY;
	WindowArea2(float posX, float posY, float sizeX, float sizeY) {
		this->startX = (float)window_y * posX;
		this->startY = (float)window_y * posY;
		this->endX = this->startX + (float)window_y * sizeX;
		this->endY = this->startY + (float)window_y * sizeY;
	}
	// マウスのクリック位置判定関数
	bool mouse_in() {
		int mouseX = 0, mouseY = 0;
		GetMousePoint(&mouseX, &mouseY);
		return (mouseX >= this->startX && mouseX <= this->endX && mouseY >= this->startY && mouseY <= this->endY);
	}
};
//位置はウィンドウ比、サイズは固定
class ConstArea {
public:
	int startX, startY, endX, endY;
	ConstArea(float posX, float posY, int sizeX, int sizeY) {
		this->startX = window_x * posX;
		this->startY = window_y * posY;
		this->endX = this->startX + sizeX;
		this->endY = this->startY + sizeY;
	}
	// マウスのクリック位置判定関数
	bool mouse_in() {
		return mouse_in_area(this->startX, this->startY, this->endX, this->endY);
	}
	void DrawExtend(const TCHAR* path) {
		DrawExtendGraph(this->startX, this->startY, this->endX, this->endY, LoadGraph(path), true);
	}
	void DrawRota(double exRate, const TCHAR* path) {
		DrawRotaGraph((this->startX + this->endX) / 2, (this->startY + this->endY) / 2, exRate, 0, LoadGraph(path), true);
	}
};
//位置はウィンドウ比、サイズは固定
class CircleArea {
public:
	int centerX, centerY, r;
	CircleArea(float posX, float posY, int size) {
		this->centerX = window_x * posX;
		this->centerY = window_y * posY;
		this->r = size;
	}
	// マウスのクリック位置判定関数
	bool mouse_in() {
		int mouseX = 0, mouseY = 0;
		GetMousePoint(&mouseX, &mouseY);
		dx = (pow(mouseX - centerX,2) + pow(mouseY - centerY,2));
		return (sqrt(dx)<=r);
	}
};
WindowArea* HostButtun, * GuestButton;
WindowArea2*Charaenter, * Charaback;
ConstArea* Card1,* Card2,* Card3,* Card4,* Card5, * Card6, * Card7;
CircleArea* Skill;
int input(void) {
	WaitKey();
	if (gamestep == 0) {
		while (1) {
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				if (HostButtun->mouse_in()) {
					return 1;
				}
				else if (GuestButton->mouse_in()) {
					return 2;
				}
			}
		}
	}
	else if (gamestep == 1) {
		while (1) {
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				GetMousePoint(&mouseX, &mouseY);
				if (Card1->mouse_in()) {
					return 1;
				}
				else if (Card2->mouse_in()) {
					return 2;
				}
				else if (Card3->mouse_in()) {
					return 3;
				}
				else if (Card4->mouse_in()) {
					return 4;
				}
				else if (Card5->mouse_in()) {
					return 5;
				}
				else if (Card6->mouse_in()) {
					return 6;
				}
				else if (Card7->mouse_in()) {
					return 7;
				}
				
			}

		}
	}
	else if (gamestep == 2) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			GetMousePoint(&mouseX, &mouseY);
			if (Charaenter->mouse_in()) {
				return 1;
			}
			else if (Charaback->mouse_in()) {
				return 2;
			}
		}
	}
	//DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0,
	else if (gamestep == 3) {
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			GetMousePoint(&mouseX, &mouseY);
			if (Skill->mouse_in()) {
				if (skillbt == 0) {
					return 1;
				}
				else if (skillbt == 1) {
					return 0;
				}
			}
		}
	}
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ChangeWindowMode(false);
	SetGraphMode(1920, 1080,32);
	DxLib_Init();
	char StrBuf[256];    // データバッファ
	int receive=0;
	int receive2;
	int connection_select = 0;
	int selection = 0;
	int goback=0;
	int chara1, chara2, chara3, chara4, chara5, chara6, chara7,chara7_2;
	int charaex1, charaex2, charaex3, charaex4, charaex5, charaex6, charaex7;
	int card[9];
	int back[8];
	int red_botan;
	int blue_botan;
	int connection = 0;
	int connection_wait;
	int playmat;
	IPDATA ip;
	int NetHandle, LostHandle;    // ネットワークハンドル
	int DataLength;        // 受信データ量保存用変数
	int title;
	int vs;
	int backcard;
	int cardselect_back;
	int chara_select = 0;
	int round = 0;

	int skill_on, skill_off=0, skilled;
	int skillsizeX = 0, skillsizeY = 0;

	title = LoadGraph("cardimage/title.png");
	connection_wait= LoadGraph("cardimage/通信待ち3.png");
	cardselect_back = LoadGraph("cardimage/select_card_back.png");
	vs = LoadGraph("cardimage/vs.jpg");
	backcard = LoadGraph("cardimage/backcard3.png");
	playmat = LoadGraph("cardimage/playmat.png");
	chara1 = LoadGraph("cardimage/キャラ01.png");
	chara2 = LoadGraph("cardimage/キャラ02.png");
	chara3 = LoadGraph("cardimage/キャラ03.png");
	chara4 = LoadGraph("cardimage/キャラ04.png");
	chara5 = LoadGraph("cardimage/キャラ05.png");
	chara6 = LoadGraph("cardimage/キャラ06.png");
	chara7 = LoadGraph("cardimage/キャラ07.png");
	chara7_2 = LoadGraph("cardimage/キャラ07-2.png");

	charaex1 = LoadGraph("cardimage/キャラ1.jpg");
	charaex2 = LoadGraph("cardimage/キャラ2.jpg");
	charaex3 = LoadGraph("cardimage/キャラ3.jpg");
	charaex4 = LoadGraph("cardimage/キャラ4.jpg");
	charaex5 = LoadGraph("cardimage/キャラ5.jpg");
	charaex6 = LoadGraph("cardimage/キャラ6.jpg");
	charaex7 = LoadGraph("cardimage/キャラ7.jpg");

	back[0] = LoadGraph("cardimage/背景1.png");
	back[1] = LoadGraph("cardimage/背景2.png");
	back[2] = LoadGraph("cardimage/背景3.png");
	back[3] = LoadGraph("cardimage/背景4.png");
	back[4] = LoadGraph("cardimage/背景5.png");
	back[5] = LoadGraph("cardimage/背景6.png");
	back[6] = LoadGraph("cardimage/背景7.png");
	back[7] = LoadGraph("cardimage/背景7-2.png");

	card[0] = LoadGraph("cardimage/1.5gu-.png");
	card[1] = LoadGraph("cardimage/1.5pa-.png");
	card[2] = LoadGraph("cardimage/1.5choki.png");
	card[3] = LoadGraph("cardimage/poisongu-.png");
	card[4] = LoadGraph("cardimage/poisonpa-.png");
	card[5] = LoadGraph("cardimage/1.5gu-.png");
	card[6] = LoadGraph("cardimage/1.5gu-.png");
	card[7] = LoadGraph("cardimage/1.5gu-.png");
	card[8] = LoadGraph("cardimage/1.5gu-.png");
	red_botan = LoadGraph("cardimage/再考決定ボタン.png");
	blue_botan = LoadGraph("cardimage/再考戻るボタン.png");
	skill_on = LoadGraph("cardimage/skill_on.png");
	skill_off = LoadGraph("cardimage/skill_off.png");
	skilled = LoadGraph("cardimage/skilled.png");
	GetGraphSize(skill_off, &skillsizeX, &skillsizeY);

	GetScreenState(&window_x, &window_y, &color);
	GetGraphSize(backcard, &x, &y);
	SetMouseDispFlag(TRUE);
	SetFontSize(50);


	DrawExtendGraph(0, 0,window_x+1,window_y+1, title, true);

	DrawBox((window_x / 5) * 1, (window_y / 6) * 4, (window_x / 5) * 2, (window_y / 6) * 5, GetColor(255, 0, 255), true);
	DrawBox((window_x / 5) * 3, (window_y / 6) * 4, (window_x / 5) * 4, (window_y / 6) * 5, GetColor(255, 255, 0), true);
	DrawBox(0, 0, 100, 100, GetColor(0, 0, 0), true);
	DrawString((window_x / 5) * 1, (window_y / 6) * 4, "ホスト", GetColor(0, 0, 0));
	DrawString((window_x / 5) * 3, (window_y / 6) * 4, "ゲスト", GetColor(0, 0, 0));


	HostButtun = new WindowArea(1.0 / 5.0, 4.0 / 6.0, 1.0 / 5.0, 1.0 / 6.0);
	GuestButton = new WindowArea(3.0 / 5.0, 4.0 / 6.0, 1.0 / 5.0, 1.0 / 6.0);
	Card1 = new ConstArea((1.0 / 5.0) - (x / 2),(1.5 / 5.0) - (y / 2), x, y);
	Card2 = new ConstArea((2.0 / 5.0) - (x / 2),(1.5 / 5.0) - (y / 2), x, y);
	Card3 = new ConstArea((3.0 / 5.0) - (x / 2),(1.5 / 5.0) - (y / 2), x, y);
	Card4 = new ConstArea((4.0 / 5.0) - (x / 2),(1.5 / 5.0) - (y / 2), x, y);
	Card5 = new ConstArea((1.5 / 5.0) - (x / 2),(3.5 / 5.0) - (y / 2), x, y);
	Card6 = new ConstArea((2.5 / 5.0) - (x / 2),(3.5 / 5.0) - (y / 2), x, y);
	Card7 = new ConstArea((3.5 / 5.0) - (x / 2),(3.5 / 5.0) - (y / 2), x, y);
	Charaenter = new WindowArea2(3.0 / 20.0, 3.0 / 4.0, 1.0 / 20.0, 1.0 / 4.0);
	Charaback = new WindowArea2(9.0 / 20.0, 3.0 / 4.0, 1.0 / 20.0, 1.0 / 4.0);
	Skill = new CircleArea(9.0 / 10.0,4.0 / 5.0, 256);


	connection_select = input();
	//printfDx("%d", connection_select);
	gamestep=1;

	while (chara_select < 2) {
		switch (chara_select)
		{
		case 0:
			ClearDrawScreen();
			DrawExtendGraph(0, 0, window_x + 1, window_y + 1, cardselect_back, true);
			for (int i = 1; i < 8; i++) {
				if (i < 5) {
					DrawRotaGraph((window_x / 5) * i, (window_y / 5) * 1.5, 1, 0.0, backcard, true);
				}
				else {
					DrawRotaGraph((window_x / 5) * (i - 3.5), (window_y / 5) * 3.5, 1, 0.0, backcard, true);
				}
			}
			//printfDx("%d", gamestep);

			selection = input();
			//printfDx("%d", selection);
			chara_select=1;
			gamestep = 2;
			//WaitKey();
		case 1:
			ClearDrawScreen();
			DrawBox(0, 0, window_y * 3 / 4, window_y * 3 / 4, GetColor(0, 0, 0), true);
			DrawBox(0, window_y * 3 / 4, window_y * 3 / 4, window_y, GetColor(255, 255, 255), true);
			if (selection == 1) {
				DrawExtendGraph(0, 0, window_y * 3 / 4, window_y * 3 / 4, charaex1, true);
				DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara1, true);
			}
			else if (selection == 2) {
				DrawExtendGraph(0, 0, window_y * 3 / 4, window_y * 3 / 4, charaex2, true);
				DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara2, true);
			}
			else if (selection == 3) {
				DrawExtendGraph(0, 0, window_y * 3 / 4, window_y * 3 / 4, charaex3, true);
				DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara3, true);
			}
			else if (selection == 4) {
				DrawExtendGraph(0, 0, window_y * 3 / 4, window_y * 3 / 4, charaex4, true);
				DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara4, true);
			}
			else if (selection == 5) {
				DrawExtendGraph(0, 0, window_y * 3 / 4, window_y * 3 / 4, charaex5, true);
				DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara5, true);
			}
			else if (selection == 6) {
				DrawExtendGraph(0, 0, window_y * 3 / 4, window_y * 3 / 4, charaex6, true);
				DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara6, true);
			}
			else if (selection == 7) {
				DrawExtendGraph(0, 0, window_y * 3 / 4, window_y * 3 / 4, charaex7, true);
				DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara7, true);
			}
			DrawExtendGraph((window_y * 3 / 4) * 1 / 5, window_y * 3 / 4, (window_y * 3 / 4) * 2 / 5, window_y, red_botan, true);
			DrawExtendGraph((window_y * 3 / 4) * 3 / 5, window_y * 3 / 4, (window_y * 3 / 4) * 4 / 5, window_y, blue_botan, true);
			goback = input();
			if (goback == 1) {
				chara_select = 2;
				gamestep = 3;
			}
			else if(goback==2) {
				chara_select = 0;
				gamestep = 1;
				goback = 0;
			}
		default:
			break;
		}
	}
	ClearDrawScreen();
	DrawExtendGraph(0, 0, window_x, window_y, vs, true);
	if (selection == 1) {
		DrawExtendGraph((window_x/10)*0.5, 0, (window_x/10)*3.5, window_y + 1, chara1, true);
	}
	else if (selection == 2) {
		DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara2, true);
	}
	else if (selection == 3) {
		DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara3, true);
	}
	else if (selection == 4) {
		DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara4, true);
	}
	else if (selection == 5) {
		DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara5, true);
	}
	else if (selection == 6) {
		DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara6, true);
	}
	else if (selection == 7) {
		DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara7, true);
	}
	WaitTimer(10);
	SetFontSize(150);
	while (1) {
		ClearDrawScreen();
		if (selection == 1) {
			DrawExtendGraph(0, 0, window_x, window_y, back[0], true);
		}
		else if (selection == 2) {
			DrawExtendGraph(0, 0, window_x, window_y, back[1], true);
		}
		else if (selection == 3) {
			DrawExtendGraph(0, 0, window_x, window_y, back[2], true);
		}
		else if (selection == 4) {
			DrawExtendGraph(0, 0, window_x, window_y, back[3], true);
		}
		else if (selection == 5) {
			DrawExtendGraph(0, 0, window_x, window_y, back[4], true);
		}
		else if (selection == 6) {
			DrawExtendGraph(0, 0, window_x, window_y, back[5], true);
		}
		else if (selection == 7) {
			DrawExtendGraph(0, 0, window_x, window_y, back[6], true);
		}
		DrawExtendGraph(0, 0, window_x, window_y, playmat, true);
		DrawFormatString(window_x*7 / 15, 0,GetColor(0, 0, 0),"%d", round);

		if (skillbt == 0) {
			DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0, skill_off, true);
		}
		else if (skillbt == 1) {
			DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0, skilled, true);
		}
		else if (skillbt == 2) {

		}
		skillbt = input();
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			round++;
			printfDx("%d", gamestep);
		}
		if (round == 6) {
			break;
		}
	}


	DxLib_End();
	return 0;

}