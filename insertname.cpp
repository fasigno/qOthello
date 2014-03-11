/*
qOthello - file: insertname.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/
#include "insertname.h"

InsertName::InsertName(QWidget * parent) : QDialog(parent) // costruttore.
{
    iname1 = "";
    iname2 = "";

}

InsertName::~InsertName(){ // nel distruttore si impostano i nomi dei giocatori.

    if (iname1 != "") {Pl1->set_name(iname1);

    } else {Pl1->set_name(tr("Giocatore Grigio"));}


    if (iname2 != "" && Pl2 != NULL) {Pl2->set_name(iname2);

    } else if (Pl2 != NULL) {Pl2->set_name(tr("Giocatore Blu"));}

}

void InsertName::enableFindButton(){

    ok->setEnabled(true);

}

void InsertName::clicked_b(){
    iname1 = name1->text();

    if (name2 != NULL) {
        iname2 = name2->text();
    }


    // this->close(); // chiude la finestra.

    this->deleteLater();

}


void InsertName::dialog_ut1(){
w_dialog = new QVBoxLayout(this);

// inserimento un solo nome (modalità contro il pc);

text1 = new QLabel(tr("Giocatore 1 - Inserisci il tuo nome:"));
name1 = new QLineEdit;
name2 = NULL;
text1->setBuddy(name1);

ok = new QPushButton("Ok");
ok->setDefault(true);
ok->setEnabled(false);

w_dialog->addWidget(text1);
w_dialog->addWidget(name1);
w_dialog->addWidget(ok);

connect(name1, SIGNAL(textChanged(const QString &)),
this, SLOT(enableFindButton()));

connect(ok, SIGNAL(clicked()),
this, SLOT(clicked_b()));

  setLayout(w_dialog);
  setWindowTitle(tr("Nome giocatore"));
  setFixedHeight(sizeHint().height());
  setFixedWidth(sizeHint().width());

}

void InsertName::dialog_ut2() {
w_dialog = new QVBoxLayout(this);

text1 = new QLabel(tr("Giocatore 1 - Inserisci il tuo nome:"));
text2 = new QLabel(tr("Giocatore 2 - Inserisci il tuo nome :"));

name1 = new QLineEdit;
text1->setBuddy(name1);

name2 = new QLineEdit;
text2->setBuddy(name2);

ok = new QPushButton("Ok");
ok->setDefault(true);
ok->setEnabled(false);

w_dialog->addWidget(text1);
w_dialog->addWidget(name1);

w_dialog->addWidget(text2);
w_dialog->addWidget(name2);

w_dialog->addWidget(ok);

connect(name2, SIGNAL(textChanged(const QString &)),
this, SLOT(enableFindButton()));

connect(ok, SIGNAL(clicked()),
this, SLOT(clicked_b()));

  setLayout(w_dialog);
  setWindowTitle(tr("Nomi giocatori"));
  setFixedHeight(sizeHint().height());
  setFixedWidth(sizeHint().width());

}

void InsertName::set_pl(umano* Pla1, umano* Pla2){
    Pl1 = Pla1;
    Pl2 = Pla2;;
}
