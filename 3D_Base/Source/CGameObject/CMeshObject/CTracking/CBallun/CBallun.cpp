#include "CBallun.h"
CBallun::CBallun()
    : m_PlayerPos(0.0f, 0.0f, 0.0f)
    , m_Life(0)
{
}

CBallun::~CBallun()
{
}
void CBallun::LoadData()
{
}
//動作関数
void CBallun::Update()
{
    // Playerの上に表示
    m_vPosition.y += 1.5f;

	CCharacter::Update();
}
//描画関数
void CBallun::Draw(const CCamera* pCamera)
{
	CCharacter::Draw(pCamera);
}

void CBallun::SetBalloon(
    const D3DXVECTOR3& position,bool isHit, int life)
{

    //========================================================
    // LifeはCGameから受け取る
    //========================================================

    m_Life = life;
    //========================================================
    // 座標はTrackingから取得
    //========================================================

    m_vPosition = position;
}
