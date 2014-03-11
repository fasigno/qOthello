/*
qOthello - file: insertname.h - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#ifndef INSERTNAME_H
#define INSERTNAME_H

#include <QDialog>
#include <QVBoxLayout>
#include <QtGui>
#include "Othcons/Giocatori.h"
#include "game.h"

    class QLabel;
    class QLineEdit;
    class QPushButton;

class InsertName : public QDialog
{
Q_OBJECT

QVBoxLayout * w_dialog;

QLineEdit * name1, *name2;

QLabel * text1, * text2;
QPushButton * ok;

        QString iname1; // variabile che conterrà il nome del giocatore1.
        QString iname2; // variabile che conterrà il nome del giocatore2.

            umano * Pl1; // servono di appoggio per fissare il nome.
            umano * Pl2; // servono di appoggio per fissare il nome.

public:
    InsertName(QWidget* parent=0); // costruttore.

    ~InsertName(); // distruttore.

    void dialog_ut2(); // la funzione crea un dialogo che chiede l'inserimento di due nomi.
    void dialog_ut1(); // la funzione crea un dialogo che chiede l'inserimento di un nome.

    void set_pl(umano*, umano*); // queste due funzioni impostano i puntatori agli oggetti umano e scacchiera.


public slots:

    void enableFindButton(); // attiva il pulsante ok non appena si inserisce qualcosa nella line edit.

    void clicked_b(); // funzione richiamata al click dell'utente su ok.

};

#endif // INSERTNAME_H
