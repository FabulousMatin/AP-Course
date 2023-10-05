#ifndef USER_H
#define USER_H

#include <string>

#define DRIVER 1
#define PASSENGER 2

class User
{
public:
    bool is_same_name(std::string username);
    User(std::string _name);
    virtual bool is_allowed(int type) = 0;
    bool is_in_trip();
    void start_trip();
    void finish_trip();
protected:
    std::string name;
    int in_trip = false;
};

class Driver : public User 
{
public:
    Driver(std::string _name);
    bool is_allowed(int type);
private:
};

class Passenger : public User
{
public:
    Passenger(std::string _name);
    bool is_allowed(int type);

};
#endif