#include "Utaxi.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Location Utaxi::read_loc_file(string line)
{
    string loc;
    double lat = 0, lon = 0;
    int pos, traffic;

    pos = line.find(',');
    loc = line.substr(0, pos);
    line.erase(0, pos + 1);

    pos = line.find(',');
    lat = stod(line.substr(0, pos));
    line.erase(0, pos + 1);

    pos = line.find(',');
    lon = stod(line.substr(0, pos));
    line.erase(0, pos + 1);

    traffic = stoi(line);


    return Location(loc, lat, lon, traffic);
}

void Utaxi::import_locations(string file_address)
{
    ifstream loc_file;
    loc_file.open(file_address);
    
    string line;
    getline(loc_file, line);
    while(getline(loc_file, line))
        locations.push_back(read_loc_file(line));
}

vector<string> Utaxi::parse_command(string command_line)
{
    vector<string> parsed_words;
	string word = "";
	for (int i = 0; i < command_line.size(); i++)
	{
		if (command_line[i] == ' ')
		{
			parsed_words.push_back(word);
			word = "";
		}
		else
		{
			word += command_line[i];
		}
	}
	parsed_words.push_back(word);

	return parsed_words;
}

vector<string> Utaxi::get_locs()
{
    vector<string> locs;
    for(int i = 0; i < locations.size(); i++)
        locs.push_back(locations[i].get_name());
    return locs;
}

bool Utaxi::is_user_exist(std::string username)
{
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i]->is_same_name(username))
            return true;
    }
    return false;
}

User* Utaxi::find_user(std::string username)
{
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i]->is_same_name(username))
            return users[i];
    }
    return NULL;
}

bool Utaxi::is_trip_exist(int id)
{
    for(int i = 0; i < trips.size(); i++)
    {
        if(trips[i]->is_same_id(id))
            return true;
    }
    return false;
}

Location Utaxi::find_location(string name)
{
    for(int i = 0; i < locations.size(); i++)
    {
        if(locations[i].is_same_name(name))
            return locations[i];
    }
}

Trip* Utaxi::find_trip(int id)
{
    for(int i = 0; i < trips.size(); i++)
    {
        if(trips[i]->is_same_id(id))
            return trips[i];
    }
}

int Utaxi::trip_index(int id)
{
    for(int i = 0; i < trips.size(); i++)
    {
        if(trips[i]->is_same_id(id))
            return i;
    }
}

int Utaxi::find_element(vector<string> vec, string goal)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == goal)
            return i;
    }
    throw Bad_request(0);
}

bool Utaxi::is_element_exist(vector<string> vec, string goal)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == goal)
            return true;
    }
    return false;
}


bool Utaxi::is_role_valid(string role)
{
    return (role == "driver" || role == "passenger" );
}

bool Utaxi::is_active(std::string str)
{
    if(str == "yes")
        return true;
    else if(str == "no")
        return false;
    else 
        throw(Bad_request(Bad_request::types::DEFAULT));
}

bool Utaxi::is_location_exist(string loc_name)
{
    for(int i = 0; i < locations.size(); i++)
    {
        if(locations[i].is_same_name(loc_name))
            return true;
    }
    return false;
}

void Utaxi::print_trips(ostringstream& body, std::string username)
{
    for(int i = 0; i < trips.size(); i++)
        trips[i]->print(body, username);
}

void Utaxi::sort_and_print_trips(ostringstream& body, std::string username)
{
    vector<Trip*> available_trips = trips;
    for (int i = available_trips.size() - 1; i >= 0; i--)
		for (int j = 0; j < i; j++)
			if (available_trips[j + 1]->get_price() > available_trips[j]->get_price())
				swap(available_trips[j], available_trips[j + 1]);

    for(int i = 0; i < available_trips.size(); i++)
        available_trips[i]->print(body, username);
}

void Utaxi::run(string file_address)
{
    import_locations(file_address);
}

