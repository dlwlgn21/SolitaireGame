#include <cassert>
#include "Card.h"
#include "MyBitmapManager.h"
namespace solitaire
{
    Card::Card(D2DFramework* pFramework, std::wstring filename, float x, float y, eCardType cardType)
        : Actor(pFramework, filename)
    {
        mX = x;
        mY = y;
        mOpacity = 1.f;
        mBIsFront = false;
        mECardType = cardType;
        mpBackBitmapImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(BACK_CARD);
        switch (mECardType)
        {
        case eCardType::WOLF:
            mpFrontBitmapImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(FRONT_CARD_WOLF);
            break;
        case eCardType::BEAR:
            mpFrontBitmapImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(FRONT_CARD_BEAR);
            break;
        case eCardType::DRAGON:
            mpFrontBitmapImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(FRONT_CARD_DRAGON);
            break;
        default:
            assert(false);
            break;
        }
    }

    bool Card::IsClicked(float mouseX, float mouseY)
    {
        if (mouseX >= mX && mouseX <= mX + static_cast<float>(mpBitmapImg->GetPixelSize().width) &&
            mouseY >= mY && mouseY <= mY + static_cast<float>(mpBitmapImg->GetPixelSize().height))
        {
            Flip();
            return true;
        }
        return false;
    }

    eCardType Card::GetCardType() const
    {
        return mECardType;
    }

    bool Card::GetIsFront() const
    {
        if (mBIsFront)
        {
            return true;
        }
        return false;
    }

    void Card::Draw()
    {
        float width = static_cast<float>(mpBackBitmapImg->GetPixelSize().width);
        float height = static_cast<float>(mpBackBitmapImg->GetPixelSize().height);
        D2D1_RECT_F rect{
            mX,
            mY,
            mX + width,
            mY + height
        };
        if (mBIsFront)
        {
            mpFramework->GetRenderTarget()->DrawBitmap(
                mpFrontBitmapImg,
                rect,
                mOpacity
            );
        }
        else
        {
            mpFramework->GetRenderTarget()->DrawBitmap(
                mpBitmapImg,
                rect,
                mOpacity
            );
        }
    }

    void Card::Flip()
    {
        mBIsFront = !mBIsFront;
    }


}
