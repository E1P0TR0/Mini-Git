#ifndef __MENU_HPP__
#define __MENU_HPP__

// para el registro de usuario
//#include "stdafx.h"
#include <string>
#include <cstdlib>

#define ENTER 13
#define BACKSPACE 8
#define INTENTOS 3

// --------------------------------------

#include "usuario.hpp"
#include "archivo.hpp"

#include <iostream>
#include <iomanip>
#include <conio.h>

class Menu
{
private:
    File* usersFile;

public:
    Menu();
    ~Menu();
    void menuInterface();
    void mainMenu();

    void registerUser();
    void loginUser();
};

Menu::Menu()
{
    usersFile = new File();
}

Menu::~Menu()
{
    //free(usersFile);
}

void Menu::menuInterface()
{
    system("cls");
    std::cout << " ----------------------MENU--------------------- \n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "1) Iniciar Sesion." << "|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "2) Registrarse." << "|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "3) Salir." << "|\n";
    std::cout << " ----------------------------------------------- \n";
}

void Menu::mainMenu()
{
   char option = '\0';
    do
    {
        menuInterface();
        option = getch();
        system("cls");
        switch (option)
        {
        case '1':
            // Iniciar sesión
            std::cout << "Se inicio sesion\n";
            break;
        case '2':
            registerUser();
            break;
        case '3':
            std::cout << "Saliendo...\n";
            break;
        default:
            std::cerr << "Opcion invalida\n\n";
            break;
        }
        system("pause");
    } while (option != '3');
    
}

void Menu::registerUser()
{
    std::string _name = "", _passw = "";

    // Para verificar diferentes usuarios
    bool anotherUser = false;

    do
    {
        system("cls");
        std::cout << "\t\t\tREGISTRO DE USUARIO\n";
        std::cout << "\t\t\t-------------------\n";
        std::cout << "\n\tUsuario: ";
        getline(std::cin, _name);
        std::cout << "\n\tConstrasena: ";
        getline(std::cin, _passw);

        User* newUser = new User(_name, _passw);
        usersFile->writeFile(newUser->getName(), newUser->getPassword());

    } while (anotherUser);
    
}

// falta implementar y corregir
void Menu::loginUser()
{
    std::string _name = "", _password = "";
    
    char keyPressed = '\0';

    unsigned int accountant = 0;
    bool valid = false;

    do
    {
        system("cls");
        std::cout << "\t\t\tLOGIN DE USUARIO\n";
        std::cout << "\t\t\t----------------\n";
        std::cout << "\n\tUsuario: ";

        getline(std::cin, _name);

        std::cout << "\tPassword: ";
        keyPressed = _getch();

        _password = "";

        while(keyPressed != ENTER) // se lee contraseña
        {
            if(keyPressed != BACKSPACE)
            {
                _password.push_back(keyPressed);
                std::cout << "*";
            }
            else
            {
                if(_password.length() > 0)
                {
                    std::cout << "\b \b";
                    _password = _password.substr(0, _password.length() - 1);
                }
            }
            keyPressed = _getch();
        }

        // Validar datos en archivo .txt

        // if (usuarios[i] == _name && claves[i] == _password)
        // {
        //     valid = true;
        //     break;
        // }

        if(!valid)
        {
            std::cout << "\n\n\tEl usuario y/o password son incorrectos" << std::endl;
            std::cin.get();
            accountant++;
        }

    } while(valid == false && accountant < INTENTOS);

    if(valid == false)
        std::cout << "\n\tUsted no pudo ingresar al sistema. ADIOS" << std::endl;
    else
    {
        std::cout << "\n\n\tBienvenido al sistema" << std::endl;
        
        // Aquí va el código del programa cuando el usuario ingresa sus credenciales correctas
        
    }
    std::cin.get();
}

#endif