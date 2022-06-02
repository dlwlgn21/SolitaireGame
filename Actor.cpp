#include "Actor.h"
#include "MyBitmapManager.h"
namespace solatiare
{
	Actor::Actor(D2DFramework* pFramework, std::wstring filename)
		: mpFramework(pFramework)
		, mX{}
		, mY{}
		, mOpacity{1.f}
	{
		mpBitmapImg = MyBitmapManager::GetInstance().LoadBitmapW(filename);
	}
	Actor::Actor(D2DFramework* pFramework, std::wstring filename, float x, float y, float opacity)
		: Actor(pFramework, filename)
	{
		mX = x;
		mY = y;
		mOpacity = opacity;
	}

	Actor::~Actor()
	{
	}
	void Actor::Draw()
	{
	}
	void Actor::draw(float x, float y, float opacity)
	{
		D2D1_SIZE_U size = mpBitmapImg->GetPixelSize();
		D2D1_RECT_F rect{
			x,
			y,
			static_cast<float>(x + size.width),
			static_cast<float>(y + size.height)
		};
		mpFramework->GetRenderTarget()->DrawBitmap(
			mpBitmapImg,
			rect,
			opacity
		);
	}
}