/*
qOthello - file: scacchiera.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include <iostream>
#include <stdlib.h>
// per il file di testo.
#include <fstream>

#include "Scacchiera.h"
#include "game.h"

using namespace std;

scacchiera::scacchiera() { 
	
	for(int i=0; i<8; i++){
		
		for(int j=0; j<=8; j++){
			
			scac[i][j] = 0;

	    }

	}
	
	a1= 3;
	b1= 3;
	a2= 4;
	b2= 4;
	
	// eventualmente sostituire le variabili ai numeri che identificano le prime pedine nell'array.
	
	scac[3][3] = 1;
	scac[4][4] = 1;
	scac[4][3] = 2;
	scac[3][4] = 2;	

} // il costruttore inizializza l'array scac.

bool scacchiera::mosse_valide(int color){ // color e' il colore del giocatore in gioco.
// restituisce un valore booleano se ci sono ancora mosse valide per il giocatore del relativo colore.

//    int g = 1; // la variabile serve per cambiare il valore sottratto o aggiunto agli estremi.
//    int h = 1;
//
//    // per evitare che esca dalla matrice.
//    if (a1 == 0 && a2 == 7) g = 0;
//    if (b1 == 0 && b2 == 7) h = 0;
//
//        for(int i = b1 - h; i <= b2 + h; i++)  // viene fatto -1 +1 per iniziare il controllo in un riquadro che contenga tutte le pedine sulla scacchiera.
//                for(int j = a1 - g; j <= a2 + g; j++){
//
//                        if (controlla_mossa(i,j, color) == true) {return true;}
//
//	 }

    for(int i = 0; i <= 7; i++)
        for(int j = 0; j <= 7; j++){

        if (controlla_mossa(i,j, color) == true) {return true;}

    }

return false;

}

void scacchiera::disegna_scacchiera(Game * w) { // colora i button sullo schermo. Viene passato un puntatore a game per richiamare la funzione che colora i bottoni.

	for(int i=0; i<8; i++){
                 for(int j=0; j<8; j++){
			
                     if (scac[j][i] == 1){
                         w->color_button(j,i, 1); // richiamo funzione con parametro bianco.

                     } else if (scac[j][i] == 2) { w->color_button(j,i, 2); } // richiamo funzione con parametro nero.
					
			
                }

        }
}

bool scacchiera::controlla_mossa(int x1, int y1, int color) {
// vengono passate le coordinate della nuova pedina inserita dall'utente. x1, y1 e il colore del giocatore in gioco.

        // x1 = riga, y1 = colonna.

        int line = x1, column = y1;

        int da_mangiare; // indica il colore delle pedine dell'avversario.

        if (color == 1) da_mangiare = 2;
        if (color == 2) da_mangiare = 1;

bool concluso = false; // indica se la posizione della pedina va bene.

    if (scac[line][column] == 0) { // controllo posizione sia vuota.

                   bool trovata = false;

                   // controlla alla sinistra della pedina:

        if (scac[line][column-1] != color && scac[line][column-1] != 0 ) { // se ce' subito dopo un posto vuoto non controlla piu'.

                   for (int x = column-1; x >= b1; x--){

                   if (trovata == true)
                       if (scac[line][x] == color){

                       concluso = true;
                       break;

                       } else if (scac[line][x] == 0) {break;} // se incontra uno 0 smette.

                   if ((scac[line][x] == da_mangiare) && (trovata == false)) trovata = true;  // messa dopo per evitare un if inutile.

                   }

        } // fine if.


                   // controlla alla destra della pedina:

                   trovata = false;

        if (scac[line][column+1] != color && scac[line][column+1] != 0) { // se c'? subito dopo un posto vuoto non controlla pi?.

                   if (concluso != true) // condizione che evita di ripetere i costrutti se la posizione va gia' bene.
                   for (int x = column+1; x <= b2; x++){

                   if (trovata == true)
                       if (scac[line][x] == color){

                       concluso = true;
                       break;

                       } else if (scac[line][x] == 0) {break;}

                   if ((scac[line][x] == da_mangiare) && (trovata == false)) trovata = true;

                   }

        } // fine if.


                   // controlla alla su della pedina:

                   trovata = false;

        if (scac[line-1][column] != color && scac[line-1][column] != 0) { // se c'? subito dopo un posto vuoto non controlla pi?.

                   if (concluso != true)
                   for (int y = line-1; y >= a1; y--){

                   if (trovata == true)
                       if (scac[y][column] == color){

                       concluso = true;
                       break;

                       } else if (scac[y][column] == 0) {break;}

                    if ((scac[y][column] == da_mangiare) && (trovata == false)) trovata = true;

                   }

        } // fine if.


                    // controlla alla giu' della pedina:

                    trovata = false;

        if (scac[line+1][column] != color && scac[line+1][column] != 0) { // se c'? subito dopo un posto vuoto non controlla pi?.

                   if (concluso != true)
                   for (int y = line+1; y <= a2; y++){

                       if (trovata == true)
                           if (scac[y][column] == color){

                           concluso = true;
                           break;

                       } else if (scac[y][column] == 0) {break;}

                   if ((scac[y][column] == da_mangiare) && (trovata == false)) trovata = true;

                   }

        } // fine if.





        {// inizio blocco obliqui..serve per usare una sola x e y.

                   // controlla alla obliquo-dx-su / della pedina:
                   int x,y;

                   trovata = false;

                   if (scac[line-1][column+1] != color && scac[line-1][column+1] != 0) { // se c'e' subito dopo un posto vuoto non controlla piu'.


                       x = line-1; y = column+1;

                       if (concluso != true)
                       while(x >= a1 && y <= b2){

                           if (trovata == true)
                               if (scac[x][y] == color){

                               concluso = true;
                               break;

                           } else if (scac[x][y] == 0) {break;}

                           if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

                       x--; y++;
                       } // fine while.

                   } // fine if.



                   // controlla alla obliquo-dx-giu' / della pedina:

                   trovata = false;

                   if (scac[line+1][column-1] != color && scac[line+1][column-1] != 0) { // se c'e' subito dopo un posto vuoto non controlla piu'.

                       x = line+1; y = column-1;

                       if (concluso != true)
                           while(x <= a2 && y >= b1){

                           if (trovata == true)
                               if (scac[x][y] == color){

                               concluso = true;
                               break;

                           } else if (scac[x][y] == 0) {break;}

                           if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

                       x++; y--;
                       } // fine while.

                   } // fine if.



                   // controlla alla obliquo-sx-su \ della pedina:

                   trovata = false;

                   if (scac[line-1][column-1] != color && scac[line-1][column-1] != 0) { // se c'e' subito dopo un posto vuoto non controlla piu'.

                       x = line-1; y = column-1;

                       if (concluso != true)
                           while(x>=a1 && y >= b1){

                           if (trovata == true)
                               if (scac[x][y] == color){

                               concluso = true;
                               break;

                           } else if (scac[x][y] == 0) {break;}

                           if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

                       x--; y--;
                       }// fine while.

                   } // fine if.


                   // controlla alla obliquo-sx-giu' \ della pedina:

                   trovata = false;

                   if (scac[line+1][column+1] != color && scac[line+1][column+1] != 0) { // se c'e' subito dopo un posto vuoto non controlla piu'.

                       x = line+1; y = column+1;

                       if (concluso != true)
                           while(x<=a2 && y <= b2){

                           if (trovata == true)
                               if (scac[x][y] == color){

                               concluso = true;
                               break;

                           } else if (scac[x][y] == 0) {break;}

                           if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

                       x++; y++;
                       } // fine while.

                   } // fine if.



                   } // fine blocco obliqui

    } // fine if iniziale controllo posizione vuota.

return concluso;

} // fine metodo controlla mossa.


void scacchiera::mangia_pedine(int x1, int y1, int color){ // x1 e y1 sono l'ultima posizione della pedina inserita.

    // x1 = riga, y1 = colonna.
        int line = x1, column = y1;

        int da_mangiare; // indica il colore delle pedine dell'avversario.

        if (color == 1) da_mangiare = 2;
        if (color == 2) da_mangiare = 1;


        bool trovata = false;

        // controlla alla sinistra della pedina:

        if (scac[line][column-1] != color && scac[line][column-1] != 0 ) {

        for (int x = column-1; x >= b1; x--){

            if (trovata == true)
                if (scac[line][x] == color){

                int x_ultima=x; // indica la posizione dell'ultima pedina 1 che racchiude i 2.
                // codice di cambio pedina in mezzo.

                for (int delta = column-1; delta >= x_ultima; delta--){

                    scac[line][delta] = color;

                }

                break;

            } else if (scac[line][x] == 0) {break;} // se incontra uno 0 smette.

            if ((scac[line][x] == da_mangiare) && (trovata == false)) trovata = true;  // messa dopo per evitare un if inutile.

        }

    } // fine if.



        // controlla alla destra della pedina:

        trovata = false;

    if (scac[line][column+1] != color && scac[line][column+1] != 0) {

        for (int x = column+1; x <= b2; x++){

            if (trovata == true)
                if (scac[line][x] == color){

                // codice di cambio pedina in mezzo.
                int x_ultima=x;

                for (int delta = column+1; delta <= x_ultima; delta++){

                    scac[line][delta] = color;

                }


                break;

            } else if (scac[line][x] == 0) {break;} // se incontra uno 0 smette.

            if ((scac[line][x] == da_mangiare) && (trovata == false)) trovata = true;

        }

    } // fine if.



        // controlla alla su della pedina:

        trovata = false;

     if (scac[line-1][column] != color && scac[line-1][column] != 0) {

        for (int y = line-1; y >= a1; y--){

            if (trovata == true)
                                if (scac[y][column] == color){

                // codice di cambio pedina in mezzo.

                int y_ultima = y;

                for (int delta = line-1; delta >= y_ultima; delta--){

                    scac[delta][column] = color;

                }

                break;

            } else if (scac[y][column] == 0) {break;} // se incontra uno 0 smette.

            if ((scac[y][column] == da_mangiare) && (trovata == false)) trovata = true;

        }

    } // fine if.



        // controlla alla giu' della pedina:

        trovata = false;

    if (scac[line+1][column] != color && scac[line+1][column] != 0) {

        for (int y = line+1; y <= a2; y++){

            if (trovata == true)
                if (scac[y][column] == color){

                // codice di cambio pedina in mezzo.

                int y_ultima = y;

                for (int delta = line+1; delta <= y_ultima; delta++){

                    scac[delta][column] = color;

                }

                break;

            } else if (scac[y][column] == 0) {break;} // se incontra uno 0 smette.

            if ((scac[y][column] == da_mangiare) && (trovata == false)) trovata = true;

        }

    } // fine if.





        {// inizio blocco obliqui..serve per usare una sola x e y che vengono distrutte fuori dal blocco.
            trovata = false;
            int x,y;

        // controlla alla obliquo-dx-su / della pedina:
         x = line-1; y = column+1;

         if (scac[line-1][column+1] != color && scac[line-1][column+1] != 0) {

             while(x >= a1 && y <= b2){

                if (trovata == true)
                    if (scac[x][y] == color){

                    // codice di cambio pedina in mezzo.

                    int x_ultima = x, y_ultima = y;

                    int deltaX, deltaY; // servono di appoggio per avere un for a due variabili. Come prima |^

                    deltaX = line-1; deltaY = column+1;
                    while(deltaX >= x_ultima && deltaY <= y_ultima) {

                        scac[deltaX][deltaY] = color;

                        deltaX--; deltaY++;
                    }


                    break;

                } else if (scac[x][y] == 0) {break;} // se incontra uno 0 smette.

                if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

            x--; y++;
            } // fine while generale.

        } // fine if.



            // controlla alla obliquo-dx-giu' / della pedina:

            trovata = false;

            x = line+1; y = column-1;

         if (scac[line+1][column-1] != color && scac[line+1][column-1] != 0) {

             while(x <= a2 && y >= b1){

                if (trovata == true)
                    if (scac[x][y] == color){

                    // codice di cambio pedina in mezzo.

                    int x_ultima = x, y_ultima = y;

                    int deltaX, deltaY; // servono di appoggio per avere un for a due variabili. Come prima |^

                    deltaX = line+1; deltaY = column-1;
                    while(deltaX <= x_ultima && deltaY >= y_ultima) {

                        scac[deltaX][deltaY] = color;

                        deltaX++; deltaY--;
                    }


                    break;

                } else if (scac[x][y] == 0) {break;} // se incontra uno 0 smette.

                if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

            x++; y--;
            } // fine while generale.

        } // fine if.



            // controlla alla obliquo-sx-su \ della pedina:

            trovata = false;
            x = line-1; y = column-1;

         if (scac[line-1][column-1] != color && scac[line-1][column-1] != 0) {

             while(x>=a1 && y >= b1){

                if (trovata == true)
                    if (scac[x][y] == color){

                    // codice di cambio pedina in mezzo.

                    int x_ultima = x, y_ultima = y;

                    int deltaX, deltaY; // servono di appoggio per avere un for a due variabili. Come prima |^

                    deltaX = line-1; deltaY = column-1;
                    while(deltaX >= x_ultima && deltaY >= y_ultima) {

                        scac[deltaX][deltaY] = color;

                        deltaX--; deltaY--;
                    }


                    break;

                } else if (scac[x][y] == 0) {break;} // se incontra uno 0 smette.

                if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

            x--; y--;
            } // fine while generale.

        } // fine if.



            // controlla alla obliquo-sx-giu' \ della pedina:

            trovata = false;
            x = line+1; y = column+1;

            if (scac[line+1][column+1] != color && scac[line+1][column+1] != 0) {

                while(x<=a2 && y <= b2){

                if ((scac[x][y] == da_mangiare) && (trovata == false)) trovata = true;

                if (trovata == true)
                    if (scac[x][y] == color){

                    // codice di cambio pedina in mezzo.

                    int x_ultima = x, y_ultima = y;

                    int deltaX, deltaY; // servono di appoggio per avere un for a due variabili. Come prima |^

                    deltaX = line+1; deltaY = column+1;
                    while(deltaX <= x_ultima && deltaY <= y_ultima) {

                        scac[deltaX][deltaY] = color;

                         deltaX++; deltaY++;
                    }

                    break;

                } else if (scac[x][y] == 0) {break;} // se incontra uno 0 smette.

            x++; y++;
            } // fine while generale.

        } // fine if.



                                } // fine blocco obliqui

} // fine metodo.

int scacchiera::aggiorna_punteggio(int color){
	int punteggio = 0;

	int i,j; 

		for(i = b1; i <= b2; i++)
			for(j = a1; j <= a2; j++){

				if (scac[j][i] == color) {punteggio++;}

			}

		return punteggio;
}

bool scacchiera::inserisciPedina(int color, int x, int y) { // restituisce true se la pedina e' stata inserita.
        // false se la pedina non e' stata inserita.

    std::fstream lab;

    lab.open("scacchiera.txt", std::ios::out | std::ios::app);

	if (controlla_mossa(x, y, color) == true) {
                                  
			scac[x][y] = color;   

                // codice di aggiornamento a1 a2 b1 b2.

			if (x < a1) a1 = x;
			if (y < b1) b1 = y;
			if (x > a2) a2 = x;
			if (y > b2) b2 = y;

				mangia_pedine(x, y, color);

                                // prova salvataggio mosse su file.


                                lab << "Mossa : " << y << " : " << x << " pl " << color;

                                lab << "\n";

                                for(int i=0; i<8; i++) {
                                    for(int j=0; j<8; j++){

                                        lab << " " << scac[i][j];

                                    }

                                    lab << "\n";
                                }

                                lab << "\n\n";


                                lab.close();

                                // fine prova salvataggio mosse su file.

			return true;
                         
        } else { return false; } // posizione coordinate errate.
	
}

int scacchiera::r_a1(){
return a1;
}

int scacchiera::r_a2(){
return a2;
}

int scacchiera::r_b1(){
return b1;
}

int scacchiera::r_b2(){
return b2;
}

int scacchiera::salva_scacchiera(int x, int y) { // per il salvataggio su file.

    return scac[x][y];
}

void scacchiera::imposta_scacchiera(int x, int y, int colore) { // per il caricamento da file.

scac[x][y] = colore;

}

void scacchiera::setVar(int A1, int A2, int B1, int B2) {
    a1 = A1;
    a2 = A2;

    b1 = B1;
    b2 = B2;
}
