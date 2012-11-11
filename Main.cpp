//Main.cpp

#include <GL/freeglut.h>
#include <cstdio>

//グローバル変数の宣言
int WindowWidth = 400;	//ウィンドウ幅
int WindowHeight = 400;	//ウィンドウ高さ
const char WindowTitle[] = "OpenGLGame";	//ウィンドウタイトル

//関数のプロトタイプ宣言
void Init();
void Display();
void Reshape(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void Close();



/*-----------------------------------------------------------------------------------*
    エントリーポイント、初期化
 *-----------------------------------------------------------------------------------*/

//エントリーポイント
int main(int argc, char *argv[])
{
	//GLUT初期化
	glutInit(&argc, argv);
	
	//ウィンドウ作成
	glutInitWindowSize(WindowWidth, WindowHeight);	//ウィンドウサイズ
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);	//RGBAカラー、zバッファ、ダブルバッファリング
	glutCreateWindow(WindowTitle);	//ウィンドウを作る
	
	//コールバック関数の登録
	glutDisplayFunc(Display);	//再描画時
	glutCloseFunc(Close);	//ウィンドウが閉じられたとき
	glutReshapeFunc(Reshape);	//ウィンドウサイズ変更時
	glutKeyboardFunc(Keyboard);	//キー入力
	glutKeyboardUpFunc(KeyboardUp);	//キーが離された
	
	//初期化
	Init();
	
	//メインループ
	glutMainLoop(); //※決して返ってこない
	
	return 0;
}

//初期化処理
void Init(void)
{
	//　バックバッファをクリアする色(背景色)の指定
	glClearColor(0.5, 0.5, 1.0, 1.0);
	
	//　深度テストON
	glEnable(GL_DEPTH_TEST);
	
	//ライト
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	//片面表示（高速化のため）
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


/*-----------------------------------------------------------------------------------*
    画面描き換え
 *-----------------------------------------------------------------------------------*/

// 画面描き換え
void Display(){
	//　バックバッファをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// 箱を表示する
	glTranslated(0.0, 0.0, -2.0);
	glutSolidCube(1.0);	//箱

	//ダブルバッファ入れ替え
	glutSwapBuffers();
}

// ウィンドウサイズ変更
void Reshape(int x, int y)
{
	//　ウィンドウサイズを保存
	// 今のとこは、保存する意味はないけど、将来つかうので
	WindowWidth = x;
	WindowHeight = y;
	
	//　ビューポートの設定
	glViewport(0, 0, WindowWidth, WindowHeight);
	
	//　射影行列の設定
	glMatrixMode(GL_PROJECTION);	//PROJECTION行列を操作
	glLoadIdentity();
	gluPerspective(45.0, (double)WindowWidth/(double)WindowHeight, 0.1, 1000.0);	//設定
}

/*-----------------------------------------------------------------------------------*
    入力関係
 *-----------------------------------------------------------------------------------*/

// キーボード処理
void Keyboard(unsigned char key, int x, int y)
{
	switch ( key ){
	case '\033':	//Esc
		Close();
		exit(0);
		break;
	}
}

//キーが離された
void KeyboardUp(unsigned char key, int x, int y)
{
	
}

/*-----------------------------------------------------------------------------------*
    その他
 *-----------------------------------------------------------------------------------*/

// 終了処理
void Close(void)
{
	printf("finish!\n");
}



