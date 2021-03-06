#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <random>
#include <algorithm>
#include "SolitaireGameManager.h"

#pragma comment (lib, "Dwrite.lib")

namespace solitaire
{
	HRESULT SolitaireGameManager::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
	{
		D2DFramework::Initialize(hInstance, title, width, height);
		mspBackground = std::make_unique<Actor>(this, BACKGROUND_FILENAME2);
		createDeviceIndependentResources();
		mspGameMenu = std::make_unique<GameMenu>(this);
		mspMSGBox = std::make_unique<YesNoGameMessageBox>(this, L"Data/BlueBorder.png", NEXT_TEXT);
		mLeftTrialCount = FIRST_GAME_LEVEL_TRIAL_COUNT - (mCurGameLevel * SUBTRACT_COUNT);;

		return S_OK;
	}
	void SolitaireGameManager::Release()
	{
		mcpBrush.Reset();
		mcpDwriteTextFormat.Reset();
		mcpDwriteFactory.Reset();
		for (auto& e : mCardList)
		{
			e.reset();
		}
		mCardList.clear();
		mspMSGBox.reset();
		mspGameMenu.reset();
		mspBackground.reset();
		D2DFramework::Release();
	}

	void SolitaireGameManager::Render()
	{
		if (mLeftTrialCount <= 0)
		{
			mBIsEnteredContinue = true;
			mspMSGBox->SetText(AGAIN_TEXT);
			clearCardList();
		}

		HRESULT hr;
		mspRenderTarget->BeginDraw();
		if (mBIsEnteredGame == false)
		{
			mspGameMenu->Draw();
		}
		else
		{
			mspBackground->Draw();
			if (mBIsEnteredContinue)
			{
				mspMSGBox->Draw();
			}
			else
			{
				for (auto& e : mCardList)
				{
					e->Draw();
				}

				mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

				mspRenderTarget->DrawTextW(
					LEFT_GAME_LEVEL_TEXT,
					static_cast<UINT32>(wcslen(LEFT_GAME_LEVEL_TEXT)),
					mcpDwriteTextFormat.Get(),
					D2D1::RectF(LEVEL_TEXT_BOX_X_POS, LEVEL_TEXT_BOX_Y_POS, LEVEL_TEXT_BOX_WIDTH, LEVEL_TEXT_BOX_HEIGHT),
					mcpBrush.Get()
				);
				mspRenderTarget->DrawTextW(
					_itow(getLeftGameLevel(), gameLevelBuffer, 10),
					static_cast<UINT32>(wcslen(gameLevelBuffer)),
					mcpDwriteTextFormat.Get(),
					D2D1::RectF(LEVEL_COUNT_BOX_X_POS, LEVEL_COUNT_BOX_Y_POS, COUNT_TEXT_BOX_Y_POS, COUNT_TEXT_BOX_Y_POS),
					mcpBrush.Get()
				);

				mspRenderTarget->DrawTextW(
					LEFT_FLIP_COUNT_TEXT,
					static_cast<UINT32>(wcslen(LEFT_FLIP_COUNT_TEXT)),
					mcpDwriteTextFormat.Get(),
					D2D1::RectF(FLIP_TEXT_BOX_X_POS, FLIP_TEXT_BOX_Y_POS, FLIP_TEXT_BOX_WIDTH, FLIP_TEXT_BOX_HEIGHT),
					mcpBrush.Get()
				);
				mspRenderTarget->DrawTextW(
					_itow(mLeftTrialCount, countBuffer, 10),
					static_cast<UINT32>(wcslen(countBuffer)),
					mcpDwriteTextFormat.Get(),
					D2D1::RectF(COUNT_TEXT_BOX_X_POS, COUNT_TEXT_BOX_Y_POS, COUNT_TEXT_BOX_Y_POS, COUNT_TEXT_BOX_Y_POS),
					mcpBrush.Get()
				);
			}
		}
		hr = mspRenderTarget->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			CreateDeviceResources();
		}

	}
	void SolitaireGameManager::OnClick(float mouseX, float mouseY)
	{
		if (mBIsEnteredGame == false)
		{
			if (mspGameMenu->IsStartButtonClicked(mouseX, mouseY))
			{
				mspGameMenu.reset();
				mBIsEnteredGame = true;
				initCardType();
				initCard();
				return;
			}
			if (mspGameMenu->IsEndButtonClicked(mouseX, mouseY))
			{
				DestroyWindow(mHwnd);
				return;
			}
		}

		if (mBIsEnteredContinue)
		{
			clearCardList();
			Render();
			if (mspMSGBox->IsYesClicked(mouseX, mouseY))
			{
				if (mspMSGBox->GetText() == AGAIN_TEXT)
				{

					initCard();
					mspMSGBox->SetText(NEXT_TEXT);
				}
				else if (mspMSGBox->GetText() == NEXT_TEXT)
				{
					++mCurGameLevel;
					releaseAndInitCard();
				}
				else
				{
					mCurGameLevel = 0;
					mspMSGBox->SetText(NEXT_TEXT);
					mCardList.clear();
					initCard();
				}
				mLeftTrialCount = FIRST_GAME_LEVEL_TRIAL_COUNT - (mCurGameLevel * SUBTRACT_COUNT);
				mBIsEnteredContinue = false;
			}
			else if (mspMSGBox->IsNoClicked(mouseX, mouseY))
			{
				DestroyWindow(mHwnd);
			}
		}


		Card* pCurCard = nullptr;
		for (auto& e : mCardList)
		{
			if (e->IsClicked(mouseX, mouseY))
			{
				pCurCard = e.get();
				break;
			}
		}

		if (pCurCard != nullptr)
		{
			if (pPrevCard == nullptr)
			{
				pPrevCard = pCurCard;
			}
			else
			{
				Render();
				if (pCurCard->GetCardType() == pPrevCard->GetCardType() && pCurCard != pPrevCard)
				{
					--mLeftTrialCount;
					Sleep(STOP_MILI_SEC);
					auto iter = std::remove_if(mCardList.begin(), mCardList.end(), [&](auto& card) {
						return card->GetIdx() == pCurCard->GetIdx() || card->GetIdx() == pPrevCard->GetIdx();
						}
					);
					mCardList.erase(iter, mCardList.end());
					pPrevCard = nullptr;
					if (mCardList.size() == 0)
					{
						if (mCurGameLevel >= MAX_GAME_LEVEL)
						{
							mspMSGBox->SetText(CLEAR_TEXT);
						}
						mBIsEnteredContinue = true;
					}
				}
				else
				{
					if (pCurCard == pPrevCard)
					{
						pPrevCard = nullptr;
					}
					else
					{
						--mLeftTrialCount;
						Sleep(STOP_MILI_SEC);
						pCurCard->Flip();
						pPrevCard->Flip();
						pPrevCard = nullptr;
					}

				}
			}

		}
	}

	IDWriteTextFormat* SolitaireGameManager::GetDWriteTextFormat() const
	{
		return mcpDwriteTextFormat.Get();
	}

	ID2D1SolidColorBrush* SolitaireGameManager::GetD2DSolidColorBrush() const
	{
		return mcpBrush.Get();
	}


	void SolitaireGameManager::initCard()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(mCardTypes.begin(), mCardTypes.end(), gen);

		int idx{};
		for (int i = 0; i < MAX_ROW; ++i)
		{
			for (int j = 0; j < MAX_COLUMN; ++j)
			{
				mCardList.push_back(std::make_unique<Card>(
					this, 
					BACK_CARD, 
					j * CARD_X_POS + CARD_X_GAP, 
					i * CARD_Y_POS + CARD_Y_GAP, 
					mCardTypes[idx], 
					idx)
				);
				++idx;
			}
		}
	}
	
	HRESULT SolitaireGameManager::createDeviceIndependentResources()
	{
		HRESULT hr;
		static const WCHAR MSC_FONTNAME[] = L"Verdana";
		static const FLOAT msc_fontSize = 50;
		
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(mcpDwriteFactory.Get()),
			reinterpret_cast<IUnknown **>(mcpDwriteFactory.GetAddressOf())
		);
		
		ThrowIfFailed(hr, "Failed DWriteCreateFactory()");
	
		hr = mcpDwriteFactory->CreateTextFormat(
			MSC_FONTNAME,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"us",
			mcpDwriteTextFormat.GetAddressOf()
		);
		ThrowIfFailed(hr, "Failed CreateTextFormat()");

		mcpDwriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		ThrowIfFailed(hr);

		mcpDwriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		ThrowIfFailed(hr);

		mspRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::OrangeRed), mcpBrush.GetAddressOf());
		
		return S_OK;
	}

	void SolitaireGameManager::clearCardList()
	{
		for (auto& e : mCardList)
		{
			e.reset();
		}
		mCardList.clear();
	}

	int SolitaireGameManager::getLeftGameLevel() const
	{
		if (mCurGameLevel == 0)
		{
			return 2;
		}
		else if (mCurGameLevel == 1)
		{
			return mCurGameLevel;
		}
		else
		{
			return 0;
		}
	}

	void SolitaireGameManager::releaseAndInitCard()
	{
		for (auto& e : mCardList)
		{
			e.reset();
		}
		mCardList.clear();
		initCard();
	}
	void SolitaireGameManager::initCardType()
	{
		
		mCardTypes.reserve(MAX_CARD_COUNT);
		int typeCount = static_cast<int>(eCardType::COUNT);
		for (int i = 0; i < (MAX_CARD_COUNT / 2); ++i)
		{
			switch (i % typeCount)
			{
			case 0:
				mCardTypes.push_back(eCardType::WOLF);
				mCardTypes.push_back(eCardType::WOLF);
				break;
			case 1:
				mCardTypes.push_back(eCardType::BEAR);
				mCardTypes.push_back(eCardType::BEAR);
				break;
			case 2:
				mCardTypes.push_back(eCardType::DRAGON);
				mCardTypes.push_back(eCardType::DRAGON);
				break;
			default:
				assert(false);
				break;
			}
		}
	}
}