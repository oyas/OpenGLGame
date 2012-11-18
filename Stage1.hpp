//Stage1.hpp
#ifndef _STAGE1_HPP
#define _STAGE1_HPP

//インクロード
#include "assist.hpp"


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
	
	//ライト
	GLfloat light0pos[4];	//ライトの位置
	
	//床クラス
	Ita ita;
	
	//箱の回転
	int rot;
	
	//キーの状態
	int key_on;
	
	//画面表示用文字列
	char str[20];
	
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
