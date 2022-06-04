#include "GameMenu.h"
#include "MyBitmapManager.h"
namespace solitaire
{
    GameMenu::GameMenu(D2DFramework* pFramework, std::wstring filename)
        : Actor(pFramework, filename)
    {
        mpStartImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/StartButton.png");
        mpEndImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/EndButton.png");
        mpleftWolfImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/card_creature_wolf.png");
        mpCenterDragonImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/card_creature_dragon.png");
        mpRightBearImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/card_creature_bear.png");


        mXStartEndImg = 290.f;
        mYStartImg = 200.f;
        mYEndImg = 500.f;
        mWidthStartEndImg = 450.f;
        mHeightStartEndImg = 250.f;

        mXLeftWolf = 290.f;
        mYLeftWolf = 50.f;
        mWolfRotation = -45.f;


        mXCenterDragon = 470.f;
        mXRightBear = 640.f;
        mYWolfDragonBear = 50.f;


    }

    bool GameMenu::StartMenuIsClicked(float mouseX, float mouseY)
    {
        if (mouseX >= mXStartEndImg && mouseX <= mXStartEndImg + mpStartImg->GetPixelSize().width &&
            mouseY >= mYStartImg && mouseY <= mYStartImg + mpStartImg->GetPixelSize().height)
        {
            return true;
        }
        return false;
    }
    bool GameMenu::EndMenuIsClikced(float mouseX, float mouseY)
    {
        if (mouseX >= mXStartEndImg && mouseX <= mXStartEndImg + mpEndImg->GetPixelSize().width &&
            mouseY >= mYEndImg && mouseY <= mYEndImg + mpEndImg->GetPixelSize().height)
        {
            return true;
        }
        return false;
    }
    void GameMenu::Draw()
    {
        ID2D1HwndRenderTarget* pRT = mpFramework->GetRenderTarget();
        D2D1_SIZE_U size = mpBitmapImg->GetPixelSize();
        D2D1_RECT_F rect{
            mX,
            mY,
            static_cast<float>(mX + size.width),
            static_cast<float>(mY + size.height)
        };
        pRT->DrawBitmap(
            mpBitmapImg,
            rect,
            mOpacity
        );

        size = mpStartImg->GetPixelSize();
        rect = {
            mXStartEndImg,
            mYStartImg,
            static_cast<float>(mXStartEndImg + mWidthStartEndImg),
            static_cast<float>(mYStartImg + mHeightStartEndImg)
        };
        pRT->DrawBitmap(
            mpStartImg,
            rect,
            mOpacity
        );

        size = mpEndImg->GetPixelSize();
        rect = {
            mXStartEndImg,
            mYEndImg,
            static_cast<float>(mXStartEndImg + mWidthStartEndImg),
            static_cast<float>(mYEndImg + mHeightStartEndImg)
        };
        pRT->DrawBitmap(
            mpEndImg,
            rect,
            mOpacity
        );

        // Three Image Draw
        
        // Wolf section.
        auto dir = UP_VECTOR * D2D1::Matrix3x2F::Rotation(mWolfRotation);
        mXLeftWolf += dir.x;
        mYLeftWolf += dir.y;

        size = mpleftWolfImg->GetPixelSize();
        auto matRotation = D2D1::Matrix3x2F::Rotation(
            mWolfRotation,
            D2D_POINT_2F{size.width * 0.5f, size.height * 0.5f}
        );

        rect = {
            mXLeftWolf,
            mYLeftWolf,
            static_cast<float>(mXLeftWolf + size.width),
            static_cast<float>(mYLeftWolf + size.height)

        };
        // HOW..???? 이곳에서 막힘...
        pRT->SetTransform(matRotation);
        pRT->DrawBitmap(
            mpleftWolfImg,
            rect,
            mOpacity
        );
        
        rect = {
            mXCenterDragon,
            mYWolfDragonBear,
            static_cast<float>(mXCenterDragon + size.width),
            static_cast<float>(mYWolfDragonBear + size.height)

        };

        pRT->DrawBitmap(
            mpCenterDragonImg,
            rect,
            mOpacity
        );

        rect = {
            mXRightBear,
            mYWolfDragonBear,
            static_cast<float>(mXRightBear + size.width),
            static_cast<float>(mYWolfDragonBear + size.height)

        };

        pRT->DrawBitmap(
            mpRightBearImg,
            rect,
            mOpacity
        );

    }
}

