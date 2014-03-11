/*
qOthello - file: game.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStatusBar>

#include "game.h"
#include "info.h"
#include "score_win.h" // Finestra del punteggio.
#include "insertname.h" // Dialogo che chiede l'inserimento del nome.

Game::Game(QWidget *parent)
    : QWidget(parent)
{

    // codice finestra al centro.
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

 QGridLayout * mainLayout = new QGridLayout; // layout della finestra su una grid.
 QMenuBar *menu_bar = new QMenuBar(this); // Menu bar della finestra principale.

        for(int i=0; i<8; i++) // allocamento dei bottoni.
                for(int j=0; j<8; j++) {

                    bottoni[i][j] = new buttons(i, j); // allocamento bottoni.

                    bottoni[i][j]->setFixedSize(50,50); // bottoni quadrati.

                    bottoni[i][j]->setEnabled(false); // sono non cliccabili, verranno attivati non appena inizierÃ  il gioco.

                    QObject::connect(bottoni[i][j], SIGNAL(clicked()),
                    this, SLOT(click()));

                    mainLayout->addWidget(bottoni[i][j], i, j); // aggiunta bottoni al layout.

                }

    // viene aggiunta una status bar per le informazioni del gioco.

    inf = new QStatusBar;
    inf->showMessage(tr("Benvenuto in Othello!")); // clear message per cancellare.
    inf->setSizeGripEnabled(false); // viene disattivata la possibilitÃ  di modificarla cliccando il bordo.
    inf->adjustSize();

    QVBoxLayout *Layout = new QVBoxLayout(this); // indica il layout definitivo del form che include gli altri.
    Layout->addWidget(menu_bar);
    Layout->addLayout(mainLayout);
    Layout->addWidget(inf);

    this->setLayout(Layout); // viene impostato il layout predefinito per il form.

    // adatta la finestra secondo i widget, sia in altezza che in larghezza.
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    // impostazione configurazione menubar.

    QMenu *menu_file = menu_bar->addMenu(tr("&File"));
    QMenu *menu_help = menu_bar->addMenu(tr("&?"));

    action_play = menu_file->addAction(tr("&Play"));

    menu_file->addSeparator();

    QAction *action_save = menu_file->addAction(tr("&Save"));
    QAction *action_load = menu_file->addAction(tr("&Load"));

    menu_file->addSeparator();

    QAction *action_exit = menu_file->addAction(tr("&Esci"));
    QAction *action_info = menu_help->addAction(tr("&Info"));

    QObject::connect(action_exit, SIGNAL(activated()),
    this, SLOT(quit()));

    QObject::connect(action_play, SIGNAL(activated()),
    this, SLOT(play()));

    QObject::connect(action_save, SIGNAL(activated()),
    this, SLOT(save()));

    QObject::connect(action_load, SIGNAL(activated()),
    this, SLOT(load()));

    QObject::connect(action_info, SIGNAL(activated()),
    this, SLOT(info_mess()));

    // this->setMenuBar(menu_bar);

    // fine impostazione configurazione menubar.

    // inizializzazioni:

    utente1 = NULL;
    utente2 = NULL;
    computer = NULL;
    tav = NULL;

    play_pc = false; // inizializzazione variabile gioco pc.

}

void Game::save() {

    // se la partita non e' stata eseguita, non e' possibile salvare.
    if (tav == NULL) { QMessageBox text; text.setText(tr("Impossibile salvare una partita non eseguita !")); text.exec();

    } else {
        saveDialog dialog(true, utente1, utente2, computer, tav, this);
        dialog.exec();
    }
}

void Game::load() {
    // se vi e' una partita in corso non sara'  possibile caricare.
    if (tav != NULL) { QMessageBox text; text.setText(tr("Terminare la partita in corso prima di caricarne una nuova !")); text.exec();
    } else {
        saveDialog dialog(false, utente1, utente2, computer, tav, this);
        dialog.exec();
    }
}

Game::~Game()
{

}

void Game::click(){

    int x,y;

    buttons * sender = dynamic_cast<buttons*> (QObject::sender());

    // coordinate pulsante premuto.
    x = sender->return_x();
    y = sender->return_y();

    // qWarning() << x << y;

    interface(x,y);

}

void Game::quit(){
   this->close();
}

void Game::score(){
    score_win *diag = new score_win(utente1, utente2, computer, tav);
    diag->show();
}

void Game::info_mess(){
info *diag = new info;
diag->show();
}

void Game::play(){ // esegue la partita non appena l'utente fa file->play.

    // configurazione menu bar tasto concludi partita.

    action_play->setText(tr("Termina"));
    action_play->disconnect(action_play, 0, 0, 0);

    QObject::connect(action_play, SIGNAL(activated()),
                     this, SLOT(finished()));

    // Fine configurazione menu bar tasto concludi partita.


    // cancellazione bottoni :

    cancellaBottoni();

    // attivazione bottoni:

    attivaBottoni();


    QMessageBox msgbox;
    msgbox.setText(tr("Vuoi giocare con un avversario umano? Premi SI, altrimenti per giocare contro il computer premi NO"));
    msgbox.setWindowTitle(tr("Gioco Othello"));
    msgbox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);

    InsertName * dig = new InsertName; // dialogo inserimento nome utente.

    int tasto = msgbox.exec();
          if (tasto == QMessageBox::Yes) {

            dig->dialog_ut2(); //viene impostato il dialogo per i due giocatori.

            utente2 = new umano;
            utente2->imposta_colore(2); // viene impostato il colore del giocatore 2.

            } else if (tasto == QMessageBox::No) {

           dig->dialog_ut1(); //viene impostato il dialogo per un giocatore.

           computer = new pc;

           computer->imposta_colore(2); // viene impostato il colore del computer.

           pcMove = new QTimer; // timer mossa computer.

//           pcMove->setSingleShot(1000);
//
           // pcMove->singleShot(2000, this, SLOT(computerMove()));

//           pcMove->singleShot(2000, this, SLOT(computerMove()));



//           QObject::connect(pcMove, SIGNAL(timeout()),
//                            this, SLOT(computerMove()));

           play_pc = true;

          }

    tav = new scacchiera;

    utente1 = new umano;

    utente1->imposta_colore(1); // viene impostato il colore del giocatore 1.

    tav->disegna_scacchiera(this); // cambia il colore ai pulsanti.

    if (play_pc != true) {

        // qui utente 1_ingioco = false
        // qui utente 2_ingioco = true
        utente2->imposta_inGioco(); // viene impostato a true, era false in principio.

        dig->set_pl(utente1, utente2); // gli vengono passati gli indirizzi dei puntatori.

    } else {

            computer->imposta_inGioco(); // viene impostato a true, era false in principio.

            dig->set_pl(utente1, NULL); // gli vengono passati gli indirizzi dei puntatori.

    }

    dig->show(); // viene mostrato il dialogo di inserimento del nome.

    inf->showMessage(tr("Turno Grigio")); // gioca per primo l'utente 1 e viene scritto.
    // non si puÃ² scrivere qui il nome dell'utente perchÃ¨ non Ã¨ stato ancora inserito.

}

void Game::color_button(int x, int y, int color){ // metodo che colora i pulsanti.

    QPixmap *image = new QPixmap; // immagine pedina
    QString path; // contiene il percorso delle immagini.

    if (color == 1){

        //path = "./images/white.gif";

        path = ":/images/white.gif";

        image->load(path);

        //bottoni[x][y]->setPixmap(*image);

        QSize dim;
        dim.setHeight(50);
        dim.setWidth(50);

        bottoni[x][y]->setIconSize(dim);
        bottoni[x][y]->setIcon(*image);

     // bottoni[x][y]->setStyleSheet("*{ background-color: rgb(255,255,255)}"); // colore bianco.


    } else {

        path = ":/images/black.gif";

        image->load(path);

        QSize dim;
        dim.setHeight(50);
        dim.setWidth(50);

        bottoni[x][y]->setIconSize(dim);
        bottoni[x][y]->setIcon(*image);

        // bottoni[x][y]->setPixmap(*image);


    // bottoni[x][y]->setStyleSheet("*{ background-color: rgb(0,0,0)}"); // colore nero.

    }

}

void Game::interface(int x, int y){ // Qui i controlli di avanzamento gioco.

int pl = 0; // la variabile assume il valore 1 o 2 in base al giocatore che ha giocato.
bool errore = false; // la variabile indica se i giocatori hanno sbagliato l'inserimento.

    // se tutti e due i giocatori hanno passato il turno senza giocare, il gioco conclude.
    if (((play_pc == false) && (utente1->passato_sgioc() == false || utente2->passato_sgioc() == false)) || ((play_pc == true) && (utente1->passato_sgioc() == false || computer->passato_sgioc() == false))){

        if (utente1->imposta_inGioco() == true){

                pl = 1; // ha giocato il 1Â° giocatore.

                if (utente1->inserisci_Pedina(tav, x, y) == false) { // dovrÃ  restituire true o false nel caso la pedina sia stata inserita.
                // nel caso la pedina non sia stata inserita per errore.

                // messaggio di errore sulla status bar.
                error_m(1);
                pl=0; // per evitare che cancelli l'errore.

                errore = true;
                }

                if (errore == false && play_pc == true) {computer->imposta_inGioco(); control(pl); tav->disegna_scacchiera(this);}
        }

        if (play_pc == false && utente2->imposta_inGioco() == true) {

                pl = 2; // ha giocato il 2Â° giocatore.

                if (utente2->inserisci_Pedina(tav, x, y) == false) { // dovrÃ  restituire true o false nel caso la pedina sia stata inserita.
                // nel caso la pedina non sia stata inserita per errore.

                // messaggio di errore sulla status bar.
                error_m(2);
                pl=0; // per evitare che cancelli l'errore.

                errore = true;
                }

            }

// else aggiunto per il computer.
        else if (play_pc == true && computer->imposta_inGioco() == true) { // gioca il computer.

                pl = 2; // si sostituisce al giocatore umano 2.

                //computer->inserisci_Pedina(tav);
                QTimer::singleShot(2000, this, SLOT(computerMove()));

                utente1->imposta_inGioco(); // per far si che al prossimo turno tocchi ancora all'utente 1.

            }

      if (errore == true) { // se Ã¨ avvenuto un errore da parte dei giocatori.

      utente1->imposta_inGioco(); // si reimpostano le condizioni di partenza in modo che tocchi ancora al giocatore che ha sbagliato.

      if (play_pc == false) {utente2->imposta_inGioco();} else {computer->imposta_inGioco();}

      errore = false;

      }

      // si reimposta passato_sgioc a false per tutti i giocatori.

      utente1->setpassato_sgioc(false);

      if (play_pc == false){utente2->setpassato_sgioc(false); control(pl);} else {computer->setpassato_sgioc(false);}

       // control() :: Controllo delle mosse valide per il giocatore successivo e relativo messaggio sulla status bar.

      tav->disegna_scacchiera(this);

    } else { // fine gioco.

    // blocco bottoni:

            for(int i=0; i<8; i++)
                for(int j=0; j<8; j++) {

                bottoni[i][j]->setEnabled(false);

            }

    // fine blocco bottoni:

    inf->showMessage("Fine Partita");

    score(); // finestra punteggio.

    // si deallocano le risorse.

    delete utente1;

    if (play_pc == false) {delete utente2;} else {delete computer;}

    delete tav;

    tav = NULL;

    // si reimposta la menu bar per poter eseguire una nuova partita.

    action_play->setText("Play");

    action_play->disconnect(action_play, 0, 0, 0);

    QObject::connect(action_play, SIGNAL(activated()),
                     this, SLOT(play()));

    // fine gioco.
    }

} // fine metodo interface().

void Game::error_m(int num){
inf->clearMessage();

    switch(num) {

    case 1:
    inf->showMessage(utente1->r_name() + tr(" Coordinate errate! - reinserire la pedina : Colore Grigio"), 1400);
    break;

    case 2:
    inf->showMessage(utente2->r_name() + tr(" Coordinate errate! - reinserire la pedina : Colore Blu"), 1400);
    break;

    }

}

void Game::view_t(int num){

inf->clearMessage();

QString punt1, punt2;

    switch(num) {

    case 1: // gioca il player 1.

    // messaggio punteggio parziale :

        QTextStream(&punt1) << utente1->restituisci_punteggio(tav);

        if (play_pc == false) {QTextStream(&punt2) << utente2->restituisci_punteggio(tav);

            inf->showMessage(utente1->r_name() + " : " + punt1 + " , " + utente2->r_name() + " : " + punt2, 2000); }

        else {

            QTextStream(&punt2) << computer->restituisci_punteggio(tav);

            inf->showMessage(utente1->r_name() + " : " + punt1 + " , " + computer->r_name() + " : " + punt2, 2000);

        }

            QObject::connect(inf, SIGNAL(messageChanged(QString)),
            this, SLOT(message()));

    // fine messaggio punteggio parziale.

        break;

    case 2: // gioca il player 2.

        if (play_pc == false) {inf->showMessage(utente2->r_name() + tr(" - E' il tuo turno : Colore Blu"));
        } else {inf->showMessage(tr("Attendere turno ") + computer->r_name() + tr(" : Colore Blu"));}

        break;

    }

}

void Game::message() {

disconnect(inf,0,0,0); // viene disconnesso il segnale per evitare che si cancellino gli altri messaggi.
inf->showMessage(utente1->r_name() + tr(" - E' il tuo turno : Colore Grigio"));

}

void Game::computerMove() { // mette la pedina del computer.

    // mosse gioco computer.
    computer->inserisci_Pedina(tav);

    control(2);

    tav->disegna_scacchiera(this);

}

void Game::playLoad(bool mode, saveDialog *diag) { // mode = true partita contro umano, false partita contro computer.

    tav = new scacchiera;

    utente1 = new umano;
    utente1->imposta_colore(1);

    if (mode == true) {
    utente2 = new umano;
    utente2->imposta_colore(2);
    utente2->imposta_inGioco();

    diag->setPunt(utente1, utente2, tav, this);

    } else {
    computer = new pc;
    computer->imposta_colore(2);
    computer->imposta_inGioco();
    play_pc = true;

    diag->setPunt(utente1, computer, tav, this);
    }

    // configurazione menu bar tasto concludi partita.

    action_play->setText(tr("Termina"));
    action_play->disconnect(action_play, 0, 0, 0);

    QObject::connect(action_play, SIGNAL(activated()),
                     this, SLOT(finished()));

    // Fine configurazione menu bar tasto concludi partita.

}

void Game::attivaBottoni() {

            for(int i=0; i<8; i++)
                for(int j=0; j<8; j++) {

                bottoni[i][j]->setEnabled(true);

            }
}

void Game::control(int pl){  // Controllo delle mosse valide per il giocatore successivo e relativo messaggio sulla status bar :


      switch(pl) { // se ha giocato il Pl 1.

          case (1):

      if (tav->mosse_valide(2) == true) {view_t(2); // il prossimo sarÃ  il giocatore 2.

            } else {

                    if (play_pc == false) { // caso gioco contro umano 2

                                utente2->setpassato_sgioc(true); // si imposta il passaggio del turno dell'utente successivo.

                                if (tav->mosse_valide(1) == true) {
                                utente1->imposta_inGioco(); // si reimpostano le condizioni di partenza in modo che tocchi ancora al giocatore che ha giocato prima.
                                utente2->imposta_inGioco();

                                inf->showMessage(utente2->r_name() + "-  Salti il turno per mancanza di mosse possibili ");

                                } else { utente1->setpassato_sgioc(true); tav->disegna_scacchiera(this); interface(0,0);} // si richiama interface con valori inutili per far concludere il gioco.

                    } else { // caso gioco contro pc.

                    computer->setpassato_sgioc(true); // si imposta il passaggio del turno dell'utente successivo.

                                if (tav->mosse_valide(1) == true) {
                                utente1->imposta_inGioco(); // si reimpostano le condizioni di partenza in modo che tocchi ancora al giocatore che ha giocato prima.
                                computer->imposta_inGioco();

                                inf->showMessage(computer->r_name() + "-  Salti il turno per mancanza di mosse possibili ");

                                } else {utente1->setpassato_sgioc(true); tav->disegna_scacchiera(this); interface(0,0);} // si richiama interface con valori inutili per far concludere il gioco.

                }

            }

           break;

       case (2): // se ha giocato il Pl 2.

       if (tav->mosse_valide(1) == true) {view_t(1); // il prossimo sarÃ  il giocatore 1.

         } else {

             if (play_pc == false) { // caso gioco contro umano 1

                 utente1->setpassato_sgioc(true); // si imposta il passaggio del gioco dell'utente successivo.


                                if (tav->mosse_valide(2) == true) {
                                utente1->imposta_inGioco(); // si reimpostano le condizioni di partenza in modo che tocchi ancora al giocatore che ha giocato prima.
                                utente2->imposta_inGioco();

                                inf->showMessage(utente1->r_name() + "-  Salti il turno per mancanza di mosse possibili ");

                                } else { utente2->setpassato_sgioc(true); tav->disegna_scacchiera(this); interface(0,0);} // si richiama interface con valori inutili per far concludere il gioco.


             } else { // caso gioco contro pc.

                 utente1->setpassato_sgioc(true); // si imposta il passaggio del gioco dell'utente successivo.

                                if (tav->mosse_valide(2) == true) {
                                utente1->imposta_inGioco(); // si reimpostano le condizioni di partenza in modo che tocchi ancora al giocatore che ha giocato prima.
                                computer->imposta_inGioco();

                                inf->showMessage(utente1->r_name() + "-  Salti il turno per mancanza di mosse possibili ");

                                } else {computer->setpassato_sgioc(true); tav->disegna_scacchiera(this); interface(0,0);} // si richiama interface con valori inutili per far concludere il gioco.

             }

         }

     break;

    // fine controllo mosse valide e messaggio giocatore successivo.

     } // fine switch.

}

void Game::finished(){ // qui si conclude la partita prima di averla finita.

    utente1->setpassato_sgioc(true);

    if (play_pc == false){
        utente2->setpassato_sgioc(true);

    }else { computer->setpassato_sgioc(true);}

    interface(0,0); // si richiama interface per far concludere la partita.

    // si reimposta la menu bar per poter eseguire una nuova partita.

    action_play->setText("Play");

    action_play->disconnect(action_play, 0, 0, 0);

    QObject::connect(action_play, SIGNAL(activated()),
                     this, SLOT(play()));

}

void Game::cancellaBottoni(){

    // cancellazione i bottoni : (serve nel caso si incominci una nuova partita).

    QPixmap *image = new QPixmap; // immagine vuota per togliere le icone ai bottoni.

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++) {

        bottoni[i][j]->setIcon(*image);

    }


    // fine cancellazione i bottoni :


}
