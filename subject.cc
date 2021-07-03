#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm>
using namespace std;

// Add view
void Subject::attach(Observer *o) {
	observers.emplace_back(o);
}

// Detach view
void Subject::detach(Observer *o) {
	observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
}

// Update view
void Subject::notifyObservers() {
	for (auto ob : observers) ob->update();
}
