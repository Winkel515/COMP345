#pragma once

#include <list>
#include <string>
using std::list;
using std::string;
class CommandProcessor;

class ILoggable {
 public:
  virtual string stringToLog() = 0;
};

class Observer {
 public:
  ~Observer();
  virtual void Update(ILoggable* ILog) = 0;

 protected:
  Observer();
};

class Subject {
 public:
  virtual void Attach(Observer* o);
  virtual void Detach(Observer* o);
  virtual void Notify(ILoggable* ILog);
  Subject();
  ~Subject();

 private:
  list<Observer*>* _observers;
};

class A : public Subject, public ILoggable {
 public:
  ~A();
  A();
  int a;
  A(int a);
  string stringToLog();
  void callNotify();
};

class B {
 public:
  ~B();
  B();
  int b;
  B(int b);
};

class LogObserver : public Observer {
 public:
  LogObserver();
  LogObserver(A* s);
  LogObserver(CommandProcessor* commandProcessor);
  ~LogObserver();
  void Update(ILoggable* ILog);

 private:
  A* _subjectA;
  CommandProcessor* _subjectCommandProcessor;
};
