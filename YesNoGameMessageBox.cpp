#include "YesNoGameMessageBox.h"
namespace solitaire
{
	YesNoGameMessageBox::YesNoGameMessageBox(D2DFramework* pFramework, std::wstring filename)
		: Actor(pFramework, filename, 0.5f)
	{
		mspYesButtonImg = std::make_unique<Actor>(pFramework, L"Data/yes.png");
		mspNoButtonImg = std::make_unique<Actor>(pFramework, L"Data/no.png", 0.8f);
		mspYesButtonImg->SetPosition(50.f, 50.f);
		mspNoButtonImg->SetPosition(100.f, 100.f);
	}

	YesNoGameMessageBox::~YesNoGameMessageBox()
	{
		mspNoButtonImg.reset();
		mspYesButtonImg.reset();
	}

	void YesNoGameMessageBox::Draw()
	{
		Actor::Draw();

		mspYesButtonImg->Draw();
		mspNoButtonImg->Draw();
	}


}