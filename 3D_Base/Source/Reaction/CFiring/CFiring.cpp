#include "CFiring.h"


CFiring::CFiring(MoveType tag)
    :CReaction(tag)
{
}


void CFiring::Apply(const D3DXVECTOR3& from, const D3DXVECTOR3& to, float power, float time)
{

}

void CFiring::Update()
{
	m_StateTime += 0.1f;

	float t = m_StateTime / 10.0f;

	float pitch = D3DX_PI / 4.0f * sinf(t * D3DX_PI);

	D3DXQUATERNION tilt;
	D3DXQuaternionRotationYawPitchRoll(
		&tilt,
		0.f,
		0.f,
		pitch);

	// 常に固定のベースに対して合成
	m_vQuaternion = tilt * m_ShotBaseRot;
	if (t >= 1.0f)
	{
		m_StateTime = 0.f;
		m_MoveState = enMoveState::Live;
	}
}
