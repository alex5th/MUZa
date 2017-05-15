#include "song.h"


int Song::getCountBars()
{
    return p[0].size();
}

int Song::getCountNote(int p, int x)
{
    return this->p[p][x].size();
}

const Note Song::operator ()(int p, int x, int y)
{
    return this->p[p][x][y];
}

Song::Song(int ladSize, QVector<QVector<int> > acc, int lengthAcc)
{

    QVector<int> chords;
    chords.resize(lengthAcc);
    for (int &i: chords)
        i = rand() % ladSize;
    chords[lengthAcc - 1] = 0;


    qDebug() << chords;

    int accSize = 0;
    for (auto i: acc)
        accSize += i[0];
    p[0].resize(accSize/8.0 * lengthAcc);
    p[1].resize(p[0].size());

    int barPos = 0;
    int bar = 0;
    for (int i: chords)
    {
        for (auto j: acc)
        {
            if (barPos == 8)
            {
                bar++;
                barPos = 0;
                qDebug() << "bar++";
            }
            if (j.size() == 1)
            {
                p[0][bar].push_back(Note(j[0], (i + 1 - 1) % ladSize, 0));
                p[0][bar].push_back(Note(j[0], (i + 3 - 1) % ladSize, 1));
                p[0][bar].push_back(Note(j[0], (i + 5 - 1) % ladSize, 1));
            }
            else
                for (int k = 1; k < j.size(); ++k)
                {
                    bool ch = true;
                    if (k == 1) ch = false;
                    p[0][bar].push_back(Note(j[0], (i + j[k] - 1) % ladSize, ch));

                }
            barPos+=j[0];
        }
    }
}
