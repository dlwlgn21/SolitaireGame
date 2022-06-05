#pragma once
#include "Actor.h"
#include "D2DFramework.h"
namespace solitaire
{
	class GameMenu : public Actor
	{
	public: 
		GameMenu(D2DFramework* pFramework, std::wstring filename = L"Data/background2.png");
		bool StartMenuIsClicked(float mouseX, float mouseY);
		bool EndMenuIsClikced(float mouseX, float mouseY);
		void Draw() override;

	private:
		const D2D_POINT_2F UP_VECTOR{ 0.0f, -1.0f };

		ID2D1Bitmap* mpStartImg;
		ID2D1Bitmap* mpEndImg;
		ID2D1Bitmap* mpLeftWolfImg;
		ID2D1Bitmap* mpCenterDragonImg;
		ID2D1Bitmap* mpRightBearImg;

		float mXStartEndImg;
		float mYStartImg;
		float mYEndImg;
		float mWidthStartImg;
		float mWidthEndImg;
		float mHeightStartEndImg;

		float mXLeftWolf;
		float mYLeftWolf;
		float mWolfRotation;

		float mXCenterDragon;

		float mBearRotation;
		float mXRightBear;

		float mYWolfDragonBear;
		
	};
}

