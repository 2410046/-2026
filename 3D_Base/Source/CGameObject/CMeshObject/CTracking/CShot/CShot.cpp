#include "CShot.h"
#include "Reaction/CReactionApply/CReactionFactory.h"
#include "CMeshObject/CTracking/CTracking.h"
CShot::CShot()
	: m_ShotFlag( false )
{
	AttachMesh(*CMeshManager::GetStatic("Ballun"));
}


CShot::~CShot()
{
}
//動作関数
void CShot::Update()
{
	if (!m_ShotFlag)
	{
		return;
	}

	//方向や座標を取得
	CReaction::ReactionParam param;
	param.rot = m_vQuaternion;
	m_pReaction = CReactionFactory::Create(CReaction::Boost);
	m_pReaction->Apply(param);

	if (m_pReaction->TimeOut() == false)
	{
		m_ShotFlag = false;
	}

}
//描画関数
void CShot::Draw(const CCamera* pCamera)
{
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
