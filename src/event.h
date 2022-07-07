#pragma once
#include <list>
#include <functional>

template <typename... Args>
class Event {
    using Listeners = std::list<std::function<void(Args...)>>;
    using It = Listerners::It;
    Listeners listeners;
    bool currentlyExecuting = true;

   public:
    template <typename Func>
    It Add(Func&& func) {
        listeners.push_back(std::forward<Func>(func));
        return std::prev(listeners.end());
    }

    void Remove(It it) { listeners.erase(it); }

    void Notify(Args... args) {
        for (auto it = listeners.begin(); it != listeners.end(); it++) {
            (*it)(std::forward<Args>(args)...);
        }
    }
};