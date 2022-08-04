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

#include "menu.h"

#define MAIN_COLOUR 1
#define SECOND_COLOUR 2
#define SELECTION_COLOUR 5

//prototyping struct for menu item
//struct Menu_Item
//{
//    char* Title_Name;//and the title
//    //position return a x and y the names are easier then using numbers in an array
//    //fuction pointer to the fuction the menu item needs to run
//    int Item_Number;//this should be adding automatally, this sorts the order and tells the program were it is
//};

int the_menu(int* p_max_x, int* p_max_y)
{
    int c;//keypress char
    int max_y = *p_max_y, max_x = *p_max_x;
    int selection = 1;
    int loop = 1;
    
    //char items[][] = "Start Game","Exit", -1;//the -1 is for the end of the array
    //was going to start malloc menu stuff here but getting the mutiply files working toke longer then i through
    
    bkgdset(COLOR_PAIR(MAIN_COLOUR));
    clear();
    attrset(COLOR_PAIR(SECOND_COLOUR));
    mvprintw(1,1, "Luner Space Lander");//title
    
    //instructions
    draw_instructions();
    
    mvprintw(max_y-4,1, "[");
    mvprintw(max_y-4,12, "]");
    mvprintw(max_y-2,1, "[Exit]");
    
    //set top menu item to the selection colour
    attrset(COLOR_PAIR(SELECTION_COLOUR));
    mvprintw(max_y-4,2,"Start Game");
    
    //could i made the menu items structs ??
    while (loop)
    {
        refresh();
    
        c = getch();
        //mvprintw(0,0, "%d",c);//finding the presskeys numbers
    
        if (c == 259)//up arrow
        {
            //set exit back to stardard colours
            attrset(COLOR_PAIR(SECOND_COLOUR));
            mvprintw(max_y-2,2, "Exit");
            
            attrset(COLOR_PAIR(SELECTION_COLOUR));
            mvprintw(max_y-4, 2,"Start Game");
            selection = 1;
        }
    
        if (c == 258)//down arrow
        {
            //back to stardard colours
            attrset(COLOR_PAIR(SECOND_COLOUR));
            mvprintw(max_y-4, 2,"Start Game");
            
            attrset(COLOR_PAIR(SELECTION_COLOUR));
            mvprintw(max_y-2,2, "Exit");
            selection = 2;
        }
    
        if (selection == 1 && c == 13)//enter and selection start
        {
            //start the game
            
            return selection;
        }
            
        if (selection == 2 && c == 13)//enter and selection exit
        {
            //loop = 0;
            return selection;
        }
    }
    return 0;
}

void draw_instructions()
{
    mvprintw(3,1,"Hello and Welcome to my Lunder Lander Game");
    mvprintw(4,1,"Let me set the scene the year is 1969 and 'i can't remember the exact date nor can i be bothed googling it,'");
    mvprintw(5,1,"and you, yes you, 'small little, inexperinenced you' has been chosen to hold your live, and the lives of");
    mvprintw(6,1,"your other crew members in your fingertips.");//the other one crew member
    mvprintw(8,1,"SO PAID ATTENTION!!");//should change the colour of this
    mvprintw(10,1,"First the 'S' Key is your most important key it fires your rocket some as soon as you start falling PRESS IT");
    mvprintw(11,1,"Your veltical speed is not important, but what is, is to land on a flat surface this is your ship '>8<'");
    mvprintw(12,1,"it uses 3 characters thier for needs 3 spaces of free surface to land on, which brings me to the other keys");
    mvprintw(13,1,"'A' and 'D' simply move the ship left and right. Thats it.");
    mvprintw(14,1,"Good Luck... :D");
    
}










