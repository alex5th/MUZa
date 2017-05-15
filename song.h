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
    int getCountNote(int p, int x);
    const Note operator ()(int p, int x, int y);
};

#endif // SONG_H
