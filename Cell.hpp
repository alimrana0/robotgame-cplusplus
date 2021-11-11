#ifndef CELL_HPP
#define CELL_HPP



#include <cstddef>



// struct representing a grid cell
struct Cell {
  size_t row;
  size_t col;
};

// operators for comparing cells
bool operator==(const Cell & lhs, const Cell & rhs);
bool operator!=(const Cell & lhs, const Cell & rhs);



#endif
