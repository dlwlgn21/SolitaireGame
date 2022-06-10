#pragma once
#include "Actor.h"

namespace solitaire
{
    class YesNoGameMessageBox : public Actor
    {
    public:
        YesNoGameMessageBox(D2DFramework* pFramework, std::wstring filename);
        virtual ~YesNoGameMessageBox();

        void Draw() override;
    private:
        std::unique_ptr<Actor> mspYesButtonImg;
        std::unique_ptr<Actor> mspNoButtonImg;
        
    };
}

