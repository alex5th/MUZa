#ifndef SONG_H
#define SONG_H
#include <part.h>
#include <QVector>

class Song
{
    QVector<Part> p;
    int tempo;
    bool accident; //0 - доминирование диезов, 1 - доминирование бемолей в ладу
public:
    Song(QVector<int> lad, QVector<QVector<int>> acc, int tempo, int lengthAcc, int bias);
};

#endif // SONG_H
