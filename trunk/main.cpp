#include "Application.hpp"

int main(){
    Application* App = new Application (800,600);
    App->EventHandle();
    return EXIT_SUCCESS;
}
