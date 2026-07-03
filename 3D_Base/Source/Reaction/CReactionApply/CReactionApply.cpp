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
   // pReaction->Apply(pos,speed,time,rot);
    return pReaction;
}

std::shared_ptr<CReaction> CReactionApply::CreateKnockBack(
    CReaction::MoveType tag, D3DXVECTOR3 pos, float speed, float time, const D3DXQUATERNION& rot)
{
    std::shared_ptr<CReaction> pReaction
        = std::make_shared<CKnockBack>(tag);
  //  CReactionManager::GetInstance()->Register(pCollider);
    //pReaction->Apply();
    return pReaction;
}

std::shared_ptr<CReaction> CReactionApply::CreateFiring(
    CReaction::MoveType tag, const D3DXQUATERNION& rot)
{
    return std::shared_ptr<CReaction>();
}

std::shared_ptr<CReaction> CReactionApply::Create(
    CReaction::MoveType tag)
{
    switch (tag)
    {
    case CReaction::Boost:
        return std::make_unique<CBoost>();

    case CReaction::Firing:
        return std::make_unique<CFiring>();

    case CReaction::KnockBack:
        return std::make_unique<CKnockBack>();
    }

    return nullptr;
}
