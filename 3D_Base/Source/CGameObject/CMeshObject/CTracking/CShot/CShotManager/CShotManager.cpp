#include "CShotManager.h"
//============================================================
// Constructor
//============================================================

CShotManager::CShotManager()
{
}


//============================================================
// Destructor
//============================================================

CShotManager::~CShotManager()
{
    Release();
}


//============================================================
// SetTracking
//============================================================

//void CShotManager::SetTracking(
//    std::vector<std::unique_ptr<CTracking>>& tracking)
//{
//    m_pTracking = &tracking;
//}
void CShotManager::SetTracking(
    const std::vector<
    std::unique_ptr<CTracking>>&trackings)
{
    m_Tracking.clear();

    m_Tracking.reserve(
        trackings.size());


    for (const auto& tracking : trackings)
    {
        if (!tracking)
        {
            m_Tracking.push_back(nullptr);
            continue;
        }


        m_Tracking.push_back(
            tracking.get());
    }
}

//============================================================
// Update
//============================================================

void CShotManager::Update(
    const std::vector<bool>& shotFlags)
{

    //========================================================
    // PlayerごとのShotフラグを確認
    //========================================================

    for (int i = 0;
        i < static_cast<int>(shotFlags.size());
        ++i)
    {
        // Shotしない
        if (!shotFlags[i])
        {
            continue;
        }


        // Trackingが存在しない
        if (i >= static_cast<int>(
            m_Tracking.size()))
        {
            continue;
        }


        CTracking* pTracking = m_Tracking[i];


        if (pTracking == nullptr)
        {
            continue;
        }


        //====================================================
        // Trackingから座標・方向取得
        //====================================================

        D3DXVECTOR3 position =
            pTracking->GetPosition();


        D3DXVECTOR3 direction =
            pTracking->GetDirection();


        //====================================================
        // Shot生成
        //====================================================

        CreateShot(
            position,
            direction,
            i);
    }


    //========================================================
    // 既存Shot更新
    //========================================================

    for (auto& shot : m_Shots)
    {
        if (shot == nullptr)
        {
            continue;
        }


        shot->Update();
    }


    //========================================================
    // 死んだShot削除
    //========================================================

    m_Shots.erase(
        std::remove_if(
            m_Shots.begin(),
            m_Shots.end(),
            [](const std::unique_ptr<CShot>& shot)
            {
                return shot == nullptr; //||
                   // !shot->IsAlive();
            }),
        m_Shots.end());
}


//============================================================
// CreateShot
//============================================================

void CShotManager::CreateShot(
    const D3DXVECTOR3& position,
    const D3DXVECTOR3& direction,
    int playerIndex)
{
    auto shot =
        std::make_unique<CShot>();

    //座標取得
    //shot->SetShot(
    //    position,
    //    direction,
    //    playerIndex);


    m_Shots.push_back(
        std::move(shot));
}


//============================================================
// Draw
//============================================================

void CShotManager::Draw(CCamera*pCamera)
{
    for (auto& shot : m_Shots)
    {
        if (shot == nullptr)
        {
            continue;
        }
        shot->Draw(pCamera);
    }
}


//============================================================
// Release
//============================================================

void CShotManager::Release()
{
    m_Shots.clear();

    m_Tracking.clear();
}