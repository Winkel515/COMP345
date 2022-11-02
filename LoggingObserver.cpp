//#include "LoggingObserver.h"

#include <fstream>
#include <iostream>

#include "CommandProcessing.h"
using std::cout;
using std::endl;
using std::ofstream;

A::A() { a = 0; }

string A::stringToLog() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "print to gamelog" << endl;
  output << "In A string to log" << endl;
  output.close();
  cout << "In A string to log" << endl;
  return "string";
}

A::A(int a) { a = 1; }

void A::callNotify() { Notify(this); }

B::B() { b = 0; }

B::B(int b) { b = 2; }

Subject::Subject() { _observers = new list<Observer*>; }

Subject::~Subject() { delete _observers; }

Observer::Observer(){};

Observer::~Observer(){};

LogObserver::LogObserver(A* s) {
  _subjectA = s;
  _subjectA->Attach(this);
}

LogObserver::LogObserver(CommandProcessor* commandProcessor) {
  _subjectCommandProcessor = commandProcessor;
  _subjectCommandProcessor->Attach(this);
}

void Subject::Attach(Observer* o) { _observers->push_back(o); };

void Subject::Detach(Observer* o) { _observers->remove(o); };

void Subject::Notify(ILoggable* ILog) {
  list<Observer*>::iterator i = _observers->begin();
  for (; i != _observers->end(); ++i) (*i)->Update(ILog);
};

void LogObserver::Update(ILoggable* ILog) { ILog->stringToLog(); }
/*
int main() {
  std::cout << "bla" << std::endl;
  A* a1 = new A(1);
  LogObserver* view = new LogObserver(a1);
  a1->callNotify();

  return 0;
}*/