# Dominoes

A simple command line game of double six dominoes.
## Tech
C++.
## Run
### Option 1
- Run demo [here](https://www.onlinegdb.com/ikM0FmoZ4)
### Option 2
- Download [here](https://github.com/t-a-s-h/dominoes/archive/refs/heads/main.zip).
- Unzip folder.
- Navigate to unzipped folder in terminal.
- Run `make`.
- Run `./main` to start game.
## Current status
 #working #on_hold #needs_ui_improvements #needs_functional_improvements
## Notes
This game, in its current form, uses a command line interface and can be played with one terminal instance only.
## Future considerations
### Functional changes
0. ~~Fix non terminating loop on early exit error.~~ Done!
1. Incorporate machine learning to build meaningfully competent opponent(s).
	- Run the game with random plays (where more than one play could occur).
	- Repeat game play several times and store results.
	- Store minimal output as a tree.
	- Leaf nodes should include number of times the game was won with that particular set of moves.
2. Maybe implement ability to play against someone using a different device.
### UI / UX improvements
- Create some sort of UI as none currently exists for this game.
	- Will likely use TypeScript for frontend.
