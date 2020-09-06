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


//to compile sfml on cmd - g++ Grid.cpp -lsfml-graphics -lsfml-window -lsfml-system
//execute with a.exe

//for testing purposes:
//int state [ROW][COLUMN];
//state[0][0] =4;
//state [49][49] = 5;

class Grid{
    //Access specifier
    public:
    Grid(){}
    sf::Event event;
    int dimension = 30;
    //int lastEvent = 0;

    //data members
    

    //member function
    //sf::RenderWindow getWindow(){
      // return 
   // }
    //test leftclick
   /*void clickTest(sf::Event event){
        if (event.type == sf::Event::MouseButtonPressed){
           printf("in clicked\n");
          
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                printf("Left clicked!\n");
            }
        }
   }*/

  /*  Pair clickNew(sf::Event event){
         if (event.type == sf::Event::MouseButtonPressed){
           printf("in clicked\n");
          
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int i = event.mouseButton.x;
                int j = event.mouseButton.y;
                Pair coord = std::make_pair(i/30, j/30);
                return coord;
            }
         }

      
    }*/

    /*
    int getStartEnd(sf::Event event, Pair src, Pair dest){
        //Pair newStart = src;
        //Pair newEnd = dest;

       if (event.type == sf::Event::MouseButtonPressed){
           printf("in clicked\n");
          
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                printf("in left\n");
                int i = event.mouseButton.x;
                int j = event.mouseButton.y;

                 if(i/30 == src.first && j/30 == src.second){
                     lastEvent = -1;
                     //sf::Event event2;

                    
                }
                else if(i/30 == dest.first && j/30 == dest.second){
                    lastEvent = 1;
                }


                     //return src;
                     /*bool mousePressed = true;
                     sf::Event event2;
                    printf("in source\n");
                    while(mousePressed){
                        if(event2.type == sf::Event::MouseButtonReleased){
                            printf("in released start\n");
                            if (event2.mouseButton.button == sf::Mouse::Left){
                                printf("in released start LEFT\n");
                                int x = event2.mouseButton.x;
                                int y = event2.mouseButton.y;

                                newStart = std::make_pair(x/30, y/30);
                                mousePressed = false;
                               

                         }
                        }
                    }*/
                   // }
        

              //  else if (i/30 == dest.first && j/30 == dest.second){
                  //  return dest;
                    /*printf("in dest\n");
                    bool mousePressed = true;
                    sf::Event event2;
                    while(mousePressed){
                        if(event2.type == sf::Event::MouseButtonReleased){
                        printf("in released end\n");
                        
                            if (event2.mouseButton.button == sf::Mouse::Left){
                                int x = event2.mouseButton.x;
                                int y = event2.mouseButton.y;
                                newEnd = std::make_pair(x/30, y/30);
                                mousePressed = false;
                               

                            }
                     }

                    }
                    
             
                }*/

                //printf("%d%d\n", i/30, j/30);
               // pPair givenSet = drag(event, i, j, src, dest);
               // newStart = givenSet.first;
               // newEnd = givenSet.second;
              

           // }
           

       /* }
        else {lastEvent = 0;}
    return lastEvent;        
       }*/

 
       // pPair oldSet = std::make_pair(src, dest);
        //return
        // pPair newSet = std::make_pair(newStart, newEnd);
        //return;

    
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

    /*
    void testDraw(sf::RenderWindow& w, Pair src, Pair dest){
       for(int i = 0; i<ROW; i++){
            for(int j = 0; j<COLUMN; j++){
                sf::RectangleShape rectangle(sf::Vector2f(dimension, dimension));

                //rectangle.setFillColor(sf::Color(255, 255, 255));
                rectangle.setOutlineThickness(2);
                rectangle.setOutlineColor(sf::Color(0, 0, 0));
                rectangle.setPosition(dimension*i, dimension*j);
                if(src.first == dest.first && src.second == dest.second){
                    if(i==src.first && j == src.second){
                    rectangle.setFillColor(sf::Color(255, 255, 0));
                    }
                }
                else if(i==src.first && j == src.second){
                    rectangle.setFillColor(sf::Color(0, 255, 0));
                }
               else if (i == dest.first && j == dest.second){
                    rectangle.setFillColor(sf::Color(255, 0, 0));
                }
                else{
                    rectangle.setFillColor(sf::Color(255,255,255));
                }
                
                  w.draw(rectangle);
            }
       }
   }*/

//official code not for testing yet
    void drawGrid(sf::RenderWindow& w, int state[][COLUMN], Pair src, Pair dest){
        for(int i = 0; i<ROW; i++){
            for(int j = 0; j<COLUMN; j++){
                sf::RectangleShape rectangle(sf::Vector2f(dimension, dimension));

                //rectangle.setFillColor(sf::Color(255, 255, 255));
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
                //Done->//will later on need to edit this function such that it checks the array to see the state of the cell
                
                w.draw(rectangle);

            }
        }
        
    

    }
    

    void makeBlocks(sf::Event event, int state [][COLUMN], int grid [][COLUMN]){

        if (event.type == sf::Event::MouseButtonPressed){
           // printf("A");
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                //printf("B");
                int i = event.mouseButton.x / dimension;
                int j = event.mouseButton.y / dimension;
                state[i][j] = 0;
                grid[i][j] = 0;


                /*if(posRow <= event.mouseButton.x && event.mouseButton.x <= posRow + dimension){
                    if(posCol <= event.mouseButton.y  && event.mouseButton.y <= posCol + dimension){
                        return true;
                    }
                }*/
                //std::cout << "the right button was pressed" << std::endl;
                //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                //std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            }
            if (event.mouseButton.button == sf::Mouse::Right)
            {
             int i = event.mouseButton.x / dimension;
                int j = event.mouseButton.y / dimension;
                state[i][j] = 1;
                grid[i][j] = 1;   
            }

        }
        //return false;

    }


    /*void tracePath(sf::RenderWindow& w,std::vector<Pair> v){
    
        int len = v.size();
        if (len >= 2){
            for(int i =0; i < len-1; i++){
                int xStart = v.at(i).first * dimension + dimension/2;
                int yStart = v.at(i).second * dimension + dimension/2;
                int xEnd = v.at(i+1).first * dimension + dimension/2;
                int yEnd = v.at(i+1).second * dimension + dimension/2;

                sf::Vertex line[] = {{{xStart, yStart}, (255,255,0)}, {{xEnd, yEnd}, (255,255,0)}};
                w.draw(line, sf::Lines);
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(xStart, yStart)),
                    sf::Vertex(sf::Vector2f(yStart, yEnd)),
                    line.color = sf::Color::Yellow
                };

                w.draw(line, 2, sf::Lines);  
            }
        }
        

    }*/
};








