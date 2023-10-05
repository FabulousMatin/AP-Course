#include "Handlers.hpp"

using namespace std;

#define TRIP_RES 1

Signup::Signup(Utaxi* _utaxi) { utaxi = _utaxi; }
Post_trip::Post_trip(Utaxi* _utaxi) { utaxi = _utaxi; }
New_trip::New_trip(Utaxi* _utaxi) { utaxi = _utaxi; }
Get_all_trips::Get_all_trips(Utaxi* _utaxi) { utaxi = _utaxi; }
Get_a_trip::Get_a_trip(Utaxi* _utaxi) { utaxi = _utaxi; }
Get_cost::Get_cost(Utaxi* _utaxi) { utaxi = _utaxi; }
Show_cost::Show_cost(Utaxi* _utaxi) { utaxi = _utaxi; }
Cancel_trip::Cancel_trip(Utaxi* _utaxi) { utaxi = _utaxi; }
Accept_trip::Accept_trip(Utaxi* _utaxi) { utaxi = _utaxi; }
Finish_trip::Finish_trip(Utaxi* _utaxi) { utaxi = _utaxi; }



Response* Signup::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string user_type = req->getBodyParam("user_type");
    
    ostringstream body;
    try 
    { 
        utaxi->signup(username, user_type);
        body << res_html_creator("signed-up successfully.");
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }
    
    res->setBody(body.str());
    return res;
}

Response* Post_trip::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");

    res->setBody(trips_html_creator(utaxi, "new_trip_res", "Post"));  
    return res;
}

Response* New_trip::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string hurry = req->getBodyParam("in_hurry");
    string origin = req->getBodyParam("origin");
    string dest = req->getBodyParam("dest");

    ostringstream body;
    try 
    { 
        int trip_id = utaxi->add_trip(username, hurry, origin, dest);
        body << res_html_creator("Your trip has been added successfully.",TRIP_RES ,trip_id);
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }

    res->setBody(body.str());
    return res;
}


Response* Get_all_trips::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string is_sorted = req->getBodyParam("sort");

    ostringstream body;
    try
    {
        utaxi->get_trips(username, is_sorted, body);
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }
    res->setBody(body.str());
    return res;
}

Response* Get_a_trip::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string id = req->getBodyParam("id");

    ostringstream body;
    try
    {
        utaxi->get_a_uniqe_trip(username, id, body);
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }
    res->setBody(body.str());
    return res;
}

Response* Get_cost::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");

    res->setBody(trips_html_creator(utaxi, "getCost_res", "Get cost of"));  
    return res;
}



Response* Show_cost::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string hurry = req->getBodyParam("in_hurry");
    string origin = req->getBodyParam("origin");
    string dest = req->getBodyParam("dest");

    ostringstream body;
    try
    {
        double price = utaxi->get_price(username, hurry, origin, dest);
        body
            << "<!DOCTYPE html>" << endl
            << "<html>" << endl
            << "<body>" << endl
            << "price of a trip from " << origin << " to " << dest;
            if(hurry == "yes")
                body << " with";
            else    
                body << " without";
            body
                << " hurry is " << fixed << setprecision(2) << price << "<br/><hr>" << endl

                << "<a href='/getCost'>" << endl
                << "<input type='submit' value='Try another trip'>" << endl
                << "</a><br>" << endl

                << "<a href='/newtrip'>" << endl
                << "<input type='submit' value='Request a trip'>" << endl
                << "</a><br>" << endl

                << "<a href='/utaxi'>" << endl
                << "<input type='submit' value='Back to App'>" << endl
                << "</a><br>" << endl

                << "</body>" << endl
                << "</html>" << endl
                << res_css_creator();
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }
    
    res->setBody(body.str());
    return res;
}

Response* Cancel_trip::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string id = req->getBodyParam("id");

    ostringstream body;
    try
    {
        utaxi->cancel_trip(username, id);
        body << res_html_creator("Your trip has been canceled successfully.");
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }

    res->setBody(body.str());
    return res;
}


Response* Accept_trip::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string id = req->getBodyParam("id");

    ostringstream body;
    try
    {
        utaxi->accept_trip(username, id);
        body << res_html_creator("Trip accepted successfully.");
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }

    res->setBody(body.str());
    return res;
}


Response* Finish_trip::callback(Request* req)
{
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string id = req->getBodyParam("id");

    ostringstream body;
    try
    {
        utaxi->finish_trip(username, id);
        body << res_html_creator("Trip finished successfully.");
    }
    catch(Exceptions& ex)
    {
        int status_code;
        body << ex.handle_error(status_code);
    }

    res->setBody(body.str());
    return res;
}

