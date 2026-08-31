#pragma once
#include "CMeshObject/CCharacter.h"
//ブースとを使ってショットの動作を
/********************************************************************************
* ショットクラス
*
**/
class CShot
	:public CCharacter
{
public:
	CShot();
	virtual~CShot()override;
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(
		const CCamera* pCamera) override;

	void SetShot(
		const D3DXVECTOR3& position,
		const D3DXQUATERNION& Quaternion,
		int ID);
private:
	std::shared_ptr<CReaction>	m_pReaction;	//当たり判定
	bool m_ShotFlag;
};
