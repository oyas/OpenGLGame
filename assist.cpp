//assist.cpp


#include "assist.hpp"

/*-----------------------------------------------------------------------------------*
	FPS測定
	毎フレームごとに呼ぶことで、"FPS: --.-"という形式の文字列へのアドレスを返す。
 *-----------------------------------------------------------------------------------*/
char* fps(void)
{
	static int count=0, t1, t2=0;	//count:前回からのフレーム数 t1:現在の時間 t2:前回測定時の時間
	static char txt_fps[20]="";	//fpsが書かれる文字列
	
	t1 = glutGet(GLUT_ELAPSED_TIME);
	if(t1 - t2 > 1000) {	//一秒ごとにfps計算
		sprintf(txt_fps, "FPS: %g", (1000.0 * count) / (t1 - t2) );
		t2 = t1;
		count = 0;
	}
	count++; 
	
	return txt_fps;
}


/*-----------------------------------------------------------------------------------*
	デフォルトマテリアルセット
	マテリアルをデフォルト値に戻す。カラーは白がセットされる
	参考：http://wisdom.sakura.ne.jp/system/opengl/gl16.html
 *-----------------------------------------------------------------------------------*/
void setDefaultMaterial(){
	//デフォルトマテリアル
	GLfloat defoma_a[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat defoma_d[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat defoma_i[4] = { 0.0, 0.0, 0.0, 1.0 };
	
	//　基本色
	glColor4f(1.0, 1.0, 1.0, 1.0);

	//　Ambient Color
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, defoma_a);
	
	//　Diffuse Color
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, defoma_d);

	//　Specular Color
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defoma_i);

	//　Emissive Color
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, defoma_i);

	//　Shininess
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0);
}


/*-----------------------------------------------------------------------------------*
	文字描画
	2D専用。描画位置と描画文字列、フォントを指定すると、描いてくれる。
 *-----------------------------------------------------------------------------------*/
void DRAW_STRING(int x, int y, char *string, void *font)
{
	int len, i;
	
	glRasterPos2f(x, y);	//書き始めの位置
	len = (int)strlen(string);
	for (i = 0; i < len; i++){
		glutBitmapCharacter(font, string[i]);	//ビットマップフォントを使って文字描画（こいつが文字描画本体）
	}
}


/*-----------------------------------------------------------------------------------*
	床クラス
	床を表示&管理する
 *-----------------------------------------------------------------------------------*/
//コンストラクタ
Ita::Ita(float u, float v){
	pos.x=0.0;
	pos.y=0.0;
	pos.z=0.0;
	size.x = 0.0;
	size.y = 0.0;
	SetRender(u, v);
}

//セット。ディスプレイリストを作成する
//１２分割の白黒の板をつくる
void Ita::SetRender(float u, float v){
	const static GLfloat ground[][4] = {   /* 台の色 */
		{ 0.6, 0.6, 0.6, 1.0 },
		{ 1.0, 1.0, 1.0, 1.0 }
	};
	
	DisplayList = glGenLists(1);//ディスプレイリストを作成
	glNewList(DisplayList,GL_COMPILE); //コンパイルのみ
	
	//マテリアルをデフォルトにもどす。
	setDefaultMaterial();
	
	//交互に白黒のポリゴンを並べて床を作っていく。
	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	for (int j = -6; j < 6; ++j) {
		for (int i = -6; i < 6; ++i) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
			glVertex3f((GLfloat)i*(u/12.0), 0.0, (GLfloat)j*(v/12.0));
			glVertex3f((GLfloat)i*(u/12.0), 0.0, (GLfloat)(j + 1)*(v/12.0));
			glVertex3f((GLfloat)(i + 1)*(u/12.0), 0.0, (GLfloat)(j + 1)*(v/12.0));
			glVertex3f((GLfloat)(i + 1)*(u/12.0), 0.0, (GLfloat)j*(v/12.0));
		}
	}
	glEnd();
	
	glEndList();	//ディスプレイリストおわり
	
	//サイズ保存
	size.x = u; size.y = v;
	//床の四角形の頂点位置保存
	vertex[0].x = -u/2; vertex[0].y = 0.0; vertex[0].z = -v/2;
	vertex[1].x =  u/2; vertex[1].y = 0.0; vertex[1].z = -v/2;
	vertex[2].x =  u/2; vertex[2].y = 0.0; vertex[2].z =  v/2;
	vertex[3].x = -u/2; vertex[3].y = 0.0; vertex[3].z =  v/2;
}

//描画
void Ita::Render(){
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);	//移動
	glCallList(DisplayList);	//描画
	glPopMatrix();
}


/*-----------------------------------------------------------------------------------*
	キー入力補助
	KeyBufのKeysと対応するビットを変更する。
	例：
	Keys = { a, b, c, d }　とする。
	KeyBufの中身は、２進数(実際のメモリ配置)で表すと
	00100000 00000000 00000000 00000000 (32ビット)
	abcd
	１ビットづつ順番にa,b,c,dと割り当て、そのビットが1か0かでキーの状態を保存する。
	KeyBufが上記の時は、cは押されていて、他のキーは離されている。
 *-----------------------------------------------------------------------------------*/
//KeyBufの状態を変更する。
bool SetKeyState(int *KeyBuf, int key, bool onoff, int *Keys, int size)
{
	//サイズを要素数に変換	
	size /= sizeof(int);

	//サイズが大き過ぎないかチェック
	if( size >= sizeof(int)*8 )
		return false;
	
	//サイズ分処理
	for(int i=0; i<size; i++){
		if( key == Keys[i] ){
			int k=1;
			if( onoff )
				*KeyBuf |= k << i;	//ビットON
			else
				*KeyBuf &= ~( k << i );	//ビットOFF
		}
	}
	
	return true;
}

//状態を取得。押されていたらtrue
bool GetKeyState(int *KeyBuf, int key, int *Keys, int size)
{
	//サイズが大き過ぎないかチェック
	if( size >= sizeof(int)*8 )
		return false;
	
	//サイズ分処理
	for(int i=0; i<size; i++){
		if( key == Keys[i] ){
			int k=1;
			return *KeyBuf & (k<<i);
		}
	}
	
	return true;
}

