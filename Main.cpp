#include <cstdio>
#include <GL/glut.h>

//関数のプロトタイプ宣言
void disp();

//エントリーポイント
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("OpenGLGame");
	glutDisplayFunc(disp);
	glutMainLoop();
	
	return 0;
}

//画面の書き換え
void disp(void)
{
}
