//stage1.cpp


#include "Stage1.hpp"
#include<time.h>	//乱数初期化時に使用


//定数定義
#define KUNE_IDORYOU 0.2	//くねくね移動時の移動量
#define KUNE_CAMRA 0.05	//カメラ操作時の移動量
#define ITA_SIZE 24.0	//床の大きさ
#define GAME_GRAVITY 0.02	//重力
#define JUMP_SPEED 0.3	//ジャンプ力
#define GAME_TIMER 1000	//タイムアウトまでの時間

//////////////////////
//チェックするキー
static int Keys[] = {	//チェックするボタン
		'a',	//1
#define KEY_A 1
		'd',	//2
#define KEY_D 2
		'w',	//4
#define KEY_W 4
		's',		//8
#define KEY_S 8
		' '		//16
#define KEY_SPACE 16
};

/*-----------------------------------------------------------------------------------*
	ステージ1 クラス
 *-----------------------------------------------------------------------------------*/

//コンストラクタ（初期化）
Stage1::Stage1() : ita(ITA_SIZE, ITA_SIZE)
{
	//乱数初期化
	srand((unsigned)time(NULL));
	
	//くねくねの読み込み
	char a[]="Models/anim2.x";
	kune.offset.y=-0.2;
	model.Load(a, 0);
	//Xオブジェクト作成
	kune.setXModel(&model);
	//初期化
	kune_vec.x=0.0; kune_vec.y=0.0; kune_vec.z=-1.0;	//どせいの前方向ベクトル
	kune_svec.x=1.0; kune_svec.y=0.0; kune_svec.z=0.0;	//どせいの横方向ベクトル
	
	//ライトの位置セット
	light0pos[0] = 1.0;
	light0pos[1] = 10.0;
	light0pos[2] = 5.0;
	light0pos[3] = 1.0;
	//カメラ角度
	cam_z=20.0; cam_r=M_PI; cam_rx=M_PI_4/2;
	//キー
	key_on=0;
	
	//浮遊する箱
	rot = 0.0;
	for(int a=0; a<BOX_MAX; a++){
		pos[a].x = ((float)rand() / (float)RAND_MAX) * ITA_SIZE - ITA_SIZE/2.0;
		pos[a].y = ((float)rand() / (float)RAND_MAX) * 3.0 + 0.5;
		pos[a].z = ((float)rand() / (float)RAND_MAX) * ITA_SIZE - ITA_SIZE/2.0;
	}
	score = 0;
	str_score[0] = '\0';
	timer = GAME_TIMER;
	str_timer[0] = '\0';
}


