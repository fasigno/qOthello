/*
qOthello - file: Scacchiera.h - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/
#ifndef Scacchiera_H
#define Scacchiera_H

#include "game.h"

class Game;

class scacchiera{
      
    private:
      		
        int scac[8][8];   // puo' contenere 0 = nessuna pedina
                          // puo' contenere 1 = pedina bianca
                          // puo' contenere 2 = pedina nera
				     
        int a1, a2, b1, b2;
    
	public:
	
	scacchiera(); // costruttore
	
	bool controlla_mossa(int, int, int);

        void mangia_pedine(int, int, int);
	
        void disegna_scacchiera(Game *);

	bool mosse_valide(int); // la funzione controlla se ci sono ancora mosse valide per il giocatore e ferma il gioco in caso contrario.
	
        bool inserisciPedina(int, int, int);

	int aggiorna_punteggio(int); // restituisce il punteggio relativo al colore di pedina passato per argomento.ù

        int salva_scacchiera(int x, int y);

        void imposta_scacchiera(int x, int y, int colore);

	int r_a1(); // restituisce il valore di a1.
	int r_a2(); //     "             "   di a2. 
	int r_b1(); //     "             "   di b1.
	int r_b2(); //     "             "   di b2.

        void setVar(int A1, int A2, int B1, int B2);

};

#endif // Scacchiera_H
