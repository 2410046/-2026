#pragma once
#include "CMeshObject/CCharacter.h"
#include "Global.h"
#include "Reaction/ReactionManager.h"

//#include "Reaction/KnockBack/CKnockBack.h"
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
protected:
	//当たり判定
	void OnCollision(
		CollisionBase* pCollider) override;
	//コントローラー操作
	void Controller();
	//クオータニオン対応
	void Quotanion(D3DXVECTOR3 moveDir);

	// 攻撃方向を計算
	void AttackDirection()
	{
		//D3DXMATRIX Quat;

		////  回転行列
		//D3DXMatrixRotationQuaternion(
		//	&Quat,
		//	&m_vQuaternion
		//);
		//// 基本方向ベクトルを回転
		//m_Direction = BaseDirection;


		//// 正規化
		//D3DXVec3Normalize(&m_Direction, &m_Direction);
		//// 当たり判定位置
		//m_vPosition = m_Direction * AttackForward;
		//// エフェクト表示位置
		//m_EffectPos = m_PlayerPos
		//	+ m_Direction * EffectForward + EffectHeight;
	}
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
};