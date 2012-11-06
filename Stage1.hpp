//stage1.h
#ifndef _STAGE1_HPP
#define _STAGE1_HPP

//インクロード
#include "assist.hpp"

#define BOX_MAX 3	//浮遊する箱の数

/*-----------------------------------------------------------------------------------*
	ステージ１　クラス
	Main.cppでインスタンスが作られ関数が呼ばれる
 *-----------------------------------------------------------------------------------*/
class Stage1 : public StageClass{
private:
	//くねくね用
	XModel model;		//Xモデルクラス
	XObj kune;	//Xオブジェクト
	Vector3 kune_vec;	//前方向の向き(移動時に使用)vector
	Vector3 kune_svec;	//横方向の向き(移動時に使用)side_vector
	
	//ライト
	GLfloat light0pos[4];	//ライトの位置
	
	//カメラ
	float cam_z, cam_r, cam_rx;	//カメラの向き z:距離 r:横周り rx:縦周り
	
	//fps表示用文字列
	char *str_fps;
	
	//キーの状態
	int key_on;
	
	//床クラス
	Ita ita;
	
	int onface;	//着地しているかどうか
	
	//浮遊する箱
	float rot;	//回転角度
	Vector3 pos[BOX_MAX];
	
	//得点用
	int score;
	char str_score[20];
	
	//タイマー
	int timer;
	char str_timer[20];
	

public:
	//コンストラクタ
	Stage1();
	
	//画面再描画時によばれる(1フレーム毎に呼ばれる)
	virtual void Disp();
	
	//2D
	virtual void Disp2D(int Width, int Height);
	
	//入力処理
	virtual void Input(char event, int key, int x, int y);
	
	//デストラクタ
	virtual ~Stage1();
};


#endif	//_STAGE1_HPP
