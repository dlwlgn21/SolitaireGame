#include "Actor.h"
#include "MyBitmapManager.h"
namespace solitaire
{
	Actor::Actor(D2DFramework* pFramework, std::wstring filename)
		: mpFramework(pFramework)
		, mX{}
		, mY{}
		, mOpacity{1.f}
	{
		mpBitmapImg = MyBitmapManager::GetInstance().LoadBitmapVersionTwo(filename);
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
		draw(mX, mY, mOpacity);
	}
	D2D_VECTOR_2F Actor::GetPosition() const
	{
		return D2D_VECTOR_2F{mX, mY};
	}

	void Actor::SetPosition(float x, float y)
	{
		mX = x;
		mY = y;
	}

	void Actor::SetPosition(D2D_VECTOR_2F vector)
	{
		mX = vector.x;
		mY = vector.y;
	}

	D2D1_SIZE_U Actor::GetBitmapPixelSize()
	{
		return D2D1_SIZE_U{mpBitmapImg->GetPixelSize().width, mpBitmapImg->GetPixelSize().height};
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