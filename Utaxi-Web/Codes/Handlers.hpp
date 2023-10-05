#ifndef _HANDLERS_
#define _HANDLERS_

#include <iostream>
#include <string>
#include <sstream> 
#include <iomanip>
#include "../server/server.hpp"
#include "../Codes/Utaxi.hpp"

std::string trips_html_creator(Utaxi* , std::string redirect, std::string key_word);
std::string trips_css_creator();
std::string res_html_creator(std::string res_text, int mode = 0, int trip_id = 0);
std::string res_css_creator();

class Signup : public RequestHandler
{
public:
   Signup(Utaxi*);
   Response* callback(Request*);
};

class Post_trip : public RequestHandler
{
public:
   Post_trip(Utaxi*);
   Response* callback(Request*);
};

class New_trip : public RequestHandler
{
public:
   New_trip(Utaxi*);
   Response* callback(Request*);
};

class Get_all_trips : public RequestHandler
{
public:
   Get_all_trips(Utaxi*);
   Response* callback(Request*);
};

class Get_a_trip : public RequestHandler
{
public:
   Get_a_trip(Utaxi*);
   Response* callback(Request*);
};

class Get_cost : public RequestHandler
{
public:
   Get_cost(Utaxi*);
   Response* callback(Request*);
};

class Show_cost : public RequestHandler
{
public:
   Show_cost(Utaxi*);
   Response* callback(Request*);
};

class Cancel_trip : public RequestHandler
{
public:
   Cancel_trip(Utaxi*);
   Response* callback(Request*);
};

class Accept_trip : public RequestHandler
{
public:
   Accept_trip(Utaxi*);
   Response* callback(Request*);
};

class Finish_trip : public RequestHandler
{
public:
   Finish_trip(Utaxi*);
   Response* callback(Request*);
};
#endif