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
  cout << msg_filename << endl;
  string fileName;
  cin >> fileName;
  ifstream infile(fileName + ".txt");

  if (!infile) {
    throw invalid_argument(errmsg_world_file);
  }

  string line;
  size_t row = 0;
  size_t col = 0;
  size_t lineCounter = 0;
  size_t colCounter = 0;
  while (getline(infile, line)) {
    ++lineCounter;
    for (char c : line) {
      if (c == 'x') {
        const Cell c{row, col};
        RobotOrDebris tempX(c, true, counter);
        m_robotsAndDebris.push_back(tempX);
      } else if (c == 'r') {
        const Cell c{row, col};
        RobotOrDebris tempR(c, false, counter);
        m_robotsAndDebris.push_back(tempR);
      } else if (c == 'p') {
        const Cell c{row, col};
        Player tempP(c, counter);
        m_player.push_back(tempP);
      } else if (c != '.') {
        throw invalid_argument(errmsg_world_char);
      }
      ++col;
    }
    if (colCounter != col || col == 0) {
      throw invalid_argument(errmsg_world_shape);
    }
    colCounter = col;
    col = 0;
    ++row;
  }
  m_worldRows = row - 1;
  m_worldCols = col - 1;

  if (m_player.size() == 0) {
    throw invalid_argument(errmsg_world_player_missing);
  }
  if (m_player.size() > 1) {
    throw invalid_argument(errmsg_world_player_multiple);
  }
  // TODO: prompt user for filename
  
  // TOOD: read and validate world from file
}

void
Game::display_world() const
{
  string world = "";
  for (size_t row = 0; row < m_worldRows; ++row) {
    for (size_t col = 0; col < m_worldCols; ++col) {
      Cell currentC{row, col};
      bool inRD = false;
      bool isD = false;
      bool inP = false;
      for (RobotOrDebris rd : m_robotsAndDebris) {
        inRD = inRD || rd.get_cell() == currentC;
        if (inRD) {
          isD = rd.is_debris();
        }
      }
      for (Player p : m_player) {
        inP = inP || p.get_cell() == currentC;
      }
      if (inRD && isD) {
        world = world + "x";
      } else if (inRD) {
        world = world + "r";
      } else if (inP) {
        world = world + "p";
      } else {
        world = world + ".";
      }
    }
    if (row + 1 < m_worldRows) {
      world = world + "\n";
    }
  }
  cout << world << endl;
}

GameStatus
Game::input_next_move_and_update()
{
  string direction;
  cout << msg_direction << endl;
  cin >> direction;
  // TODO: prompt user and input direction

  // TODO: update player and robot locations

  // TODO: handle collisions

  // TODO: determine game status

  return GameStatus::player_lost; // TODO: return game status
}
