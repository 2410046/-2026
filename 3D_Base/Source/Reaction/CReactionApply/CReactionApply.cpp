#include "stdafx.h"
#include "CReactionApply.h"

std::shared_ptr<CReaction> CReactionApply::CreateBoost(CReaction::MoveType tag, 
    D3DXVECTOR3 pos,
    float speed,
    float time,
    const D3DXQUATERNION& rot)
{
    std::shared_ptr<CReaction> pReaction
        = std::make_shared<CBoost>(tag);
    CReactionManager::GetInstance()->Register(pCollider);
    pReaction->Apply();
    return pReaction;
}

std::shared_ptr<CReaction> CReactionApply::CreateKnockBack(
    CReaction::MoveType tag, D3DXVECTOR3 pos, float speed, float time, const D3DXQUATERNION& rot)
{
    std::shared_ptr<CReaction> pReaction
        = std::make_shared<CKnockBack>(tag);
    CReactionManager::GetInstance()->Register(pCollider);
    pReaction->Apply();
    return pReaction;
}

std::shared_ptr<CReaction> CReactionApply::CreateFiring(CReaction::MoveType tag, const D3DXQUATERNION& rot)
{
    return std::shared_ptr<CReaction>();
}
