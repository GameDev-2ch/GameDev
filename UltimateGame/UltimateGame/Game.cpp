#include "Game.h"
#include <math.h>

#include <assert.h>

void Chara::update(int timeSinceLast)
{

	if(graphID != -1){
		DrawGraph((int)x , (int)y , graphID , TRUE);
	}
}

int Chara::setGraphicFromFile(const TCHAR *filename)
{

	if(graphID != -1) return -1;
	graphID = LoadGraph(filename);

	return graphID;
}

int Chara::setGraphicFromID(int graph_id)
{

	if(graphID != -1) return -1;
	graphID = graph_id;

	return graphID;
}

void Player::shot(void)
{

	int div = 18;
	float pi = 3.14159265f;
	float shot_range = pi * 45 / 180;

	float speed, sin_tmp, cos_tmp;
	Tama *tama;
	for(int j=1;j<=div;j++){

		sin_tmp = sin(shot_range / div * j);
		cos_tmp = cos(shot_range / div * j);

		speed = 0.4f;
		for(int i=0;i<5;i++){

			tama = pGame->createTama();
			tama->x = x;
			tama->y = y;
			tama->directionX = sin_tmp * speed;
			tama->directionY = -cos_tmp * speed;

			tama = pGame->createTama();
			tama->x = x;
			tama->y = y;
			tama->directionX = -sin_tmp * speed;
			tama->directionY = -cos_tmp * speed;

			speed *= 0.9f;
		}
	}
}

void Player::update(int timeSinceLast)
{

	// �v���C���[�L�[����
	float speed = 0.1f;

	if(CheckHitKey(KEY_INPUT_A)){
		x -= speed * timeSinceLast;
	}	else if(CheckHitKey(KEY_INPUT_D)){
		x += speed * timeSinceLast;
	}
	
	if(CheckHitKey(KEY_INPUT_W)){
		y -= speed * timeSinceLast;
	}else if(CheckHitKey(KEY_INPUT_S)){
		y += speed * timeSinceLast;
	}

	int winWidth, winHeight, charaWidth, charaHeight, color;

	GetScreenState(&winWidth, &winHeight, &color);
	GetGraphSize(graphID, &charaWidth, &charaHeight);

	if(x < 0) x = 0;
	else if(x > winWidth - charaWidth) x =  (float)winWidth - charaWidth;

	if(y < 0) y = 0;
	else if(y > winHeight - charaHeight) y =  (float)winHeight - charaHeight; 

	Chara::update(timeSinceLast);


	// �}�E�X�ŃV���b�g
	static bool mouseL = false;

	if(GetMouseInput() & MOUSE_INPUT_LEFT ){

		if(!mouseL){

			shot();
			mouseL = true;
		}
	}else{

		mouseL = false;
	}
}

void Tama::update(int timeSinceLast)
{
	x += directionX * timeSinceLast;
	y += directionY * timeSinceLast;

	Chara::update(timeSinceLast);
}

void Game::update(int timeSinceLast)
{

	pPlayer->update(timeSinceLast);

	int tama_width, tama_height;

	GetGraphSize(tamaGraphID, &tama_width, &tama_height);

	for(TamaIt it=tama.begin();it!=tamaFreePos;++it){

		(*it)->update(timeSinceLast);

		if((*it)->x < 0 || (*it)->x > winWidth + tama_width || 
			(*it)->y < 0 || (*it)->y > winHeight + tama_height)
		{
			(*it)->live = false;
		}
	}

	// live��true�̂��̂�O���ɏW�߂�
	TamaIt it, it_false;
	bool find_to = false;
	for(it=tama.begin(), it_false=tamaFreePos;it!=tamaFreePos;++it){

		if((*it)->live == find_to){

			if(find_to){

				// swap
				Tama *tamap = (*it_false);
				(*it_false) = (*it);
				(*it) = tamap;
				find_to = !find_to;
				it = it_false;

			}else{

				it_false = it;
				find_to = !find_to;
			}
		}
	}

	tamaFreePos = it_false;

#ifdef	_DEBUG // �f�o�b�O�p

	bool f=true;
	int live_count=0;
	int false_count=0;
	for(TamaIt t=tama.begin();t!=tama.end();++t){

		if(t==tamaFreePos) f=false;

		if(f){

			live_count++;
			assert((*t)->live == true);

		}	else {

			false_count++;
			assert((*t)->live == false);
		}
	}

	DrawFormatString(0, 48, GetColor(255, 255, 255), _T("   Live:%d"), live_count);
	DrawFormatString(0, 64, GetColor(255, 255, 255), _T("NotLive:%d"), false_count);

#endif

}

Tama *Game::createTama(void)
{

	Tama *ret;
	if(tamaFreePos == tama.end()){

		ret = new Tama(this);
		tama.push_back(ret);
		tamaFreePos = tama.end();
		ret->setGraphicFromID(tamaGraphID);

	}else{

		ret = *tamaFreePos;
		tamaFreePos++;
	}

	ret->live = true;
	return ret;
}

Game::Game(int win_width, int win_height, const TCHAR *playerGraph, const TCHAR *tamaGraph, int numMaxTama) : pPlayer(0)
{

	winWidth = win_width;
	winHeight = win_height;

	pPlayer = new Player(this);
	pPlayer->setGraphicFromFile(playerGraph);
	pPlayer->x = 250;
	pPlayer->y = 350;

	tamaGraphID = LoadGraph(tamaGraph);

	// �\�ߒe�I�u�W�F�N�g��new���Ă���
	tama.resize(numMaxTama);
	for(TamaIt it=tama.begin();it!=tama.end();++it){
		(*it) = new Tama(this);
		(*it)->live = false;
		(*it)->setGraphicFromID(tamaGraphID);
	}

	tamaFreePos = tama.begin();

}

Game::~Game(void)
{

	delete pPlayer;

	for(TamaIt it=tama.begin();it!=tama.end();++it){
		delete (*it);
	}
}
