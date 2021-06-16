#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <string>

class User
{
private:
    std::string name;
    std::string password;

public:
    User(std::string _name = "", std::string _passw = "") : name(_name), password(_passw) {};
    ~User();
    inline std::string getName() const { return this->name; }
    inline std::string getPassword() const { return this->password; }

};

User::~User() {}

#endif