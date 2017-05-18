#include "mainwindow.h"

void MainWindow::enter()
{
    Song s(lad.size(), acc, cb2->currentText().toInt());
    Output b(s, lad, cb3->currentIndex(), cb1->currentText().toInt());
    QDialog t;
    t.setWindowFlags(Qt::WindowCloseButtonHint);
    t.setWindowTitle("Композиция " + b.getFileName() + " готова");
    t.setFixedSize(250, 1);
    t.setModal(true);
    t.exec();
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
    if (file->fileName() != "") lb4->setText("Лад: " + QFileInfo(*file).fileName().remove(".lad"));
    file->close();
    if (!lad.empty() && !acc.empty()) pb0->setDisabled(false);
}

void MainWindow::pp2()
{
    QString fn;
    mkdir("accompaniment");
    fn = QFileDialog::getOpenFileName(0,QString("Выберите нужный аккомпанемент"),"accompaniment",QString("*.acc"));
    file->setFileName(fn);
    file->open(QIODevice::ReadOnly);
    if (fn!="") acc.clear();
    while (!file->atEnd())
    {
        acc.resize(acc.length()+1);
        QStringList temp = QString(file->readLine()).split(QRegExp("[\\D]"),QString::SkipEmptyParts);
        for (QString j: temp)
            acc[acc.length()-1].push_back(j.toInt());
    }
    if (file->fileName() != "") lb5->setText("Аккомпанемент: " + QFileInfo(*file).fileName().remove(".acc"));
    file->close();
    if (!lad.empty() && !acc.empty()) pb0->setDisabled(false);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pb0->setDisabled(true);

    lb0->setWordWrap(true);

    tl1 << "80" <<"100" << "120" << "160";
    cb1->addItems(tl1);

    tl2 << "2" <<"4" << "6" << "8";
    cb2->addItems(tl2);

    tl3 << "До" <<"До♯/Ре♭" << "Ре" << "Ре♯/Ми♭" << "Ми" <<
          "Фа" <<"Фа♯/Соль♭" << "Соль" << "Соль♯/Ля♭" << "Ля" << "Ля♯/Си♭" << "Си";
    cb3->addItems(tl3);
    cb3->setMaxVisibleItems(12);

    this->setCentralWidget(w);
    this->setWindowTitle("Генератор Хитов 3000");
    w->setLayout(lm);
    lm->addWidget(lb0);
    lm->addWidget(lb1);
    lm->addWidget(cb1);
    lm->addWidget(lb2);
    lm->addWidget(cb2);
    lm->addWidget(lb3);
    lm->addWidget(cb3);
    lm->addWidget(lb4);
    lm->addWidget(lb5);
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
