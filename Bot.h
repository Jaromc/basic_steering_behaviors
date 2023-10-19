#pragma once

#include "Vector2.h"

class Bot
{
   public:
      Bot(){}
      Bot(const Vector2f& pos, float maxSpeed): _position(pos), _maxSpeed(maxSpeed){}

      void flee(const Vector2f& enemyPosition);
      void seek(const Vector2f& targetPosition);
      void wander();

      void update(double dt);

      const Vector2f& getPosition()const {return _position;}
      const Vector2f& getVelocity()const {return _velocity;}
      const Vector2f& getFacing()const {return _facing;}
   private:
      Vector2f _facing = Vector2f();
      Vector2f _position = Vector2f();
      Vector2f _force = Vector2f();
      Vector2f _velocity = Vector2f();
      float _maxSpeed = 0.0f;
      float _wander_angle = 0.0f;
};