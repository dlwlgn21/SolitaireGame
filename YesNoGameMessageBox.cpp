#include "SolitaireGameManager.h"
#include "YesNoGameMessageBox.h"
namespace solitaire
{
	YesNoGameMessageBox::YesNoGameMessageBox(D2DFramework* pFramework, std::wstring filename, std::wstring text)
		: Actor(pFramework, filename, 0.2f)
	{
		mspYesButtonImg = std::make_unique<Actor>(pFramework, L"Data/yes.png");
		mspNoButtonImg = std::make_unique<Actor>(pFramework, L"Data/no.png", 0.2f);

		mspYesButtonImg->SetPosition(YES_X_POS, YES_NO_Y_POS);
		mspNoButtonImg->SetPosition(NO_X_POS, YES_NO_Y_POS);

		mText = text;
	}

	YesNoGameMessageBox::~YesNoGameMessageBox()
	{
		mspNoButtonImg.reset();
		mspYesButtonImg.reset();
	}

	void YesNoGameMessageBox::Draw()
	{
		auto pRT = mpFramework->GetRenderTarget();
		SolitaireGameManager* pManager = static_cast<SolitaireGameManager*>(mpFramework);
		pManager->GetRenderTarget()->DrawTextW(
			mText.c_str(),
			static_cast<UINT32>(wcslen(mText.c_str())),
			pManager->GetDWriteTextFormat(),
			D2D1::RectF(
				DRAW_RECT_X_POS,
				DRAW_RECT_Y_POS,
				DRAW_RECT_X_POS + DRAW_RECT_WIDTH,
				DRAW_RECT_Y_POS + DRAW_RECT_HEIGHT
			),
			pManager->GetD2DSolidColorBrush()
		);

		D2D1_RECT_F rect{
			BACK_X_POS,
			BACK_Y_POS,
			BACK_X_POS + BACK_WIDTH,
			BACK_Y_POS + BACK_HEIGHT
		};

		SizedDraw(rect);
		D2D1_RECT_F yesRect{
			YES_X_POS,
			YES_NO_Y_POS,
			YES_X_POS + YES_NO_WIDTH,
			YES_NO_Y_POS + YES_NO_HEIGHT
		};

		D2D1_RECT_F noRect{
			NO_X_POS,
			YES_NO_Y_POS,
			NO_X_POS + YES_NO_WIDTH,
			YES_NO_Y_POS + YES_NO_HEIGHT
		};
		mspYesButtonImg->SizedDraw(yesRect);
		mspNoButtonImg->SizedDraw(noRect);
		
	}

	bool YesNoGameMessageBox::IsYesClicked(float mouseX, float mouseY)
	{
		float xPos = mspYesButtonImg->GetPosition().x;
		float yPos = mspYesButtonImg->GetPosition().y;
		if (mouseX >= xPos && mouseX <= xPos + YES_NO_WIDTH &&
			mouseY >= yPos && mouseY <= yPos + YES_NO_HEIGHT)
		{
			return true;
		}
		return false;
	
	}

	bool YesNoGameMessageBox::IsNoClicked(float mouseX, float mouseY)
	{

		float xPos = mspNoButtonImg->GetPosition().x;
		float yPos = mspNoButtonImg->GetPosition().y;
		if (mouseX >= xPos && mouseX <= xPos + YES_NO_WIDTH &&
			mouseY >= yPos && mouseY <= yPos + YES_NO_HEIGHT)
		{
			return true;
		}
		return false;

	}

	void YesNoGameMessageBox::SetText(std::wstring text)
	{
		mText = text;
	}

	std::wstring YesNoGameMessageBox::GetText() const
	{
		return mText;
	}


}