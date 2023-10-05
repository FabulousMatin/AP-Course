#include "Trip.hpp"


using namespace std;

Trip::Trip(int _id, string _passenger, string _origin, string _destination, double _price)
{
    status = WAITING;
    id = _id;
    passenger = _passenger;
    origin = _origin;
    destination = _destination;
    driver = "" ;
    price = _price;
}

void Trip::print(ostringstream& body, string username)
{
    body
        << "<tr>" << endl
        << "<td>" << id << "</td>" << endl
        << "<td>" << passenger << "</td>" << endl
        << "<td>" << origin << "</td>" << endl
        << "<td>" << destination << "</td>" << endl
        << "<td>" << fixed << setprecision(2) << price << "</td>" << endl;

    switch (status)
    {
    case WAITING:
        body << "<td>waiting</td>" << endl;
        break;
    case TRAVELING:
        body << "<td>traveling</td>" << endl;
        break;
    case FINISHED:
        body << "<td>finished</td>" << endl;
        break;
    }
    
    body 
        << "<td>" << endl
        << "<form method='post'>" << endl
        << "<input type='hidden' name='username' value='"<< username << "' >" << endl
        << "<input type='hidden' name='id' value='" << id << "' >" << endl
        << "<input type='submit' value='accept trip' formaction='acceptTrip_res'>" << endl
        << "<input type='submit' value='finish trip' formaction='finishTrip_res'>" << endl
        << "</form>" << endl
        << "</td>" << endl
        << "</tr>" << endl;
}

bool Trip::is_same_id(int _id)
{
    return (id == _id);
}

bool Trip::can_be_canceled(string username)
{
    return (username == passenger);
}
bool Trip::can_be_canceled()
{
    return (status == WAITING);
}

string Trip::get_passenger()
{
    return passenger;
}

void Trip::start()
{
    status = TRAVELING;
}
void Trip::finish()
{
    status = FINISHED;
}

bool Trip::can_be_accepted()
{
    return (status == WAITING);
}
bool Trip::can_be_finished()
{
    return (status == TRAVELING);
}

void Trip::set_driver(std::string _driver)
{
    driver = _driver;
}

bool Trip::can_be_finished_by(std::string username)
{
    return(driver == username);
}

double Trip::get_price()
{
    return price;
}