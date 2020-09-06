#include <iostream>
#include <stdio.h>     
#include <stdlib.h>    
#include <algorithm>
#include <string.h> 
#include <stack>
#include <vector>
#include <limits.h>
#include <set>
#include <SFML/Graphics.hpp>
#include "Grid.cpp"
#define ROW 50
#define COLUMN 50
#define HORIZONTAL 0
#define VERTICAL 1
#define S 1
#define E 2
using namespace std;

//old command line to compile g++ MazePathFindermain.cpp -o main.exe
//to compile sfml on cmd - g++ MazePathFindermain.cpp -lsfml-graphics -lsfml-window -lsfml-system
//to execute: a.exe


typedef pair<int,int> Pair;
typedef pair<int, pair<int, int>> pPair; 

int grid [ROW][COLUMN];
//2d array to show state of each cell:
// 0 = blocked, 1= unvisited and unblocked, 2 = visited in the closed list, 3 = visited in the open list, 9 = node on the final path
int state [ROW][COLUMN];
sf::RenderWindow window(sf::VideoMode(1500, 1500), "SFML works!");

  Grid g;

//struct to store info about each node (cell)
struct node{
    int parent_i, parent_j;
    int f, g, h;
};

//function to initialize the grid and state of the grid:
void refreshGrid(int grid[][COLUMN], int state [][COLUMN]){
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j<COLUMN; j++){            
            grid[i][j] = 1;
     
            state[i][j] = 1;
          
        }
    }
    
}

//helper function to help check the validity of travelling to a node
bool isValid(int row, int column){
     return (row >= 0) && (row < ROW) && 
           (column >= 0) && (column < COLUMN); 
}

//helper function to check whether node is blocked
bool isUnBlocked(int grid[][COLUMN], int row, int column) 
{ 
    // Returns true if the cell is not blocked else false 
    if (grid[row][column] == 1) {
        return (true); 
    }
    else{
        return (false); 
    }
}

// helper function to check if destination has been reached or not 
bool isDestination(int row, int column, Pair dest) 
{ 
    if (row == dest.first && column == dest.second){
        return (true); 
    }
    else{
        return (false);
    } 
} 


//helper function to calculate heuristic of a node
int heuristic(int r, int c, Pair destination){
    int h = max(abs(destination.first - r), abs(destination.second - c));

    return h;
}


//helper function to trace path from the source to the destination
//returns the path as a vector of pairs
vector<Pair> getPath(node nodeDetails[][COLUMN], Pair dest){
    printf ("\nThe Path is "); 
    int row = dest.first; 
    int col = dest.second; 

    stack<Pair> path;

    while (!(nodeDetails[row][col].parent_i == row 
             && nodeDetails[row][col].parent_j == col )) 
    { 
        path.push (make_pair (row, col));
        int temp_row = nodeDetails[row][col].parent_i; 
        int temp_col = nodeDetails[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    }
    path.push(make_pair (row, col));
    vector<Pair> finalPath;
    while(!path.empty()){
        Pair p = path.top();
        path.pop();
        
        finalPath.push_back(p);
        printf("-> (%d,%d) ",p.first,p.second); 
    }
    return finalPath;
}


//A* path finder

vector<Pair> aStar(sf::Event event,int grid[][COLUMN], Pair src, Pair des){

    //create vector of pairs for my path
vector<Pair> path;
    //check if source node is out of the range
    if(isValid(src.first, src.second) == false){
        printf("source out of range\n");
        return path;
    }
    //checks if destination node is out of range

    if(isValid(des.first, des.second) == false){
        printf("destination out of range\n");
        return path;
    }

    //check if source or destination is obtructed (blocked off)

    if(isUnBlocked(grid, src.first, src.second) == false || isUnBlocked(grid, des.first, des.second) == false){
          printf ("Source or the destination is blocked\n"); 
        return path; 
    }

    //checks is destination and source cell are the same
    if(isDestination(src.first, src.second, des) == true){
        printf("destination reached\n");
        return path;
    }

    //create a list of visited nodes, initialize it to false (2d array)
    bool cList [ROW][COLUMN];
    memset(cList, false, sizeof(cList));
    //2d array of structure to hold the detail of nodes
    node nodeDetails [ROW] [COLUMN];

    int i,j;
    for(i=0; i < ROW; i++){
        for(j=0; j<COLUMN; j++){
            nodeDetails[i][j].f = INT_MAX;
            nodeDetails[i][j].g = INT_MAX;
            nodeDetails[i][j].h = INT_MAX;
            nodeDetails[i][j].parent_i = -1;
            nodeDetails[i][j].parent_j = -1;
        }
    }

    //initialize starting node
    i = src.first;
    j = src.second;
    nodeDetails[i][j].f = 0;
    nodeDetails[i][j].g = 0;
    nodeDetails[i][j].h = 0;
    nodeDetails[i][j].parent_i = i;
    nodeDetails[i][j].parent_j = j;
//create set of ppairs to <f, <i,j>> openlist of pair of pairs
set<pPair> oList;

//push starting node to this set and set f=0
oList.insert(make_pair (0, make_pair (i, j))); 


//initially, boolean value is false as destination is not reached
bool arrived = false;




while(!arrived && !oList.empty()){
     if (event.type == sf::Event::MouseButtonPressed){
           
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                //tries to ignore the mouse if it is pressed during execution of the search algorithm (to avoid crashing the program)
                printf("mouse pressed!");
            }
        }
 
    //get the first node from openlist
    pPair p = *oList.begin();

    //pop the first node from open list
    oList.erase(oList.begin());

    //add this node to the closed list
    i = p.second.first;
    j = p.second.second;

    cList[i][j] = true;
    state[i][j] = 2;
    

    //////** Investigating all 8 neighbours
int fNew, gNew, hNew;

//** 1) NORTHERN NEIGHBOUR **
if(isValid(i-1,j)==true){
    //if current node is destination

    if(isDestination(i-1, j, des) == true){
        //set parent of destination node
        nodeDetails[i-1][j].parent_i = i;
        nodeDetails[i-1][j].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
        break;

    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i-1, j, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i-1][j].f == INT_MAX  || nodeDetails[i-1][j].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i-1,j)));
            state[i-1][j] = 3;

            //update node details
            nodeDetails[i-1][j].f = fNew;
            nodeDetails[i-1][j].g = gNew;
            nodeDetails[i-1][j].h = hNew;
            nodeDetails[i-1][j].parent_i= i;
            nodeDetails[i-1][j].parent_j = j;
         }

    }

    

}


