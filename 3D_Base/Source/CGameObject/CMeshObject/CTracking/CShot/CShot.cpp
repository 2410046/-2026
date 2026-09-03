#include "CShot.h"
#include "Reaction/CReactionApply/CReactionFactory.h"
CShot::CShot()
	: m_ShotFlag( false )
{
	m_vScale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
}


CShot::~CShot()
{
}
void CShot::Init(CTracking* pTracking)
{
	if (pTracking == nullptr)
	{
		return;
	}

	// プレイヤーの現在位置を取得
	SetPosition(
		pTracking->GetPosition());

	// プレイヤーの現在方向を取得
	m_vQuaternion =
		pTracking->GetQuaternion();

	AttachMesh(*AssetManager::GetStatic("Cloud"));

	// プレイヤーID
	m_ID = pTracking->GetID();

	//方向や座標を取得
	CReaction::ReactionParam param;
	param.rot = m_vQuaternion;
	m_pReaction = CReactionFactory::Create(CReaction::Boost);
	m_pReaction->Apply(param);

	// 生存
	m_ShotFlag = true;


}
//動作関数
void CShot::Update()
{
	if (!m_ShotFlag)
	{
		return;
	}

	if (m_pReaction == nullptr)
	{
		m_ShotFlag = false;
		return;
	}

	//// Boostの更新
	//m_pReaction->Update();

	//// Boost終了
	//if (m_pReaction->TimeOut() == false)
	//{
	//	m_ShotFlag = false;
	//}
}
//描画関数
void CShot::Draw(const CCamera* pCamera)
{
	if (!m_ShotFlag)
	{
		return;
	}

	CCharacter::Draw(pCamera);
}

void CShot::SetShot(
	const D3DXVECTOR3& position, const D3DXQUATERNION& Quaternion, int ID)
{
	m_vPosition = position;
	m_vQuaternion = Quaternion;
	m_ID = ID;

	m_ShotFlag = true;
}
