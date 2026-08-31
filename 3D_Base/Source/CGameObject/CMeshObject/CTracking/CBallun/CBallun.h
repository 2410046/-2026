#pragma once
#include "CMeshObject/CCharacter.h"
/********************************************************************************
* バルーンクラス
* プレイヤーのライフのようなもの
**/
class CBallun
	:public CCharacter
{
public:
	CBallun();
	virtual~CBallun()override;
	void LoadData();
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(
		const CCamera* pCamera) override;
	//風船の設定
	void SetBalloon(
		const D3DXVECTOR3& position,
		bool isHit,
		int life);
private:
	// 座標
	D3DXVECTOR3 m_PlayerPos;
	int m_Life;
};
