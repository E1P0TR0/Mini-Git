#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "menu.hpp"
#include "usuario.hpp"

class Controller
{
private:
    Menu<User>* objMenu;

public:
    Controller(); // por el momento
    ~Controller();
};

Controller::Controller()
{
    // Creación de objetos
    objMenu = new Menu<User>();
    objMenu->mainMenu();
}

Controller::~Controller()
{
    free(objMenu);
}

#endif