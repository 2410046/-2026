#pragma once
#include "CMeshObject/CCharacter.h"
#include "Global.h"

//#include "Reaction/CBoost/CBoost.h"
/********************************************************************************
* プレイヤークラス
**/
class CPlayer
	: public CCharacter,public CollisionListener
	//キャラクタークラスを継承.
{
public:
	// プレイヤーの状態
	enum enMoveState
	{
		App = 0,		// 出現
		Live,			// 生存状態
		Boost,			// ブースト状態
		ShotIN,		   // 射撃状態
		Shot,			// 射撃状態
		Down,			// ダウン状態
	};

public:
	//コンストラクタ
	CPlayer();
	//デストラクタ
	virtual ~CPlayer() override;
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(
		const CCamera* pCamera ) override;
public:
	//プレイヤーIDの取得
	int  GetID()const{ return m_ID; }
	//プレイヤーIDの設定
	void SetID(int id) { m_ID = id; }
	//ブースト状態の取得
	bool GetBoost() { return m_MoveState == enMoveState::Boost; }
protected:
	//当たり判定
	void OnCollision(
		CollisionBase* pCollider) override;
	//コントローラー操作
	void Controller();
	//クオータニオン対応
	void Quotanion(D3DXVECTOR3 moveDir);

protected:
	enMoveState	m_MoveState;	//移動状態
	int			m_ID;			//プレイヤーID
	float       m_StateTime;	//状態の開始時間
	//CKnockBack  m_pKnockBack;	//ノックバック
	//CBoost      m_pBoost;	//ブースト
	//CReaction  m_Reaction;
	//キーボード
	float       m_angle = 0.0f;
	float       m_Scale;
	int         m_Life;			//ライフの数
	D3DXQUATERNION m_ShotBaseRot;

	std::shared_ptr<CReaction>	m_pReaction;	//当たり判定
};