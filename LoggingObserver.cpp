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
  output << this->a << endl;
  output << "In A string to log" << endl;
  output.close();
  cout << "In A string to log" << endl;
  return "string";
}

A::A(int a) { this->a = a; }

void A::callNotify() {
  Notify(this);
  cout << "this->a" << this->a << endl;
}

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

LogObserver::LogObserver(Command* c) {
  _subjectCommand = c;
  _subjectCommand->Attach(this);
  cout << "this " << this << endl;
  cout << "attached" << endl;
}

LogObserver::LogObserver(CommandProcessor* commandProcessor) {
  _subjectCommandProcessor = commandProcessor;
  _subjectCommandProcessor->Attach(this);
}

void Subject::Attach(Observer* o) {
  cout << "in attach" << endl;
  _observers->push_back(o);
  cout << "obs size in attach " << _observers->size() << endl;
};

void Subject::Detach(Observer* o) { _observers->remove(o); };

void Subject::Notify(ILoggable* ILog) {
  cout << "bla from notify " << ILog << endl;
  list<Observer*>::iterator i = _observers->begin();
  cout << "i" << (*i) << endl;
  cout << "observer size in notify " << _observers->size() << endl;

  for (; i != _observers->end(); ++i) (*i)->Update(ILog);
};

void LogObserver::Update(ILoggable* ILog) {
  ILog->stringToLog();
  cout << "bla from update" << endl;
}
/*
int main() {
  std::cout << "bla" << std::endl;
  A* a1 = new A(10);
  LogObserver* view = new LogObserver(a1);
  a1->callNotify();
  cout << a1->a << endl;

  return 0;
}*/