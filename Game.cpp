#include "Game.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <set>
#include <map>
using namespace std;



const char * msg_filename = "Please enter a world file:";
const char * msg_direction = "Please enter a direction to move (wasd or space):";

const char * errmsg_world_file = "Error reading world file.";
const char * errmsg_world_shape = "Invalid world shape.";
const char * errmsg_world_char = "Invalid world character.";
const char * errmsg_world_player_missing = "World missing player.";
const char * errmsg_world_player_multiple = "World has multiple players.";

const char * errmsg_direction = "Invalid direction input.";



void
Game::input_and_read_world_from_file(const EntityCounter & counter)
{
  // TODO: prompt user for filename
  
  // TOOD: read and validate world from file
}

void
Game::display_world() const
{
  // TODO: display world
}

GameStatus
Game::input_next_move_and_update()
{
  // TODO: prompt user and input direction

  // TODO: update player and robot locations

  // TODO: handle collisions

  // TODO: determine game status

  return GameStatus::player_lost; // TODO: return game status
}
