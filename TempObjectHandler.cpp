#include "TempObjectHandler.hpp"

    TempObjectHandler::TempObjectHandler(){
	    grenadeImg.LoadFromFile("contents/Granade1.png");
        detonation[0].LoadFromFile("contents/det1.png");
        detonation[1].LoadFromFile("contents/det2.png");
        detonation[2].LoadFromFile("contents/det3.png");
        GranadeSoundBuffer.LoadFromFile("contents/Grenade3.wav");
        GranadeThrowSoundBuffer.LoadFromFile("contents/grenade_throw.wav");
	    rocketImg.LoadFromFile("contents/rocket2.png");
	    RocketFlightSoundBuffer.LoadFromFile("contents/Rocket.wav");
    }

    void TempObjectHandler::ShowGrenades(){
	    for(int i=Grenades.size();i>0;i--){
            Grenades[i-1]->Show();
        }
    }

	void TempObjectHandler::ShowBullets(){
        for(int i=0;i<Bullets.size();i++){
            Bullets[i]->Show();
        }
    }

    void TempObjectHandler::ShowRockets(){
	    for(int i=Rockets.size();i>0;i--){
            Rockets[i-1]->Show();
        }
    }

    void TempObjectHandler::ShowRocketsDetonation(){
	    for(int i=Rockets.size();i>0;i--){
	        if(Rockets[i-1]->exploding){
                Rockets[i-1]->Show();
	        }
        }
    }

    void TempObjectHandler::ShowDBodyes(){
        for(int i=0;i<DBodyes.size();i++){
            DBodyes[i]->Show();
        }
    }

	void TempObjectHandler::InputHandling(){
	    for(int i=0;i<Grenades.size();i++){
            Grenades[i]->InputHandling();
        }
        for(int i=0;i<Bullets.size();i++){
            Bullets[i]->InputHandling();
        }
	    for(int i=0;i<Rockets.size();i++){
            Rockets[i]->InputHandling();
        }
        for(int i=0;i<DBodyes.size();i++){
            DBodyes[i]->InputHandling();
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

    void TempObjectHandler::Add(Rocket* rocket){
        rocket->SetNumber(Rockets.size());
        Rockets.push_back(rocket);
    }

    void TempObjectHandler::Remove(Rocket* rocket){
        int num=rocket->GetNumber();
        for(int i=num+1;i<Rockets.size();i++){
            Rockets[i]->SetNumber(i-1);
        }
        Rockets.erase(Rockets.begin()+num);
    }

    void TempObjectHandler::Add(DestroyableBody* dbody){
        dbody->SetNumber(DBodyes.size());
        DBodyes.push_back(dbody);
    }

    void TempObjectHandler::Remove(DestroyableBody* dbody){
        int num=dbody->GetNumber();
        for(int i=num+1;i<DBodyes.size();i++){
            DBodyes[i]->SetNumber(i-1);
        }
        DBodyes.erase(DBodyes.begin()+num);
    }
