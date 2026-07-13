#pragma once
/********************************************************************************
* リアクションクラス
**/
//#include "CReactionApply/CReactionApply.h"
class CReaction
{
public:
    // 動きのタイプ
    enum MoveType
    {
        Boost,      //ブースト
        Firing,     //射撃
        KnockBack,  //ノックバック
    };
    struct ReactionParam
    {
        D3DXVECTOR3 from = {};
        D3DXVECTOR3 to = {};

        D3DXQUATERNION rot = {};

        float power = 0.f;
        float time = 0.f;
    };
protected:
    //リアクションステータス
    struct ReactionState
    {
        bool active = false;          // アクション中か
        D3DXVECTOR3 velocity;         // 速度
        float timer = 0.0f;           // 継続時間
    };
public:
    CReaction();
    virtual ~CReaction() = default;
     //初期化
    virtual void Apply(const ReactionParam& param) = 0;
     //更新関数
	 virtual void Update() = 0;
     //座標を取得
    void SetPosition(D3DXVECTOR3* pos)
    {
        m_pPosition = pos;
    }
     //モーションを設定
     virtual MoveType GetType() const = 0;

     bool IsActive() const
     {
         return m_State.active;
     }

     //時間が０の場合
     bool TimeOut()
     {
         return m_State.timer <= 0.f;
     };

protected:
    ReactionState m_State = {};
    D3DXVECTOR3* m_pPosition = nullptr;//これを戻すとエラーが
   // D3DXVECTOR3 m_vPosition = {};
};
