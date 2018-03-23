#include "mainwindow.h"

void MainWindow::enter()
{
    QVector<QVector<int>> emptyAcc;
    Song s(lad.size(), (ch1->isChecked())? emptyAcc : acc, cb2->currentText().toInt());
    Output b(s, lad, cb3->currentIndex(), cb1->currentText().toInt());
    QDialog t;
    t.setWindowFlags(Qt::WindowCloseButtonHint);
    t.setWindowTitle("Композиция " + b.getFileName() + " готова");
    t.setFixedSize(450, 1);
    t.setModal(true);
    t.exec();
}

void MainWindow::check()
{
    pb0->setDisabled(((!acc.empty() || ch1->isChecked()) && !lad.empty())? false : true);
}

void MainWindow::pp0()
{
    pb2->setDisabled((ch1->isChecked())? true : false);
    lb5->setDisabled((ch1->isChecked())? true : false);
    check();
}

void MainWindow::pp1()
{
    QString fn;
    QDir().mkdir("lad");
    fn = QFileDialog::getOpenFileName(0,QString("Выберите нужный лад"),"lad",QString("*.lad"));
    file->setFileName(fn);
    file->open(QIODevice::ReadOnly);
    QStringList temp = QString(file->readAll()).split(QRegExp("[\\D]"),QString::SkipEmptyParts);
    int test = 0;
    for (QString i: temp)
        test += i.toInt();
    if (fn!="")
        if (test != 12)
        {
            pp1();
            return;
        }
        else lad.clear();
    for (QString i: temp)
        lad.push_back(i.toInt());
    if (file->fileName() != "") lb4->setText("Лад: " + QFileInfo(*file).fileName().remove(".lad"));
    file->close();
    check();
}

void MainWindow::pp2()
{
    QString fn;
    QDir().mkdir("accompaniment");
    fn = QFileDialog::getOpenFileName(0,QString("Выберите нужный аккомпанемент"),"accompaniment",QString("*.acc"));
    file->setFileName(fn);
    file->open(QIODevice::ReadOnly);
    int test = 0;
    while (!file->atEnd())
    {
        QStringList temp = QString(file->readLine()).split(QRegExp("[\\D]"), QString::SkipEmptyParts);
        if ((temp[0] == "5") || (temp[0] == "7") || (temp[0] < "1") || (temp[0] > "8"))
        {
            pp2();
            return;
        }
        test += temp[0].toInt();
    }
    qDebug() << test;
    file->close();
    file->open(QIODevice::ReadOnly);
    if (fn != "")
        if (test % 8 != 0)
        {
            pp2();
            return;
        }
        else acc.clear();
    while (!file->atEnd())
    {
        acc.resize(acc.length() + 1);
        QStringList temp = QString(file->readLine()).split(QRegExp("[\\D]"), QString::SkipEmptyParts);
        for (QString j: temp)
            acc[acc.length() - 1].push_back(j.toInt());
    }
    if (file->fileName() != "") lb5->setText("Аккомпанемент: " + QFileInfo(*file).fileName().remove(".acc"));
    file->close();
    check();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pb0->setDisabled(true);

    lb0->setWordWrap(true);

    tl1 << "80" <<"100" << "120" << "140" << "160";
    cb1->addItems(tl1);

    tl2 << "2" <<"4" << "8";
    cb2->addItems(tl2);

    tl3 << "До" <<"До♯/Ре♭" << "Ре" << "Ре♯/Ми♭" << "Ми" <<
           "Фа" <<"Фа♯/Соль♭" << "Соль" << "Соль♯/Ля♭" << "Ля" << "Ля♯/Си♭" << "Си";
    cb3->addItems(tl3);
    cb3->setMaxVisibleItems(12);

    this->setCentralWidget(w);
    this->setWindowTitle("Автокомпозитор МУЗа");
    w->setLayout(lm);
    lm->addWidget(lb0);
    lm->addWidget(lb1);
    lm->addWidget(cb1);
    lm->addWidget(lb2);
    lm->addWidget(cb2);
    lm->addWidget(lb3);
    lm->addWidget(cb3);
    lm->addWidget(ch1);
    lm->addWidget(lb4);
    lm->addWidget(lb5);
    lm->addLayout(lh);
    lh->addWidget(pb1);
    lh->addWidget(pb2);
    lh->addWidget(pb0);
    QObject::connect(pb0, &QPushButton::clicked, this, &MainWindow::enter);
    QObject::connect(pb1, &QPushButton::clicked, this, &MainWindow::pp1);
    QObject::connect(pb2, &QPushButton::clicked, this, &MainWindow::pp2);
    QObject::connect(ch1, &QCheckBox::clicked, this, &MainWindow::pp0);
}

MainWindow::~MainWindow()
{

}
