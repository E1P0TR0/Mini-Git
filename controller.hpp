#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "menu.hpp"

class Controller
{
private:
    Menu* objMenu;

public:
    Controller(); // por el momento
    ~Controller();
};

Controller::Controller()
{
    // Creación de objetos
    objMenu = new Menu();
    objMenu->mainMenu();
}

Controller::~Controller()
{
    free(objMenu);
}

#endif