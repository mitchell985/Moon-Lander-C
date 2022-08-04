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

#ifndef _game_h
#define _game_h

int get_random(int low, int high);
int start_game(int* p_max_x, int* p_max_y);

#endif
