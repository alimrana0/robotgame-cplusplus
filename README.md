# Assignment: Robots Game



## Overview

In this assignment you will implement a simplified text version of the game
[Robots](https://en.wikipedia.org/wiki/Robots_(1984_video_game)).

Starting from the provided repository, which includes starter code,
reference implementations, and test cases, fill in the function
implementations to complete the Robots game in C++.

Implementation notes:
* All the user input is line-based. Use the non-member getline to read the user's input, don't use operator >>.
* The first line entered is the name of the world file to use.
* The implementations of copy constructors should copy all the fields from the other object.
* In a turn, first the player moves, then the robots move, then any collisions are handled.

Requirements:
* **Error conditions must be handled by throwing exceptions, to be caught in main.**
* **You must not change the entity count (e.g. call `EntityCounter::increment` or `EntityCounter::decrement`) outside Entity.cpp.**
* **Modifiable files:** You can edit `Entity.cpp` and `Game.cpp`.



## Grading

* 5: meta.txt filled out.
* 5: Code is written and follows instructions.
* 10: Code written compiles with Makefile.
* 20/16/8/4: all/most/some/any test cases pass for reporting errors reading world.
* 20/16/8/4: all/most/some/any test cases pass for displaying world.
* 20/16/8/4: all/most/some/any test cases pass for making moves.
* 10/8/4/2: all/most/some/any test cases pass for detecting lose.
* 10/8/4/2: all/most/some/any test cases pass for detecting win.
* -X: *code does not follow assignment requirements or guidelines*
