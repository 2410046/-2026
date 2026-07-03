#include "CFiring.h"


CFiring::CFiring()
    :CReaction()
{
}


void CFiring::Apply(
	const D3DXQUATERNION Quaternion)
{
	m_ShotBaseRot = Quaternion;//クオータニオンを取得
	m_vQuaternion;
}

void CFiring::Update()
{
	m_State.timer += 0.1f;

	float t = m_State.timer / 10.0f;

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
		m_State.timer = 0.f;
		//return true;
		//m_MoveState = enMoveState::Live;
	}
}
