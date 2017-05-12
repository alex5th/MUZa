#ifndef SONG_H
#define SONG_H
#include <note.h>
#include <QVector>
#include <QDate>

class Song
{
    QVector<QVector<Note>> p[2]; //партия аккомпонимента
//    QVector<int> st;
public:
    Song(QVector<int> lad, QVector<QVector<int>> acc, int lengthAcc);
    int getCountBars();
    Note noteGet();
};

#endif // SONG_H
