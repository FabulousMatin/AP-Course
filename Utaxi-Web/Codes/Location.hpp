#ifndef LOCATIONS_H
#define LOCATIONS_H 


#include <string>

class Location
{

public:
    Location(std::string _location, double _latitude, double _longitude, int _traffic);
    bool is_same_name(std::string loc_name);
    double calc_price(Location dest, int hurry);
    std::string get_name();
private:
    std::string location;
    double latitude;
    double longitude;
    int traffic;
    
};



#endif