#include "CTracking.h"
#include "CGameObject/CMeshObject/CPlayer/CPlayerManager.h"	    //プレイヤークラス

//============================================================
// 対象を設定
//============================================================
void CTracking::SetTarget(CPlayer* pPlayer)
{
    m_pTarget = pPlayer;
}

//============================================================
// 座標取得
//============================================================
D3DXVECTOR3 CTracking::GetPosition() const
{
    if (m_pTarget == nullptr)
    {
        return D3DXVECTOR3(
            0.0f,
            0.0f,
            0.0f);
    }

    return m_pTarget->GetPosition();
}

//============================================================
// 方向取得
//============================================================
D3DXVECTOR3 CTracking::GetDirection() const
{
    if (m_pTarget == nullptr)
    {
        return D3DXVECTOR3(
            0.0f,
            0.0f,
            1.0f);
    }

    return m_pTarget->GetRotation();
}

//============================================================
// 対象取得
//============================================================
CPlayer* CTracking::GetTarget() const
{
    return m_pTarget;
}