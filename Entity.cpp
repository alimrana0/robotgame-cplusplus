#include "Entity.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;



Player::Player(const Cell & cell, const EntityCounter & counter): // TODO
m_cell(cell),
m_counter(counter){
  // TODO
}

Player::Player(const Player & other): // TODO
m_cell(other.m_cell),
m_counter(other.m_counter)
{
}

Player::~Player()
{
  // TODO
}

void
Player::update(Direction input_direction, size_t worldRows, size_t worldCols)
{
  if(input_direction == Direction::east) {
    if(m_cell.col + 1 <= worldCols) {
      m_cell.col + 1;
    }
  }
  if(input_direction == Direction::west) {
    if(m_cell.col - 1 >= 0) {
      m_cell.col - 1;
    }
  }
  if(input_direction == Direction::north) {
    if(m_cell.row - 1 >= 0) {
      m_cell.row - 1;
    }
  }
  if(input_direction == Direction::south) {
    if(m_cell.row + 1 <= worldRows) {
      m_cell.row + 1;
    }
  }
}

const Cell &
Player::get_cell() const
{
  return m_cell;
}



RobotOrDebris::RobotOrDebris(const Cell & cell, bool isDebris, const EntityCounter & counter) // TODO
{
  // TODO
}

RobotOrDebris::RobotOrDebris(const RobotOrDebris & other) // TODO
{
  // TODO
}

RobotOrDebris::~RobotOrDebris()
{
  // TODO
}

void
RobotOrDebris::update(const Player & player)
{
  // TODO
}

const Cell &
RobotOrDebris::get_cell() const
{
  return m_cell;
}

void
RobotOrDebris::make_debris()
{
  m_isDebris = true;
}

bool
RobotOrDebris::is_debris() const
{
  return m_isDebris;
}
