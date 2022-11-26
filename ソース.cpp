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
int handcard[8] = {0};
int used[5] = { 0 };
int turn = 0;
int showcard;
int vscard;
int card[18];
int enemy;
int go = 0;
WindowArea* HostButtun, * GuestButton;
WindowArea2*Charaenter, * Charaback;
ConstArea* Chara_Card[7], * hand[7];
CircleArea* Skill;
int input();
int show(int c);
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ChangeWindowMode(false);
	SetGraphMode(1920, 1080,32);
	DxLib_Init();
	char Buf[256];    // データバッファ
	int receive=0;
	int receive2;
	int connection_select = 0;
	int selection = 0;
	int goback=0;
	int chara[7], chara7_2;
	int charaex[7];
	int random=rand()% 20000;
	int back[8];
	int red_botan;
	int blue_botan;
	int connection = 0;
	int connection_wait;
	int playmat;
	int you[3];


	int mul = 0;
	int NetHandle, LostHandle;    // ネットワークハンドル
	int DataLength;        // 受信データ量保存用変数
	int title;
	int vs;
	int damage;
	int heal;
	int wincard;
	int losecard;
	int drawcard;
	int backcard;
	int cardselect_back;
	int chara_select = 0;
	int judge;
	int carddamage=0;
	int poison=0;
	int mypoison=0;
	int enepoison=0;
	int cardheal=0;
	int skill_on, skill_off=0, skilled;
	int skillsizeX = 0, skillsizeY = 0;
	int cardsizeX = 0, cardsizeY = 0;

	int mydamage = 0;
	int enedamage = 0;
	int position=0;

	title = LoadGraph("cardimage/タイトル.png");
	connection_wait= LoadGraph("cardimage/通信待ち3.png");
	cardselect_back = LoadGraph("cardimage/select_card_back.png");
	vs = LoadGraph("cardimage/vs.jpg");
	vscard = LoadGraph("cardimage/VS画面.png");
	drawcard = LoadGraph("cardimage/引き分け.png");
	wincard = LoadGraph("cardimage/勝ち.png");
	losecard = LoadGraph("cardimage/負け.png");
	damage = LoadGraph("cardimage/damage.png");
	heal = LoadGraph("cardimage/heal.png");
	backcard = LoadGraph("cardimage/backcard3.png");
	playmat = LoadGraph("cardimage/playmat.png");
	you[0] = LoadGraph("cardimage/you_win.png");
	you[1] = LoadGraph("cardimage/you_lose.png");
	you[2]=LoadGraph("cardimage/you_draw.png");
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

	hand[0] = new ConstArea((1.0 / 10.0), (4.3 / 5.0), cardsizeX/5, cardsizeY/5);
	hand[1] = new ConstArea((2.0 / 10.0), (4.3 / 5.0), cardsizeX/5, cardsizeY/5);
	hand[2] = new ConstArea((3.0 / 10.0), (4.3 / 5.0), cardsizeX/5, cardsizeY/5);
	hand[3] = new ConstArea((4.0 / 10.0), (4.3 / 5.0), cardsizeX/5, cardsizeY/5);
	hand[4] = new ConstArea((5.0 / 10.0), (4.3 / 5.0), cardsizeX/5, cardsizeY/5);
	hand[5] = new ConstArea((6.0 / 10.0), (4.3 / 5.0), cardsizeX/5, cardsizeY/5);
	hand[6] = new ConstArea((7.0 / 10.0), (4.3 / 5.0), cardsizeX/5, cardsizeY/5);


	Charaenter = new WindowArea2(3.0 / 20.0, 8.0 / 10.0, 3.0 / 20.0, 1.0 / 10.0);
	Charaback = new WindowArea2(9.0 / 20.0, 8.0 / 10.0, 3.0 / 20.0, 1.0 / 10.0);
	Skill = new CircleArea(9.0 / 10.0,4.0 / 5.0, 170);

	WaitKey();
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
	SetFontSize(120);
	srand(random);
	for (int i = 0; i < 7; i++) {
		handcard[i] = rand() % 300;
		for (int j = 0; j < i; j++) {
			if (handcard[i] == handcard[j]) {
				i--;
			}
		}
	}
	while (1) {
		ClearDrawScreen();
		if (selection == 6 && turn > 2) {
			DrawExtendGraph(0, 0, window_x, window_y, back[7], true);
		}
		else {
			DrawExtendGraph(0, 0, window_x, window_y, back[selection], true);
		}
		DrawExtendGraph(0, 0, window_x, window_y, playmat, true);
		for (int i = 0; i < 7 - turn; i++) {
			show(handcard[i]);
			DrawRotaGraph((window_x / 10) * (i + 1), (window_y / 5) * 4.3, 0.2, 0.0, card[showcard], true);
		}
		SetFontSize(120);
		DrawFormatString(window_x * 7 / 15, window_y / 45, GetColor(0, 0, 0), "%d", turn+1);
		if (mydamage < 10) {
			position = 0;
		}
		else if (mydamage < 100) {
			position = 1;
		}
		else {
			position = 2;
		}
		DrawFormatString(window_x * (6 - (position * 0.5)) / 17, window_y / 45, GetColor(0, 0, 0), "%d", mydamage);

		if (enedamage < 10) {
			position = 0;
		}
		else if (enedamage < 100) {
			position = 1;
		}
		else {
			position = 2;
		}
		DrawFormatString(window_x * (10.8 - (position * 0.5)) / 17, window_y / 45, GetColor(0, 0, 0), "%d", enedamage);

		//if (skillbt == 0) {
		if (selection == 6&& turn > 2) {
			DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.5, 0, chara7_2, true);
		}
		else {
			DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.5, 0, chara[selection], true);
		}
		//}
		//else if (skillbt == 1) {
		//	DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0, skill_on, true);
		//}
		//else if (skillbt == 2) {
		//	DrawRotaGraph(window_x / 10 * 9, window_y / 5 * 4, 0.75, 0, skilled, true);
		//}
			input();
			WaitKey();
		if (used[turn] < 100) {
			if (enemy < 100) {
				DrawExtendGraph(0, 0, window_x, window_y, drawcard, true);
				judge = 0;
			}
			else if (enemy < 200) {
				DrawExtendGraph(0, 0, window_x, window_y, wincard, true);
				judge = 1;
			}
			else if (enemy < 300) {
				DrawExtendGraph(0, 0, window_x, window_y, losecard, true);
				judge = 2;
			}
		}
		else if (used[turn] < 200) {
			if (enemy < 100) {
				DrawExtendGraph(0, 0, window_x, window_y, losecard, true);
				judge = 2;
			}
			else if (enemy < 200) {
				DrawExtendGraph(0, 0, window_x, window_y, drawcard, true);
				judge = 0;
			}
			else if (enemy < 300) {
				DrawExtendGraph(0, 0, window_x, window_y, wincard, true);
				judge = 1;
			}
		}
		else if (used[turn] < 300) {
			if (enemy < 100) {
				DrawExtendGraph(0, 0, window_x, window_y, wincard, true);
				judge = 1;
			}
			else if (enemy < 200) {
				DrawExtendGraph(0, 0, window_x, window_y, losecard, true);
				judge = 2;
			}
			else if (enemy < 300) {
				DrawExtendGraph(0, 0, window_x, window_y, drawcard, true);
				judge = 0;
			}
		}
		WaitKey();
		if (judge == 1) {
			show(used[turn]);
		}
		else if (judge == 2) {
			show(enemy);
		}
		if (showcard == 15 || showcard == 16 || showcard == 17) {
			carddamage = 100;
		}
		else if (showcard == 0 || showcard == 1 || showcard == 2) {
			carddamage = 15;
			mul = 1;
		}
		else if (showcard == 3 || showcard == 4 || showcard == 5) {
			carddamage = 10;
			poison = 1;
		}
		else if (showcard == 6 || showcard == 7 || showcard == 8) {
			carddamage = 10;
			skillbt = 0;
		}
		else if (showcard == 9 || showcard == 10 || showcard == 11) {
			carddamage = 5;
		}
		else if (showcard == 12 || showcard == 13 || showcard == 14) {
			cardheal = 10;
		}
		SetFontSize(350);
		if (judge != 0) {
			if (judge == 1) {
				if (cardheal == 0) {
					DrawExtendGraph(0, 0, window_x, window_y, damage, true);
					DrawFormatString(window_x * 3 / 7, window_y * 5 / 7, GetColor(255, 255, 255), "%d", carddamage + mypoison);
					DrawRotaGraph((window_x / 4) * 1, window_y / 2, 0.5, 0, card[showcard], true);
				}
				else if (cardheal != 0) {
					DrawExtendGraph(0, 0, window_x, window_y, heal, true);
					DrawRotaGraph((window_x / 4) * 1, window_y / 2, 0.5, 0, card[showcard], true);
				}
			}
			if (judge == 2) {
				if (cardheal == 0) {
					DrawExtendGraph(0, 0, window_x, window_y, damage, true);
					DrawFormatString(window_x * 3 / 7, window_y * 5 / 7, GetColor(255, 255, 255), "%d", carddamage + enepoison);
					DrawRotaGraph((window_x / 4) * 1, window_y / 2, 0.5, 0, card[showcard], true);
				}
				else if (cardheal != 0) {
					DrawExtendGraph(0, 0, window_x, window_y, heal, true);
					DrawRotaGraph((window_x / 4) * 1, window_y / 2, 0.5, 0, card[showcard], true);
				}
			}
			SetFontSize(120);
			DrawFormatString(window_x * 3 / 7, window_y * 1 / 7, GetColor(255, 255, 255), "基本ダメージ：%d",carddamage);
			if (judge == 1) {
				DrawFormatString(window_x * 3 / 7, window_y * 2 / 7, GetColor(255, 255, 255), "毒ダメージ：%d", mypoison);
			}
			else if(judge==2){
				DrawFormatString(window_x * 3 / 7, window_y * 2 / 7, GetColor(255, 255, 255), "毒ダメージ：%d", enepoison);
			}
		}
		WaitKey();
		if (judge == 1) {
			enedamage = enedamage + carddamage+mypoison;
			mydamage = mydamage - cardheal;
			if (mydamage < 0) {
				mydamage = 0;
			}
		}
		else if (judge == 2) {
			mydamage = mydamage + carddamage+enepoison;
			enedamage = enedamage - cardheal;
			if (enedamage < 0) {
				enedamage = 0;
			}
		}
		if (mypoison > 0 || enepoison > 0) {
			mypoison--;
			enepoison--;
			if (mypoison < 0) {
				mypoison = 0;
			}
			if (enepoison < 0) {
				enepoison = 0;
			}
		}
		if (poison == 1) {
			if (judge == 1) {
				mypoison = 2;
			}
			else if (judge == 2) {
				enepoison = 2;
			}
			poison = 0;
		}
		if(mul==1){
			if (judge == 1) {
				enedamage = enedamage * 1.5;
			}
			else if (judge == 2) {
				mydamage = mydamage*1.5;
			}
			mul = 0;
		}
		cardheal = 0;
		turn++;
		if (turn == 5) {
			ClearDrawScreen();
			if (mydamage == enedamage) {
				DrawExtendGraph(0, 0, window_x, window_y, you[2], true);
			}
			else if (mydamage < enedamage) {
				DrawExtendGraph(0, 0, window_x, window_y, you[0], true);
			}
			else if (mydamage > enedamage) {
				DrawExtendGraph(0, 0, window_x, window_y, you[1], true);
			}
			DrawExtendGraph((window_x / 10) * 0.5, 0, (window_x / 10) * 3.5, window_y + 1, chara[selection], true);
			WaitTimer(3000);
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
				//if (Skill->mouse_in()) {
				//	skillbt= !skillbt;
				//	return 0;
				}
				for (int i = 0; i < 7-turn; i++) {
					if (hand[i]->mouse_in()) {
						used[turn] = handcard[i];
						for (int j = i; j < 7 - turn; j++) {
							handcard[j] = handcard[j + 1];
						}
						DrawExtendGraph(0, 0, window_x, window_y, vscard, true);
						show(used[turn]);
						DrawRotaGraph((window_x / 4) * 1, window_y / 2, 0.5, 0, card[showcard], true);
						enemy = rand() % 300;
						show(enemy);
						DrawRotaGraph((window_x / 4) * 3, window_y / 2, 0.5, 0, card[showcard], true);
						go = 1;
						return 0;
					}
				}
			}
		}
	}


int show(int c) {
	//gu-
	if (c == 0) {
		showcard = 15;
	}
	else if (c < 10) {
		showcard = 0;
	}
	else if (c < 25) {
		showcard = 3;
	}
	else if (c < 40) {
		showcard = 6;
	}
	else if (c < 90) {
		showcard = 9;
	}
	else if (c < 100) {
		showcard = 12;
	}
	//choki
	else if (c == 100) {
		showcard = 17;
	}
	else if (c < 110) {
		showcard = 2;
	}
	else if (c < 125) {
		showcard = 5;
	}
	else if (c < 140) {
		showcard = 8;
	}
	else if (c < 190) {
		showcard = 11;
	}
	else if (c < 200) {
		showcard = 14;
	}
	//pa-
	else if (c == 200) {
		showcard = 16;
	}
	else if (c < 210) {
		showcard = 1;
	}
	else if (c < 225) {
		showcard = 4;
	}
	else if (c < 240) {
		showcard = 7;
	}
	else if (c < 290) {
		showcard = 10;
	}
	else if (c < 300) {
		showcard = 13;
	}
	return 0;
}
