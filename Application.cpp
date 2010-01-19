#include "Application.hpp"

	Application::Application(int width, int height){
        Window=new RenderWindow(VideoMode(width, height, 32), "AnimalFighter",Style::Close);
        Window->UseVerticalSync(true);
        //Window->SetFramerateLimit(60);
        menu=new Menu(Window);
	}

	void Application::EventHandle(){
        while(Window->IsOpened()){
            Event Event;
            while (Window->GetEvent(Event)){
                menu->EventHandle(Event);
                if (Event.Type == Event::Closed) Window->Close();

                if (Event.Type == Event::KeyPressed){
                    if (Event.Key.Code == Key::Escape) Window->Close();
                }

            }

            Window->Clear();
            menu->Show();
            Window->Display();
        }
	}
