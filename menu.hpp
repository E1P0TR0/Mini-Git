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

#include "archivo.hpp"

#include <iostream>
#include <iomanip>
#include <conio.h>

    
auto existUser = [](LinkedList<User*>* _list, std::string _name, std::string _passw)
{
    bool exist = true;
    for(LinkedList<User*>::Iterator it = _list->beginIt(); it != _list->endIt(); ++it)
    {
        User* currentData = *it;
        if(currentData->getName() == _name || currentData->getPassword() == _passw)
            return exist;
    }
    return !exist;
};

class Menu
{
private:
    File* usersFile;
    // Cambiar a templates luego
    LinkedList<User*>* listUser;

public:
    Menu();
    ~Menu();
    void mainMenuInterface();
    void mainMenu();

    void registerUser();
    void loginUser();

    void secondMenuInterface(std::string _nameMenu);
    void secondMenu(User* _user);
};

Menu::Menu()
{
    usersFile = new File();
    listUser = new LinkedList<User*>();
    usersFile->loadFile(listUser);
    
}

Menu::~Menu()
{
    //free(usersFile);
}

void Menu::mainMenuInterface()
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
        mainMenuInterface();
        option = getch();
        system("cls");
        switch (option)
        {
        case '1':
            // Iniciar sesión
            loginUser();
            break;
        case '2':
            // Registrarse 
            registerUser();
            break;
        case '3':
            std::cout << "Saliendo...\n";
            break;
        default:
            std::cerr << "Opcion invalida\n\n";
            break;
        }
        //system("pause>0");
    } while (option != '3');
}

void Menu::secondMenuInterface(std::string _nameMenu)
{
    system("cls");
    std::cout << " ----------------- LOGIN MENU DE " << _nameMenu << " ---------------- \n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "1) Inicializar Repositorio." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "2) Crear archivo." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "3) Clonar Carpeta." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "4) Menu Principal." << "\t|\n";
    std::cout << " ------------------------------------------------------- \n";
}

void Menu::secondMenu(User* _user)
{
    char option = '\0';
    do
    {
        secondMenuInterface(_user->getName());
        option = getch();
        system("cls");
        switch (option)
        {
        case '1':
            // Inicializar Repositorio
            std::cout << "Se inicializo\n";
            break;
        case '2':
            // Crear archivo
            std::cout << "Se Creo archivo\n";
            break;
        case '3':
            // Clonar
            std::cout << "Se clono archivo\n";
            break;
        case '4': break;
        default:
            std::cerr << "Opcion invalida\n\n";
            break;
        }
        //system("pause>0");
    } while (option != '4');
}

void Menu::registerUser()
{
    std::string _name = "", _passw = "", _email = "";

    // Para verificar diferentes usuarios
    bool anotherUser = true;
    char exitKey = '\0';


    do
    {
        system("cls");
        std::cout << "\t\t\tREGISTRO DE USUARIO\n";
        std::cout << "\t\t\t-------------------\n";
        std::cout << "\n\tUsuario: ";
        getline(std::cin, _name);
        std::cout << "\n\tConstrasena: ";
        getline(std::cin, _passw);
        std::cout << "\n\tCorreo: ";
        getline(std::cin, _email);


        if(_name != "\0" && _passw != "\0" && _email != "\0")
            if(!existUser(listUser, _name, _passw)) // usuario no existente
            {
                User* newUser = new User(_name, _passw, _email);
                listUser->addFinal(newUser);
                usersFile->writeFile(newUser->getName(), newUser->getPassword(), newUser->getEmail());
                usersFile->createUserFolder(newUser->getName());
                anotherUser = false;
            }
            else   
                std::cout << "\t\t\nUsuario existente!\n\n";
        else    
            std::cout << "\t\t\nDatos invalidos, Vuelva a intentarlo...\n\n";

        std::cin.ignore();

        std::cout << "\n3) Volver.\n";
    } while (anotherUser || (exitKey = getch()) != '3');
}

void Menu::loginUser()
{
    std::string _name = "", _password = "";
    
    char keyPressed = '\0';
    char exitKey = '\0';

    User* user = new User();

    unsigned int accountant = 0;
    bool valid = false;

    do
    {
        system("cls");
        std::cout << "\t\t\tLOGIN DE USUARIO\n";
        std::cout << "\t\t\t----------------\n";
        std::cout << "\n\tUsuario: ";

        std::getline(std::cin, _name);

        std::cout << "\n\tPassword: ";
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
        if(existUser(listUser, _name, _password))
        {
            user = listUser->getElement(_name);
            valid = true;
            break;
        }

        if(!valid)
        {
            std::cout << "\n\n\tEl usuario y/o password son incorrectos" << std::endl;
            std::cin.get();
            accountant++;
        }

        std::cout << "\n3) Volver.\n";
        if((exitKey = getch()) == '3') return;

    } while(valid == false && accountant < INTENTOS);


    if(valid == false)
        std::cout << "\n\tUsted no pudo ingresar al sistema. ADIOS" << std::endl;
    else
    {
        std::cout << "\n\n\tBienvenido al sistema" << std::endl;
        
        // Se inicia las principales funciones
        system("pause>0");


        secondMenu(user); 
    }
}

#endif