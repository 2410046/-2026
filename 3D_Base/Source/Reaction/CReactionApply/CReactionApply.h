#pragma once
#include <memory>
#include "KnockBack/CKnockBack.h"
#include "CReaction.h"
#include "ReactionManager.h"
#include "CBoost/CBoost.h"
#include "CFiring/CFiring.h"
/********************************************************************************
*	リアクション生成クラス
**/
class CReactionApply
{
public:
    //ブーストの呼び出し
    static std::shared_ptr<CReaction> CreateBoost(
        CReaction::MoveType tag, D3DXVECTOR3 pos,
        float speed,
        float time,
        const D3DXQUATERNION& rot);
    //ノックバックの呼び出し
    static std::shared_ptr<CReaction> CreateKnockBack(
        CReaction::MoveType tag, D3DXVECTOR3 pos,
        float speed,
        float time,
        const D3DXQUATERNION& rot);

    static std::shared_ptr<CReaction> CreateFiring(
        CReaction::MoveType tag,
        const D3DXQUATERNION& rot);


    static std::shared_ptr<CReaction> Create(
        CReaction::MoveType tag);
};

////スフィアの当たり判定を生成
//std::shared_ptr<CollisionBase> CreateCollider::CreateSphere(
//    float Radius, CollisionListener* pOwner, CollisionBase::LayerTag tag)
//{
//    std::shared_ptr<CollisionBase> pCollider
//        = std::make_shared<CollisionSphere>(Radius, pOwner, tag);
//    CollisionManager::GetInstance()->Register(pCollider);
//    return pCollider;
//}
////カプセルの当たり判定を生成
//std::shared_ptr<CollisionBase> CreateCollider::CreateCaupsule(
//    float Radius, float Height, CollisionListener* pOwner,
//    CollisionBase::LayerTag tag)
//{
//    std::shared_ptr<CollisionBase> pCollider
//        = std::make_shared<CollisionCapsule>(Radius, Height, pOwner, tag);
//    CollisionManager::GetInstance()->Register(pCollider);
//    return pCollider;
//}
////ボックスの当たり判定を生成
//std::shared_ptr<CollisionBase> CreateCollider::CreateBox(
//    D3DXVECTOR3 Langth, CollisionListener* pOwner, CollisionBase::LayerTag tag)
//{
//    std::shared_ptr<CollisionBase> pCollider
//        = std::make_shared<CollisionBox>(Langth, pOwner, tag);
//    CollisionManager::GetInstance()->Register(pCollider);
//    return pCollider;
//}