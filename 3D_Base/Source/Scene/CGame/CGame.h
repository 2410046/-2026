#pragma once
#include "CScene.h"				//シーンクラス
#include "CGameObject/CMeshObject/CPlayer/CPlayerManager.h"	    //プレイヤークラス
//#include "CGameObject/CUIObject/Score/CScoreManager.h"		    //スコアマネージャークラス

/********************************************************************************
*	ゲームクラス.
**/
class CGame
	:public CScene
{
public:
	//コンストラクタ
	CGame();
	//デストラクタ
	~CGame() override;

	//構成関数
	void    Create()   override;
	//ロード関数
	HRESULT LoadData() override;
	//破棄関数
	void    Release()  override;
	//動作関数
	void    Update()   override;
	//描画関数
	void    Draw()     override;
private:
	//スカイの動作関数
	void Sky();		
	//ボタンの動作関数
	void Button();
	//シーン遷移関数
	void Next();
private:
	std::unique_ptr<CPlayerManager>			   m_pPlayer;	   //プレイヤークラス

	std::unique_ptr<CStaticMeshObject>		m_pSky;		   //スカイクラス

	//std::unique_ptr<CScoreManager>			m_pScores;	   //スコアクラス

	std::vector<std::unique_ptr<CSelectUI>> m_pButton;	   //ボタンクラス
private:
	float m_RotY;					   // SkyのY座標
	int   m_PadButton[2] = { -1, -1 }; // コントローラーが押しているボタン(0:Pad0, 1:Pad1)
	int	  m_PlayerCount;			   // プレイヤーの人数
};
