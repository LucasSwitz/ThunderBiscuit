#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <chrono>

class System
{
  public:
    std::string GetName() const
    {
        return _name;
    }
    
    std::string GetAfter() const
    {
        return _after;
    }

   virtual void Update(double seconds_since_last_update) = 0;

  protected:
    System(std::string name = "") : _name(name){};
    std::string _name = "";
    std::string _after = "";
};

#endif