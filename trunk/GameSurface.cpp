#include "GameSurface.hpp"

	GameSurface::GameSurface(RenderWindow* window){
	    Window=window;

        barImg.LoadFromFile("contents/button1.png");
        baroutlineImg.LoadFromFile("contents/button1_outline.png");

        LifebarSp.SetImage(barImg);
        LifebarSp.SetColor(Color(200,0,0));
        LifebarSp.Resize(200,10);
        LifebarOutlineSp.SetImage(baroutlineImg);
        LifebarOutlineSp.Resize(200,10);

        StaminabarSp.SetImage(barImg);
        StaminabarSp.SetColor(Color(0,200,0));
        StaminabarSp.Resize(200,10);
        StaminabarOutlineSp.SetImage(baroutlineImg);
        StaminabarOutlineSp.Resize(200,10);

        SurfaceFont.LoadFromFile("contents/Army.ttf");
        HealthText=new String("Health",SurfaceFont,15);
        StaminaText=new String("Stamina",SurfaceFont,15);
        AmmoText=new String("Ammo: ",SurfaceFont,15);
        ClipText=new String("Clip: ",SurfaceFont,15);
	}

	void GameSurface::Show(){
	    Window->Draw(LifebarSp);
	    Window->Draw(LifebarOutlineSp);
	    Window->Draw(StaminabarSp);
	    Window->Draw(StaminabarOutlineSp);

	    Window->Draw(*HealthText);
	    Window->Draw(*StaminaText);
	    Window->Draw(*AmmoText);
	    Window->Draw(*ClipText);
    }

    void GameSurface::InputHandling(){
        koord=Window->ConvertCoords(65,20);
        LifebarSp.SetPosition(koord.x,koord.y);
        LifebarOutlineSp.SetPosition(koord.x,koord.y);
        koord=Window->ConvertCoords(65,40);
        StaminabarSp.SetPosition(koord.x,koord.y);
        StaminabarOutlineSp.SetPosition(koord.x,koord.y);

        koord=Window->ConvertCoords(5,15);
        HealthText->SetPosition(koord.x,koord.y);
        koord=Window->ConvertCoords(5,35);
        StaminaText->SetPosition(koord.x,koord.y);
        koord=Window->ConvertCoords(5,55);
        AmmoText->SetPosition(koord.x,koord.y);
        koord=Window->ConvertCoords(5,75);
        ClipText->SetPosition(koord.x,koord.y);
    }

    void GameSurface::SetHealth(int health){
        LifebarSp.Resize(health*2+0.01,10);
    }

    void GameSurface::SetStamina(int stamina){
        StaminabarSp.Resize(stamina*2,10);
    }

    void GameSurface::SetAmmo(int ammo){
        stringstream sstr;
        sstr<<"Ammo: "<<ammo;
        AmmoText->SetText(sstr.str());
    }

    void GameSurface::SetClip(int clip){
        stringstream sstr;
        sstr<<"Clip: "<<clip;
        ClipText->SetText(sstr.str());
    }
