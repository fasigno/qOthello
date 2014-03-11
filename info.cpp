/*
qOthello - file: info.cpp - Compiler QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmail.com

Under GPLv3.
*/

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "info.h"

info::info()
{
    QVBoxLayout * w_dialog = new QVBoxLayout(this);
    QPushButton *close = new QPushButton("OK");
    QLabel * text = new QLabel;

    text->setText(" - qOthello - \n\nExam project - Programmazione ad oggetti in c++, \ndegree course in software engineering. \n\n Fabrizio Signoretti, \n fasigno37@gmail.com \n\nRepository: github.com/fasigno/qOthello.git\n\nEnvironment: QT Creator - QT 4.8.5.\n\n Parma 2009/2010");
    w_dialog->addWidget(text);
    w_dialog->addWidget(close);

    QObject::connect(close, SIGNAL(clicked()),
    this, SLOT(quit()));

    setWindowTitle(tr("Info"));
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    setLayout(w_dialog);
}

void info::quit(){
this->deleteLater();
}
