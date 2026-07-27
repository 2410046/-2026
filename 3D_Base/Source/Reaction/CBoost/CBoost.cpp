#include "CBoost.h"


CBoost::CBoost()
    :CReaction()
{
}

void CBoost::Apply(const ReactionParam& param)
{
        // 前方向(X+)
        D3DXVECTOR3 forward(1.0f, 0.0f, 0.f);

        // 回転行列へ変換
        D3DXMATRIX matRot;
        D3DXMatrixRotationQuaternion(&matRot, &param.rot);

        // forward を回転
        D3DXVECTOR3 dir;
        D3DXVec3TransformNormal(&dir, &forward, &matRot);

        D3DXVec3Normalize(&dir, &dir);

        m_State.active = true;
        m_State.velocity = dir * 0.5f;
        m_State.timer = 10.f;
}

void CBoost::Update()
{
    if (m_State.active == false)
    {
        return;
    }

    *m_pPosition += m_State.velocity;

    // 減衰（吹っ飛び感）
    m_State.velocity *= 0.9f;

    m_State.timer -= 1.0f;

    if (m_State.timer <= 0.0f)
    {
        m_State.active = false;
        m_State.velocity = D3DXVECTOR3(0.f, 0, 0);
    }
}
