/*
qOthello - file: main.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include <QtGui/QApplication>
#include <QMessageBox>

#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Qt linguistic code loader:

    QTranslator translator;
    qWarning() << translator.load(":/qothello_en");
    a.installTranslator(&translator);

    Game w; // definizione dell'oggetto grafico finestra.

    w.show(); // mostra la finestra. Mostrare le finestre al centro dello schermo.

    return a.exec();
}
