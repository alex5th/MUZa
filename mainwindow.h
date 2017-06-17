#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QStringList>
#include "output.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <dir.h>
#include <song.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QFile* file = new QFile;
    QVector<int> lad;
    QVector<QVector<int>> acc;

    QWidget* w = new QWidget;
    QVBoxLayout* lm = new QVBoxLayout;
    QHBoxLayout* lh = new QHBoxLayout;
    QLabel* lb0 = new QLabel("Автокомпозитор МУЗа позволяет создавать музыкальные заготовки. "
                             "Обязательно выберите лад и аккомпанемент. "
                             "Результат сохраняется в виде MusicXML-файла в папке files, "
                             "которая находится в папке с программой.");
    QLabel* lb1 = new QLabel("Темп композиции");
    QComboBox* cb1 = new QComboBox;
    QStringList tl1;
    QLabel* lb2 = new QLabel("Длина аккордовой последовательности");
    QComboBox* cb2 = new QComboBox;
    QStringList tl2;
    QLabel* lb3 = new QLabel("Тоника");
    QComboBox* cb3 = new QComboBox;
    QStringList tl3;
    QLabel* lb4 = new QLabel("Лад: ");
    QLabel* lb5 = new QLabel("Аккомпанемент: ");
    QPushButton* pb1 = new QPushButton("Загрузка лада");
    QPushButton* pb2 = new QPushButton("Загрузка аккомпанемента");
    QPushButton* pb0 = new QPushButton("Создание композиции");

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void enter();
    void pp1();
    void pp2();
};

#endif // MAINWINDOW_H
