#pragma once
#include "Actor.h"

namespace solitaire
{
    class YesNoGameMessageBox : public Actor
    {
        const float YES_X_POS = 200.f;
        const float YES_Y_POS = 150.f;
        const float NO_X_POS = 200.f;
        const float NO_Y_POS = 500.f;
        const float YES_NO_WIDTH = 200.f;
        const float YES_NO_HEIGHT = 200.f;

    public:
        YesNoGameMessageBox(D2DFramework* pFramework, std::wstring filename);
        virtual ~YesNoGameMessageBox();

        void Draw() override;
    private:
        std::unique_ptr<Actor> mspYesButtonImg;
        std::unique_ptr<Actor> mspNoButtonImg;
        
    };
}

