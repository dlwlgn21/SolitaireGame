#pragma once
#include "Actor.h"
#include "D2DFramework.h"

namespace solitaire
{

	enum class eCardType
	{
		WOLF,
		BEAR,
		DRAGON,
		COUNT
	};
	const int MAX_CARD_NAME_LNEGH = 64;
	const wchar_t BACK_CARD[MAX_CARD_NAME_LNEGH] = L"Data/card_back.png";
	const wchar_t FRONT_CARD_WOLF[MAX_CARD_NAME_LNEGH] = L"Data/card_creature_wolf.png";
	const wchar_t FRONT_CARD_BEAR[MAX_CARD_NAME_LNEGH] = L"Data/card_creature_bear.png";
	const wchar_t FRONT_CARD_DRAGON[MAX_CARD_NAME_LNEGH] = L"Data/card_creature_dragon.png";

	class Card : public Actor
	{
	public:
		Card(D2DFramework* pFramework, std::wstring filename, float x, float y, eCardType cardType);

		bool IsClicked(float mouseX, float mouseY);
		eCardType GetCardType() const;
		bool GetIsFront() const;
		void Draw() override;
		void Flip();
		
	private:
		eCardType mECardType;
		bool mBIsFront;
		ID2D1Bitmap* mpFrontBitmapImg;
		ID2D1Bitmap* mpBackBitmapImg;
	};
}

