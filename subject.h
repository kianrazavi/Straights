#include "observer.h"
#include <vector>
using namespace std;

#ifndef SUBJECT_H
#define SUBJECT_H

class Subject {

// View(s)
vector<Observer*> observers;

public:

// Constructor
Subject();

// Attach view
void attach(Observer *o);

// Detach view
void detach(Observer *o);

// Notify view of any changes
void notifyObservers();

};

#endif
