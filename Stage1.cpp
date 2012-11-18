//Stage1.cpp


#include "Stage1.hpp"

//定数定義
#define ITA_SIZE 24.0	//床の大きさ
#define KUNE_IDORYOU 0.2	//くねくね移動時の移動量
#define KUNE_KAITEN 2.0	//回転量(単位は度)


//////////////////////
//チェックするキー
//2のn乗の数を使う。(ビットと対応)
//新しく追加するときは、defineで定義して、Keys[]にも登録する。
#define KEY_A 1		// = 10000000 …
#define KEY_D 2		// = 01000000 …
#define KEY_W 4		// = 00100000 …
#define KEY_S 8
#define KEY_SPACE 16

static int Keys[] = {	//チェックするキーの登録
		'a',	//1
		'd',	//2
		'w',	//4
		's',	//8
		' '		//16
};

/*-----------------------------------------------------------------------------------*
	ステージ1 クラス
 *-----------------------------------------------------------------------------------*/

//コンストラクタ（初期化）
Stage1::Stage1() : ita(ITA_SIZE, ITA_SIZE)
{
	//くねくねの読み込み
	char a[]="Model/anim2.x";
	model.Load(a, false);
	//Xオブジェクト作成
	kune.setXModel(&model);
	kune.offset.y=-0.2;
	//初期化
	kune_vec.x=0.0; kune_vec.y=0.0; kune_vec.z=1.0;	//くねくねの前方向ベクトル
	
	//ライトの位置セット
	light0pos[0] = 1.0;
	light0pos[1] = 10.0;
	light0pos[2] = 5.0;
	light0pos[3] = 1.0;
	
	//箱の回転角度初期化
	rot = 0;
	
	//キー
	key_on=0;
}


//画面再描画時によばれる(1フレーム毎に呼ばれる)
void Stage1::Disp()
{
	glLoadIdentity();
	
	//ライトの位置セット
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	
	//カメラの位置セット
	gluLookAt(0.0,5.0,-15.0, kune.pos.x,kune.pos.y,kune.pos.z, 0.0,1.0,0.0);
	
	//移動させる
	kune.force = 0.0;
	if( key_on & KEY_W ){	//前へ
		kune.force += kune_vec * KUNE_IDORYOU;
	}
	if( key_on & KEY_S ){	//後ろへ
		kune.force -= kune_vec * KUNE_IDORYOU;
	}
	if( key_on & KEY_A ){	//左回転
		kune.angle.y += KUNE_KAITEN;	//くねくねを回転
		kune_vec.x = sin(kune.angle.y/180 * M_PI);	//前方向ベクトルを修正「/180*M_PI」で度→radへ変換
		kune_vec.z = cos(kune.angle.y/180 * M_PI);
	}
	if( key_on & KEY_D ){	//右回転
		kune.angle.y -= KUNE_KAITEN;
		kune_vec.x = sin(kune.angle.y/180 * M_PI);
		kune_vec.z = cos(kune.angle.y/180 * M_PI);
	}
	
	//適用
	kune.pos += kune.force;
	
	
	//床表示
	ita.Render();
	//くねくねを表示する
	kune.Render();
	
	// 箱を表示する
	//赤色のマテリアルをセット
	setDefaultMaterial();
	GLfloat color[4] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glTranslated(0.0, 0.0, -2.0);
	glRotatef(5*rot, 0.0, 1.0, 0.0);	//y軸まわり回転
	glutSolidCube(1.0);	//箱
	
	rot++;	//回転角度を増やしていく
	
	if( key_on & KEY_SPACE ){	//キーのチェック
		sprintf(str, "SPACE ON");
	}else{
		sprintf(str, "SPACE OFF");
	}
}

//2Dの描画
void Stage1::Disp2D(int Width, int Height){
	glColor4f(0.0,0.0,0.0, 1.0);	//カラー
	DRAW_STRING(10, Height-30, fps(), GLUT_BITMAP_TIMES_ROMAN_24);	//FPS表示
	DRAW_STRING(10, Height-50, str, GLUT_BITMAP_TIMES_ROMAN_24);	//スペースキーの状態表示
}

//入力処理
void Stage1::Input(char event, int key, int x, int y){
	switch(event){
	case SC_INPUT_KEY_DOWN:	//キーが押されたとき
		SetKeyState(&key_on, key, true, Keys, sizeof(Keys) );
		break;
	case SC_INPUT_KEY_UP:	//キーが離されたとき
		SetKeyState(&key_on, key, false, Keys, sizeof(Keys) );
		break;
	}
}

//デストラクタ（終了処理）
Stage1::~Stage1(){
}


