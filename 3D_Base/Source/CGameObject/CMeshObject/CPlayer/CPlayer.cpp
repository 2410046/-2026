#include "CPlayer.h"
#include "Asset/CXInput/CXInput.h"
#include "MathUtility.h"
#include "Collision/CreateCollider/CreateCollider.h"
#include "Collision/CollisionManager/CollisionManager.h"
#include <algorithm>

namespace
{
	//カプセルのサイズ
	float radius = 0.5f;
	float height = 0.7f;

	constexpr float TimeSpeed = 0.1f;	//経過速度
	constexpr float MaxTime   = 10.f;   //指定時間
	constexpr float Base_Size = 0.01f;
}
//コンストラクタ
CPlayer::CPlayer()
	: m_MoveState		( enMoveState::App )
	, m_StateTime		( 0.f )
	, m_ID				( 0 )
	, m_Life			( 3 )
	, m_Scale			( 0 )
	, m_ShotBaseRot		( 0.f,0.f,0.f,1.f)
{	
	//カプセルの当たり判定
	m_pCollider = CreateCollider::CreateCaupsule(
		radius, height, this, CollisionBase::Player);

	OutputDebugStringA("Player Created\n");
}
//デストラクタ
CPlayer::~CPlayer()
{
	CollisionManager::GetInstance()->Unregister(m_pCollider);
}
//動作関数
void CPlayer::Update()
{

	switch (m_MoveState)
	{

	case enMoveState::App:
	{
		m_Scale += 0.0001f;
		if (m_Scale>=Base_Size)
		{
			m_Scale = Base_Size;
			m_MoveState = enMoveState::Live;
		}
		//サイズを設定
		m_vScale = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
	}
		break;
	case enMoveState::Live:
		//コントローラー操作
		Controller();
		CCharacter::Update();
		break;
	case enMoveState::Down:

		m_angle += 0.1f; // 回転速度

		D3DXQuaternionRotationYawPitchRoll(
			&m_vQuaternion,
			m_angle,
			0.0f,
			0.0f);

		if (m_angle >= D3DX_PI * 2.0f)
		{
			m_MoveState = enMoveState::Live;
			m_angle = 0.f;
		}
		break;
	case enMoveState::Boost:
	{
		//プレイヤーの方向にまっすぐ進む
		//ブースと状態
		m_pBoost.Apply(m_vPosition, 0.5f, 10.f, m_vQuaternion);

		if (m_pBoost.TimeOut() == false)
		{
			m_MoveState = enMoveState::Live;
		}
	}
		break;
	case enMoveState::ShotIN://
		m_ShotBaseRot = m_vQuaternion;//クオータニオンを取得
		m_MoveState = enMoveState::Shot;//ショット状態に遷移
		break;
	case enMoveState::Shot:
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
		m_vQuaternion =  tilt* m_ShotBaseRot;
		if (t >= 1.0f)
		{
			m_StateTime = 0.f;
			m_MoveState = enMoveState::Live;
		}
	}
		break;
	default:
		break;
	}
	//ノックバック中
	m_pKnockBack.Update();
	m_pBoost.Update();
}
//描画関数
void CPlayer::Draw(
	const CCamera* pCamera)
{
	OutputDebugStringA("Player Draw\n");
	CCharacter::Draw(pCamera);
}

//コントローラー操作
void CPlayer::Controller()
{
#if 1
	//ダウン状態の場合
	if (m_MoveState != enMoveState::Live )
	{
		return;
	}

	//キーボード
	float moveX = 0.0f;
	float moveZ = 0.0f;
	switch (m_ID)
	{
	case 0:
		if (GetAsyncKeyState(VK_UP) & 0x8000) moveZ += 1.0f;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) moveZ -= 1.0f;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) moveX -= 1.0f;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) moveX += 1.0f;
		
		if (GetAsyncKeyState('Z') & 0x8000) m_MoveState = enMoveState::Boost;
		if (GetAsyncKeyState('X') & 0x8000) m_MoveState = enMoveState::ShotIN;
		break;
	case 1:
		if (GetAsyncKeyState('W') & 0x8000) moveZ += 1.0f;
		if (GetAsyncKeyState('S') & 0x8000) moveZ -= 1.0f;
		if (GetAsyncKeyState('A') & 0x8000) moveX -= 1.0f;
		if (GetAsyncKeyState('D') & 0x8000) moveX += 1.0f;

		if (GetAsyncKeyState('1') & 0x8000) m_MoveState = enMoveState::Boost;
		if (GetAsyncKeyState('2') & 0x8000) m_MoveState = enMoveState::ShotIN;
		break;
	default:
		break;
	}

	// 移動ベクトル
	D3DXVECTOR3 moveDir(moveX, 0.0f, moveZ);

	float len = D3DXVec3Length(&moveDir);

	if (len > 0.01f)
	{
		// 移動
		m_vPosition += moveDir * m_Speed;
		//クオータニオン
		Quotanion(moveDir);
		//nanamehayasi
	}
#else
	//ダイレクト操作
	CXInput* pPad = CXInput::GetInstance(m_ID); // 1Pコントローラー

	if (pPad && pPad->Update())
	{
		//ダウン状態じゃない場合
		if (m_MoveState == Down)
		{
			return;
		}
		float LX = static_cast<float>(pPad->GetLThumbX()) / 32767.0f;
		float LY = static_cast<float>(pPad->GetLThumbY()) / 32767.0f;

		// デッドゾーン処理
		const float DEAD_ZONE
			= static_cast<float>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / 32767.0f;
		if (fabs(LX) < DEAD_ZONE) LX = 0.0f;
		if (fabs(LY) < DEAD_ZONE) LY = 0.0f;

		// 入力方向にそのまま動く（Z軸反転なし）
		D3DXVECTOR3 moveDir(LX, 0.0f, LY);

		float len = D3DXVec3Length(&moveDir);


		if (len > 0.01f) {
			// 移動
			m_vPosition += moveDir * m_Speed;

			Quotanion(moveDir);

			m_MoveState = enMoveState::Walk;	//移動状態
		}
		else
		{
			m_MoveState = enMoveState::Idle;    //待機状態
		}

	}
#endif

}
//クオータニオン対応
void CPlayer::Quotanion(D3DXVECTOR3 moveDir)
{
	D3DXVec3Normalize(&moveDir, &moveDir);


	// ===== 回転（クォータニオン）=====
	float yaw = atan2f(moveDir.x, moveDir.z) - D3DX_PI / 2;

	D3DXQUATERNION targetRot;
	D3DXQuaternionRotationYawPitchRoll(
		&targetRot,
		yaw,
		0.0f,
		0.0f
	);

	// スムーズ回転
	D3DXQuaternionSlerp(
		&m_vQuaternion,
		&m_vQuaternion,
		&targetRot,
		0.2f
	);
}

//当たり判定
void CPlayer::OnCollision(CollisionBase* pCollider)
{
	switch (pCollider->GetTag())
	{
		//プレイヤーと接触した場合
	    case CollisionBase::Player:
	    {
			auto* other = dynamic_cast<CPlayer*>(pCollider->GetListener());
			if (!other || other == this)
				return;
			//ノックバック
			m_pKnockBack.Apply(
				other->GetPosition(), GetPosition(), 0.5f, 20.0f);
			//相手のプレイヤーも
			other->m_pKnockBack.Apply(
				GetPosition(), other->GetPosition(), 0.5f, 20.0f);
	    }
		break;
	default:
		break;
	}
}
