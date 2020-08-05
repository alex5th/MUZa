#include "mainwindow.h"

void MainWindow::createSong()
{
    QVector<QVector<int>> emptyAcc;
    Song tmp_song(m_lad.size(), (checkBoxAuto->isChecked())? emptyAcc : m_accomp, comboBoxAccArrayLength->currentText().toInt());
    Output tmp_output(tmp_song, m_lad, comboBoxTonic->currentIndex(), comboBoxTempo->currentText().toInt());
    QDialog tmp_dialog;
    tmp_dialog.setWindowFlags(Qt::WindowCloseButtonHint);
    tmp_dialog.setWindowTitle("Композиция " + tmp_output.getFileName() + " готова");
    tmp_dialog.setFixedSize(450, 1);
    tmp_dialog.setModal(true);
    tmp_dialog.exec();
}

void MainWindow::check()
{
    buttonCreateSong->setDisabled(((!m_accomp.empty() || checkBoxAuto->isChecked()) && !m_lad.empty())? false : true);
}

void MainWindow::setAuto()
{
    buttonLoadAccomp->setDisabled((checkBoxAuto->isChecked())? true : false);
    labelAccomp->setDisabled((checkBoxAuto->isChecked())? true : false);
    check();
}

void MainWindow::loadLad()
{
    QString fn;
    QDir().mkdir("lad");
    fn = QFileDialog::getOpenFileName(0,QString("Выберите нужный лад"),"lad",QString("*.lad"));
    m_file->setFileName(fn);
    m_file->open(QIODevice::ReadOnly);
    QStringList temp = QString(m_file->readAll()).split(QRegExp("[\\D]"),QString::SkipEmptyParts);
    int test = 0;
    for (QString i: temp)
        test += i.toInt();
    if (fn!="")
        if (test != 12)
        {
            loadLad();
            return;
        }
        else m_lad.clear();
    for (QString i: temp)
        m_lad.push_back(i.toInt());
    if (m_file->fileName() != "") labelLad->setText("Лад: " + QFileInfo(*m_file).fileName().remove(".lad"));
    m_file->close();
    check();
}

void MainWindow::loadAccomp()
{
    QString fn;
    QDir().mkdir("accompaniment");
    fn = QFileDialog::getOpenFileName(0,QString("Выберите нужный аккомпанемент"),"accompaniment",QString("*.acc"));
    m_file->setFileName(fn);
    m_file->open(QIODevice::ReadOnly);
    int test = 0;
    while (!m_file->atEnd())
    {
        QStringList temp = QString(m_file->readLine()).split(QRegExp("[\\D]"), QString::SkipEmptyParts);
        if ((temp[0] == "5") || (temp[0] == "7") || (temp[0] < "1") || (temp[0] > "8"))
        {
            loadAccomp();
            return;
        }
        test += temp[0].toInt();
    }
    qDebug() << test;
    m_file->close();
    m_file->open(QIODevice::ReadOnly);
    if (fn != "")
        if (test % 8 != 0)
        {
            loadAccomp();
            return;
        }
        else m_accomp.clear();
    while (!m_file->atEnd())
    {
        m_accomp.resize(m_accomp.length() + 1);
        QStringList temp = QString(m_file->readLine()).split(QRegExp("[\\D]"), QString::SkipEmptyParts);
        for (QString j: temp)
            m_accomp[m_accomp.length() - 1].push_back(j.toInt());
    }
    if (m_file->fileName() != "") labelAccomp->setText("Аккомпанемент: " + QFileInfo(*m_file).fileName().remove(".acc"));
    m_file->close();
    check();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    buttonCreateSong->setDisabled(true);

    labelMainAbout->setWordWrap(true);

    listTempo << "80" <<"100" << "120" << "140" << "160";
    comboBoxTempo->addItems(listTempo);

    listAccArrayLength << "2" <<"4" << "8";
    comboBoxAccArrayLength->addItems(listAccArrayLength);

    listTonic << "До" <<"До♯/Ре♭" << "Ре" << "Ре♯/Ми♭" << "Ми" <<
           "Фа" <<"Фа♯/Соль♭" << "Соль" << "Соль♯/Ля♭" << "Ля" << "Ля♯/Си♭" << "Си";
    comboBoxTonic->addItems(listTonic);
    comboBoxTonic->setMaxVisibleItems(12);

    this->setCentralWidget(w);
    this->setWindowTitle("Автокомпозитор МУЗа");
    w->setLayout(layoutV);
    layoutV->addWidget(labelMainAbout);
    layoutV->addWidget(labelTempo);
    layoutV->addWidget(comboBoxTempo);
    layoutV->addWidget(labelAccArrayLength);
    layoutV->addWidget(comboBoxAccArrayLength);
    layoutV->addWidget(labelTonic);
    layoutV->addWidget(comboBoxTonic);
    layoutV->addWidget(checkBoxAuto);
    layoutV->addWidget(labelLad);
    layoutV->addWidget(labelAccomp);
    layoutV->addLayout(layoutH);
    layoutH->addWidget(buttonLoadLad);
    layoutH->addWidget(buttonLoadAccomp);
    layoutH->addWidget(buttonCreateSong);
    QObject::connect(buttonCreateSong, &QPushButton::clicked, this, &MainWindow::createSong);
    QObject::connect(buttonLoadLad, &QPushButton::clicked, this, &MainWindow::loadLad);
    QObject::connect(buttonLoadAccomp, &QPushButton::clicked, this, &MainWindow::loadAccomp);
    QObject::connect(checkBoxAuto, &QCheckBox::clicked, this, &MainWindow::setAuto);
}

MainWindow::~MainWindow()
{

}
