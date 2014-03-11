/*
qOthello - file: saveDialog.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include "saveDialog.h"

saveDialog::saveDialog(bool mode1, umano* utente1, umano* utente2, pc* computer, scacchiera* tav1, Game * gioco1)
{

    mode = mode1;
    utenteA = utente1;
    utenteB = utente2;
    comp = computer;
    tav = tav1;
    gioco = gioco1;

    this->setFixedHeight(373);
    this->setFixedWidth(368);

    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(40, 10, 271, 41));
    QFont font;
    font.setFamily(QString::fromUtf8("DejaVu Sans"));
    font.setPointSize(16);
    font.setUnderline(true);
    label->setFont(font);
    label->setTextFormat(Qt::AutoText);

    pushButton = new QPushButton(this);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(70, 90, 221, 51));

    QObject::connect(pushButton, SIGNAL(clicked()),
    this, SLOT(click1()));

    pushButton_2 = new QPushButton(this);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(70, 160, 221, 51));

    QObject::connect(pushButton_2, SIGNAL(clicked()),
    this, SLOT(click2()));

    pushButton_3 = new QPushButton(this);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setGeometry(QRect(70, 230, 221, 51));

    QObject::connect(pushButton_3, SIGNAL(clicked()),
    this, SLOT(click3()));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(180, 330, 181, 34));
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);


    QObject::connect(buttonBox, SIGNAL(accepted()),
    this, SLOT(close()));

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 350, 200, 21));

    switch(mode){

    case (true):

        setWindowTitle(tr("Salva"));
        label->setText("Salva :");

        init();

        break;

    case (false):

        setWindowTitle(tr("Carica"));
        label->setText("Carica :");

        init();

        if (pushButton->text() == "< empty >" && pushButton_2->text() == "< empty >" && pushButton_3->text() == "< empty >" ) {
            label_2->setText("Nessuna partita salvata."); }

        break;

    } // fine switch.

}

void saveDialog::click1(){

    switch (mode) {

    case (true): // salva.
        save(1);
        break;

    case (false): // carica.

        if (pushButton->text() != "< empty >") {
            load(1);
        } else {label_2->setText("Nulla da caricare");}

        break;

    }

}

void saveDialog::click2(){

    switch (mode) {

    case (true): // salva.
        save(2);
        break;

    case (false): // carica.

        if (pushButton_2->text() != "< empty >") {
            load(2);
        } else {label_2->setText("Nulla da caricare");}

        break;

    }
}

void saveDialog::click3(){
    switch (mode) {

    case (true): // salva.
        save(3);
        break;

    case (false): // carica.

        if (pushButton_3->text() != "< empty >") {
            load(3);
        } else {label_2->setText("Nulla da caricare");}

        break;

    }
}

void saveDialog::save(int button) {

        switch(button) {

    case 1:

        file.open("saves/game1.dat", std::ios::out); // apertura file di testo.

        break;

    case 2:

        file.open("saves/game2.dat", std::ios::out); // apertura file di testo.

        break;

    case 3:

        file.open("saves/game3.dat", std::ios::out); // apertura file di testo.

        break;

    }

    // file.seekp(0, ios_base::beg);

    // modalit√  partita.
    if (comp == NULL){ file << true << "\n";

        file << utenteA->r_name().toStdString() << "\n";

        file << utenteA->restituisci_punteggio(tav) << "\n";

        file << utenteA->imposta_inGioco() << "\n";

        file << utenteB->r_name().toStdString() << "\n";

        file << utenteB->restituisci_punteggio(tav) << "\n";

        file << utenteB->imposta_inGioco() << "\n";

        } else {file << false << "\n";

        file << utenteA->r_name().toStdString() << "\n";

        file << utenteA->restituisci_punteggio(tav) << "\n";

        file << utenteA->imposta_inGioco() << "\n";

        file << comp->r_name().toStdString() << "\n";

        file << comp->restituisci_punteggio(tav) << "\n";

        file << comp->imposta_inGioco() << "\n";

        }

        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++){

                file << tav->salva_scacchiera(i, j) << " ";

            }

            file << "\n";
        }

        file << tav->r_a1() << "\n";
        file << tav->r_a2() << "\n";
        file << tav->r_b1() << "\n";
        file << tav->r_b2() << "\n";

      file.close();

    init();

    // nel salvataggio i valori vengono girati, qui si riportano corretti per poter continuare la partita.
    utenteA->imposta_inGioco();
    if (comp == NULL) {utenteB->imposta_inGioco();} else {comp->imposta_inGioco();}

    label_2->setText("Salvataggio completato");

} // fine metodo save().

void saveDialog::load(int button){ // caricamento dati partita da file.

    switch(button) {

    case 1:

        file.open("saves/game1.dat", std::ios::in); // apertura file di testo.

        break;

    case 2:

        file.open("saves/game2.dat", std::ios::in); // apertura file di testo.

        break;

    case 3:

        file.open("saves/game3.dat", std::ios::in); // apertura file di testo.

        break;

    }

    // definizione varibili di appoggio.
    string name1;
    string name2;

    string buffer;

    bool modalita;

    bool inGioco1, inGioco2; // variabile in_gioco utente1 e 2. (Nel file sono negate.)

    // prelievo dati da file nelle variabili di appoggio.

    file >> modalita; // modalit√  di gioco. true partita contro umano, false partita contro computer.

    gioco->playLoad(modalita, this); // alloca una nuova partita prima di impostare le variabili caricate.

    file >> name1; // nome utente1.

    file >> buffer; // punteggio buttato via.

    file >> inGioco1; // variabile in_gioco utente1.

    file >> name2; // nome utente2.

    file >> buffer; // punteggio buttato via.

    file >> inGioco2; // variabile in_gioco utente2.


    // prelievo e settaggio scacchiera :

    int pedina = 0; // variabile di appoggio che conterra'  la pedina presa da file.

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){

            file >> pedina;

            tav->imposta_scacchiera(i, j, pedina);

     }

    // fine prelievo e settaggio scacchiera :

    int A1, A2, B1, B2;

    file >> A1; file >> A2; file >> B1; file >> B2;

    tav->setVar(A1, A2, B1, B2);

    // settaggio dati prelevati.

    utenteA->set_name(QString::fromStdString(name1));
    if (mode == true) utenteB->set_name(QString::fromStdString(name2));

    if (modalita == true) { // partita contro umano.
        if (inGioco1 == false && inGioco2 == true){
            utenteA->imposta_inGioco();
            utenteB->imposta_inGioco();

            // gioca il prossimo turno il giocatore2.
            gioco->inf->showMessage(utenteB->r_name() + " - E' il tuo turno : Colore Blu");

            // altrimenti giocatore1.
        } else { gioco->inf->showMessage(utenteA->r_name() + " - E' il tuo turno : Colore Grigio");}

    } else { // partita contro computer.

        if (inGioco1 == false && inGioco2 == true){
            utenteA->imposta_inGioco();
            comp->imposta_inGioco();

            // gioca il prossimo turno il computer.
            gioco->inf->showMessage("Attendere turno " + comp->r_name() + " : Colore Blu");

            gioco->computerMove();

            // altrimenti giocatore1.
        } else { gioco->inf->showMessage(utenteA->r_name() + " - E' il tuo turno : Colore Grigio");}

    }


    label_2->setText("Caricamento completato");

    gioco->cancellaBottoni();

    gioco->attivaBottoni();

    tav->disegna_scacchiera(gioco);

    file.close();

} // fine metodo load().

void saveDialog::init(){

    // variabili:
    string name1;
    string name2;

    string buffer; // variabile di appoggio, i dati all'interno verranno buttati via.

    int punt1;
    int punt2;

    file1.open("saves/game1.dat", std::ios::in); // apertura file di testo1.

    if (!file1){
        pushButton->setText("< empty >");
    } else {

        file1 >> buffer;

        file1 >> name1;

        file1 >> punt1;

        file1 >> buffer;

        file1 >> name2;

        file1 >> punt2;

        QString text;

        QTextStream(&text) << punt1 << "   :   " << punt2;

        pushButton->setText(QString::fromStdString(name1) + " vs " + QString::fromStdString(name2) + "\n" + text);


    }

    file2.open("saves/game2.dat", std::ios::in); // apertura file di testo2.

    if (file2.fail()){
        pushButton_2->setText("< empty >");
    } else {


        file2 >> buffer;

        file2 >> name1;

        file2 >> punt1;

        file2 >> buffer;

        file2 >> name2;

        file2 >> punt2;

        QString text;

        QTextStream(&text) << punt1 << "   :   " << punt2;

        pushButton_2->setText(QString::fromStdString(name1) + " vs " + QString::fromStdString(name2) + "\n" + text);


    }

    file3.open("saves/game3.dat", std::ios::in); // apertura file di testo3.

    if (file3.fail()){
        pushButton_3->setText("< empty >");
    } else {

        file3 >> buffer;

        file3 >> name1;

        file3 >> punt1;

        file3 >> buffer;

        file3 >> name2;

        file3 >> punt2;

        QString text;

        QTextStream(&text) << punt1 << "   :   " << punt2;

        pushButton_3->setText(QString::fromStdString(name1) + " vs " + QString::fromStdString(name2) + "\n" + text);

    }

    file1.close();

    file2.close();

    file3.close();

    label_2->setText("Pronto");

} // fine metodo init().

void saveDialog::setPunt(umano* utente1, umano* utente2, scacchiera* tav1, Game * gioco1){

    utenteA = utente1;
    utenteB = utente2;
    tav = tav1;
    gioco = gioco1;

}

void saveDialog::setPunt(umano* utente1, pc* computer, scacchiera* tav1, Game * gioco1){

    utenteA = utente1;
    comp = computer;
    tav = tav1;
    gioco = gioco1;

}

