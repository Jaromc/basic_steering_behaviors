#pragma once

class Params
{
  private:
    static Params* instancePtr;

    Params() {}
   
  public:
    Params(const Params& obj) = delete; 
  
    static Params* getInstance()
    {
      if (instancePtr == nullptr) 
      {
        instancePtr = new Params(); 

        return instancePtr; 
      }
      else
      {
        return instancePtr;
      }
    }

    //TODO : Load from file
    float panicDistance = 50.0;
    float wanderRate = 0.2;
    float wanderDistance = 200;
    float wanderRadius = 100;
    int windowX = 800;
    int windowY = 600;
};