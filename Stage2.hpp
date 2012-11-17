//Stage2.hpp
#ifndef _STAGE2_HPP
#define _STAGE2_HPP

//インクロード
#include "assist.hpp"
#include "Stage1.hpp"	//次のステージ


/*-----------------------------------------------------------------------------------*
	ステージ2　クラス
	Main.cppでインスタンスが作られ関数が呼ばれる
 *-----------------------------------------------------------------------------------*/
class Stage2 : public StageClass{
private:
	int lot;

public:
	//コンストラクタ
	Stage2();
	
	//画面再描画時によばれる(1フレーム毎に呼ばれる)
	virtual void Disp();
	
	//2D
	virtual void Disp2D();
	
	//入力処理
	virtual void Input(char event, int key, int x, int y);
	
	//デストラクタ
	virtual ~Stage2();
};


#endif	//_STAGE2_HPP
