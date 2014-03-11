/*
qOthello - file: giocatori.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include <string>
#include <stdlib.h>
#include <iostream>

#include "Giocatori.h"


giocatori::giocatori() { 
	
	punteggio = 0;
	colore = 0;
	in_gioco = false;
	passato_gioc = false;
	
} // costruttore inizializza il punteggio.

umano::umano():giocatori(){} // costruttore class umano

pc::pc():giocatori(){

	name = "Computer";

} // costruttore classe pc

void giocatori::imposta_colore(int col){

colore = col;

}

bool giocatori::imposta_inGioco(){ // imposta e restituisce il valore di in_gioco.

	if (in_gioco == false){
		in_gioco = true;
	}
	else {in_gioco = false;}

	return in_gioco;
}

bool umano::inserisci_Pedina(scacchiera *tav, int x, int y){

        if(tav->inserisciPedina(colore, x, y) == false){ // se la pedina non e' stata inserita.

            return false; // viene restituito false.

        }

       return true;  // altrimenti true = pedina inserita.
}

void pc::inserisci_Pedina(scacchiera * tav){

        int x, y;

        int a1= tav->r_a1();
//        int a2= tav->r_a2();

        int b1= tav->r_b1();
//	int b2= tav->r_b2(); // variabili che assumeranno i valori di a1, a2, b1, b2 della scacchiera.
//
        x= --a1;
        y= --b1; // si incomincia la ricerca di una posizione valida.
//
//	a2++;
//	b2++;

        // messaggio attendere mossa computer.

        while(tav->controlla_mossa(x, y, colore) == false && tav->mosse_valide(colore) == true){  // Logica di inserimento pc.


            if (y <= 7){ y++;} else { y = 0; x++;}

            if (x > 7) { x = 0; y = 0;}

//            // simulazione coordinate.
//            x = rand() % 7;
//            y = rand() % 7;


        }


        if (tav->mosse_valide(colore) == false) { passato_gioc = true; // se non ci sono mosse valide per il giocatore
            // viene passato il turno senza giocare.

        } else { tav->inserisciPedina(colore, x, y); }

}

int giocatori::restituisci_punteggio(scacchiera * tav){

return	tav->aggiorna_punteggio(colore);

}

bool giocatori::passato_sgioc(){
return passato_gioc;
}

void giocatori::setpassato_sgioc(bool passato){
passato_gioc = passato;
}

QString giocatori::r_name(){ // viene restituito il nome del giocatore.
return name;
}

void giocatori::set_name(QString nm) { // viene impostato il nome del giocatore.
name = nm;
}
