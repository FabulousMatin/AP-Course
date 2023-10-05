#include "Web.hpp"

using namespace std;

Web::Web(int port)
    :server(port)
{
    utaxi = new Utaxi();
}

void Web::run(string file_address)
{
    utaxi->run(file_address);
    try
    {
        server.get("/", new ShowPage("Static/HomePage.html"));
        server.get("/utaxi", new ShowPage("Static/Utaxi.html"));
        server.get("/signup", new ShowPage("Static/signup.html"));
        server.get("/newtrip", new Post_trip(utaxi));
        server.get("/all_trips", new ShowPage("Static/GetTrips.html"));
        server.get("/show_a_trip", new ShowPage("Static/GetAtrip.html"));
        server.get("/getCost", new Get_cost(utaxi));
        server.get("/cancelTrip", new ShowPage("Static/CancelTrip.html"));
        server.get("/acceptTrip", new ShowPage("Static/AcceptTrip.html"));
        server.get("/finishTrip", new ShowPage("Static/FinishTrip.html"));
        
        server.get("/homePage_img", new ShowImage("Images/homePage.jpg"));

        server.post("/finishTrip_res", new Finish_trip(utaxi));
        server.post("/acceptTrip_res", new Accept_trip(utaxi));
        server.post("/cancelTrip_res", new Cancel_trip(utaxi));
        server.post("/getCost_res", new Show_cost(utaxi));
        server.post("/a_trip_res", new Get_a_trip(utaxi));
        server.post("/allTrips_res", new Get_all_trips(utaxi));
        server.post("/new_trip_res", new New_trip(utaxi));
        server.post("/signup_res", new Signup(utaxi));
        server.run();
    }
    catch(Server::Exception e) 
    {
        cerr << e.getMessage() << endl;
    }
}