#include "Button.hpp"
#include <SFML/Graphics.hpp>

    void Button::Setup(RenderWindow* window, Menu* parent, float PositionX, float PositionY, float Width, float Height, string Label){
        Window=window;
        Parent=parent;
        label=Label;
        infocus=false;
        StandardColor=new Color(200,0,0);
        InFocusColor=new Color(255,0,0);
        btnimage.LoadFromFile("contents/button1.png");
        SetImage(btnimage);
        SetPosition(PositionX, PositionY);
        Resize(Width, Height);
        SetColor(*StandardColor);
        ButtonFont.LoadFromFile("contents/Army.ttf");
        Text= new String(label,ButtonFont,20);
        Text->SetPosition(PositionX, PositionY);
    }

    void Button::SetTextPosition(float RelativePositionX, float RelativePositionY){
        Text->SetPosition(GetPosition().x+RelativePositionX, GetPosition().y+RelativePositionY);
    }

    void Button::SetStandardColor(Color color){
        *StandardColor=color;
        SetColor(*StandardColor);
    }

    void Button::SetInFocusColor(Color color){
        *InFocusColor=color;
    }

    void Button::EventHandle(Event ev){

        if ((Window->GetInput().GetMouseX()>GetPosition().x &&
             Window->GetInput().GetMouseX()<GetPosition().x+GetSize().x &&
             Window->GetInput().GetMouseY()>GetPosition().y &&
             Window->GetInput().GetMouseY()<GetPosition().y+GetSize().y) && infocus==false){
            SetColor(*InFocusColor);
            infocus = true;
        }
        if ((Window->GetInput().GetMouseX()<GetPosition().x ||
             Window->GetInput().GetMouseX()>GetPosition().x+GetSize().x ||
             Window->GetInput().GetMouseY()<GetPosition().y ||
             Window->GetInput().GetMouseY()>GetPosition().y+GetSize().y) && infocus==true){
            SetColor(*StandardColor);
            infocus = false;
        }

        if (infocus && ev.Type == Event::MouseButtonPressed){
            if(ev.Key.Code == 0){

                Parent->Action(label);

            }
        }
	}
