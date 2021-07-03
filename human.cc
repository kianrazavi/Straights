#include <memory>
#include "human.h"
#include "table.h"
//#include "view.h"
//#include "controller.h"
using namespace std;

// Constructor
Human::Human(int ID, shared_ptr<Table> t) 
: Player(ID, t)
{}

// Returns player type (in this case Human)
string Human::getType() {
return "Human";
}

string Human::moveLogic() {
return "";
}

void Human::compMove(string s)
{}
