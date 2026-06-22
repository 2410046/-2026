#include "CGame.h"
#include "CGameObject/CSpriteObject/CTIme/CTime.h"		//タイムクラス
#include "Scene/SelectText/CSelectText.h"  //選択肢の関数
#include "Collision/CollisionManager/CollisionManager.h"
// 定数定義
namespace 
{
	static const D3DXVECTOR3 Sky_Pos   
		= D3DXVECTOR3(0.f, -1.f, 11.f);		//スカイ座標
	static const D3DXVECTOR3 Camera_Pos 
		= D3DXVECTOR3(0.0f, 11.0f, -2.0f);	//カメラ座標
	static const D3DXVECTOR3 Look_Pos   
		= D3DXVECTOR3(0.0f, 2.0f, 10.0f);	//カメラの方向座標
	static const D3DXVECTOR3 Light_Pos  
		= D3DXVECTOR3(1.f, 2.f, 0.f);		//ライト座標

	//４つボタンの配置
	static const float TablePos[4][2] =
	{
		{  0.f,  20.f }, // 下
		{  20.f,  0.f }, // 右
		{  0.f, -20.f }, // 上
		{ -20.f,  0.f }, // 左
	};

	constexpr int ScoreTextCount = 2;	// スコアテキストの数
	constexpr int ButtonCount    = 4;	// ボタンの数
}
//コンストラクタ.
CGame::CGame()
	: CScene				()
	, m_RotY				( 2.f )
	, m_PlayerCount			( 0 )
{
}
//デストラクタ.
CGame::~CGame()
{
	//破棄関数
	Release();
}

//構築関数
void CGame::Create()
{
	//プレイヤー人数の取得
	m_PlayerCount = CGameData::GetInstance()->PlayerNo();
	// スカイのインスタンス生成
	m_pSky      = std::make_unique<CStaticMeshObject>();
	//プレイヤーのインスタンス生成
	m_pPlayer	= std::make_unique<CPlayerManager>();
	//ボタンのインスタンス生成
	for (int i = 0; i < m_PlayerCount * ButtonCount; ++i)//各プレイヤーに4つずつ
	{
		auto button = std::make_unique<CSelectUI>();
		m_pButton.push_back(std::move(button));
	}

}

//ロード関数.
HRESULT CGame::LoadData()
{
	//メッシュの読み込み
	m_pSky->AttachMesh(*CMeshManager::GetStatic("Sky01"));
	//座標の読み込み
	m_pSky->SetPosition(Sky_Pos);
	// プレイヤーの数
	for (int p = 0; p < m_PlayerCount; ++p)
	{
		//画像のサイズ
		static constexpr float UI_Scale = 0.4f;
		//ボタンの数
		for (int i = 0; i < ButtonCount; ++i)
		{
			//プレイヤーの数に対してテキストを4つ配置
			int No = p * ButtonCount + i;

			float baseX = 1210.f + p * -1150.f;	//X座標
			float baseY = 100.f;			   	//Y座標

			//座標
			const D3DXVECTOR3 Pos 
				= D3DXVECTOR3(baseX + TablePos[i][0], baseY + TablePos[i][1], 0.f);

			m_pButton[No]->AttachSprite(*CSpriteManager::GetSprite2D("Button"));
			m_pButton[No]->SetPosition(Pos);
			m_pButton[No]->SetPatternNo(i, 0);
			m_pButton[No]->SetScale(UI_Scale);
			m_pButton[No]->SetAlpha(0.5f);
		}
		//プレイヤーの生成
		m_pPlayer->NewPlayer(p);
		//スコアの生成
		//m_pScores->NewScore(p);
	}
	//時間のリセット
	CTime::GetInstance()->Reset();
	// カメラの座標や角度の設定
	CCamera::GetInstance()->SetCamera(Camera_Pos, Look_Pos);
	//ライトの設定
	CCamera::GetInstance()->SetLight(Light_Pos);
	//音楽を再生
	CSoundManager::PlayLoop(CSoundManager::enList(CGameData::BGMNo()));
	return S_OK;
}
//解放関数.
void CGame::Release()
{
		//初期化
	CollisionManager::GetInstance()->Init();
}
//動作関数
void CGame::Update()
{
	CTime::GetInstance()->Update();
	//ステージの移動制限

	m_pPlayer->Update();

//	m_pScores->Update();

	CollisionManager::GetInstance()->Update();

	//ボタンの動作関数
	Button();
	//スカイの動作関数
	Sky();
    //シーン遷移
	Next();
}


//描画処理
void CGame::Draw()
{
	// カメラのインスタンスを取得
	auto* camera = CCamera::GetInstance();

	camera->Camera();		//カメラ関数
	camera->Projection();	//プロジェクション関数

	m_pSky->Draw(camera);

	m_pPlayer->Draw(camera);

	for (size_t i = 0; i < m_pButton.size(); ++i)
	{
		m_pButton[i]->Draw();
	}

	//m_pScores->Draw();

	CTime::GetInstance()->Draw(camera);

	CEffect::GetInstance()->Draw(camera);

}

//スカイの動作
void CGame::Sky()
{
	constexpr float m_Speed = 0.002f;	//スピード
	m_RotY += m_Speed;              // 毎フレーム少しずつ加算
	m_pSky->SetRotation(0.f, m_RotY, 0.f); // Y軸回転
}
//コントローラー入力処理,ボタン表示更新
void CGame::Button()
{
	//ボタン
	const CXInput::KEY keys[] =
	{
		CXInput::KEY::A,
		CXInput::KEY::B,
		CXInput::KEY::Y,
		CXInput::KEY::X
	};
	//a値
	float Alpha = 0.5f;
	//コントローラー入力処理,
	for (int pad = 0; pad < ScoreTextCount; ++pad)
	{
		CXInput* pPad = CXInput::GetInstance(pad);
		if (pPad == nullptr)
		{
			continue;
		}
		// 初期化（未入力状態）
		m_PadButton[pad] = -1;
		for (int i = 0; i < ButtonCount; ++i)
		{
			// ボタン入力判定（押された瞬間のみ検出）
			if (pPad->IsDown(keys[i], true))
			{
				m_PadButton[pad] = i;
			}

		}
	}

	// ボタン表示更新
	for (int a = 0; a < m_PlayerCount; ++a)
	{
		for (int i = 0; i < ButtonCount; ++i)
		{
			// 配列インデックス計算（プレイヤーごとのボタン）
			int No = a * ButtonCount + i;
			// 押されているボタンのみ強調表示
			if (i == m_PadButton[a])
			{
				Alpha = 1.f;  // 表示
			}
			else
			{
				Alpha = 0.5f; //半透明
			}
			//a値を設定
			m_pButton[No]->SetAlpha(Alpha);
		}
	}
}
//シーン遷移
void CGame::Next()
{
	//時間が来たら
	if (CTime::GetInstance()->MaxTime(CGameData::GetLimit()))
	{
		//音楽を停止
		CSoundManager::Stop(CSoundManager::enList(CGameData::BGMNo()));
		//エフェクトをすべて止める
		CEffect::StopAll();
		//スコアをファイルに保存
		//m_pScores->ResultScore();
		//リザルトに遷移
		SceneManager::GetInstance()->NextScene(SceneManager::Result);
	}
}