#include "subject.h"

Subject::~Subject() {} // Subject::~Subject

void Subject::attach(Observer* o) {
    observers.emplace_back(o);
} // Subject::attach


void Subject::detach(Observer* o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
} // Subject::detach

void Subject::notifyObservers() {
    for (auto& ob : observers) {
        ob->notify();      // HUMARA OBSERVOR ME UPDATE JAAYEGA YA NOTIFY
    }
} // Subject::notifyObservers
