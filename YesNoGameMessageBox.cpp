#include "YesNoGameMessageBox.h"
namespace solitaire
{
	YesNoGameMessageBox::YesNoGameMessageBox(D2DFramework* pFramework, std::wstring filename)
		: Actor(pFramework, filename, 0.2f)
	{
		mspYesButtonImg = std::make_unique<Actor>(pFramework, L"Data/yes.png");
		mspNoButtonImg = std::make_unique<Actor>(pFramework, L"Data/no.png", 0.2f);
	}

	YesNoGameMessageBox::~YesNoGameMessageBox()
	{
		mspNoButtonImg.reset();
		mspYesButtonImg.reset();
	}

	void YesNoGameMessageBox::Draw()
	{
		auto pRT = mpFramework->GetRenderTarget();

		D2D1_RECT_F rect{
			BACK_X_POS,
			BACK_Y_POS,
			BACK_X_POS + BACK_WIDTH,
			BACK_Y_POS + BACK_HEIGHT
		};

		SizedDraw(rect);
		D2D1_RECT_F yesRect{
			YES_NO_X_POS,
			YES_Y_POS,
			YES_NO_X_POS + YES_NO_WIDTH,
			YES_Y_POS + YES_NO_HEIGHT
		};

		D2D1_RECT_F noRect{
			YES_NO_X_POS,
			NO_Y_POS,
			YES_NO_X_POS + YES_NO_WIDTH,
			NO_Y_POS + YES_NO_HEIGHT
		};
		mspYesButtonImg->SizedDraw(yesRect);
		mspNoButtonImg->SizedDraw(noRect);
	}


}