# A-Star-Maze-Path-Finder

This is an A* Search Algorithm Visualizer
![image](https://user-images.githubusercontent.com/69114450/147625367-84cf572f-f0bd-4dae-ae4d-7a71d7e29e18.png)

# Instructions On How To Use:

The A* Pathfinder works on a 50 X 50 grid with default start and destination nodes at (0,0) and (49,49) respectively.

1) To select a green start node, hover your mouse over a square node and hit the 'S' key.
2) To select a red destination node, hover your mouse over a square node and hit the 'D' key.
*Note that if you select the start and destination node to be the same node, the node will turn yellow.
3) To build walls (add obstacles) left click on a node (it will turn black).
4) To remove walls and obstacles, right click on a node (it will turn white);
5) To generate a maze, click the 'M' button. The Maze will be generated using a recursive division algorithm and will take a moment to complete.
6) To clear the board (everything except the start and end nodes), press the "esc" key.
7) To clear the board of everything except for the walls and the start and end nodes, click the "R" key.
8) To begin the A* Search algorithm, press "Enter". The program will begin searching for the shortest path between the start and destination nodes. As it searches, nodes that it visits will turn blue. At the end, if a path is found, the shortest path to the destination node will be highlighted in yellow.

*Note you may not generate another maze once you have already created one. If you would like to generate another maze after creating the first maze, you must first clear your board with "esc" and then press "M" to generate a new maze.
