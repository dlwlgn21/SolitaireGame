#include <cassert>
#include <vector>
#include <random>
#include "SolitaireGameManager.h"

namespace solitaire
{
	HRESULT SolitaireGameManager::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
	{
		D2DFramework::Initialize(hInstance, title, width, height);

		initCardTable();


		return S_OK;
	}
	void SolitaireGameManager::Release()
	{
		for (auto& e : mCardList)
		{
			e.reset();
		}
		mCardList.clear();
		mspBackground.reset();
		D2DFramework::Release();
	}
	void SolitaireGameManager::Render()
	{
		HRESULT hr;
		mspRenderTarget->BeginDraw();

		mspBackground->Draw();

		for (auto& e : mCardList)
		{
			e->Draw();
		}

		hr = mspRenderTarget->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			CreateDeviceResources();
		}

	}
	void SolitaireGameManager::OnClick(float mouseX, float mouseY)
	{
		Card* pPrevCard;
		for (auto& e : mCardList)
		{
			if (e->IsClicked(mouseX, mouseY))
			{
				if (pCurCard == nullptr)
				{
					pCurCard = e.get();
					break;
				}
				else
				{
					pPrevCard = pCurCard;
					pCurCard = e.get();

					if (pCurCard->GetCardType() == pPrevCard->GetCardType())
					{
						
					}


				}
			}
		}



	}
	void SolitaireGameManager::initCardTable()
	{
		mspBackground = std::make_unique<Actor>(this, BACKGROUND_FILENAME2);

		std::vector<eCardType> cardTypes;
		cardTypes.reserve(MAX_CARD_COUNT);
		int typeCount = static_cast<int>(eCardType::COUNT);
		for (int i = 0; i < (MAX_CARD_COUNT / 2); ++i)
		{
			switch (i % typeCount)
			{
			case 0 :
				cardTypes.push_back(eCardType::WOLF);
				cardTypes.push_back(eCardType::WOLF);
				break;
			case 1 :
				cardTypes.push_back(eCardType::BEAR);
				cardTypes.push_back(eCardType::BEAR);
				break;
			case 2 :
				cardTypes.push_back(eCardType::DRAGON);
				cardTypes.push_back(eCardType::DRAGON);
				break;
			default:
				assert(false);
				break;
			}
		}


		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(cardTypes.begin(), cardTypes.end(), gen);

		int idx{};
		float drawXPos = 120.f;
		float drawYPos = 150.f;
		float gap = 20.f;
		for (int i = 0; i < MAX_ROW; ++i)
		{
			drawXPos = 120.f;
			for (int j = 0; j < MAX_COLUMN; ++j)
			{
				mCardList.push_back(std::make_unique<Card>(this, BACK_CARD, j * drawXPos + 40.f, i * drawYPos + 20.f, cardTypes[idx++]));
			}
		}
	}


}