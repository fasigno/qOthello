/*
qOthello - file: score_win.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "score_win.h"

score_win::score_win(umano* utente1, umano* utente2, pc* computer, scacchiera*tav)
{

    QGridLayout * mainLayout = new QGridLayout;
    QVBoxLayout * line = new QVBoxLayout(this);

    QPushButton *close = new QPushButton("OK");

    QLabel *a, *b, *end, *win;
    QLabel *Punt1, *Punt2; // punteggio giocatore 1 e giocatore 2.

    a = new QLabel;
    b = new QLabel;
    Punt1 = new QLabel;
    Punt2 = new QLabel;
    end = new QLabel;
    win = new QLabel;

    end->setText(tr("Partita Conclusa ::"));
    a->setText(utente1->r_name());

    if (computer == NULL) {b->setText(utente2->r_name());}
    else {b->setText(computer->r_name());}

    QString text, text1, text2;

    QTextStream(&text) << utente1->restituisci_punteggio(tav);

    if (computer == NULL){
        QTextStream(&text1) << utente2->restituisci_punteggio(tav);
    } else {QTextStream(&text1) << computer->restituisci_punteggio(tav);}

    Punt1->setText(text);
    Punt2->setText(text1);

    mainLayout->addWidget(a, 0, 0);
    mainLayout->addWidget(b, 0, 1);

    mainLayout->addWidget(Punt1, 1, 0);
    mainLayout->addWidget(Punt2, 1, 1);

    QTextStream(&text2) << tr("Il vincitore e' : ");

    if (computer == NULL) {

        if (utente1->restituisci_punteggio(tav) > utente2->restituisci_punteggio(tav)){

            QTextStream(&text2) << utente1->r_name();

        } else if (utente1->restituisci_punteggio(tav) < utente2->restituisci_punteggio(tav)) {

            QTextStream(&text2) << utente2->r_name();

        } else {

            text2.clear();
            QTextStream(&text2) << tr("Pareggio !");

        }

    } else {

        if (utente1->restituisci_punteggio(tav) > computer->restituisci_punteggio(tav)){

            QTextStream(&text2) << utente1->r_name();

        } else if (utente1->restituisci_punteggio(tav) < computer->restituisci_punteggio(tav)) {

            QTextStream(&text2) << computer->r_name();

        } else {

            text2.clear();
            QTextStream(&text2) << tr("Pareggio !");

        }


    } // fine if.

    win->setText(text2);

    line->addWidget(end);
    line->addLayout(mainLayout);
    line->addWidget(win);
    line->addWidget(close);

    QObject::connect(close, SIGNAL(clicked()),
    this, SLOT(close()));

    setWindowTitle(tr("Fine Partita"));
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    setLayout(line);


}

void score_win::close(){
this->deleteLater();
}
