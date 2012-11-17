//Stage2.cpp


#include "Stage2.hpp"


/*-----------------------------------------------------------------------------------*
	ステージ2 クラス
 *-----------------------------------------------------------------------------------*/

//コンストラクタ（初期化）
Stage2::Stage2()
{
	lot = 0;
}


//画面再描画時によばれる(1フレーム毎に呼ばれる)
void Stage2::Disp(){
	// 初期化する（移動や回転などを最初の状態にする）
	glLoadIdentity();

	// 箱を表示する
	glTranslated(0.0, 0.0, -2.0);
	glRotatef(5*lot, 0.0, 1.0, 0.0);	//y軸まわり回転
	glutSolidCube(1.0);	//箱

	lot++;	//回転角度を増やしていく
}

//2Dの描画
void Stage2::Disp2D(){
}

//入力処理
void Stage2::Input(char event, int key, int x, int y){
	switch(event){
	case SC_INPUT_KEY_DOWN:
		if( key == ' ' ){	//スペースキーが押された時
			ChangeStage( new Stage1 );	//ステージ変更
		}
		break;
	}
}

//デストラクタ（終了処理）
Stage2::~Stage2(){
}


