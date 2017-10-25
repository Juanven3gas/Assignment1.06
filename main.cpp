#include <stdlib.h>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "Dungeon.h"

#define DELAY 30000
#define END_X 81
#define END_Y 23

Dungeon main_dungeon;

void print_dungeon(WINDOW *win, int fog)
{
   for(int i = 0; i < DUNGEON_ROWS; i++)
   {
         for(int j = 0; j < DUNGEON_COLUMNS; j++)
         {
             if(fog)
             {
               wprintw(win, "%c", main_dungeon.pc_dungeon[i][j]);      
             }
             else 
             {
               wprintw(win, "%c", main_dungeon.dungeon[i][j]);
             }
         }
         wprintw(win, "\n");
   }
   wrefresh(win);
}

int main (int argc, char* argv[])
{
   int num_monsters = 0;
   int arg_count = 1;

   if(argc < 3)
   {
       printf("Insufficient arguements\n");
       return -1;
   }

   while(arg_count < argc)
   {
       if(strcmp(argv[arg_count],  "--nummon") == 0)
       {
           arg_count++;
           num_monsters = atoi(argv[arg_count]);
           if(num_monsters <= 0)
           {
               printf("Incorrect argument passed\n");
               return -1;
           }

           //printf("Setting dungeon up for %d monsters\n", num_monsters);
           arg_count++;
       }
       else 
       {
           printf("incorrect argument detected: %s\n", argv[arg_count]);
           return -1;
       }
   }

   WINDOW *dungeon_win;
   //WINDOW *message_win;
   initscr();
   noecho();
   curs_set(FALSE);
   keypad(stdscr, TRUE);
   dungeon_win = newwin(END_Y, END_X, 1, 0);
   //message_win = newwin(1, END_X, 0, 0);


   while(1)
   {

      
      wclear(dungeon_win);
      print_dungeon(dungeon_win, main_dungeon.fog_state);
      wrefresh(dungeon_win);

      int ch = getch();
      
      if(ch == 'Q' || ch == 'q')
      {
         main_dungeon.win_status = -1;
         break;
      }
      else if((ch == 'y' || ch == '7'))
      {
         //Move the character to the upper left
         main_dungeon.move_pc(UPPER_LEFT);
      }
      else if((ch == 'k' || ch == '8'))
      {
         //Move the character to the up
         main_dungeon.move_pc(UP);
      }
      else if((ch == 'u' || ch == '9'))
      {
         //Move the character to the upper right
         main_dungeon.move_pc(UPPER_RIGHT);
      }
      else if((ch == 'l' || ch == '6'))
      {
         //Move the character to the right
         main_dungeon.move_pc(RIGHT);
      }
      else if((ch == 'n' || ch == '3'))
      {
         //Move the character lower right
         main_dungeon.move_pc(LOWER_RIGHT);
      }
      else if((ch == 'j' || ch == '2'))
      {
         //Move the character down
         main_dungeon.move_pc(DOWN);
      }
      else if((ch == 'b' || ch == '1'))
      {
         //Move the character to the lower left
         main_dungeon.move_pc(LOWER_LEFT);
      }
      else if((ch == 'h' || ch == '4'))
      {
         //Move the character to the left
         main_dungeon.move_pc(LEFT);
      }
      else if((ch == ' ' || ch == '5'))
      {
         //Don't move the character but move the monsters
      }
      else if(ch == 't')
      {

      }
      else if(ch == 'f')
      {
         if(main_dungeon.fog_state)
         {
            main_dungeon.fog_state = 0;
         }
         else{
            main_dungeon.fog_state = 1;
         }
      }

      main_dungeon.update_pc_dungeon();
   }

   main_dungeon.print_game_status();
   endwin();
   return 0;
}
