#pragma once
int window_x, window_y, dx = 0;
//�v���O�������́u�ʒu�v�̃N���X
//�ʒu�ƃT�C�Y���E�B���h�E��Ōv�Z
bool mouse_in_area(int startX, int startY, int endX, int endY) {
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
	// �}�E�X�̃N���b�N�ʒu����֐�
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
	// �}�E�X�̃N���b�N�ʒu����֐�
	bool mouse_in() {
		return mouse_in_area(this->startX, this->startY, this->endX, this->endY);
	}
};
//�ʒu�̓E�B���h�E��A�T�C�Y�͌Œ�
class ConstArea {
public:
	int startX, startY, endX, endY;
	ConstArea(float posX, float posY, int sizeX, int sizeY) {
		this->startX = window_x * posX - (sizeX / 2);
		this->startY = window_y * posY - (sizeY / 2);
		this->endX = this->startX + sizeX;
		this->endY = this->startY + sizeY;
	}
	// �}�E�X�̃N���b�N�ʒu����֐�
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
//�ʒu�̓E�B���h�E��A�T�C�Y�͌Œ�
class CircleArea {
public:
	int centerX, centerY, r;
	CircleArea(float posX, float posY, int size) {
		this->centerX = window_x * posX;
		this->centerY = window_y * posY;
		this->r = size;
	}
	// �}�E�X�̃N���b�N�ʒu����֐�
	bool mouse_in() {
		int mouseX = 0, mouseY = 0;
		GetMousePoint(&mouseX, &mouseY);
		dx = (pow(mouseX - centerX, 2) + pow(mouseY - centerY, 2));
		return (sqrt(dx) <= r);
	}
};