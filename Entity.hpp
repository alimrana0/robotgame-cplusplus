#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Cell.hpp"
#include <cstdlib>
#include <functional>


// Direction for player movement
enum class Direction {
  north,
  south,
  east,
  west,
  none // stay still
};



// an EntityCounter is an object used to count how many
// entities are currently active. It should have increment called when
// an entity is constructed (to increment the count) and have decrement called when an
// entity is destructed (to decrement the count).
class EntityCounter {
public:
  EntityCounter(int * count): m_count(count) {}
  EntityCounter(const EntityCounter & other): m_count(other.m_count) {}

  void increment() { ++ (*m_count); }
  void decrement() { -- (*m_count); }

private:
  int * m_count;
};



// class for an entity that is the player
class Player {
 public:

  // construct a Player from parameters
  Player(const Cell & cell, const EntityCounter & counter);

  // copy construct a Player
  Player(const Player & other);

  // destruct a Player
  ~Player();

  // update the player's position based on the given direction.
  // if the player would move off the world, they stay still.
  void update(Direction input_direction, size_t worldRows, size_t worldCols);

  // get the location
  const Cell & get_cell() const;

 private:

  Cell m_cell;
  EntityCounter m_counter;

};



// class for en entity that is either a robot or debris
class RobotOrDebris {
 public:

  // construct a RobotOrDebris from parameters
  RobotOrDebris(const Cell & cell, bool isDebris, const EntityCounter & counter);

  // copy construct a RobotOrDebris
  RobotOrDebris(const RobotOrDebris & other);

  // destruct a RobotOrDebris
  ~RobotOrDebris();

  // update the location of this RobotOrDebris based on the player's location.
  // if debris, doesn't move.
  // if a robot, moves one cell (north, south, east, or west) toward the player (unless it is in the same place as the player, in which case it doesn't move).
  // if the robot is in the same row or column as the player, it moves toward the player in that row or column.
  // otherwise, the robot prefers to change row or change column based on its current location.
  // if the sum of its row and column is even, the robot prefers to change row.
  // if the sum of its row and column is odd, the robot prefers to change column.
  void update(const Player & player);

  // get the location
  const Cell & get_cell() const;

  // set this RobotOrDebris to be debris
  void make_debris();

  // get if this RobotOrDebris is debris
  bool is_debris() const;

 private:

  Cell m_cell;
  bool m_isDebris;
  EntityCounter m_counter;

};



#endif
