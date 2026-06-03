#pragma once
#include <vector>
#include "IObserver.h"

class Subject {
private:
    std::vector<IObserver*> observers;
public:
    void addObserver(IObserver* observer) { observers.push_back(observer); }
    void notifyObservers(const std::string& eventName) {
        for (IObserver* obs : observers) { obs->onNotify(eventName); }
    }
    void clearObservers() { observers.clear(); }
};