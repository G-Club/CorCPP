#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

class User
{
public:
    User();
    ~User();
    static User Parse(const std::string& json);
};

#endif // USER_H
