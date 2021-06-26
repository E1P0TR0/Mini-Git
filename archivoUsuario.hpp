#ifndef __ARCHIVO_USUARIO_HPP__
#define __ARCHIVO_USUARIO_HPP__

#include <iostream>
#include <sstream>
#include <ctime>



class UserFile
{
private:
    std::string name;
    std::string creationDate;


    // agregar bool para el control de modificación
public:
    UserFile(std::string _name = "") : name(_name)
    {
        time_t now = time(0);
        char* dt = ctime(&now); // devuelve fecha exacta
    
        this->creationDate = dt;
        //std::stringstream ss(dt); // para separar fecha a solo horas min y seg
        //std::string part = "";

        //while(std::getline(ss, part, ' '))
        //    std::cout << part << "\n";


    } 

    UserFile(std::string _name, std::string _creationDate) : name(_name), creationDate(_creationDate) {}
    
    ~UserFile() {}

    inline std::string getName() const { return this->name; }
    inline std::string getCreationDate() const { return this->creationDate; }

};


#endif 