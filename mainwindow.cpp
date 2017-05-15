#include "mainwindow.h"

void MainWindow::enter()
{
    int tempo;
    int lengthAcc;
    for (int i=0; i<3; ++i)
    {
    if (rb[0][i].isChecked())
        tempo = rb[0][i].text().toInt();
    if (rb[1][i].isChecked())
        lengthAcc = rb[1][i].text().toInt();
    }
    Song s(lad, acc, lengthAcc);
    Output b(s, cb->currentIndex(), tempo);
}

void MainWindow::pp1()
{
    QString fn;
    mkdir("lad");
    fn = QFileDialog::getOpenFileName(0,QString("Выберите нужный лад"),"lad",QString("*.lad"));
    file->setFileName(fn);
    file->open(QIODevice::ReadOnly);
    QStringList temp = QString(file->readAll()).split(QRegExp("[\\D]"),QString::SkipEmptyParts);
    if (fn!="") lad.clear();
    for (QString i: temp)
        lad.push_back(i.toInt());
    file->close();
    if (!lad.empty() && !acc.empty()) pb0->setDisabled(false);
}

void MainWindow::pp2()
{
    QString fn;
    mkdir("accompaniment");
    fn = QFileDialog::getOpenFileName(0,QString("Выберите нужный аккомпонимент"),"accompaniment",QString("*.acc"));
    file->setFileName(fn);
    file->open(QIODevice::ReadOnly);
    while (!file->atEnd())
    {
        acc.resize(acc.length()+1);
        QStringList temp = QString(file->readLine()).split(QRegExp("[\\D]"),QString::SkipEmptyParts);
        for (QString j: temp)
            acc[acc.length()-1].push_back(j.toInt());
    }
    file->close();
    if (!lad.empty() && !acc.empty()) pb0->setDisabled(false);
}

QGroupBox* MainWindow::createGB0()
{
    QGroupBox* gb = new QGroupBox("Темп композиции");
    rb[0][0].setText("90");
    rb[0][1].setText("120");
    rb[0][2].setText("150");
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pb0->setDisabled(true);

    tl << "До" <<"До♯/Ре♭" << "Ре" << "Ре♯/Ми♭" << "Ми" <<
          "Фа" <<"Фа♯/Соль♭" << "Соль" << "Соль♯/Ля♭" << "Ля" << "Ля♯/Си♭" << "Си";
    cb->addItems(tl);
    cb->setMaxVisibleItems(12);
    this->setCentralWidget(w);
    w->setLayout(lm);
    lm->addWidget(lb0);
    lm->addWidget(createGB0());
    lm->addWidget(createGB1());
    lm->addWidget(lb4);
    lm->addWidget(cb);
    lm->addLayout(lh);
    lh->addWidget(pb1);
    lh->addWidget(pb2);
    lh->addWidget(pb0);
    QObject::connect(pb0, &QPushButton::clicked, this, &enter);
    QObject::connect(pb1, &QPushButton::clicked, this, &pp1);
    QObject::connect(pb2, &QPushButton::clicked, this, &pp2);
}

MainWindow::~MainWindow()
{

}
