#pragma once
#include <vector>
#include <memory>
#include "CReaction.h"		//当たり判定クラス
#include"Singleton.h"
//======================================
// 当たり判定管理クラス
//======================================
class CReactionManager
    :public Singleton<CReactionManager>
{
private:
    friend class Singleton<CReactionManager>;
    CReactionManager();
public:
    ~CReactionManager();
    // 初期化
    void Init();
    // 出現
    void Apply(CReaction::MoveType type);
    // 更新関数
    void Update(D3DXVECTOR3 pos);

    CReaction* GetReaction(CReaction::MoveType type);
private:
    std::vector<std::shared_ptr<CReaction>> m_List;
};