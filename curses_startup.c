/********************************************************************************
 * Programming 1 (405701) / Programming for Engineering Applications (735318):
 *
 *  File:       curses_startup.c
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
#include <string.h>
#include <unistd.h>

#include "curses_startup.h"
#include "menu.h"
#include "game.h"

#define WIN     "Oh Look at That, Aren't You Fancy, Just Because I Can't Land There's no need to Showoff :-("//defining lets me use strlen :-)
#define LOST    "You Crashed Disapponting the Whole Planet, Well Done, Prat :-)"//burning it space what??
#define PRESS   "Press Any Key to Close or Enter to Play again"

int main(int argc, char *argv[])
{
    int max_x, max_y;
    int result;
    int loop = 1;
    
    init_curses(&max_x,&max_y);//set the curses window setting and get the max screen x and y could use the stright int as its the same size as a pointer but the naming convention works better in the menu.c
    init_colour_pairs();
    
    if (the_menu(&max_x,&max_y) == 1)
    {
        while (loop)
        {
            result = start_game(&max_x,&max_y);//start the game
            loop = win_lost(result, max_x, max_y);
        }
    }

    
    
    endwin();//close current curses window
}

void init_curses(int* max_x, int* max_y)
{
    //initializing curses setting
    initscr();// initialize the curses screen
    keypad(stdscr, TRUE);//turn on keypad mapping
    nonl();//disable the standard terminals in terpratation of the enter key
    cbreak();//don't wait for a return
    noecho();//no echo on keyboard input
    getmaxyx(stdscr, *max_y, *max_x);//the max size of the screen
    curs_set(FALSE);//turn the cursor off
    //timeout(0);//setting the keypress timeout time
}

void init_colour_pairs()
{
    if (has_colors())//if screen has colours ??
    {
        start_color();
        //this just defines colour pair numbers, foreground, background
        init_pair(1, COLOR_WHITE,   COLOR_GREEN);//menu main
        init_pair(2, COLOR_WHITE,   COLOR_MAGENTA);//menu selection choose
        init_pair(3, COLOR_WHITE,   COLOR_BLACK);//background game
        init_pair(4, COLOR_MAGENTA, COLOR_WHITE);//game surface
        init_pair(5, COLOR_WHITE,   COLOR_BLUE);//trying using a colour selection instent of needing to enable the cursor
        
    }
}

//this could be done better... :-(
//would a straight copy paste have worked better
void draw_win_lost(int result, int max_x, int max_y)
{
    if (result == 1)
    {
        mvprintw(max_y/2,(max_x/2)-((strlen(WIN)-1)/2), WIN);
        mvprintw((max_y/2)+1,(max_x/2)-((strlen(PRESS)-1)/2), PRESS);
    }
    else
    {
        attrset(COLOR_PAIR(2));
        mvprintw(max_y/2,(max_x/2)-((strlen(LOST)-1)/2), LOST);
        mvprintw((max_y/2)+1,(max_x/2)-((strlen(PRESS)-1)/2), PRESS);
    }
}

int win_lost(int result, int max_x, int max_y)
{
    int c;
    int loop = 1;
    
    //set and clear the background colour then set the test colour
    bkgdset(COLOR_PAIR(1));
    clear();
    attrset(COLOR_PAIR(2));
    
    draw_win_lost(result, max_x, max_y);
    //mvprintw(0, 0, "current key: %d", c);
    refresh();
    sleep(2);//sleep for enough time for people to stop pressing a key
    
    //it not the most elegant solution but it works, ill blame not being familiar enough with the libriay
    //and the documentation does not have any examples :-(
    for (int i = 0; i < 50; ++i) {
        c = getch();
    }
    
    while (loop)
    {
        refresh();
        //mvprintw(0, 0, "current key: %d", c);
        
        draw_win_lost(result, max_x, max_y);
        
        c = getch();
        
        if (c == 13)//enter key, i don't think that 13 is portable for keyboards that are not US English
        //i know wasd is not
        {
            //start game again
            return 1;
        }
        
        if (c != -1)
        {
            return 0;
        }
    }
    return -1;//-1 for error
}











