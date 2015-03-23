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


	// 1フレーム分の処理
	void update(int timeSinceLast);

	// 弾を一つ生成
	Tama *createTama(void); 

	Game(int win_width, int win_height, const TCHAR *playerGraph, const TCHAR *tamaGraph, int numMaxTama);
	~Game(void);

private:

	Player *pPlayer;

	/* 
		弾vectorの挙動について
		このvectorはGameコンストラクト時に最大数分のTamaをnewし、vectorにそのポインタを格納
		すべてのTama::liveはfalseにセット。createTama()で弾が発生しliveはtrueに設定される。
		Game::update()時に、画面外に出ている弾はTama::liveをfalseにセットする処理がされ、
		Game::update()の最後で、Tama::liveがtrueのものをvector内の前方へ集める処理を行う。
		createTama()時はvector内で最も前方にあるliveがfalseであるものが発生した弾として使用される
	*/
	std::vector<Tama*>	tama;
	TamaIt							tamaFreePos;	// 使われてない弾の先頭位置
		
	int									winWidth;			// ウインドウ幅
	int									winHeight;		// ウインドウ高さ

	int									tamaGraphID;	// 弾用グラフィックID
};

