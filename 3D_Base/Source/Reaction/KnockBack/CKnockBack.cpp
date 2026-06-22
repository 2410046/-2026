#include "CKnockBack.h"

CKnockBack::CKnockBack(MoveType tag)
    :CReaction(tag)
{
}

void CKnockBack::Apply(
    const D3DXVECTOR3& from, const D3DXVECTOR3& to, float power, float time)
{
    D3DXVECTOR3 dir = to - from;

    float len = D3DXVec3Length(&dir);
    if (len <= 0.0001f)
        return;

    dir /= len;

    m_State.active = true;
    m_State.velocity = dir * power;
    m_State.timer = time;
}

void CKnockBack::Update()
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