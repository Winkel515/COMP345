#include "LoggingObserver.h"

#include <fstream>
#include <iostream>

#include "CommandProcessing.h"
using std::cout;
using std::endl;
using std::ofstream;
using std::ostream;

A::A() { a = 0; }

void A::stringToLog() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "print to gamelog" << endl;
  output << this->a << endl;
  output << "In A string to log" << endl;
  output.close();
  cout << "In A string to log" << endl;
  
}

A::A(int a) { this->a = a; }

void A::callNotify() {
  Notify(this);
  cout << "this->a" << this->a << endl;
}

//Subject constructor
Subject::Subject() { _observers = new list<Observer*>; }

//Subject copy constructor
Subject::Subject(const Subject& s){ 
  list<Observer*>* obs(s._observers);
  _observers = obs; 
}

//Subject assignment operator
Subject& Subject::operator=(const Subject& s) {
  list<Observer*>* obs(s._observers);
  _observers = obs; 
  return *this;
}

//Subject output stream operator
ostream& operator<<(ostream& strm, Subject& s) {
  return strm << s << endl;
}

//Subject destructor
Subject::~Subject() { delete _observers; }

//subject attach method
void Subject::Attach(Observer* o) {
  _observers->push_back(o);
};

//subject detach method
void Subject::Detach(Observer* o) { _observers->remove(o); };

//subject notify method
void Subject::Notify(ILoggable* ILog) {
  list<Observer*>::iterator i = _observers->begin();
  for (; i != _observers->end(); ++i) (*i)->Update(ILog);
};

//observer constructor
Observer::Observer(){};

//Observer copy constructor
Observer::Observer(const Observer& o){};

//Observer destructor
Observer::~Observer(){};

//Observer assignment operator
Observer& Observer::operator=(const Observer& o) {
  return *this;
}

//Observer output stream operator
ostream& operator<<(ostream& strm, Observer& o) {
  return strm << o << endl;
}

//logobserver default constructor
LogObserver::LogObserver(){

}

LogObserver::LogObserver(A* s) {
  _subjectA = s;
  _subjectA->Attach(this);
}

//logobserver constructor for command view
LogObserver::LogObserver(Command* c) {
  _subjectCommand = c;
  _subjectCommand->Attach(this);
}

//logobserver destructor
LogObserver::~LogObserver() {
  _subjectCommand->Detach(this);
  _subjectCommandProcessor->Detach(this);
  _subjectGameEngine->Detach(this);
  _subjectOrder->Detach(this);
  _subjectOrdersList->Detach(this);
  _subjectCopy->Detach(this);
}

//logobserver constructor for command processor view
LogObserver::LogObserver(CommandProcessor* commandProcessor) {
  _subjectCommandProcessor = commandProcessor;
  _subjectCommandProcessor->Attach(this);
}

//logobserver constructor for GameEngine view
LogObserver::LogObserver(GameEngine* ge) {
  _subjectGameEngine = ge;
  _subjectGameEngine->Attach(this);
}

//logobserver constructor for order view
LogObserver::LogObserver(Order* o) {
  _subjectOrder = o;
  _subjectOrder->Attach(this);
}

//logobserver constructor for orderlist view
LogObserver::LogObserver(OrdersList* ol) {
  _subjectOrdersList = ol;
  _subjectOrdersList->Attach(this);
}

//logobserver copy constructor
LogObserver::LogObserver(const LogObserver& LogObs){
  _subjectCopy = new Subject(*const_cast<Subject*>(LogObs._subjectCopy));
  _subjectCopy->Attach(this);

}

//logobserver assignment operator
LogObserver& LogObserver::operator=(const LogObserver& LogObs) {
  _subjectCopy = new Subject(*const_cast<Subject*>(LogObs._subjectCopy));
  _subjectCopy->Attach(this);
  return *this;
}

//logobserver output stream operator
ostream& operator<<(ostream& strm, LogObserver& LogObs) {
  return strm << LogObs << endl;
}

//LogObserver update method
void LogObserver::Update(ILoggable* ILog) {
  ILog->stringToLog();
}

//ILoggable constructor
ILoggable::ILoggable(){

}

//ILoggable copy constructor
ILoggable::ILoggable(const ILoggable& ILog){

}

//ILoggable destuctor
ILoggable::~ILoggable(){

}

//ILoggable assignment operator
ILoggable& ILoggable::operator=(const ILoggable& ILog) {
  return *this;
}

//ILoggable output operator
ostream& operator<<(ostream& strm, ILoggable& ILog) {
  return strm << ILog << endl;
}


//LogObserver update method

/*
int main() {
  std::cout << "bla" << std::endl;
  A* a1 = new A(10);
  LogObserver* view = new LogObserver(a1);
  a1->callNotify();
  cout << a1->a << endl;

  return 0;
}*/