#ifndef SONG_H
#define SONG_H
#include <note.h>
#include <QVector>
#include <QDate>
#include <math.h>

class Song
{
    QVector<QVector<Note>> p[2]; //партия аккомпонимента
public:
    Song(int ladSize, QVector<QVector<int>> accomp, int lengthAcc);
    int getCountBars();
    int getCountNote(const int &p, const int &x);
    const Note operator ()(const int &p, const int &x, const int &y);
    QVector<QVector<int>> generateAccomp();
};

#endif // SONG_H
