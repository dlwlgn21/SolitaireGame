#pragma once
#include "Actor.h"

namespace solitaire
{
    class YesNoGameMessageBox : public Actor
    {
        const float BACK_X_POS = 400.f;
        const float BACK_Y_POS = 400.f;
        const float BACK_WIDTH = 500.f;
        const float BACK_HEIGHT = 200.f;


        const float YES_NO_X_POS = 450.f;
        const float YES_Y_POS = 200.f;
        const float NO_Y_POS = 200.f;
        const float YES_NO_WIDTH = 250.f;
        const float YES_NO_HEIGHT = 150.f;

    public:
        YesNoGameMessageBox(D2DFramework* pFramework, std::wstring filename);
        virtual ~YesNoGameMessageBox();

        void Draw() override;
    private:
        std::unique_ptr<Actor> mspYesButtonImg;
        std::unique_ptr<Actor> mspNoButtonImg;
        
    };
}

