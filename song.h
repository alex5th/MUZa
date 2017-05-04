#ifndef SONG_H
#define SONG_H
#include <rest.h>
#include <note.h>
#include <QVector>

class Song
{
    QVector<int> chords;
    QVector<QVector<Rest>> p0; //партия аккомпонимента
    QVector<QVector<Rest>> p1; //партия мелодии
    int tempo;
    QVector<int> st;
public:
    Song(QVector<int> lad, QVector<QVector<int>> acc, int tempo, int lengthAcc, int tonic);
};

#endif // SONG_H
