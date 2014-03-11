/*
qOthello - file: saveDialog.h - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QtGui>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Othcons/Scacchiera.h"
#include "Othcons/Giocatori.h"
#include "game.h"

class pc;
class umano;
class scacchiera;
class Game;

using namespace std;

class saveDialog : public QDialog
{

Q_OBJECT

    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QStatusBar *inf;

    bool mode;
    umano* utenteA;
    umano* utenteB;
    pc* comp;
    scacchiera* tav;
    Game * gioco;

    std::fstream file;
    std::fstream file1;
    std::fstream file2;
    std::fstream file3;

public:
    saveDialog(bool mode, umano* utente1, umano* utente2, pc* computer, scacchiera* tav1, Game * gioco1); // costruttore riceve come parametro la modalita, o salva, o carica.

    void save(int button); // La funzione effettua il salvataggio dei dati, viene passato il numero del bottone.
    void load(int button); // La funzione effettua il caricamento dei dati, viene passato il numero del bottone.
    void init();

    void setPunt(umano* utente1, umano* utente2, scacchiera* tav, Game * gioco1);
    void setPunt(umano* utente1, pc* computer, scacchiera* tav, Game * gioco1);

public slots:
    void click1(); // click button1.
    void click2(); // click button2.
    void click3(); // click button3.
};

#endif // SAVEDIALOG_H
