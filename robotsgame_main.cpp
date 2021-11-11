#include "Entity.hpp"
#include "Game.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;



int main()
{
  int count = 0;
  EntityCounter counter(&count);

  try {
    Game game;
    
    game.input_and_read_world_from_file(counter);

    while (true) {
      game.display_world();
      cout << "Entities: " << count << endl;
      
      GameStatus gs = game.input_next_move_and_update();

      if (gs == GameStatus::player_won) {
	game.display_world();
	cout << "Entities: " << count << endl;
	cout << "Player won!" << endl;
	break;
      } else if (gs == GameStatus::player_lost) {
	game.display_world();
	cout << "Entities: " << count << endl;
	cout << "Player lost!" << endl;
	break;
      }
    }
  } catch (exception & e) {
    cout << "Exception: " << e.what() << endl;
  }

  cout << "Entities: " << count << endl;
}
