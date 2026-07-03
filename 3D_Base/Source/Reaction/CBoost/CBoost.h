#pragma once
#include "CReaction.h"

class CBoost
    :public CReaction
{
public:
    CBoost();
    ~CBoost();
    //出現
   void Apply(const ReactionParam& p)override;
   //virtual void Apply(
   //     const D3DXVECTOR3& direction,
   //     float power, float time,
   //     const D3DXQUATERNION& rotation);
   //更新関数
   void Update()override;
   //モーションを設定
   virtual MoveType GetType() const override { return MoveType::Boost; };
protected:
   // void Apply() override final;
};
