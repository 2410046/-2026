#include "CBallunManager.h"

//============================================================
// Constructor
//============================================================

CBalloonManager::CBalloonManager()
   // : m_pTracking(nullptr)
{
}
//============================================================
// Destructor
//============================================================

CBalloonManager::~CBalloonManager()
{
    Release();
}

void CBalloonManager::NewBalloon(int ID)
{
}
//============================================================
// SetTracking
//============================================================



//void CBalloonManager::SetTracking(
//    const std::vector<
//    std::unique_ptr<CTracking>>&trackings);
//{
//    m_Tracking = &tracking;
//}
void CBalloonManager::SetTracking(
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

void CBalloonManager::Update(
    const std::vector<bool>& hitFlags,
    const std::vector<int>& lives)
{


    //========================================================
    // Balloon数をPlayer数に合わせる
    //========================================================

    while (m_Balloons.size() <
        m_Tracking.size())
    {
        m_Balloons.emplace_back(
            std::make_unique<CBallun>());
    }


    //========================================================
    // Playerごと
    //========================================================

    for (int i = 0;
        i < static_cast<int>(
            m_Tracking.size());
        ++i)
    {
        if (!m_Balloons[i])
        {
            continue;
        }


        if (m_Tracking[i] == nullptr)
        {
            continue;
        }


        if (i >= static_cast<int>(
            hitFlags.size()))
        {
            continue;
        }


        if (i >= static_cast<int>(
            lives.size()))
        {
            continue;
        }


        //====================================================
        // Tracking
        //====================================================

        D3DXVECTOR3 position =
            m_Tracking[i]->GetPosition();


        //// Balloonへ渡す
        //m_Balloons[i]->SetBalloon(
        //    position,
        //    hitFlags[i],
        //    lives[i]);
    }
}


//============================================================
// Draw
//============================================================

void CBalloonManager::Draw(CCamera*pCamera)
{
    for (auto& balloon : m_Balloons)
    {
        if (balloon == nullptr)
        {
            continue;
        }


        balloon->Draw(pCamera);
    }
}


//============================================================
// Release
//============================================================

void CBalloonManager::Release()
{
    m_Balloons.clear();
    m_Tracking.clear();
}