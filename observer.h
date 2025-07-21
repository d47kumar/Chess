#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void notify() = 0;
    virtual void showMessage() = 0;
    virtual ~Observer() = default;
};

#endif
