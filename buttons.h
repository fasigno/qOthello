/*
qOthello - file: buttons.h - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>

class buttons : public QPushButton
{

int x;
int y;

public:

buttons(int, int);

int return_x();

int return_y();

};

#endif // BUTTONS_H
