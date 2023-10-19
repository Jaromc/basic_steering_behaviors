#include "Bot.h"
#include "Params.h"
#include <cstdlib>

namespace
{
   float randf(float max)
   {
      return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1) * max;
   }

   float randNom(float max)
   {
      return randf(max) - randf(max);
   }
}

void Bot::flee(const Vector2f& enemyPosition)
{
   Vector2f direction = _position - enemyPosition;
   float distance = direction.length();

   if (distance > Params::getInstance()->panicDistance)
   {
      //not enough distance to start panicking 
      return;
   }

   _force += direction.getNormalise() * _maxSpeed;
}

void Bot::seek(const Vector2f& targetPosition)
{
   Vector2f direction = targetPosition - _position;
   float distance = direction.length();

   if (distance <= 0.5f)
   {
      //arrived at target
      return;
   }

   _force += direction.getNormalise() * _maxSpeed;
}

void Bot::wander()
{
   //create an initial wander target
   Vector2f target = _velocity.getNormalise() * Params::getInstance()->wanderDistance;
   target += _position;

   //create a wander circle that will be attached to the end of the target.
   //This gives the bot a gradual wander.

   //rotate by a small amount
   _wander_angle += randNom(0.1f) * Params::getInstance()->wanderRate;

   //create a random target within a wander circle in local space
   Vector2f offset;
   offset.x = Params::getInstance()->wanderRadius * cos(_wander_angle);
   offset.y = Params::getInstance()->wanderRadius * sin(_wander_angle);

   //final target
   target += offset;

   seek(target);
}

void Bot::update(double dt)
{
   _velocity = _force * dt;
   if (_velocity.lengthSq() > 0.0)
   {
      _facing = _velocity.getNormalise();
   }
   
   _position += _velocity;
   
   //wrap around window limits
   if (_position.x > Params::getInstance()->windowX)
      _position.x = 0;
   if (_position.x < 0)
      _position.x = Params::getInstance()->windowX;
   if (_position.y > Params::getInstance()->windowY)
      _position.y = 0;
   if (_position.y < 0)
      _position.y = Params::getInstance()->windowY;

   _force.x = 0;
   _force.y = 0;
}