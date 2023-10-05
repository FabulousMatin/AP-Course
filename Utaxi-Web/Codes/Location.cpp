#include "Location.hpp"
#include <math.h>

#define BASE_PRICE 10000
#define DEGREE_TO_KM 110.5
#define HURRY_INCREASE_RATIO 1.2

using namespace std;

Location::Location(string _location, double _latitude, double _longitude, int _traffic)
{
    location = _location;
    latitude = _latitude;
    longitude = _longitude;
    traffic = _traffic;
}

bool Location::is_same_name(std::string loc_name)
{
    return (location == loc_name);
}

double Location::calc_price(Location dest, int hurry)
{
    double price = DEGREE_TO_KM * (sqrt(pow(latitude - dest.latitude, 2) + pow(longitude - dest.longitude, 2)))
            * (traffic + dest.traffic) * BASE_PRICE;

    if(hurry)
        return price * HURRY_INCREASE_RATIO;
    return price;
} 

string Location::get_name()
{
    return location;
}