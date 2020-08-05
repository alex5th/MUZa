#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QStringList>
#include "output.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <song.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QFile* m_file = new QFile;
    QList<int> m_lad;
    QVector<QVector<int>> m_accomp;

    QWidget* w = new QWidget;
    QVBoxLayout* layoutV = new QVBoxLayout;
    QHBoxLayout* layoutH = new QHBoxLayout;
    QLabel* labelMainAbout = new QLabel("Автокомпозитор МУЗа позволяет создавать музыкальные заготовки. "
                             "Обязательно выберите лад и аккомпанемент. "
                             "Результат сохраняется в виде MusicXML-файла в папке files, "
                             "которая находится в папке с программой.");
    QLabel* labelTempo = new QLabel("Темп композиции");
    QComboBox* comboBoxTempo = new QComboBox;
    QStringList listTempo;
    QLabel* labelAccArrayLength = new QLabel("Длина аккордовой последовательности");
    QComboBox* comboBoxAccArrayLength = new QComboBox;
    QStringList listAccArrayLength;
    QLabel* labelTonic = new QLabel("Тоника");
    QComboBox* comboBoxTonic = new QComboBox;
    QStringList listTonic;
    QCheckBox* checkBoxAuto = new QCheckBox("Автоаккомпанемент");
    QLabel* labelLad = new QLabel("Лад: ");
    QLabel* labelAccomp = new QLabel("Аккомпанемент: ");
    QPushButton* buttonLoadLad = new QPushButton("Загрузка лада");
    QPushButton* buttonLoadAccomp = new QPushButton("Загрузка аккомпанемента");
    QPushButton* buttonCreateSong = new QPushButton("Создание композиции");

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void check();
public slots:
    void createSong();
    void loadLad();
    void loadAccomp();
    void setAuto();
};

#endif // MAINWINDOW_H
