#pragma once
#include "Actor.h"

namespace solitaire
{
    class YesNoGameMessageBox : public Actor
    {
        const float BACK_X_POS = 250.f;
        const float BACK_Y_POS = 250.f;
        const float BACK_WIDTH = 500.f;
        const float BACK_HEIGHT = 300.f;


        const float YES_X_POS = 330.f;
        const float NO_X_POS = 530.f;
        const float YES_NO_Y_POS = 400.f;
        const float YES_NO_WIDTH = 150.f;
        const float YES_NO_HEIGHT = 100.f;

        const float DRAW_RECT_X_POS = 350.f;
        const float DRAW_RECT_Y_POS = 320.f;
        const float DRAW_RECT_WIDTH = 300.f;
        const float DRAW_RECT_HEIGHT = 150.f;

    public:
        YesNoGameMessageBox(D2DFramework* pFramework, std::wstring filename, std::wstring text);
        virtual ~YesNoGameMessageBox();

        void Draw() override;
        virtual bool IsYesClicked(float mouseX, float mouseY);
        virtual bool IsNoClicked(float mouseX, float mouseY);

        void Refresh();
        void SetText(std::wstring text);
    private:
        std::wstring mText;
        std::unique_ptr<Actor> mspYesButtonImg;
        std::unique_ptr<Actor> mspNoButtonImg;
        bool mBIsYesClicked = false;
    };
}

