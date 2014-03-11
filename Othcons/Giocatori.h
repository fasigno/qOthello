/*
qOthello - file: Giocatori.h - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#ifndef Giocatori_H
#define Giocatori_H

#include <string>
#include <stdlib.h>
#include <QtGui> // per la definizione QString.

#include "Scacchiera.h"

class scacchiera;

class giocatori{

	protected: // variabili protette per renderle accessibili alle classi derivate.

        bool passato_gioc; // indica se il giocatore ha passato senza giocare. (ultimo turno)

	int colore; // contiene il colore della pedina del giocatore (serve per il codice che mangia le pedine).

        QString name; // contiene il nome del giocatore.

	private:
		
	int punteggio;

	bool in_gioco; // indica se il giocatore è in gioco true = in gioco, false = non in gioco.

	public:

	giocatori(); // costruttore

	int restituisci_colore(); // restituisce il colore del giocatore.

	int restituisci_punteggio(scacchiera *); // restituisce il punteggio del giocatore.

	void imposta_colore(int);
	
	bool imposta_inGioco(); // imposta e restituisce il valore di in_gioco.

	void inserisci_Pedina(scacchiera *);

        bool passato_sgioc();  // restituisce il valore di passato_gioc.

        void setpassato_sgioc(bool); // imposta il valore di passato_gioc.

        void set_name(QString);

        QString r_name(); // la funzione restituisce il nome del giocatore.

	
};

class umano: public giocatori {
	
	public:

        bool inserisci_Pedina(scacchiera*, int, int);

	umano(); // costruttore.

};

class pc: public giocatori {
	
	public:
	
    void inserisci_Pedina(scacchiera*);
    
    pc(); // costruttore.

};

#endif // Giocatori_H
