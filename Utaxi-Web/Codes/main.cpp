#include "Web.hpp"


using namespace std;

int main(int argc, char* argv[])
{
    Web web(argc == 2 ? 5000 : stoi(argv[2]));
    web.run(argv[1]);
  
   return 0;
}