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

// problema con templates
auto existUser = [](LinkedList<User*>* _list, std::string _name, std::string _passw, int type)
{
    bool exist = true;
    for(LinkedList<User*>::Iterator it = _list->beginIt(); it != _list->endIt(); ++it)
    {
        User* currentData = *it;
        switch (type)
        {
        case 1:
            if(currentData->getName() == _name || currentData->getPassword() == _passw)
                return exist;
            break;
        case 2:
            if(currentData->getName() == _name && currentData->getPassword() == _passw)
                return exist;
            break;
        }
    }
    return !exist;
};

template <class T>
class Menu
{
private:
    File<T>* usersFile;
    LinkedList<T*>* listUser;

public:
    Menu();
    ~Menu();
    void mainMenuInterface();
    void mainMenu();

    void registerUser();
    void loginUser();

    void secondMenuInterface(std::string _nameMenu);
    void secondMenu(T* _user);


};

template <class T>
Menu<T>::Menu()
{
    usersFile = new File<T>();
    listUser = new LinkedList<T*>();
    usersFile->loadFile(listUser);
    
}

template <class T>
Menu<T>::~Menu()
{
    //free(usersFile);
}

template <class T>
void Menu<T>::mainMenuInterface()
{
    system("cls");
    std::cout << " ----------------------MENU--------------------- \n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "1) Iniciar Sesion." << "|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "2) Registrarse." << "|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "3) Salir." << "|\n";
    std::cout << " ----------------------------------------------- \n";
}

template <class T>
void Menu<T>::mainMenu()
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

template <class T>
void Menu<T>::secondMenuInterface(std::string _nameMenu)
{
    system("cls");
    std::cout << " ----------------- LOGIN MENU DE " << _nameMenu << " ---------------- \n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "1) Inicializar Repositorio." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "2) Crear archivo." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "3) Clonar Carpeta." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "4) Abrir archivo." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "5) Status." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "6) Add." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "7) Reset." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "8) Diff." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "9) commit." << "\t|\n";
    std::cout << "|\t\t" << std::left << std::setw(32) << "0) Menu Principal." << "\t|\n";
    std::cout << " ------------------------------------------------------- \n";
}

template <class T>
void Menu<T>::secondMenu(T* _user)
{
    char option = '\0';
    std::string fileName = "";
    std::string destinationPath = "";

    do
    {
        secondMenuInterface(_user->getName());
        option = getch();
        system("cls");
        switch (option)
        {
        case '1':
            // Inicializar Repositorio, se crean carpetas
            std::cout << "Se inicializa\n";
            // Se copia todos los archivos del repositorio local al area de trabajo
            usersFile->createInitUserFolder(_user->getName());
            // Pasar esos archivos --^
            break;

        case '2':
            // Crear archivo
            std::cout << "Se Crea archivo\n";
            std::cout << "Ingrese nombre del archivo sin(.txt) : ";
            getline(std::cin, fileName);
            usersFile->createFileUser(_user, fileName);
            break;
            
        case '3':
            // Clonar
            std::cout << "Se clono archivo\n";
            std::cout << "A que ruta desea pasar su repositoprio Local : ";
            getline(std::cin, destinationPath);
            usersFile->cloneRepository(_user, destinationPath);
            break;
        case '4':
            // Abrir x archivo
            std::cout << "Lista de archivos :\n";
            // Lista de archivos
            _user->printFiles();
            std::cout << "Ingrese el nombre del archivo sin(.txt) para abrir : ";
            getline(std::cin, fileName);
            // Se ingresa el nombre y procede 
            usersFile->openFile(_user, fileName);
            break;

        case '0': return;
        default:
            std::cerr << "Opcion invalida\n\n";
            break;
        }
        system("pause>0");
    } while (option != '0');
}

template <class T>
void Menu<T>::registerUser()
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
            if(!existUser(listUser, _name, _passw, 1)) // usuario no existente
            {
                T* newUser = new T(_name, _passw, _email);
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

template <class T>
void Menu<T>::loginUser()
{
    std::string _name = "", _password = "";
    
    char keyPressed = '\0';
    char exitKey = '\0';

    T* user = new T();

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
        if(existUser(listUser, _name, _password, 2))
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