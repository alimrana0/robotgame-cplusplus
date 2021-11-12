#include "Entity.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;



Player::Player(const Cell & cell, const EntityCounter & counter): // TODO
m_cell(cell),
m_counter(counter){
  m_counter.increment();
}

Player::Player(const Player & other): // TODO
m_cell(other.m_cell),
m_counter(other.m_counter)
{
  m_counter.increment();
}

Player::~Player()
{
  m_counter.decrement();
}

void
Player::update(Direction input_direction, size_t worldRows, size_t worldCols)
{
  if(input_direction == Direction::east) {
    if(m_cell.col + 1 <= worldCols) {
      m_cell.col = m_cell.col + 1;
    }
  }
  if(input_direction == Direction::west) {
    m_cell.col = m_cell.col - 1;
  }
  if(input_direction == Direction::north) {
    m_cell.row = m_cell.row - 1;
  }
  if(input_direction == Direction::south) {
    if(m_cell.row + 1 <= worldRows) {
      m_cell.row = m_cell.row + 1;
    }
  }
}

const Cell &
Player::get_cell() const
{
  return m_cell;
}



RobotOrDebris::RobotOrDebris(const Cell & cell, bool isDebris, const EntityCounter & counter):
m_cell(cell),
m_isDebris(isDebris),
m_counter(counter)
{
  m_counter.increment();
}

RobotOrDebris::RobotOrDebris(const RobotOrDebris & other):
m_cell(other.m_cell),
m_isDebris(other.m_isDebris), // TODO
m_counter(other.m_counter)
{
  m_counter.increment();
}

RobotOrDebris::~RobotOrDebris()
{
  m_counter.decrement();
}

void
RobotOrDebris::update(const Player & player)
{
  if(!m_isDebris) {
    if(!(m_cell.row == player.get_cell().row && m_cell.col == player.get_cell().col)) {
    if(m_cell.row == player.get_cell().row) {
      if(m_cell.col < player.get_cell().col)
      m_cell.col = m_cell.col + 1;
      else { m_cell.col = m_cell.col - 1;}
    }
    else if(m_cell.col == player.get_cell().col) {
      if(m_cell.row < player.get_cell().row)
      m_cell.row = m_cell.row + 1;
      else { m_cell.col = m_cell.row - 1;} 
    }
    else if(m_cell.row + m_cell.col % 2 != 0) {
        if(m_cell.row < player.get_cell().row)
      m_cell.row = m_cell.row + 1;
      else { m_cell.row = m_cell.row - 1;}
    }
    else {
       if(m_cell.col < player.get_cell().col)
      m_cell.col = m_cell.col + 1;
      else { m_cell.col = m_cell.col - 1;}
    }
    }
      
    }
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
