#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SFML/OpenGL.hpp>
#include <iostream>
#include <stdio.h>     
#include <stdlib.h> 
#include <algorithm>
#include <vector>


#define ROW 50
#define COLUMN 50

typedef std::pair<int,int> Pair;



class Grid{
    //Access specifier
    public:
    //data members
    Grid(){}
    sf::Event event;
    int dimension = 30;
    

  
    

    //member function
   
    
    Pair getSrc(sf::RenderWindow& w,sf::Event event, Pair src){
        if(event.type == sf::Event::KeyReleased ){
             if (event.key.code == sf::Keyboard::S)
                {
                    int x = sf::Mouse::getPosition(w).x;
                     int y = sf::Mouse::getPosition(w).y;
                    Pair newSrc = std::make_pair(x/dimension, y/dimension);
                    return newSrc;

                }
        }
        return src;
    }

    Pair getDest(sf::RenderWindow& w,sf::Event event, Pair dest){
        if(event.type == sf::Event::KeyReleased ){
             if (event.key.code == sf::Keyboard::D)
                {
                    int x = sf::Mouse::getPosition(w).x;
                     int y = sf::Mouse::getPosition(w).y;
                    Pair newDest = std::make_pair(x/dimension, y/dimension);
                    return newDest;

                }
        }
        return dest;
    }

   
    void drawGrid(sf::RenderWindow& w, int state[][COLUMN], Pair src, Pair dest){
        for(int i = 0; i<ROW; i++){
            for(int j = 0; j<COLUMN; j++){
                sf::RectangleShape rectangle(sf::Vector2f(dimension, dimension));

               
                rectangle.setOutlineThickness(2);
                rectangle.setOutlineColor(sf::Color(0, 0, 0));
                rectangle.setPosition(dimension*i, dimension*j);
                if(src.first == dest.first && src.second == dest.second){
                    if(i==src.first && j == src.second){
                    rectangle.setFillColor(sf::Color(255, 255, 0));
                    }
                }
                
                else if(i == src.first && j == src.second){
                    //if node is source, colour green
                    rectangle.setFillColor(sf::Color(0, 255, 0));

                }
                else if(i == dest.first && j == dest.second){
                    //if node is destination, colour red
                    rectangle.setFillColor(sf::Color(255, 0, 0));
                }
                else if(state[i][j] == 1){
                    //if unvisited and unobstructed, fill cell white
                    rectangle.setFillColor(sf::Color(255, 255, 255));
                }
                else if(state[i][j] == 0){
                    //if obstructed, fill cell grey
                    rectangle.setFillColor(sf::Color(0,0,0));
                }
                else if(state[i][j] == 2){
                    //if visited in closed list , fill cell dark blue
                    rectangle.setFillColor(sf::Color(0,0,255));
                }
                 else if(state[i][j] == 3){
                    //if JUST visited in OPEN list , fill cell sky (light) blue
                    rectangle.setFillColor(sf::Color(0,191,255));
                }
                else if(state[i][j] == 9){
                    rectangle.setFillColor(sf::Color(255,255,0));
                }
                
                
                w.draw(rectangle);

            }
        }
        
    

    }
    

    void makeBlocks(sf::Event event, int state [][COLUMN], int grid [][COLUMN]){

        if (event.type == sf::Event::MouseButtonPressed){
           
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                
                int i = event.mouseButton.x / dimension;
                int j = event.mouseButton.y / dimension;
                state[i][j] = 0;
                grid[i][j] = 0;


              }
            if (event.mouseButton.button == sf::Mouse::Right)
            {
             int i = event.mouseButton.x / dimension;
                int j = event.mouseButton.y / dimension;
                state[i][j] = 1;
                grid[i][j] = 1;   
            }

        }
  

    }

};








