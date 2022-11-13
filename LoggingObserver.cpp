#include "LoggingObserver.h"

#include <fstream>
#include <iostream>

#include "CommandProcessing.h"
using std::cout;
using std::endl;
using std::ofstream;
using std::ostream;

// Subject constructor
Subject::Subject() { _observers = new list<Observer*>; }

// Subject copy constructor
Subject::Subject(const Subject& s) {
  list<Observer*>* obs(s._observers);
  _observers = obs;
}

// Subject assignment operator
Subject& Subject::operator=(const Subject& s) {
  list<Observer*>* obs(s._observers);
  _observers = obs;
  return *this;
}

// Subject output stream operator
ostream& operator<<(ostream& strm, Subject& s) { return strm << s << endl; }

// Subject destructor
Subject::~Subject() { delete _observers; }

// subject attach method
void Subject::Attach(Observer* o) { _observers->push_back(o); };

// subject detach method
void Subject::Detach(Observer* o) { _observers->remove(o); };

// subject notify method
void Subject::Notify(ILoggable* ILog) {
  list<Observer*>::iterator i = _observers->begin();
  for (; i != _observers->end(); ++i) (*i)->Update(ILog);
};

// observer constructor
Observer::Observer(){};

// Observer copy constructor
Observer::Observer(const Observer& o){};

// Observer destructor
Observer::~Observer(){};

// Observer assignment operator
Observer& Observer::operator=(const Observer& o) { return *this; }

// Observer output stream operator
ostream& operator<<(ostream& strm, Observer& o) { return strm << o << endl; }

// logobserver default constructor
LogObserver::LogObserver() {}

// logobserver destructor
LogObserver::~LogObserver() {}

// logobserver copy constructor
LogObserver::LogObserver(const LogObserver& LogObs) {}

// logobserver assignment operator
LogObserver& LogObserver::operator=(const LogObserver& LogObs) { return *this; }

// logobserver output stream operator
ostream& operator<<(ostream& strm, LogObserver& LogObs) {
  return strm << LogObs << endl;
}

// LogObserver update method
void LogObserver::Update(ILoggable* ILog) {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << endl << ILog->stringToLog() << endl;
  output.close();
}

// ILoggable constructor
ILoggable::ILoggable() {}

// ILoggable copy constructor
ILoggable::ILoggable(const ILoggable& ILog) {}

// ILoggable destuctor
ILoggable::~ILoggable() {}

// ILoggable assignment operator
ILoggable& ILoggable::operator=(const ILoggable& ILog) { return *this; }

// ILoggable output stream operator
ostream& operator<<(ostream& strm, ILoggable& ILog) {
  return strm << ILog << endl;
}