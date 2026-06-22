#pragma once
#include "CReaction.h"

class CKnockBack
    :public CReaction
{
public:
    CKnockBack(MoveType tag);
    ~CKnockBack()override;
    //出現
    void Apply(
        const D3DXVECTOR3& from, const D3DXVECTOR3& to,
        float power, float time);
    //更新関数
    void Update()override;
    //モーションを設定
    virtual MoveType GetType() const override { MoveType::Boost; };
};

