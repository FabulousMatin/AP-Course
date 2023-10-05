#ifndef UTAXI_H 
#define UTAXI_H

#include "User.hpp"
#include "Location.hpp"
#include "Trip.hpp"
#include "Exceptions.hpp"
#include <vector>
#include <string>


class Utaxi
{
public:
    void run(std::string file_address);//
    void import_locations(std::string file_address);//
    Location read_loc_file(std::string line);//
    std::vector<std::string> parse_command(std::string command_line);
    void handle_command(std::vector<std::string> commands);
    int type(const std::vector<std::string>& commands);
    int post_command(const std::vector<std::string>& commands);
    int get_command(const std::vector<std::string>& commands);
    int delete_command(const std::vector<std::string>& commands);
    int find_element(std::vector<std::string> vec, std::string goal);
    bool is_element_exist(std::vector<std::string> vec, std::string goal);
    bool is_user_exist(std::string username);
    bool is_role_valid(std::string role);
    User* find_user(std::string username);
    bool is_location_exist(std::string loc_name);
    Trip* find_trip(int id);
    int trip_index(int id);
    void print_trips(std::ostringstream& body, std::string username);
    void sort_and_print_trips(std::ostringstream& body, std::string username);
    bool is_trip_exist(int id);
    Location find_location(std::string name);
    bool is_active(std::string str);
    

    bool is_empty(std::string);
    std::vector<std::string> get_locs();
    std::string create_trip_html();
    std::string create_trip_css();

    void signup(std::string username, std::string role);
    int add_trip(std::string username, std::string hurry_status, std::string origin, std::string dest);
    void get_trips(std::string username, std::string is_sorted, std::ostringstream& body);
    void get_a_uniqe_trip(std::string username, std::string trip_id, std::ostringstream& body);
    double get_price(std::string username, std::string hurry_status, std::string origin, std::string dest);
    void cancel_trip(std::string username, std::string trip_id);
    void accept_trip(std::string username, std::string trip_id);
    void finish_trip(std::string username, std::string trip_id);
    

    void test();
private:
  enum command_types
    {
        POST_SIGNUP,
        POST_TRIP,
        GET_TRIPS,
        GET_A_TRIP,
        CANCEL_TRIP,
        ACCEPT_TRIP,
        FINISH_TRIP,
        GET_PRICE
    };
    std::vector<User*> users;
    std::vector<Location> locations;
    std::vector<Trip*> trips;
    int trips_order = 1;
};

#endif