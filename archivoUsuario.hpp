#ifndef __ARCHIVO_USUARIO_HPP__
#define __ARCHIVO_USUARIO_HPP__

#include <iostream>

class UserFile
{
private:
    std::string name;
    std::string creationDate;

    // agregar bool para el control de modificación
public:
    UserFile(std::string _name = "", std::string _creationDate = "") : name(_name), creationDate(_creationDate) {} 
    ~UserFile() {}

    inline std::string getName() const { return this->name; }
    inline std::string getCreationDate() const { return this->creationDate; }

};


#endif 