//** 2) SOUTHERN NEIGHBOUR **
if(isValid(i+1,j)==true){
    //if current node is destination

    if(arrived == false && isDestination(i+1, j, des) == true){
        //set parent of destination node
        nodeDetails[i+1][j].parent_i = i;
        nodeDetails[i+1][j].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
        break;    


    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i+1][j] == false && isUnBlocked(grid, i+1, j) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i+1, j, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i+1][j].f == INT_MAX  || nodeDetails[i+1][j].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i+1,j)));
            state[i+1][j] = 3;

            //update node details
            nodeDetails[i+1][j].f = fNew;
            nodeDetails[i+1][j].g = gNew;
            nodeDetails[i+1][j].h = hNew;
            nodeDetails[i+1][j].parent_i= i;
            nodeDetails[i+1][j].parent_j = j;
         }

    }

    

}

//** 3) EASTERN NEIGHBOUR **
if(isValid(i,j+1)==true){
    //if current node is destination

    if(arrived == false && isDestination(i, j+1, des) == true){
        //set parent of destination node
        nodeDetails[i][j+1].parent_i = i;
        nodeDetails[i][j+1].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
          break;  

    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i][j+1] == false && isUnBlocked(grid, i, j+1) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i, j+1, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i][j+1].f == INT_MAX  || nodeDetails[i][j+1].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i,j+1)));
            state[i][j+1] = 3;

            //update node details
            nodeDetails[i][j+1].f = fNew;
            nodeDetails[i][j+1].g = gNew;
            nodeDetails[i][j+1].h = hNew;
            nodeDetails[i][j+1].parent_i= i;
            nodeDetails[i][j+1].parent_j = j;
         }

    }

    

}


//** 4) WESTERN NEIGHBOUR **
if(isValid(i,j-1)==true){
    //if current node is destination

    if(arrived == false && isDestination(i, j-1, des) == true){
        //set parent of destination node
        nodeDetails[i][j-1].parent_i = i;
        nodeDetails[i][j-1].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
          break;  

    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i, j-1, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i][j-1].f == INT_MAX  || nodeDetails[i][j-1].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i,j-1)));
            state[i][j-1] = 3;

            //update node details
            nodeDetails[i][j-1].f = fNew;
            nodeDetails[i][j-1].g = gNew;
            nodeDetails[i][j-1].h = hNew;
            nodeDetails[i][j-1].parent_i= i;
            nodeDetails[i][j-1].parent_j = j;
         }

    }

    

}

