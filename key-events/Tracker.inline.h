#pragma once

#include <key-events/Tracker.h>

using namespace key::events;
using namespace std;

template <class T>
Tracker::Tracker() {

}

template <class T>
virtual Tracker::~Tracker() {

}

template <class T>
void key::events::Tracker::listenIn(std::shared_ptr<T> listener) {
	this->listeners.push_back(listener);
}