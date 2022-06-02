#pragma once
#include <string>
#include "D2DFramework.h"

namespace solatiare
{
	class Actor
	{
	public:
		Actor(D2DFramework* pFramework, std::wstring filename);
		Actor(D2DFramework* pFramework, std::wstring filename, float x, float y, float opacity = 1.f);
		virtual ~Actor();

		virtual void Draw();

	private:

		void draw(float x, float y, float opacity = 1.f);

	protected:
		float mX;
		float mY;
		float mOpacity;
		D2DFramework* mpFramework;
		ID2D1Bitmap* mpBitmapImg;

	};

}

