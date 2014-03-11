/*
qOthello - file: buttons.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include "buttons.h"

buttons::buttons(int x1, int y1)
{

   this->x = x1;
   this->y = y1;

}

int buttons::return_x(){

return x;

}

int buttons::return_y(){

return y;

}

