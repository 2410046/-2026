#pragma once
#include <vector>
#include <memory>

#include "CMeshObject/CTracking/CBallun/CBallun.h"
#include "CMeshObject/CTracking/CTracking.h"
//============================================================
// BalloonManager
//============================================================
class CBalloonManager
{
public:

    CBalloonManager();

    ~CBalloonManager();


    void NewBalloon(int ID);
    // Tracking設定
    void SetTracking(
        const std::vector<
        std::unique_ptr<CTracking>>&trackings);
    // 更新関数
    void Update(
        const std::vector<bool>& hitFlags,
        const std::vector<int>& lives);
    // 描画関数
    void Draw( CCamera* pCamera );
    // Release
    void Release();
private:
    // Balloon
    std::vector<std::unique_ptr<CBallun>>
        m_Balloons;
    // Trackingへの参照
    std::vector<CTracking*>m_Tracking;
};