//** 5) NORTH-EASTERN NEIGHBOUR **
if(isValid(i-1,j+1)==true){
    //if current node is destination

    if(arrived == false && isDestination(i-1, j+1, des) == true){
        //set parent of destination node
        nodeDetails[i-1][j+1].parent_i = i;
        nodeDetails[i-1][j+1].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
          break;  

    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i-1][j+1] == false && isUnBlocked(grid, i-1, j+1) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i-1, j+1, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i-1][j+1].f == INT_MAX  || nodeDetails[i-1][j+1].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i-1,j+1)));
            state[i-1][j+1] = 3;

            //update node details
            nodeDetails[i-1][j+1].f = fNew;
            nodeDetails[i-1][j+1].g = gNew;
            nodeDetails[i-1][j+1].h = hNew;
            nodeDetails[i-1][j+1].parent_i= i;
            nodeDetails[i-1][j+1].parent_j = j;
         }

    }

    

}

//** 6) NORTH-WESTERN NEIGHBOUR **
if(isValid(i-1,j-1)==true){
    //if current node is destination

    if(arrived == false && isDestination(i-1, j-1, des) == true){
        //set parent of destination node
        nodeDetails[i-1][j-1].parent_i = i;
        nodeDetails[i-1][j-1].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
          break;  

    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i-1][j-1] == false && isUnBlocked(grid, i-1, j-1) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i-1, j-1, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i-1][j-1].f == INT_MAX  || nodeDetails[i-1][j-1].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i-1,j-1)));
            state[i-1][j-1]=3;

            //update node details
            nodeDetails[i-1][j-1].f = fNew;
            nodeDetails[i-1][j-1].g = gNew;
            nodeDetails[i-1][j-1].h = hNew;
            nodeDetails[i-1][j-1].parent_i= i;
            nodeDetails[i-1][j-1].parent_j = j;
         }

    }

    

}


//** 7) SOUTH-EASTERN NEIGHBOUR **
if(isValid(i+1,j+1)==true){
    //if current node is destination

    if(arrived == false && isDestination(i+1, j+1, des) == true){
        //set parent of destination node
        nodeDetails[i+1][j+1].parent_i = i;
        nodeDetails[i+1][j+1].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
          break;  

    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i+1][j+1] == false && isUnBlocked(grid, i+1, j+1) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i+1, j+1, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i+1][j+1].f == INT_MAX  || nodeDetails[i+1][j+1].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i+1,j+1)));
            state[i+1][j+1] = 3;

            //update node details
            nodeDetails[i+1][j+1].f = fNew;
            nodeDetails[i+1][j+1].g = gNew;
            nodeDetails[i+1][j+1].h = hNew;
            nodeDetails[i+1][j+1].parent_i= i;
            nodeDetails[i+1][j+1].parent_j = j;
         }

    }

    

}

//** 8) SOUTH-WESTERN NEIGHBOUR **
if(isValid(i+1,j-1)==true){
    //if current node is destination

    if(arrived == false && isDestination(i+1, j-1, des) == true){
        //set parent of destination node
        nodeDetails[i+1][j-1].parent_i = i;
        nodeDetails[i+1][j-1].parent_j = j;   
        printf("found destination\n");
        path = getPath(nodeDetails, des);
        arrived = true;
          break;  

    }

    //if the node is blocked or already visited, ignore it 
    else if(cList[i+1][j-1] == false && isUnBlocked(grid, i+1, j-1) == true){
        gNew = nodeDetails[i][j].g +1;
        hNew = heuristic(i+1, j-1, des);
        fNew = hNew + gNew;
        // If node not on the open list, add it the open list.set current node to parent. Record the 
                // f, g, and h costs of this node 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
        if(nodeDetails[i+1][j-1].f == INT_MAX  || nodeDetails[i+1][j-1].f > fNew){
            oList.insert(make_pair(fNew, make_pair(i+1,j-1)));
            state[i+1][j-1] = 3;

            //update node details
            nodeDetails[i+1][j-1].f = fNew;
            nodeDetails[i+1][j-1].g = gNew;
            nodeDetails[i+1][j-1].h = hNew;
            nodeDetails[i+1][j-1].parent_i= i;
            nodeDetails[i+1][j-1].parent_j = j;
         }

    }

    

}

//draw grid after each iteration
//Pair src, Pair des
g.drawGrid(window, state, src, des);
window.display();
    
}//end of while loop



