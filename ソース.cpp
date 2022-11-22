#include <DxLib.h>
#include <math.h>
#include<stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include "Area.h"

int color;
int x, y;
int mouseX, mouseY;
int gamestep = 0;
int skillbt = 0;
int eriaX, eriaY;
int handcard[7] = { 0 };
int used[7] = { 0 };
int turn = 0;
WindowArea* HostButtun, * GuestButton;
WindowArea2*Charaenter, * Charaback;
ConstArea* Chara_Card[7], * hand[7];
CircleArea* Skill;
int input();
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ChangeWindowMode(false);
	SetGraphMode(1920, 1080,32);
	DxLib_Init();
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	char StrBuf[256];    // データバッファ
	int receive=0;
	int receive2;
	int connection_select = 0;
	int selection = 0;
	int goback=0;
	int chara[7], chara7_2;
	int charaex[7];
	int card[18];
	int random=rand()% 20000;
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

	int skill_on, skill_off=0, skilled;
	int skillsizeX = 0, skillsizeY = 0;
	int cardsizeX = 0, cardsizeY = 0;

	title = LoadGraph("cardimage/title.png");
	connection_wait= LoadGraph("cardimage/通信待ち3.png");
	cardselect_back = LoadGraph("cardimage/select_card_back.png");
	vs = LoadGraph("cardimage/vs.jpg");
	backcard = LoadGraph("cardimage/backcard3.png");
	playmat = LoadGraph("cardimage/playmat.png");
	chara[0] = LoadGraph("cardimage/キャラ01.png");
	chara[1] = LoadGraph("cardimage/キャラ02.png");
	chara[2] = LoadGraph("cardimage/キャラ03.png");
	chara[3] = LoadGraph("cardimage/キャラ04.png");
	chara[4] = LoadGraph("cardimage/キャラ05.png");
	chara[5] = LoadGraph("cardimage/キャラ06.png");
	chara[6] = LoadGraph("cardimage/キャラ07.png");
	chara7_2 = LoadGraph("cardimage/キャラ07-2.png");

	charaex[0] = LoadGraph("cardimage/キャラ1.jpg");
	charaex[1] = LoadGraph("cardimage/キャラ2.jpg");
	charaex[2] = LoadGraph("cardimage/キャラ3.jpg");
	charaex[3] = LoadGraph("cardimage/キャラ4.jpg");
	charaex[4] = LoadGraph("cardimage/キャラ5.jpg");
	charaex[5] = LoadGraph("cardimage/キャラ6.jpg");
	charaex[6] = LoadGraph("cardimage/キャラ7.jpg");

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
	card[5] = LoadGraph("cardimage/poisonchoki.png");
	card[6] = LoadGraph("cardimage/skillgu-.png");
	card[7] = LoadGraph("cardimage/skillpa-.png");
	card[8] = LoadGraph("cardimage/skillchoki.png");
	card[9] = LoadGraph("cardimage/gu-.png");
	card[10] = LoadGraph("cardimage/pa-.png");
	card[11] = LoadGraph("cardimage/choki.png");
	card[12] = LoadGraph("cardimage/healgu-.png");
	card[13] = LoadGraph("cardimage/healpa-.png");
	card[14] = LoadGraph("cardimage/healchoki.png");
	card[15] = LoadGraph("cardimage/tgu-.png");
	card[16] = LoadGraph("cardimage/tpa-.png");
	card[17] = LoadGraph("cardimage/tchoki.png");

	red_botan = LoadGraph("cardimage/再考決定ボタン.png");
	blue_botan = LoadGraph("cardimage/再考戻るボタン.png");
	skill_on = LoadGraph("cardimage/skill_on.png");
	skill_off = LoadGraph("cardimage/skill_off.png");
	skilled = LoadGraph("cardimage/skilled.png");
	GetGraphSize(skill_off, &skillsizeX, &skillsizeY);
	GetGraphSize(card[0], &cardsizeX, &cardsizeY);
	GetScreenState(&window_x, &window_y, &color);
	GetGraphSize(backcard, &x, &y);
	SetMouseDispFlag(TRUE);
	SetFontSize(50);


	DrawExtendGraph(0, 0,window_x+1,window_y+1, title, true);

	HostButtun = new WindowArea(1.0 / 35.0, 5.0 / 6.0, 1.0 / 5.0, 1.0 / 8.0);
	GuestButton = new WindowArea(27.0 / 35.0, 5.0 / 6.0, 1.0 / 5.0, 1.0 / 8.0);
	Chara_Card[0] = new ConstArea((1.0 / 5.0), (1.5 / 5.0), x, y);
	Chara_Card[1] = new ConstArea((2.0 / 5.0), (1.5 / 5.0), x, y);
	Chara_Card[2] = new ConstArea((3.0 / 5.0), (1.5 / 5.0), x, y);
	Chara_Card[3] = new ConstArea((4.0 / 5.0), (1.5 / 5.0), x, y);
	Chara_Card[4] = new ConstArea((1.5 / 5.0), (3.5 / 5.0), x, y);
	Chara_Card[5] = new ConstArea((2.5 / 5.0), (3.5 / 5.0), x, y);
	Chara_Card[6] = new ConstArea((3.5 / 5.0), (3.5 / 5.0), x, y);

	hand[0] = new ConstArea((1.0 / 10.0), (4.3 / 5.0), cardsizeX, cardsizeY);
	hand[1] = new ConstArea((2.0 / 10.0), (4.3 / 5.0), cardsizeX, cardsizeY);
	hand[2] = new ConstArea((3.0 / 10.0), (4.3 / 5.0), cardsizeX, cardsizeY);
	hand[3] = new ConstArea((4.0 / 10.0), (4.3 / 5.0), cardsizeX, cardsizeY);
	hand[4] = new ConstArea((5.0 / 10.0), (4.3 / 5.0), cardsizeX, cardsizeY);
	hand[5] = new ConstArea((6.0 / 10.0), (4.3 / 5.0), cardsizeX, cardsizeY);
	hand[6] = new ConstArea((7.0 / 10.0), (4.3 / 5.0), cardsizeX, cardsizeY);


	Charaenter = new WindowArea2(3.0 / 20.0, 8.0 / 10.0, 3.0 / 20.0, 1.0 / 10.0);
	Charaback = new WindowArea2(9.0 / 20.0, 8.0 / 10.0, 3.0 / 20.0, 1.0 / 10.0);
	Skill = new CircleArea(9.0 / 10.0,4.0 / 5.0, 170);

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
			(new WindowArea2(0, 0, 3.0 / 4.0, 1))->DrawBox(GetColor(0, 0, 0), true);
			(new WindowArea2(0, 3.0 / 4.0, 3.0 / 4.0, 1))->DrawBox(GetColor(255, 255, 255), true);
			(new WindowArea2(0, 0, 3.0 / 4.0, 3.0 / 4.0))->DrawExtendGraph(charaex[selection]);
			DrawExtendGraph(window_y + 1, 0, window_x, window_y + 1, chara[selection], true);
			Charaenter->DrawExtendGraph(red_botan);
			Charaback->DrawExtendGraph(blue_botan);
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
	DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara[selection], true);
	WaitTimer(10);
	SetFontSize(150);
	srand(random);
	for (int i = 0; i < 18; i++) {
		handcard[i] = rand() % 18;
		for (int j = 0; j < i; j++) {
			if (handcard[i] == handcard[j]) {
				i--;
			}
		}

	}
	while (1) {
		ClearDrawScreen();
		DrawExtendGraph(0, 0, window_x, window_y, back[selection], true);
		DrawExtendGraph(0, 0, window_x, window_y, playmat, true);
		for (int i = 0; i < 18-turn; i++) {
			DrawRotaGraph((window_x / 10) * (i+1), (window_y / 5) * 4.3, 0.2, 0.0, card[handcard[i]], true);
		}

		if (skillbt == 0) {
			DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0, skill_off, true);
		}
		else if (skillbt == 1) {
			DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0, skill_on, true);
		}
		else if (skillbt == 2) {
			DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0, skilled, true);
		}
		skillbt = input();
		//used[turn] = input();
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			turn++;
			printfDx("%d", gamestep);
		}
		DrawRotaGraph((window_x / 5) * 1, (window_y / 5) * 1.5, 1, 0.0, card[2], true);
		if (turn == 3) {
			break;
		}
	}


	DxLib_End();
	return 0;

}

int input() {
	while (1) {
		WaitKey();
		if (gamestep == 0) {
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				if (HostButtun->mouse_in()) {
					return 1;
				}
				else if (GuestButton->mouse_in()) {
					return 2;
				}
			}
		}
		else if (gamestep == 1) {
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				for (int i = 0; i < 7; i++) {
					if (Chara_Card[i]->mouse_in()) {
						return i;
					}
				}

			}
		}
		else if (gamestep == 2) {
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
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
				if (Skill->mouse_in()) {
					return !skillbt;
				}

			}
		}
	}
}
