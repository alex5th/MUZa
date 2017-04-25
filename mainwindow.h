#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QComboBox>
#include <QStringList>
#include "output.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget* w = new QWidget;
    QVBoxLayout* lm = new QVBoxLayout;
    QHBoxLayout* lh = new QHBoxLayout;
    QLabel* lb0 = new QLabel("Краткое описание как этим пользоваться");
    QRadioButton rb[3][3];
    QLabel* lb4 = new QLabel("Тоника");
    QComboBox* cb = new QComboBox;
    QStringList tl;
    QPushButton* pb1 = new QPushButton("Загрузка лада");
    QPushButton* pb2 = new QPushButton("Загрузка аккомопнента");
    QPushButton* pb0 = new QPushButton("Создание композиции");

public:
    MainWindow(QWidget *parent = 0);
    QGroupBox* createGB0();
    QGroupBox* createGB1();
    QGroupBox* createGB2();
    ~MainWindow();
public slots:
    void qweq();
};

#endif // MAINWINDOW_H