string trips_css_creator()
{
    ostringstream body;
    body
        << "<style>" << endl

        << "*{" << endl
        << "margin: 15px;" << endl
        << "font-family: 'Georgia', 'serif';" << endl
        << "}" << endl

        << "body{" << endl
        << "background-color:burlywood;" << endl
        << "text-align: center;" << endl
        << "}" << endl

        << "input[type = submit], #origin, #dest{" << endl
        << "border: 2px solid black;" << endl
        << "color: black;" << endl
        << "padding: 10px 20px;" << endl
        << "text-align: center;" << endl
        << "font-size: 16px;" << endl
        << "background-color:lightblue;" << endl
        << "border-radius: 15px;" << endl
        << "}" << endl

        << ".field1{" << endl
        << "text-align: left;" << endl
        << "border: 4px dotted black;" << endl
        << "width: 70%;" << endl
        << "height: auto;" << endl
        << "margin: auto;" << endl
        << "}" << endl

        << "#back{" << endl
        << "float: left;" << endl
        << "margin-right: 1000px;" << endl
        << "}" << endl

        << "input[type = radio]{" << endl
        << "height: 19px;" << endl
        << "width: 19px;" << endl
        << "}" << endl

        << "input[type = text]{" << endl
        << "width: 25%;" << endl
        << "padding: 12px 20px;" << endl
        << "box-sizing: border-box;" << endl
        << "border: 3px solid black;" << endl
        << "background-color: white;" << endl
        << "border-radius: 5px;" << endl
        << "margin: 8px;" << endl
        << "}" << endl
  
        << "</style>" << endl;

    return body.str();
}


string trips_html_creator(Utaxi* utaxi, string redirect, string key_word)
{
    ostringstream body;
    body  
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl 
        << "<head>" << endl
        << "<title>" << key_word << " a trip</title>" << endl/////
        << "</head>" << endl
        << "<body>" << endl
        << "<input type='submit' id='back' value='back' onclick = \"window.location = '/utaxi';\"/> <br/>" << endl
        << "<fieldset class='field1'>" << endl/////
        << "<legend>Please fill all fields then " << key_word << " your trip:</legend>" << endl
        << "<form action='" << redirect << "' method='post'>" << endl
        << "Enter your username <br>" << endl
        << "<input name='username' type='text' placeholder='username'><br>" << endl
        << "Are you in hurry?<br>" << endl
        << "<input name='in_hurry' type='radio' id='yes' value='yes'>" << endl
        << "<label for='yes'>yes</label>" << endl
        << "<input name='in_hurry' type='radio' id='no' value='no'>" << endl
        << "<label for='no'>no</label><br>" << endl
        << "<label for = 'origin'>Choose your otigin:</label>" << endl
        << "<select id='origin' name='origin'>" << endl;
        for(int i = 0; i < utaxi->get_locs().size(); i++)
        {
            body << "<option value='" << utaxi->get_locs()[i] << "'>" << utaxi->get_locs()[i] << "</option>" << endl;
        }
        body 
            << "</select><br>" << endl
            << "<label for = 'dest'>Choose your destination:</label>" << endl
            << "<select id='dest' name='dest'>" << endl;
        for(int i = 0; i < utaxi->get_locs().size(); i++)
        {
            body << "<option value='" << utaxi->get_locs()[i] << "'>" << utaxi->get_locs()[i] << "</option>" << endl;
        }
        body
            << "</select><br>" << endl
            << "<input type='submit' value='" << key_word << " your trip'>" << endl
            << "</form>" << endl
            << "</fieldset>" << endl
            << "</body>" << endl
            << "</html>" << endl
            <<  trips_css_creator();

    return body.str();
}

string res_html_creator(string res_text, int mode, int trip_id)
{
    ostringstream body;
    body  
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<body>" << endl
        << "<h1>"<< res_text << "</h1><br>" << endl;

    if(mode == TRIP_RES)
        body << "your trip id is " << trip_id << "<br>" << endl;

    body        
        << "<a href='/'>" << endl
        << "<input type='submit' value='back' />" <<  endl
        << "</a>" << endl
        << "</body>" << endl
        << "</html>" << endl

        << res_css_creator();

    return body.str();
}

string res_css_creator()
{
    ostringstream body;
    body
        << "<style>" << endl
        
        << "*{" << endl
        << "margin: 15px;" << endl
        << "font-family: 'Georgia', 'serif';" << endl
        << "}" << endl

        << "body{" << endl
        << "background-color:lightgreen;" << endl
        << "text-align: center;" << endl
        << "}" << endl

        << "input[type = submit]{" << endl
        << "border: 2px solid black;" << endl
        << "color: black;" << endl
        << "padding: 15px 32px;" << endl
        << "text-align: center;" << endl
        << "font-size: 16px" << endl
        << "background-color:white;" << endl
        << "}" << endl

        << "</style>" << endl;

    return body.str();        
}