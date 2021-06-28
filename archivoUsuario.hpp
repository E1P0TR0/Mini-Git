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

    // agregar strings de contenido para el control de modificación
    // Se tiene dos string, uno de info_Anterior y otra inf_actual, y con ello se valida la modif
    std::string currentContent;

    // Ubicación
    std::string currentFolder; 

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

        // Contenido
        currentContent = creationDate;

    } 

    UserFile(std::string _name, std::string _creationDate, std::string _pathName) : name(_name), creationDate(_creationDate) 
    {
        // Actualizar contenido
        std::string pathFileOther = GEN_FOLDER_NAME "/" + _pathName + "/" + REPOSITORY + "/" + _name + ".txt";
        std::string line = "";

        std::ifstream inFile(pathFileOther, std::ios::in);
        if(inFile.fail()) std::cout << MSG_ERROR;
        else
            while(getline(inFile, line))
                currentContent += line;

        setCurrentContent(currentContent);
        inFile.close();
    }
    
    ~UserFile() {}

    void setName(std::string _name) { this->name = _name; }

    std::string getName() const { return this->name; }
    std::string getCreationDate() const { return this->creationDate; }

    std::string getCurrentContent() const { return this->currentContent; }
    void setCurrentContent(std::string _content) { this->currentContent = _content; }

    std::string getCurrentFolder() const { return this->currentFolder; }

};


#endif 