#include "CBoost.h"


CBoost::CBoost(MoveType tag)
    :CReaction(tag)
{
}

void CBoost::Apply(
    const D3DXVECTOR3& direction,
    float power, float time, 
    const D3DXQUATERNION& rotation)
{
        // 前方向(X+)
        D3DXVECTOR3 forward(1.0f, 0.0f, 0.f);

        // 回転行列へ変換
        D3DXMATRIX matRot;
        D3DXMatrixRotationQuaternion(&matRot, &rotation);

        // forward を回転
        D3DXVECTOR3 dir;
        D3DXVec3TransformNormal(&dir, &forward, &matRot);

        D3DXVec3Normalize(&dir, &dir);

        m_State.active = true;
        m_State.velocity = dir * power;
        m_State.timer = time;
}

void CBoost::Update()
{
    if (m_State.active == false)
    {
        return;
    }

    m_vPosition += m_State.velocity;

    // 減衰（吹っ飛び感）
    m_State.velocity *= 0.9f;

    m_State.timer -= 1.0f;

    if (m_State.timer <= 0.0f)
    {
        m_State.active = false;
        m_State.velocity = D3DXVECTOR3(0.f, 0, 0);
    }
}
