#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Trip
{
public:
    Trip(int _id, std::string _passenger, std::string _origin, std::string _destination, double _price);
    void print(std::ostringstream& body, std::string username);
    bool is_same_id(int _id);
    bool can_be_canceled(std::string username);
    bool can_be_canceled();
    std::string get_passenger();
    void start();
    void finish();
    bool can_be_accepted();
    bool can_be_finished();
    void set_driver(std::string _driver);
    bool can_be_finished_by(std::string username);
    double get_price();

private:
    enum trip_statuses
    {
        TRAVELING,
        WAITING,
        FINISHED
    };
    
    int id;
    int status;
    double price;

    std::string passenger;
    std::string driver;
    std::string origin;
    std::string destination;
};

#endif