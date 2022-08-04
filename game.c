/********************************************************************************
 * Programming 1 (405701) / Programming for Engineering Applications (735318):
 *
 *  File:       menu.c
 *  Author:     Mitchell Caddy
 *  Student Id: 13828045
 *
 *  The following people were consulted by the author in the creation of the
 *  code submitted in this file:
 *   - None
 *
 *  The following resources were used by the author in the creation of the
 *  code submitted in this file:
 *   - the ncurses man pages
 *   - lots of stackoverflow reading no copying
 *   - http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/ <- how i worked the colours and colour pairs out
 *   - http://viget.com/extend/game-programming-in-c-with-the-ncurses-library <- first intro stuff
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>

#include "game.h"

#define DELAY 60000//this has been tweked to work as well as i can make it
#define ENGINE_THRUST 0.05

int get_random(int low, int high)//this random number gen is good :-)
{
    return low + (rand() % (high - low));
}

int start_game(int* p_max_x, int* p_max_y)
{
    srand(time(0));
    
    int c;
    int max_y = *p_max_y, max_x = *p_max_x;
    int loop = 1;
    double thurst_x, thurst_y = 0;
    double x = 0, y = 0;
    double speed_x = 0, speed_y = 0.2;
    double gravity = .01;//i tried to make this a conset but then it falls through the surface
    double fuel = 5;

    x = (max_x / 2);//start ship at x/2 -1

    //setup the display
    //background
    bkgdset(COLOR_PAIR(3));
    clear();
    
    //setting the keypress timeout time
    timeout(0);
    
    //generating the surface randomly
    int surface_height[max_x-1];
    for (int i = 0; i < max_x - 1; ++i)//moving a across the bottom layer
    {
        surface_height[i] = get_random(3,8);
    }
    
    while (loop)
    {
        refresh();//draws or refreshs the screen
        
        //drawing the surface
        //instead of redrawing the whole screen each loop we may need to
        //get the last known ship poition erase it then draw the next ship
        //so only redraw the ship, run it on the pi see what it looks like
        attrset(COLOR_PAIR(4));
        for (int i = 0; i < max_x - 1; ++i)
        {
            for (int j = 1; j < surface_height[i]; ++j)
            {
                mvprintw(max_y-j,i,"o");
            }
        }
        
        //debug menu make this smaller with pointer again hehe
        attrset(COLOR_PAIR(3));
        mvprintw(0, 0, "speed x: %f", speed_x);
        mvprintw(1, 0, "speed y: %f", speed_y);
        mvprintw(2, 0, "x current: %f", x);
        mvprintw(3, 0, "y current: %f", y);
        mvprintw(4, 0, "thrust x: %f", thurst_x);
        mvprintw(5, 0, "thrust y: %f", thurst_y);
        mvprintw(6, 0, "fuel: %f", fuel);
        //mvprintw(7, 0, "current key: %d", c);
        //mvprintw(8, 0, "%d", ((max_y - surface_height[(int)x]) <= y) && ((surface_height[(int)x] + surface_height[(int)x+1] + surface_height[(int)x+2])/3) == surface_height[(int)x]);
        
        mvprintw(y, x, "   ");//clearing ship
        mvprintw(y+1, x+1, " ");//clearing thruster
        mvprintw(y += speed_y, x += speed_x, ">8<");//finding the presskeys numbers
        
        if (c == 115 && fuel >= 0)
        {
            mvprintw(y+1, x+1, "^");
        }
        
        speed_x -= thurst_x;
        speed_y = speed_y - gravity + thurst_y;
        
        c = getch();
        usleep(DELAY);//the delay for detecting the keypress
        
        if (fuel >= 0)
        {
            switch (c)
            {
                case 97:
                    thurst_x = ENGINE_THRUST;//left
                    fuel -= thurst_x;
                    break;
                case 100:
                    thurst_x = -ENGINE_THRUST;//right
                    fuel += thurst_x;
                    break;
                case 115:
                    thurst_y = -ENGINE_THRUST;
                    //mvprintw(y + 1, x + 1, "^"); //trying to add a little thruster animation its not working
                    //refresh();
                    fuel += thurst_y;
                    break;
                default:
                    thurst_x = 0;
                    thurst_y = 0;
                    break;
            }
        }
        else
        {
            thurst_x = 0;
            thurst_y = 0;
            //fuel = 0;
        }
        
        if (x <= 0)//wall check left
        {
            mvprintw(y, 0, "   ");
            mvprintw(y+1, 1, " ");
            x = max_x -4;//so it does not go back the other direction
        }
        
        if (x >= max_x -3)//wall check right
        {
            mvprintw(y, max_x-3,"   ");
            mvprintw(y+1, max_x-2, " ");
            x = 0;
        }
        
        if ((max_y - surface_height[(int)x]) <= y)//colision check, add new code thats being printed to 9,0 then add this as crash check
        {
            gravity = 0;
            speed_x = 0;
            speed_y = 0;
            y = max_y - surface_height[(int)x];
            
            //check if the landed surface is level, there must be a better way to do this
            //sum
            //its more lines but easier to read
            
            if(((surface_height[(int)x] + surface_height[(int)x+1] + surface_height[(int)x+2])) == surface_height[(int)x] *3)
            {
                return 1;
            }
            
            return 0;
        }
        else
        {
            gravity = -.01;
        }
    }
    return -1;//if -1 then error
}











