#pragma once
#include <memory>
#include <list>
#include <string>
#include "Card.h"
#include "D2DFramework.h"

namespace solitaire
{
	const int MAX_STR_LEN = 64;
	const int STOP_MILI_SEC = 500;
	class SolitaireGameManager : public D2DFramework
	{
		const wchar_t BACKGROUND_FILENAME [MAX_STR_LEN] = L"Data/GreenTable.png";
		const wchar_t BACKGROUND_FILENAME2 [MAX_STR_LEN] = L"Data/GreenDragon.jpg";

		const int MAX_CARD_COUNT = 40;
		const int MAX_COLUMN = 8;
		const int MAX_ROW = 5;
	public:
		HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", UINT width = 1024, UINT height = 768) override;
		void Release() override;
		void Render() override;
		void OnClick(float mouseX, float mouseY);

	private:
		void initCardTable();

	private:
		std::unique_ptr<Actor> mspBackground;
		std::list<std::unique_ptr<Card>> mCardList;

		Card* pPrevCard = nullptr;


	};
}




