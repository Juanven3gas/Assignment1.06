#include <stdlib.h>

class Monster
{
public:
   Monster(char symbol, int speed, int room, int move, int attributes)
   char symbol;
   int x_position;
   int y_position;
   int alive;
   int room;
   int speed;
   int attrib;
   int move;
};

Monster::Monster(char symbol, int speed, int room, int move, int attributes)
{
   this.symbol = symbol;
   this.speed = speed;
   this.room = room;
   this.move = move;
   this.attrib = attributes;
}