string Utaxi::create_trip_html()
{
    ostringstream body;
    body
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<style>" << endl
        << "table, th, td {border:5px solid lightblue;}" << endl
        << "</style>" << endl
        << "<body>" << endl
        << "<a href='/utaxi'>" << endl
        << "<input type='submit' value='back'>" << endl
        << "</a>" << endl
        << "<h2>Trips</h2>" << endl
        << "<table style='width:100%'>" << endl
        << "<tr>" << endl
        << "<th>id</th>" << endl
        << "<th>passenger</th>" << endl
        << "<th>origin</th>" << endl
        << "<th>destination</th>" << endl
        << "<th>price</th>" << endl
        << "<th>status</th>" << endl
        << "<th>action</th>" << endl
        << "</tr>" << endl;
    
    return body.str();
}

string Utaxi::create_trip_css()
{
    ostringstream body;
    body
        << "</table>" << endl
        << "</body>" << endl
        << "</html>" << endl

        << "<style>" << endl
        << "*{" << endl
        << "margin: 15px;" << endl
        << "font-family: 'Georgia', 'serif';" << endl
        << "}" << endl

        << "body{" << endl
        << "background-color:burlywood;" << endl
        << "text-align: center;" << endl
        << "}" << endl

        << "input[type = submit]{" << endl
        << "border: 2px solid black;" << endl
        << "color: black;" << endl
        << "padding: 15px 32px;" << endl
        << "text-align: center;" << endl
        << "font-size: 16px;" << endl
        << "background-color:lightblue;" << endl
        << "}" << endl

        << "table{" << endl
        << "border-collapse: collapse;" << endl
        << "}" << endl
        << "</style>" << endl;

    return body.str();
}

bool Utaxi::is_empty(string str)
{
    if(str == "")
        return true;
    return false;
}

void Utaxi::signup(string username, string role)
{
    if(is_empty(username) || is_empty(role))
        throw Empty(Empty::types::VARIABLE_EMPTY);

    if(is_user_exist(username))
        throw Bad_request(Bad_request::types::USER_EXIST);

    if(role == "driver")
    {
        User* new_driver = new Driver(username);
        users.push_back(new_driver);
    }
    else if(role == "passenger")
    {
        User* new_passenger = new Passenger(username);
        users.push_back(new_passenger);
    }
}

int Utaxi::add_trip(string username, string hurry_status, string origin, string dest)
{
    if(is_empty(username) || is_empty(hurry_status) || is_empty(origin) || is_empty(origin))
        throw Empty(Empty::types::VARIABLE_EMPTY);

    if(!is_user_exist(username))
        throw Not_found(Not_found::types::PASS_NF_ADD_TRIP);

    User* user = find_user(username);
    if(!user->is_allowed(PASSENGER))
        throw Permission_denied(Permission_denied::types::AFTER_ADD_TRIP);
    if(user->is_in_trip())
        throw Bad_request(Bad_request::types::ALREADY_IN_TRIP);

    int in_hurry = is_active(hurry_status);

    double price = find_location(origin).calc_price(find_location(dest), in_hurry);    
    Trip* new_trip = new Trip(trips_order, username, origin, dest, price);
    trips.push_back(new_trip);

    user->start_trip();
    trips_order++;

    return trips_order - 1;
}

void Utaxi::get_trips(string username, string sort, ostringstream& body)
{
    if(is_empty(username) || is_empty(sort))
        throw Empty(Empty::types::VARIABLE_EMPTY);

    if(!is_user_exist(username))
        throw Not_found(Not_found::types::DRI_NF_GET_TRIP);

    User* user = find_user(username);
    if(!user->is_allowed(DRIVER))
        throw Permission_denied(Permission_denied::types::AFTER_GET_TRIP);

    if(trips.size() == 0)
        throw Empty(Empty::types::NO_TRIP);

    int is_sorted = is_active(sort);

    body << create_trip_html();
    if(is_sorted)
        sort_and_print_trips(body, username);
    else
        print_trips(body, username);
    body << create_trip_css();
}