if(arrived == true){
    int len = path.size();
    for(int i = 0; i < len; i++){
        if (event.type == sf::Event::MouseButtonPressed){
           
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                printf("mouse pressed!");
            }
        }
        int x = path.at(i).first;
        int y = path.at(i).second;
        state[x][y] = 9;
        g.drawGrid(window, state, src, des);
        window.display();
         
    }
    
    return path;
}
else{
    printf("destination not found\n");
    return path;
}
  

    
}// end of A star function


//Maze Generating functions

//chooses wall orientation based on height and width (helper function for the recursive division algorithm)
int chooseOrientation(int width, int height){
    if(width < height){
        return HORIZONTAL;
    }
    else if (width > height){
        return VERTICAL;
    }
    else{
        return rand() % 2 + 1;
    }
}
//recursive division algorithm
void mazeGenerator(sf::RenderWindow& window, Pair src, Pair des, int grid [][COLUMN], int state [][COLUMN], int mx, int my, int w, int h, int orientation ){
   
    if(w < 3 || h <3){
        return;
    }
    bool horizontal = orientation == HORIZONTAL;
    int wx = mx + (horizontal ? 0 : rand()% (w-2));
    int wy = my + (horizontal ? rand()% (h-2) : 0);
     int px = wx + (horizontal ? rand()%w : 0);
     int py = wy + (horizontal ? 0:rand()%h );

    int dx = horizontal ? 1 : 0;
    int dy = horizontal ? 0 : 1;
     int length = horizontal ? w : h;
     
    int dir = horizontal ? S : E;
     for(int i = 0; i < length; i++) {
        if(wx != px || wy != py) {
           grid[wx][wy] |= dir;
          state[wx][wy] |= dir;
          
           g.drawGrid(window, state, src, des);
           window.display();
            
        
        }
        
        
        wx += dx;
        wy += dy;
    }
    int nx = mx;
    int ny = my;
    int nw = horizontal ? w : wx - mx +1;
    int nh = horizontal ? wy-my+1 : h;
    mazeGenerator(window, src, des, grid, state, nx, ny, nw, nh, chooseOrientation(w,h));

    nx = horizontal ? mx : wx+1;
    ny = horizontal ? wy+1 : my;
    nw = horizontal ? w : mx + w - wx-1;
    nh = horizontal ? my + h - wy - 1 : h;
    mazeGenerator(window, src, des, grid, state, nx, ny, nw, nh, chooseOrientation(w,h));

}


int main(){

    
    Pair src = std::make_pair(0,0);
    Pair dest = std::make_pair(49,49);
    refreshGrid(grid, state);

    //boolean to prevent the program from executing the A star search again right after it just finished it
     bool isDone = false;
    
    bool isDoneMazeBuilding = false;

    sf::Event event;
    while (window.isOpen())
    {
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        Pair newSrc = g.getSrc(window, event, src);
       Pair newDest = g.getDest(window, event, dest);
        src = newSrc;
        dest = newDest;
        g.drawGrid(window, state, src, dest);
        
        g.makeBlocks(event, state, grid);
       
       
       
        if(event.type == sf::Event::KeyReleased){
          
            if (event.key.code == sf::Keyboard::Return)
                {
                 
                    if(isDone == false){
                        
                        printf("Calling A star");
                        vector<Pair> myPath = aStar(event,grid, src, dest);
                        printf("%d\n",myPath.size()-1);  
                        isDone = true;
                      
                        
                          
                    }
                 
                               
                }
            if(event.key.code == sf::Keyboard::R){
                  for(int i = 0; i < ROW; i++){
                        for(int j = 0; j<COLUMN; j++){
                            if (state[i][j] == 2 || state[i][j] == 3 || state[i][j] == 9){
                                state[i][j] = 1;
                            }
                        }
                    }  
                    isDone = false;
                   
            }
            if(event.key.code == sf::Keyboard::M){
                if(isDoneMazeBuilding == false){
                    mazeGenerator(window, src, dest, grid, state, 0, 0, ROW, COLUMN, chooseOrientation(ROW,COLUMN));
                    for(int i = 0; i < ROW; i++){
                        for(int j = 0; j<COLUMN; j++){
                            if (state[i][j] != 1){
                                state[i][j] = 0;
                            }
                        }
                    }
                    isDone = false;
                    isDoneMazeBuilding = true;
               }
            }
            
              
            
           if (event.key.code == sf::Keyboard::Escape)
                {
                      refreshGrid(grid, state);
                      isDone = false;
                      isDoneMazeBuilding = false;
                      
                }
        }
         window.display();
        
        
    }
  

  return 0;
   
}
