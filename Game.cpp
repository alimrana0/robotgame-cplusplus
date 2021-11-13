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
  getline(cin, fileName);
  ifstream infile("world/" + fileName + ".txt");

  if (!infile.good()) {
    throw invalid_argument(errmsg_world_file);
  }

  string line;
  size_t row = 0;
  size_t col = 0;
  size_t lineCounter = 0;
  size_t colCounter = 0;
  size_t oldLength = 0;
  unsigned int itterations = 0;
  
  while (getline(infile, line)) {
    ++lineCounter;
    for (char c : line) {
      // cout << c <<endl;
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
    if (itterations == 0) {
      oldLength = line.size();
      ++itterations;
    } else {
      if (oldLength != line.size()) {
        throw invalid_argument(errmsg_world_shape);
      }
      ++itterations;
    }
    // }
    // if (colCounter != col || col == 0) {
      
    // }
    colCounter = col;
    col = 0;
    ++row;
  }
  m_worldRows = row;
  m_worldCols = colCounter;
  if (line.size() == 0 && itterations == 0) {
      throw invalid_argument(errmsg_world_shape);
  }
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
        if (inRD) {
          break;
        }
      }
      for (Player p : m_player) {
        inP = inP || p.get_cell() == currentC;
      }
      if (inRD && isD) {
        world.append("x");
      } else if (inRD) {
        world.append("r");
      } else if (inP) {
        world.append("p");
      } else {
        world.append(".");
      }
    }
    if (row + 1 < m_worldRows) {
      world.append("\n");
    }
  }
  cout << world << endl;
}

GameStatus
Game::input_next_move_and_update()
{
  string direction;
  cout << msg_direction << endl;
  getline(cin, direction);

  if (direction == "w") {
    if(m_player.at(0).get_cell().row > 0) {
    m_player.at(0).update(Direction::north, m_worldRows, m_worldCols);
    }
  } else if (direction == "s") {
    if(m_player.at(0).get_cell().row < m_worldRows) {
    m_player.at(0).update(Direction::south, m_worldRows, m_worldCols);
    }
  } else if (direction == "d") {
    if(m_player.at(0).get_cell().col < m_worldCols) {
    m_player.at(0).update(Direction::east, m_worldRows, m_worldCols);
    }
  } else if (direction == "a") {
    if(m_player.at(0).get_cell().col > 0) {
    m_player.at(0).update(Direction::west, m_worldRows, m_worldCols);
    }
  } else if (direction == " ") {
    m_player.at(0).update(Direction::none, m_worldRows, m_worldCols);
  } else {
    throw invalid_argument(errmsg_direction);
  }
  // TODO: prompt user and input direction

  
  for (unsigned int i = 0; i < m_robotsAndDebris.size(); ++i) {
    if (!m_robotsAndDebris.at(i).is_debris()) {
      m_robotsAndDebris.at(i).update(m_player.at(0));
    }
  }
  // TODO: update player and robot locations

  for (size_t row = 0; row < m_worldRows; ++row) {
    for (size_t col = 0; col < m_worldCols; ++col) {
      vector<RobotOrDebris> needRemove; 
      Cell c{row, col};
      for (RobotOrDebris r: m_robotsAndDebris) {
        if (r.get_cell() == c) {
          needRemove.push_back(r);
        }
      }
      if (needRemove.size() > 1) {
        RobotOrDebris first = needRemove.at(0);
      }

    }
  }
  vector<RobotOrDebris> copyV = m_robotsAndDebris;
  size_t numRemoved = 0;
  size_t index = 0;
  for (RobotOrDebris r : copyV) {
    int similar = 0;
    size_t index2 = 0;
    for (RobotOrDebris r2: copyV) {
      if (r.get_cell() == r2.get_cell()) {
        ++similar;
      }
      if (similar > 1) {
        m_robotsAndDebris.erase(m_robotsAndDebris.begin() + index - numRemoved);
        ++numRemoved;
        m_robotsAndDebris.at(index2 - numRemoved).make_debris();
      }
      ++index2;
    }
    if (r.get_cell() == m_player.at(0).get_cell()) {
      m_player.erase(m_player.begin());
      return GameStatus::player_lost;
    }
    ++index;
  }
  // TODO: handle collisions

  bool allDebris = true;
  for (RobotOrDebris r : m_robotsAndDebris) {
    allDebris = allDebris && r.is_debris();
  }
  if (allDebris) {
    return GameStatus::player_won;
  }
  // TODO: determine game status

  return GameStatus::playing; // TODO: return game status
}
