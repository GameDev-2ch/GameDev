#pragma once

#include "DxLib.h"

#include <vector>

class Tama;
class Game;

typedef std::vector<Tama*>::iterator TamaIt;

class Chara
{

public:

	virtual void update(int timeSinceLast);
	virtual int setGraphicFromFile(const TCHAR *filename);
	virtual int setGraphicFromID(int graph_id);
	virtual int getGraphicID(void){ return graphID; }

	float x;
	float y;

	Chara(Game *game) : x(0), y(0), graphID(-1), pGame(game) {}

protected:

	int graphID;
	Game *pGame;

};

class Player : public Chara
{

public:

	void shot(void);
	void update(int timeSinceLast);

	Player(Game *game) : Chara(game) {}

};

class Tama : public Chara
{

public:

	void update(int timeSinceLast);

	Tama(Game *game) : directionX(0), directionY(0), live(0), Chara(game) {}

	float directionX;
	float directionY;
	bool	live;

};

class Game
{

public:


	// 1�t���[�����̏���
	void update(int timeSinceLast);

	// �e�������
	Tama *createTama(void); 

	Game(int win_width, int win_height, const TCHAR *playerGraph, const TCHAR *tamaGraph, int numMaxTama);
	~Game(void);

private:

	Player *pPlayer;

	/* 
		�evector�̋����ɂ���
		����vector��Game�R���X�g���N�g���ɍő吔����Tama��new���Avector�ɂ��̃|�C���^���i�[
		���ׂĂ�Tama::live��false�ɃZ�b�g�BcreateTama()�Œe��������live��true�ɐݒ肳���B
		Game::update()���ɁA��ʊO�ɏo�Ă���e��Tama::live��false�ɃZ�b�g���鏈��������A
		Game::update()�̍Ō�ŁATama::live��true�̂��̂�vector���̑O���֏W�߂鏈�����s���B
		createTama()����vector���ōł��O���ɂ���live��false�ł�����̂����������e�Ƃ��Ďg�p�����
	*/
	std::vector<Tama*>	tama;
	TamaIt							tamaFreePos;	// �g���ĂȂ��e�̐擪�ʒu
		
	int									winWidth;			// �E�C���h�E��
	int									winHeight;		// �E�C���h�E����

	int									tamaGraphID;	// �e�p�O���t�B�b�NID
};

