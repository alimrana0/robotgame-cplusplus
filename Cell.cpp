#include "Cell.hpp"



bool operator==(const Cell & lhs, const Cell & rhs) {
  return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

bool operator!=(const Cell & lhs, const Cell & rhs) {
  return !(lhs == rhs);
}
