#pragma once
#include <string>
#include "D2DFramework.h"

namespace solitaire
{
	class Actor
	{
	public:
		Actor(D2DFramework* pFramework, std::wstring filename);
		Actor(D2DFramework* pFramework, std::wstring filename, float x, float y, float opacity = 1.f);
		virtual ~Actor();

		virtual void Draw();

		
		D2D_VECTOR_2F GetPosition() const;
		void SetPosition(float x, float y);
		void SetPosition(D2D_VECTOR_2F vector);
		void SetOpacity(float opacity);
		D2D1_SIZE_U GetBitmapPixelSize();


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

