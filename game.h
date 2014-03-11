/*
qOthello - file: game.h - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

// contiene la finestra con i button generata all'apertura del programma.

#ifndef GAME_H
#define GAME_H

#include <QtGui/QWidget>
#include <QPushButton>
#include <QtDebug>
#include "buttons.h"
#include "saveDialog.h"

#include "Othcons/Giocatori.h"
#include "Othcons/Scacchiera.h"

class scacchiera;
class umano;
class pc;
class saveDialog;

class Game : public QWidget
{
    Q_OBJECT

    buttons * bottoni[8][8];

    QTimer *pcMove; // timer per la risposta del computer.
    QAction *action_play;

    // Memorizzo dei puntatori agli oggetti.
    umano * utente1;
    umano * utente2;
    pc * computer;
    scacchiera * tav;

    bool play_pc; // la variabile indica se l'utente sta giocando contro il computer.

public:
    Game(QWidget *parent = 0); // costruttore.

    ~Game(); // distruttore.

    QStatusBar *inf; // status bar del form. Pubblico per modificare il messaggio anche da saveDialog.

    void color_button(int, int, int); // la funzione colora i bottoni prendendo come parametri la posizione x, y e il colore.

    void interface(int, int); // la funzione si interfaccia con le altre funzioni del gioco e viene richiamata dal metodo click.

    void error_m(int); // la funzione restituisce un messaggio di errore sulla status bar.

    void view_t(int); // la funzione visualizza il nome del giocatore in gioco sulla status bar.

    void score(); // visualizza la finestra del punteggio.

    void playLoad(bool mode, saveDialog *diag); // la funzione esegue il gioco da file.

    void attivaBottoni(); // la funziona attiva i bottoni.

    void cancellaBottoni(); // la funzione cancella i bottoni.

    void control(int pl); // la funzione controlla le mosse valide per l'utente successivo, e gestisce turni e messaggi.

public slots:
    void click(); // funzione click button.
    void quit();  // chiude la finestra di gioco.
    void play();  // inizia la partita.

    void message(); // visualizza info turno dopo la visualizzazione del punteggio temporaneo.
    void info_mess();

    void computerMove(); // procedura timer che mette la pedina del computer.

    void save(); // visualizzano il dialogo di salvataggio / caricamento.
    void load();

    void finished(); // conclude la partita prematuramente.
};

#endif // GAME_H
