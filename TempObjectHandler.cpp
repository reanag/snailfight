#include "TempObjectHandler.hpp"

    TempObjectHandler::TempObjectHandler(){
	    grenadeImg.LoadFromFile("contents/Granade1.png");
        detonation[0].LoadFromFile("contents/det1.png");
        detonation[1].LoadFromFile("contents/det2.png");
        detonation[2].LoadFromFile("contents/det3.png");
        GranadeSoundBuffer.LoadFromFile("contents/Grenade3.wav");
    }

	void TempObjectHandler::ShowBullets(){
        for(int i=0;i<Bullets.size();i++){
            Bullets[i]->Show();
        }
    }

    void TempObjectHandler::ShowGrenades(){
	    for(int i=Grenades.size();i>0;i--){
            Grenades[i-1]->Show();
        }
    }

	void TempObjectHandler::InputHandling(Event ev){
	    for(int i=0;i<Grenades.size();i++){
            Grenades[i]->InputHandling(ev);
        }
        for(int i=0;i<Bullets.size();i++){
            Bullets[i]->InputHandling(ev);
        }
	}

    void TempObjectHandler::Add(Grenade* grenade){
        grenade->SetNumber(Grenades.size());
        Grenades.push_back(grenade);
    }

    void TempObjectHandler::Remove(Grenade* grenade){
        int num=grenade->GetNumber();
        for(int i=num+1;i<Grenades.size();i++){
            Grenades[i]->SetNumber(i-1);
        }
        Grenades.erase(Grenades.begin()+num);
    }

    void TempObjectHandler::Add(Bullet* bullet){
        bullet->SetNumber(Bullets.size());
        Bullets.push_back(bullet);
    }

    void TempObjectHandler::Remove(Bullet* bullet){
        int num=bullet->GetNumber();
        for(int i=num+1;i<Bullets.size();i++){
            Bullets[i]->SetNumber(i-1);
        }
        Bullets.erase(Bullets.begin()+num);
    }