void Utaxi::get_a_uniqe_trip(string username, string trip_id, ostringstream& body)
{
    if(is_empty(username) || is_empty(trip_id))
        throw Empty(Empty::types::VARIABLE_EMPTY);

    if(!is_user_exist(username))
        throw Not_found(Not_found::DRI_NF_GET_TRIP);

    User* user = find_user(username);
    if(!user->is_allowed(DRIVER))
        throw Permission_denied(Permission_denied::AFTER_GET_TRIP);

    int id = stoi(trip_id);
    if(!is_trip_exist(id))
        throw Not_found(Not_found::TRIP_NF);

    body << create_trip_html();
    find_trip(id)->print(body, username);
    body << create_trip_css();
}

double Utaxi::get_price(string username, string hurry_status, string origin, string dest)
{
    if(is_empty(username) || is_empty(hurry_status))
        throw Empty(Empty::types::VARIABLE_EMPTY);

    if(!is_user_exist(username))
        throw(Not_found(Not_found::types::PASS_NF_GET_COST));
    
    User* user = find_user(username);
    if(!user->is_allowed(PASSENGER))
        throw Permission_denied(Permission_denied::types::AFTER_GET_COST);

    int in_hurry = is_active(hurry_status);

    return find_location(origin).calc_price(find_location(dest), in_hurry);
}

void Utaxi::cancel_trip(string username, string trip_id)
{
    if(is_empty(username) || is_empty(trip_id))
        throw Empty(Empty::types::VARIABLE_EMPTY);


    if(!is_user_exist(username))
        throw Not_found(Not_found::types::PASS_NF_CANCEL);

    User* user = find_user(username);
    if(!user->is_allowed(PASSENGER))
        throw Permission_denied(Permission_denied::types::AFTER_CANCEL);

    int id = stoi(trip_id);
    if(!is_trip_exist(id))
        throw Not_found(Not_found::types::TRIP_NF_CANCEL);

    Trip* current_trip = find_trip(id);
    if(!current_trip->can_be_canceled(username))
        throw Permission_denied(Permission_denied::types::CANCEL_AMOTHER_TRIP);
    else if(!current_trip->can_be_canceled())
        throw Bad_request(Bad_request::types::TRIP_NOT_CANCELABLE);

    trips.erase(trips.begin() + trip_index(id));
    user->finish_trip();
}

void Utaxi::accept_trip(string username, string trip_id)
{
    if(is_empty(username) || is_empty(trip_id))
        throw Empty(Empty::types::VARIABLE_EMPTY);

    if(!is_user_exist(username))
        throw Not_found(Not_found::types::DRI_NF_ACC);

    User* driver = find_user(username);
    if(!driver->is_allowed(DRIVER))
        throw Permission_denied(Permission_denied::types::AFTER_ACCEPT);

    int id = stoi(trip_id);
    if(!is_trip_exist(id))
        throw Not_found(Not_found::types::TRIP_NF_ACC);

    if(driver->is_in_trip())
        throw Bad_request(Bad_request::types::ALREADY_IN_TRIP);

    Trip* current_trip = find_trip(id);
    if(!current_trip->can_be_accepted())
        throw Bad_request(Bad_request::types::TRIP_NOT_ACCEPTABLE);
        
    driver->start_trip();
    find_user(current_trip->get_passenger())->start_trip();
    current_trip->set_driver(username);
    current_trip->start();
}

void Utaxi::finish_trip(string username, string trip_id)
{
    if(is_empty(username) || is_empty(trip_id))
        throw Empty(Empty::types::VARIABLE_EMPTY);

    if(!is_user_exist(username))
        throw Not_found(Not_found::types::DRI_NF_FIN);

    User* driver = find_user(username);
    if(!driver->is_allowed(DRIVER))
        throw Permission_denied(Permission_denied::types::AFTER_FINISH);

    int id = stoi(trip_id);
    if(!is_trip_exist(id))
        throw Not_found(Not_found::types::TRIP_NF_FIN);

    if(!driver->is_in_trip())
        throw Bad_request(Bad_request::types::DRIVER_NOT_IN_TRIP);

    Trip* current_trip = find_trip(id);
    if(!current_trip->can_be_finished_by(username))
        throw Permission_denied(Permission_denied::types::FINISH_ANOTHER_TRIP);


    driver->finish_trip();
    find_user(current_trip->get_passenger())->finish_trip();
    current_trip->finish();
}
