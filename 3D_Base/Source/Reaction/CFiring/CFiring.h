#pragma once
#include "CReaction.h"

class CFiring
    :public CReaction
{
public:
    CFiring(MoveType tag);
    ~CFiring()override;
    //出現
    void Apply(const D3DXQUATERNION Quaternion);
    //更新関数
    void Update()override;
    //モーションを設定
    virtual MoveType GetType() const override { MoveType::Firing; };
private:
    D3DXQUATERNION m_ShotBaseRot;
    D3DXQUATERNION m_vQuaternion;

protected:
    void Apply() override final;
};

