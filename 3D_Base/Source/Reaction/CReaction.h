#pragma once
/********************************************************************************
* リアクションクラス
**/
class CReaction
{
public:
    // 動きのタイプ
    enum MoveType
    {
        Boost,      //ブースト
        Shot,       //ショット
        KnockBack,  //ノックバック
    };
public:
    CReaction(MoveType type);
    virtual ~CReaction() {}
     //初期化
     virtual void Apply() = 0;
     //更新関数
	 virtual void Update() = 0;
     //座標を取得
     void SetPosition(D3DXVECTOR3 pos) { m_vPosition = pos; }
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
    //リアクションステータス
    struct ReactionState
    {
        bool active = false;          // アクション中か
        D3DXVECTOR3 velocity;         // 速度
        float timer = 0.0f;           // 継続時間
    };
protected:
    ReactionState m_State = {};
    D3DXVECTOR3 m_vPosition = {};
};
