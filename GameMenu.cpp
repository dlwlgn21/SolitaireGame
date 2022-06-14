#include "GameMenu.h"
#include "SolitaireGameManager.h"
namespace solitaire
{
	GameMenu::GameMenu(D2DFramework* pFramework, std::wstring filename)
		: Actor(pFramework, filename)
	{
		mspStartButtonActor = std::make_unique<Actor>(pFramework, L"Data/StartButton3.png");
		mspFakeStartButtonActor = std::make_unique<Actor>(pFramework, L"Data/EndButton3.png");
		mspEndButtonActor = std::make_unique<Actor>(pFramework, L"Data/EndButton3.png");
		mspLeftAcotr = std::make_unique<Actor>(pFramework, L"Data/card_creature_wolf.png");
		mspCenterActor = std::make_unique<Actor>(pFramework, L"Data/card_creature_dragon.png");
		mspRightActor = std::make_unique<Actor>(pFramework, L"Data/card_creature_bear.png");


		mspStartButtonActor->SetPosition(START_X_POS, START_Y_POS);
		mspFakeStartButtonActor->SetPosition(END_X_POS, END_Y_POS - 165.f);
		mspFakeStartButtonActor->SetOpacity(0.f);
		mspEndButtonActor->SetPosition(END_X_POS, END_Y_POS);
		//mspLeftAcotr->SetPosition(LEFT_X_POS, THREE_Y_POS);
		//mspCenterActor->SetPosition(CENTER_X_POS, THREE_Y_POS);
		//mspRightActor->SetPosition(RIGHT_X_POS, THREE_Y_POS);
	}

	GameMenu::~GameMenu()
	{
		mspRightActor.reset();
		mspCenterActor.reset();
		mspLeftAcotr.reset();
		mspEndButtonActor.reset();
		mspFakeStartButtonActor.reset();
		mspStartButtonActor.reset();
	}

	void GameMenu::Draw()
	{
		Actor::Draw();
		D2D1_SIZE_U size = mspLeftAcotr->GetBitmapPixelSize();
		ID2D1HwndRenderTarget* pRT = mpFramework->GetRenderTarget();
		SolitaireGameManager* pGM = static_cast<SolitaireGameManager*>(mpFramework);
		D2D1::Matrix3x2F matScale = D2D1::Matrix3x2F::Scale(0.5f, 0.5f);
		pRT->SetTransform(matScale);
		mspStartButtonActor->Draw();
		pRT->SetTransform(D2D1::Matrix3x2F::Identity());

		D2D1::Matrix3x2F matRotation = D2D1::Matrix3x2F::Rotation(
			ROTATION_ANGLE * 7,
			D2D1_POINT_2F{
				static_cast<float>(size.width * 0.5f),
				static_cast<float>(size.height * 0.5f)
			}
		);
		D2D1::Matrix3x2F matTranslation = D2D1::Matrix3x2F::Translation(LEFT_X_POS, THREE_Y_POS);
		pRT->SetTransform(matRotation * matTranslation);
		mspLeftAcotr->Draw();
		pRT->SetTransform(D2D1::Matrix3x2F::Identity());

		matTranslation = D2D1::Matrix3x2F::Translation(CENTER_X_POS, THREE_Y_POS - 20.f);
		pRT->SetTransform(matTranslation);
		mspCenterActor->Draw();
		pRT->SetTransform(D2D1::Matrix3x2F::Identity());

		matRotation = D2D1::Matrix3x2F::Rotation(
			ROTATION_ANGLE,
			D2D1_POINT_2F{
				static_cast<float>(size.width * 0.5f),
				static_cast<float>(size.height * 0.5f)
			}
		);
		matTranslation = D2D1::Matrix3x2F::Translation(RIGHT_X_POS, THREE_Y_POS);
		pRT->SetTransform(matRotation * matTranslation);
		mspRightActor->Draw();
		pRT->SetTransform(D2D1::Matrix3x2F::Identity());
		mspEndButtonActor->Draw();
		mspFakeStartButtonActor->Draw();
		D2D1_RECT_F textRect{
			TEXT_RECT_X_POS,
			TEXT_RECT_Y_POS,
			TEXT_RECT_X_POS + TEXT_RECT_WIDTH,
			TEXT_RECT_Y_POS + TEXT_RECT_HEIGHT
		};
		pRT->DrawTextW(
			GAME_TITLE,
			static_cast<UINT32>(wcslen(GAME_TITLE)),
			pGM->GetDWriteTextFormat(),
			textRect,
			pGM->GetD2DSolidColorBrush()
		);
		
	}

	bool GameMenu::IsStartButtonClicked(float mouseX, float mouseY)
	{
		D2D_VECTOR_2F pos = mspFakeStartButtonActor->GetPosition();
		D2D_SIZE_U size = mspFakeStartButtonActor->GetBitmapPixelSize();
		if (mouseX >= pos.x && mouseX <= pos.x + size.width &&
			mouseY >= pos.y && mouseY <= pos.y + size.height)
		{
			OutputDebugStringA("Entered Start Menu\n");
			return true;
		}
		return false;
	}

	bool GameMenu::IsEndButtonClicked(float mouseX, float mouseY)
	{
		D2D_VECTOR_2F pos = mspEndButtonActor->GetPosition();
		D2D_SIZE_U size = mspEndButtonActor->GetBitmapPixelSize();
		if (mouseX >= pos.x && mouseX <= pos.x + size.width &&
			mouseY >= pos.y && mouseY <= pos.y + size.height)
		{
			OutputDebugStringA("Entered End Menu\n");
			return true;
		}
		return false;
	}

}