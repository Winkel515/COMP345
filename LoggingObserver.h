#pragma once

#include <list>
#include <string>
using std::list, std::string;
class CommandProcessor;
class GameEngine;
class Command;

class ILoggable {
 public:
  // ILoggable();
  //  ILoggable(const ILoggable& ILog);
  virtual string stringToLog() = 0;
};

class Observer {
 public:
  // Observer();
  //  Observer(const Observer& o);
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
  // Subject(const Subject& s);
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
  // LogObserver();
  //  LogObserver(const LogObserver& LogObserver);
  LogObserver(A* s);
  LogObserver(Command* c);
  LogObserver(CommandProcessor* cp);
  LogObserver(GameEngine* ge);
  ~LogObserver();
  void Update(ILoggable* ILog);

 private:
  A* _subjectA;
  Command* _subjectCommand;
  CommandProcessor* _subjectCommandProcessor;
  GameEngine* _subjectGameEngine;
};
