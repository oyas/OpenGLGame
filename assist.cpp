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
