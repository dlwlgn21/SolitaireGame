#pragma once
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <dwrite.h>
#include "Card.h"
#include "GameMenu.h"
#include "D2DFramework.h"

namespace solitaire
{
	const int MAX_STR_LEN = 64;
	const int STOP_MILI_SEC = 500;
	class SolitaireGameManager : public D2DFramework
	{
		const wchar_t BACKGROUND_FILENAME2[MAX_STR_LEN] = L"Data/GreenDragon.jpg";
		const wchar_t LEFT_FLIP_COUNT_TEXT[MAX_STR_LEN] = L"Left flip count : ";
		const wchar_t LEFT_GAME_LEVEL_TEXT[MAX_STR_LEN] = L"LEFT GAME LEVEL : ";
		wchar_t gameLevelBuffer[MAX_STR_LEN];
		wchar_t countBuffer[MAX_STR_LEN];
		const int MAX_CARD_COUNT = 10;
		const int MAX_COLUMN = 5;
		const int MAX_ROW = 2;

		const float LEVEL_TEXT_BOX_X_POS = 200.f;
		const float LEVEL_TEXT_BOX_Y_POS = 10.f;
		const float LEVEL_TEXT_BOX_WIDTH = 700.f;
		const float LEVEL_TEXT_BOX_HEIGHT = 50.f;
		
		const float LEVEL_COUNT_BOX_X_POS = 1400.f;
		const float LEVEL_COUNT_BOX_Y_POS = 12.f;

		
		const float FLIP_TEXT_BOX_X_POS = 200.f;
		const float FLIP_TEXT_BOX_Y_POS = 250.f;
		const float FLIP_TEXT_BOX_WIDTH = 700.f;
		const float FLIP_TEXT_BOX_HEIGHT = 100.f;
		

		const float COUNT_TEXT_BOX_X_POS = 1300.f;
		const float COUNT_TEXT_BOX_Y_POS = 100.f;

		const float CARD_X_POS = 200.f;
		const float CARD_X_GAP = 50.f;
		const float CARD_Y_POS = 250.f;
		const float CARD_Y_GAP = 200.f;
		
		const int FIRST_GAME_LEVEL_TRIAL_COUNT = 20;
		const int MAX_GAME_LEVEL = 2;
		const int SUBTRACT_COUNT = 4;
		
	public:
		HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", UINT width = 1024, UINT height = 768) override;
		void Release() override;
		void Render() override;

		void OnClick(float mouseX, float mouseY);
	
	private:
		void initCard();
		void initCardType();
		void releaseAndInitCard();
		inline int getLeftGameLevel() const;
		HRESULT createDeviceIndependentResources();


	private:
		std::unique_ptr<Actor> mspBackground;
		std::unique_ptr<GameMenu> mspGameMenu;
		std::list<std::unique_ptr<Card>> mCardList;
		std::vector<eCardType> mCardTypes;
		Microsoft::WRL::ComPtr<IDWriteFactory> mcpDwriteFactory;
		Microsoft::WRL::ComPtr<IDWriteTextFormat> mcpDwriteTextFormat;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mcpBrush;
		Card* pPrevCard = nullptr;

		int mCurGameLevel{};
		int mLeftTrialCount{};
	};
}




