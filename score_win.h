/*
qOthello - file: score_win.h - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#ifndef SCORE_WIN_H
#define SCORE_WIN_H

#include "Othcons/Giocatori.h"
#include "Othcons/Scacchiera.h"
#include <QWidget>

class score_win : public QWidget
{

Q_OBJECT
public:
    score_win(umano*,umano*, pc*, scacchiera*); // costruttore.

public slots:
    void close();
};

#endif // SCORE_WIN_H
