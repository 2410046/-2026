#pragma once
#include <vector>
#include <memory>
#include "CGameObject/CMeshObject/CPlayer/CPlayer.h"//プレイヤークラス

/********************************************************************************
* プレイヤーマネージャークラス
**/
class CPlayerManager
{
public:
    //コンストラクタ
    CPlayerManager();
    //デストラクタ
    ~CPlayerManager() = default;

    // IDを指定してプレイヤーの生成
    void NewPlayer(int ID);
    // 動作関数
    void Update();
    //描画関数
    void Draw(const CCamera* pCamera);
    // 全プレイヤー取得
    std::vector<CPlayer*> GetPlayers()const;
    //プレイヤーの取得
    CPlayer* GetPlayer(int index);
private:
    std::vector<std::unique_ptr<CPlayer>> m_Players;     //プレイヤー
};