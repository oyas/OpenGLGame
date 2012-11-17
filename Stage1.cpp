//Stage1.cpp


#include "Stage1.hpp"


/*-----------------------------------------------------------------------------------*
	ステージ1 クラス
 *-----------------------------------------------------------------------------------*/

//コンストラクタ（初期化）
Stage1::Stage1()
{
	lot = 0;
	
	//赤色のマテリアルをセット
	GLfloat color[4] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
}


//画面再描画時によばれる(1フレーム毎に呼ばれる)
void Stage1::Disp()
{
	glLoadIdentity();
	
	// 箱を表示する
	glTranslated(0.0, 0.0, -2.0);
	glRotatef(5*lot, 0.0, 1.0, 0.0);	//y軸まわり回転
	glutSolidCube(1.0);	//箱
	
	lot++;	//回転角度を増やしていく
}

//2Dの描画
void Stage1::Disp2D(int Width, int Height){
	glColor4f(0.0,0.0,0.0, 1.0);	//カラー
	DRAW_STRING(10, Height-30, fps(), GLUT_BITMAP_TIMES_ROMAN_24);	//FPS表示
}

//入力処理
void Stage1::Input(char event, int key, int x, int y){
	switch(event){
	case SC_INPUT_KEY_DOWN:	//キーが押されたとき
		if( key == ' ' ){	//スペースキーが押された時
			setDefaultMaterial();	//マテリアルをデフォルトに戻す
		}
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


