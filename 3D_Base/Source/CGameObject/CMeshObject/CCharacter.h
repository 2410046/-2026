#pragma once
#include "CGameObject/CMeshObject/CStaticMeshObject.h"
//#include "Reaction/CReaction.h"
/**************************************************
*   キャラクタークラス
**/
class CCharacter
	: public CStaticMeshObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Update() override;
	virtual void Draw(const CCamera* pCamera) override;
protected:
	float	m_Speed;	//移動速度
	D3DXQUATERNION m_Quat;
	float t = 0.f;
};