#include "GameMenu.h"
#include "MyBitmapManager.h"
namespace solitaire
{
    GameMenu::GameMenu(D2DFramework* pFramework, std::wstring filename)
        : Actor(pFramework, L"Data/background2.png")
    {
        mpStartImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/StartButton3.png");
        mpEndImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/EndButton3.png");
        mpLeftWolfImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/card_creature_wolf.png");
        mpCenterDragonImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/card_creature_dragon.png");
        mpRightBearImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(L"Data/card_creature_bear.png");


        mXStartEndImg = 290.f;
        mYStartImg = 350.f;
        mYEndImg = 500.f;
        mWidthStartImg = 450.f;
        mWidthEndImg = 440.f;
        mHeightStartEndImg = 150.f;

        mXLeftWolf = 300.f;
        mYLeftWolf = 55.f;
        mWolfRotation = -45.f;


        mXCenterDragon = 470.f;
        
        mXRightBear = 640.f;
        mBearRotation = 45.f;
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
            static_cast<float>(mXStartEndImg + mWidthStartImg),
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
            static_cast<float>(mXStartEndImg + mWidthEndImg),
            static_cast<float>(mYEndImg + mHeightStartEndImg)
        };
        pRT->DrawBitmap(
            mpEndImg,
            rect,
            mOpacity
        );

        // Three Image Draw
        
        // Wolf section.
        size = mpLeftWolfImg->GetPixelSize();
        rect = {
            0,
            0,
            static_cast<float>(0 + size.width),
            static_cast<float>(0 + size.height)

        };
        //auto dir = UP_VECTOR * D2D1::Matrix3x2F::Rotation(mWolfRotation);
        /*mXLeftWolf += dir.x;
        mYLeftWolf += dir.y;*/

        D2D1::Matrix3x2F matRotation = D2D1::Matrix3x2F::Rotation(
            mWolfRotation,
            D2D_POINT_2F{size.width * 0.5f, size.height * 0.5f}
        );

        D2D1::Matrix3x2F matTranslation = D2D1::Matrix3x2F::Translation(
            mXLeftWolf, mYLeftWolf
        );

        // HOW..???? 이곳에서 막힘...
        pRT->SetTransform(matRotation * matTranslation);
        pRT->DrawBitmap(
            mpLeftWolfImg,
            rect,
            mOpacity
        );

        pRT->SetTransform(D2D1::Matrix3x2F::Identity());
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

        // Draw Bear
        rect = {
            0,
            0,
            static_cast<float>(0 + size.width),
            static_cast<float>(0 + size.height)

        };
        D2D1::Matrix3x2F matBearRotation = D2D1::Matrix3x2F::Rotation(
            mBearRotation,
            D2D1_POINT_2F{ size.width * 0.5f, size.height * 0.5f }
        );

        D2D1::Matrix3x2F matBearTranslation = D2D1::Matrix3x2F::Translation(
            mXRightBear, mYLeftWolf
        );

        pRT->SetTransform(matBearRotation * matBearTranslation);
        pRT->DrawBitmap(
            mpRightBearImg,
            rect,
            mOpacity
        );
        pRT->SetTransform(D2D1::Matrix3x2F::Identity());

    }
}

