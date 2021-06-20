#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <string>

class User
{
private:
    std::string name;
    std::string password;
    std::string email;

public:
    User(std::string _name = "", std::string _passw = "", std::string _email = "") : name(_name), password(_passw), email(_email) {};
    ~User();
    inline std::string getName() const { return this->name; }
    inline std::string getPassword() const { return this->password; }
    inline std::string getEmail() const { return this->email; }
  
};

User::~User() {}

#endif