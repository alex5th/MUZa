#include "mainwindow.h"
#include <QDebug>


void MainWindow::qweq()
{
    if (rb[1][1].isChecked())
    qDebug() << rb[1][1].text();
}

QGroupBox* MainWindow::createGB0()
{
    QGroupBox* gb = new QGroupBox("Темп композиции");
    rb[0][0].setText("90");
    rb[0][1].setText("130");
    rb[0][2].setText("170");
    rb[0][0].setChecked(true);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(&rb[0][0]);
    vbox->addWidget(&rb[0][1]);
    vbox->addWidget(&rb[0][2]);
    vbox->addStretch(1);
    gb->setLayout(vbox);
    return gb;
}

QGroupBox* MainWindow::createGB1()
{
    QGroupBox* gb = new QGroupBox("Длина аккордовой последовательности");
    rb[1][0].setText("2");
    rb[1][1].setText("4");
    rb[1][2].setText("8");
    rb[1][0].setChecked(true);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(&rb[1][0]);
    vbox->addWidget(&rb[1][1]);
    vbox->addWidget(&rb[1][2]);
    vbox->addStretch(1);
    gb->setLayout(vbox);
    return gb;
}

QGroupBox* MainWindow::createGB2()
{
    QGroupBox* gb = new QGroupBox("Смещение аккордов");
    rb[2][0].setText("0");
    rb[2][1].setText("-1/4");
    rb[2][2].setText("-1/2");
    rb[2][0].setChecked(true);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(&rb[2][0]);
    vbox->addWidget(&rb[2][1]);
    vbox->addWidget(&rb[2][2]);
    vbox->addStretch(1);
    gb->setLayout(vbox);
    return gb;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    tl << "До" <<"До♯/Ре♭" << "Ре" << "Ре♯/Ми♭" << "Ми" <<
          "Фа" <<"Фа♯/Соль♭" << "Соль" << "Соль♯/Ля♭" << "Ля" << "Ля♯/Си♭" << "Си";
    cb->addItems(tl);
    cb->setMaxVisibleItems(12);
    int a = 0;
    this->setCentralWidget(w);
    w->setLayout(lm);
    lm->addWidget(lb0);
    lm->addWidget(createGB0());
    lm->addWidget(createGB1());
    lm->addWidget(createGB2());
    lm->addWidget(lb4);
    lm->addWidget(cb);
    lm->addLayout(lh);
    lh->addWidget(pb1);
    lh->addWidget(pb2);
    lh->addWidget(pb0);
    QObject::connect(pb0,SIGNAL(clicked()),this,SLOT(qweq()));
}

MainWindow::~MainWindow()
{

}
