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
		RECT clientRect{};

		GetClientRect(mpFramework->GetWindowHandle(), &clientRect);

		D2D1_RECT_F rect{
			0.f,
			0.f,
			static_cast<float>(clientRect.right - clientRect.left),
			static_cast<float>(clientRect.bottom - clientRect.top)
		};

		SizedDraw(rect);
		D2D1_RECT_F yesRect{
			YES_X_POS,
			YES_Y_POS,
			YES_NO_WIDTH,
			YES_NO_HEIGHT
		};

		D2D1_RECT_F noRect{
			NO_X_POS,
			NO_Y_POS,
			YES_NO_WIDTH,
			YES_NO_HEIGHT
		};
		mspYesButtonImg->SizedDraw(yesRect);
		mspNoButtonImg->SizedDraw(noRect);
	}


}