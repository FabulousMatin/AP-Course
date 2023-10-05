#include "Exceptions.hpp"

using namespace std;

string Empty::handle_error(int& code)
{
    code = 204;
    switch (error_type)
    {
    case NO_TRIP:
        err_text = "there is no trip";
        prev_page_url = "/utaxi";
    break;
    case VARIABLE_EMPTY:
        err_text = "Please fill all fileds";
        prev_page_url = "/";
    break;
    }

    return create_html();
}
//////////////////////////////////////////////////////////////////////////////////////////////

string Not_found::handle_error(int& code)
{
    code = 404;
    
    switch (error_type)
    {
    case PASS_NF_ADD_TRIP:
        prev_page_url = "/newtrip";
        err_text = "User does not exist!";
    break;
    case DRI_NF_GET_TRIP:
        prev_page_url = "/all_trips";
        err_text = "User does not exist!";
    break;
    case TRIP_NF:
        prev_page_url = "/show_a_trip";
        err_text = "Trip not found!";
    break;
    case PASS_NF_GET_COST:
        prev_page_url = "/getCost";
        err_text = "User does not exist!";
    break;
    case PASS_NF_CANCEL:
        prev_page_url = "/cancelTrip";
        err_text = "User does not exist!";
    break;
    case TRIP_NF_CANCEL:
        prev_page_url = "/cancelTrip";
        err_text = "Trip not found!";
    break;
    case DRI_NF_ACC:
        prev_page_url = "/cancelTrip";
        err_text = "User not found!"; 
    break;
    case TRIP_NF_ACC:
        prev_page_url = "/acceptTrip";
        err_text = "Trip not found!";
    break;
    case DRI_NF_FIN:
        prev_page_url = "/finishTrip";
        err_text = "User not found!"; 
    break;
    case TRIP_NF_FIN:
        prev_page_url = "/finishTrip";
        err_text = "Trip not found!"; 
    break;
    }
    return create_html();
}

//////////////////////////////////////////////////////////////////////////////////////////////


string Bad_request::handle_error(int& code)
{
    code = 400;
    switch (error_type)
    {
    case USER_EXIST:
        err_text = "user already exist!";
        prev_page_url = "/signup";
    break;
    case ALREADY_IN_TRIP:
        err_text = "You are already in a trip!";
        prev_page_url = "/utaxi";
    break;
    case DEFAULT:
        err_text = "some error happened, please try again later.";
        prev_page_url = "/";
    break;
    case TRIP_NOT_CANCELABLE:
        err_text = "trip is in a stage which can not be canceled";
        prev_page_url = "/utaxi";
    break;
    case TRIP_NOT_ACCEPTABLE:
        err_text = "trip is in a stage which can not be accepted";
        prev_page_url = "/acceptTrip";
    break;
    case DRIVER_NOT_IN_TRIP:
        err_text = "You do not have any trip in progress";
        prev_page_url = "/utaxi";
    break;
    }
    return create_html();    
}


//////////////////////////////////////////////////////////////////////////////////////////////


string Permission_denied::handle_error(int& code)
{
    code = 101;
    prev_page_url = "/utaxi";

    switch (error_type)
    {
    case AFTER_ADD_TRIP:
        err_text = "Drivers can not access to passenger's pannel";
    break;
    case AFTER_GET_TRIP:
        err_text = "Passengers can not access to driver's pannel";
    break;
    case AFTER_GET_COST:
        err_text = "Drivers can not access to passenger's pannel";
    break;
    case AFTER_CANCEL:
        err_text = "Drivers can not access to passenger's pannel";
    break;
    case CANCEL_AMOTHER_TRIP:
        err_text = "You can not cancel another trip";
    break;
    case AFTER_ACCEPT:
        err_text = "Passengers can not access to driver's pannel";
    break;
    case AFTER_FINISH:
        err_text = "Passengers can not access to driver's pannel";
    break;
    case FINISH_ANOTHER_TRIP:
        err_text = "You can not finish another trip";
    break;
    }

   return create_html();
}


//////////////////////////////////////////////////////////////////////////////////////////////

string Exceptions::create_html()
{
    ostringstream body;
    body
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<body>" << endl
        << "<h1>" << err_header << "</h1><br/>" << endl
        << err_text << "<br/>" << endl
        << "<a href='" << prev_page_url << "'>" << endl
        << "<input type='button' value='back' />" <<  endl
        << "</a>" << endl
        << "</body>" << endl
        << "</html>" << endl
        << create_style();

    return body.str();
}
string Exceptions::create_style()
{
    ostringstream body;
    body
        << "<style>" << endl

        << "*{" << endl
        << "margin: 15px;" << endl
        << "font-family: 'Georgia', 'serif';" << endl
        << "}" << endl

        << "body{" << endl
        << "background-color:lightcoral;" << endl
        << "text-align: center;" << endl
        << "}" << endl

        << "input[type = button]{" << endl
        << "border: 2px solid black;" << endl
        << "color: black;" << endl
        << "padding: 15px 32px;" << endl
        << "text-align: center;" << endl
        << "font-size: 16px" << endl
        << "background-color:white;" << endl
        << "}" << endl
        
        << "</style>" << endl
        << "" << endl;

    return body.str();
}

Exceptions::Exceptions(int err)
{
    error_type = err;
}
Empty::Empty(int err) 
    :Exceptions(err)
{
    err_header = "ERROR 204 - EMPTY";
}
Not_found::Not_found(int err) 
    :Exceptions(err)
{
    err_header = "ERROR 404 - NOT FOUND";
}
Bad_request::Bad_request(int err) 
    :Exceptions(err)
{
    err_header = "ERROR 400 - BAD REQUEST";
}
Permission_denied::Permission_denied(int err) 
    :Exceptions(err)
{
    err_header = "ERROR 101 - PERMISSION DENIED";
}
