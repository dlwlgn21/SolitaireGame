#pragma once
#include "Actor.h"
namespace solitaire 
{
    class GameMenu : public Actor
    {
        const float START_X_POS = 680.f;
        const float START_Y_POS = 550.f;
        const float END_X_POS = 350.f;
        const float END_Y_POS = 450.f;
        
        const float X_GAP = 150.f;
        const float LEFT_X_POS = 330.f;
        const float CENTER_X_POS = LEFT_X_POS + X_GAP;
        const float RIGHT_X_POS = CENTER_X_POS + X_GAP;
        const float THREE_Y_POS = 50.f;

        const float ROTATION_ANGLE = 45.f;

    public:
        GameMenu(D2DFramework* pFramework, std::wstring filename = L"Data/bg_blank.png");
        ~GameMenu();
        void Draw() override;
    private:
        std::unique_ptr<Actor> mspStartButtonActor;
        std::unique_ptr<Actor> mspEndButtonActor;
        std::unique_ptr<Actor> mspLeftAcotr;
        std::unique_ptr<Actor> mspCenterActor;
        std::unique_ptr<Actor> mspRightActor;
    };

}

