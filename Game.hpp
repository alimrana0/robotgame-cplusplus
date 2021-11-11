#ifndef GAME_HPP
#define GAME_HPP



#include "Entity.hpp"
#include <vector>



// enum represeting the current game status
enum class GameStatus {
  playing,
  player_won,
  player_lost
};



// class holding and updateing game and world state
class Game {
 public:

  // reads the world description from a file.
  // world files describe the world as a grid of characters, with 'p' for the player, 'r' for a robot, 'x' for debris, and '.' for an empty space.
  // first prompts the user to input a world name.
  // the filename is "world/" + worldname + ".txt".
  // if there is an error opening the file, throws an exception.
  // if the world is not a rectangle, or is empty, throws an exception.
  // if there is an unrecognized character, throws an exception.
  // if there is not exactly one player in the world, throws an exception.
  void input_and_read_world_from_file(const EntityCounter & counter);

  // display the current world state.
  // the player is displayed as a 'p'.
  // robots are displayed as a 'r'.
  // debris are displayed as a 'x'.
  // empty cells are displayed as '.'.
  void display_world() const;

  // prompts the user for a direction to move the player in, and updates the world state.
  // reads an entire line of text; valid inputs are w/a/s/d/space for north/west/south/east/still.
  // throws an exception on an invalid input.
  // after updating the player and then the robots, checks for collisions (e.g., being in the same Cell).
  // if the player collided with any robot or debris, the player is removed.
  // if any number of robots or debris collided, all that is left is a single debris and the rest are removed (potentially by turning a robot into debris).
  // if the player has been removed, the player loses.
  // otherwise, if there are not robots left, the player wins.
  // otherwise, the player is still playing.
  GameStatus input_next_move_and_update();

 private:

  size_t m_worldRows; // number or rows in world
  size_t m_worldCols; // number or columns in world

  std::vector<Player> m_player; // a vector holding the player; should only be of size 0 or 1
  std::vector<RobotOrDebris> m_robotsAndDebris; // a vector holding robots and debris

};



#endif
