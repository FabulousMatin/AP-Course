#include "User.hpp"

using namespace std;

bool User::is_same_name(string username)
{
    return (username == name);
}

User::User(string _name)
{
    name = _name;
}
Driver::Driver(string _name)
    : User(_name)
{

}
Passenger::Passenger(string _name)
    : User(_name)
{

}

bool Driver::is_allowed(int type)
{
    if(type == DRIVER)
        return true;
    return false;
}

bool Passenger::is_allowed(int type)
{
    if(type == DRIVER)
        return false;
    return true;
}

bool User::is_in_trip()
{
    return in_trip;
}

void User::start_trip()
{
    in_trip = true;
}
void User::finish_trip()
{
    in_trip = false;
}