//画面再描画時によばれる(1フレーム毎に呼ばれる)
void Stage1::Disp()
{
	glLoadIdentity();
	
	//ライトの位置セット
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	
	//カメラの位置計算
	float _x,_y,_z;
	_x = sin(cam_r) * cos(cam_rx) * cam_z;
	_y = sin(cam_rx) * cam_z;
	_z = cos(cam_r) * cos(cam_rx) * cam_z;
	//カメラの位置セット
	gluLookAt(kune.pos.x-_x, kune.pos.y+_y, kune.pos.z-_z, 
		kune.pos.x,kune.pos.y,kune.pos.z, 0.0,1.0,0.0);
	
	
	//移動させる
	kune.force = 0.0;
	if( key_on & KEY_W ){	//前へ
		kune.force += kune_vec * KUNE_IDORYOU;
	}
	if( key_on & KEY_S ){	//後ろへ
		kune.force -= kune_vec * KUNE_IDORYOU;
	}
	if( key_on & KEY_A ){	//左回転
		cam_r += KUNE_CAMRA;
		if(cam_r>2*M_PI) cam_r -= 2*M_PI;
		//くねくねも回転
		kune.angle.y += KUNE_CAMRA*180/M_PI;
		kune_vec.x = -sin(kune.angle.y/180 * M_PI);
		kune_vec.z = -cos(kune.angle.y/180 * M_PI);
		kune_svec.x = kune_vec.z;
		kune_svec.z = -kune_vec.x;
	}
	if( key_on & KEY_D ){	//右回転
		cam_r -= KUNE_CAMRA;
		if(cam_r<-2*M_PI) cam_r += 2*M_PI;
		//くねくねも回転
		kune.angle.y -= KUNE_CAMRA*180/M_PI;
		kune_vec.x = -sin(kune.angle.y/180 * M_PI);
		kune_vec.z = -cos(kune.angle.y/180 * M_PI);
		kune_svec.x = kune_vec.z;
		kune_svec.z = -kune_vec.x;
	}
	//ジャンプ
	if( key_on & KEY_SPACE && onface){
			kune.speed.y += JUMP_SPEED;
	}
	
	//救出(下に落ちた場合の処理)
	if(kune.pos.y < -50.0){
			//初期位置へ戻す
			kune.pos.x = 0.0;
			kune.pos.y = 10.0;
			kune.pos.z = 0.0;
			kune.speed = 0.0;
	}
	
	//当たり判定 描画・物理処理等を各オブジェクトごとに行う
	{		
		kune.speed.y -= GAME_GRAVITY;	//重力
		Vector3 speed = kune.speed;	//現在のどせいのスピード＋力
		if( (kune.force.x<0 && speed.x>kune.force.x)||(kune.force.x>0 && speed.x<kune.force.x) ) speed.x = kune.force.x;
		if( (kune.force.y<0 && speed.y>kune.force.y)||(kune.force.y>0 && speed.y<kune.force.y) ) speed.y = kune.force.y;
		if( (kune.force.z<0 && speed.z>kune.force.z)||(kune.force.z>0 && speed.z<kune.force.z) ) speed.z = kune.force.z;
		Vector3 bspeed = speed;	//当たり判定前のspeedを保存
		
		//床との当たり判定
		if( -(ITA_SIZE / 2) < kune.pos.x + speed.x && kune.pos.x + speed.x < ITA_SIZE / 2 && 
			-(ITA_SIZE / 2) < kune.pos.z + speed.z && kune.pos.z + speed.z < ITA_SIZE / 2 && 
			kune.pos.y >= 0.0 && kune.pos.y + speed.y < 0.0 ){
			speed.y = -kune.pos.y;
			kune.speed = 0.0;
		}
		
		//摩擦 接地していたら止まる
		if( speed.y-bspeed.y != 0.0){
			kune.speed = 0.0;
			onface = 1;
		}else{
			onface = 0;
		}
		
		kune.pos += speed;	//適用
	}
		
	
	//床描画
	ita.Render();
	//くねくね描画
	kune.Render();
	
	//浮遊する箱
	rot += 1;
	for(int a=0; a<BOX_MAX; a++){
		//箱描画
		glPushMatrix(); //Push
		glTranslated(pos[a].x, pos[a].y, pos[a].z);
		glRotatef(rot, 0.0, 1.0, 0.0);	//y軸まわり回転
		setDefaultMaterial();
		GLfloat color[4] = { 1.0, 0.0, 0.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
		glutSolidCube(1.0);	//箱
		glPopMatrix(); //Pop
		//当たり判定
		Vector3 v = pos[a] - kune.pos;
		v.y -= 0.5;
		if( sqrt( v.x*v.x + v.y*v.y + v.z*v.z ) < 1.0 ){
			//得点加算
			if(timer >= 0) score++;
			sprintf(str_score, "SCORE : %d", score );
			//新しい位置
			pos[a].x = ((float)rand() / (float)RAND_MAX) * ITA_SIZE - ITA_SIZE/2.0;
			pos[a].y = ((float)rand() / (float)RAND_MAX) * 3.0 + 0.5;
			pos[a].z = ((float)rand() / (float)RAND_MAX) * ITA_SIZE - ITA_SIZE/2.0;
		}
	}
	
	//タイマー
	if( timer-- < 0 ){
		sprintf(str_timer, "TIME OUT");
	}else{
		sprintf(str_timer, "TIME : %d", timer);
	}
}

//2Dの描画
void Stage1::Disp2D(int Width, int Height){
	str_fps = fps();
	glColor4f(0.0,0.0,0.0, 1.0);	//カラー
	DRAW_STRING(10, Height-30, str_fps, GLUT_BITMAP_TIMES_ROMAN_24);
	DRAW_STRING(10, Height-50, str_score, GLUT_BITMAP_TIMES_ROMAN_24);
	DRAW_STRING(10, Height-70, str_timer, GLUT_BITMAP_TIMES_ROMAN_24);
}

//入力処理
void Stage1::Input(char event, int key, int x, int y){
	//ボタン状態チェック
	if( event==SC_INPUT_KEY_DOWN ){
		SetKeyState(&key_on, key, true, Keys, sizeof(Keys) );
	}else if( event==SC_INPUT_KEY_UP ){
		SetKeyState(&key_on, key, false, Keys, sizeof(Keys) );
	}
}

//デストラクタ（終了処理）
Stage1::~Stage1(){
}


