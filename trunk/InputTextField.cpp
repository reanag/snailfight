#include "InputTextField.hpp"

void InputTextField::Setup(RenderWindow* window, Menu* parent, float PositionX, float PositionY, float Width, float Height, string Label) {
    Window=window;
    Parent=parent;
    label=Label;
    infocus=false;
    StandardColor=new Color(200,0,0);
    InFocusColor=new Color(255,0,0);
    btnimage.LoadFromFile("contents/button1.png");
    SetImage(btnimage);
    PosX = PositionX;
    PosY = PositionY;
    SetPosition(PositionX, PositionY);
    Resize(Width, Height);
    SetColor(*StandardColor);
    ButtonFont.LoadFromFile("contents/Army.ttf");
    Text= new String(label,ButtonFont,20);
    Text->SetPosition(PositionX, PositionY);
}

void InputTextField::SetTextPosition(float RelativePositionX, float RelativePositionY) {
    Text->SetPosition(GetPosition().x+RelativePositionX, GetPosition().y+RelativePositionY);
}

void InputTextField::SetStandardColor(Color color) {
    *StandardColor=color;
    SetColor(*StandardColor);
}

void InputTextField::SetInFocusColor(Color color) {
    *InFocusColor=color;
}

void InputTextField::SetLabel(string s) {
    label=s;
}

string InputTextField::GetLabel() {
    return label;
}

void InputTextField::EventHandle(Event ev) {

    if ((Window->GetInput().GetMouseX()>GetPosition().x &&
            Window->GetInput().GetMouseX()<GetPosition().x+GetSize().x &&
            Window->GetInput().GetMouseY()>GetPosition().y &&
            Window->GetInput().GetMouseY()<GetPosition().y+GetSize().y) && infocus==false) {
        SetColor(*InFocusColor);
        infocus = true;
    }
    if ((Window->GetInput().GetMouseX()<GetPosition().x ||
            Window->GetInput().GetMouseX()>GetPosition().x+GetSize().x ||
            Window->GetInput().GetMouseY()<GetPosition().y ||
            Window->GetInput().GetMouseY()>GetPosition().y+GetSize().y) && infocus==true) {
        SetColor(*StandardColor);
        infocus = false;
    }

    if (infocus&&(ev.Type==ev.KeyPressed)) {
        string s = "";

        if (ev.Key.Code=='0') {
            s="0";
        }
        if (ev.Key.Code=='1') {
            s="1";
        }
        if (ev.Key.Code=='2') {
            s="2";
        }
        if (ev.Key.Code=='3') {
            s="3";
        }
        if (ev.Key.Code=='4') {
            s="4";
        }
        if (ev.Key.Code=='5') {
            s="5";
        }
        if (ev.Key.Code=='6') {
            s="6";
        }
        if (ev.Key.Code=='7') {
            s="7";
        }
        if (ev.Key.Code=='8') {
            s="8";
        }
        if (ev.Key.Code=='9') {
            s="9";
        }
        if (ev.Key.Code=='d') {
            s=".";
        }

        if(GetLabel().size()<18){//&& nem backspace
            SetLabel(GetLabel()+s);
            if(GetLabel().size()>13){
                Parent->SetIP(GetLabel());
                Parent->IpIsSet=true;
            }
        }

        Text= new String(label,ButtonFont,20);
        Text->SetPosition(PosX,PosY);
    }


}



