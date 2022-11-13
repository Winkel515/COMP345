#pragma once

#include <list>
#include <string>
using std::list;
using std::ostream;
using std::string;
class CommandProcessor;
class GameEngine;
class Command;
class Order;
class OrdersList;

class ILoggable {
 public:
  ILoggable();
  ILoggable(const ILoggable& ILog);
  ~ILoggable();
  virtual string stringToLog() = 0;
  ILoggable& operator=(const ILoggable& ILog);
  friend ostream& operator<<(ostream& strm, const ILoggable& ILog);
};

class Observer {
 public:
  Observer(const Observer& o);
  ~Observer();
  virtual void Update(ILoggable* ILog) = 0;
  Observer& operator=(const Observer& o);
  friend ostream& operator<<(ostream& strm, const Observer& o);

 protected:
  Observer();
};

class Subject {
 public:
  virtual void Attach(Observer* o);
  virtual void Detach(Observer* o);
  virtual void Notify(ILoggable* ILog);
  Subject();
  Subject(const Subject& s);
  ~Subject();
  Subject& operator=(const Subject& s);
  friend ostream& operator<<(ostream& strm, const Subject& s);

 private:
  list<Observer*>* _observers;
};

class LogObserver : public Observer {
 public:
  LogObserver();
  LogObserver(const LogObserver& LogObs);
  ~LogObserver();
  void Update(ILoggable* ILog);
  LogObserver& operator=(const LogObserver& LogObs);
  friend ostream& operator<<(ostream& strm, const LogObserver& LogObs);
};
