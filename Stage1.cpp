//stage1.cpp


#include "Stage1.hpp"


/*-----------------------------------------------------------------------------------*
	ステージ1 クラス
 *-----------------------------------------------------------------------------------*/

//コンストラクタ（初期化）
Stage1::Stage1()
{

}


//画面再描画時によばれる(1フレーム毎に呼ばれる)
void Stage1::Disp(){
	
}

//2Dの描画
void Stage1::Disp2D(){
}

//入力処理
void Stage1::Input(char event, int key, int x, int y){
	switch(event){
	case SC_INPUT_KEY_DOWN:	//キーが押されたとき
		printf("%cが押された!\n", key);
		break;
	case SC_INPUT_KEY_UP:	//キーが離されたとき
		printf("%cが離された!\n", key);
		break;
	}
}

//デストラクタ（終了処理）
Stage1::~Stage1(){
}


