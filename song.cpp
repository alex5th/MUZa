#include "song.h"


int Song::getCountBars()
{
    return p[0].size();
}

Song::Song(QVector<int> lad, QVector<QVector<int> > acc, int lengthAcc)
{

//    int tonToCur = 0;  в XML
//    for(int i: lad)
//    {
//        st.push_back((tonic + tonToCur) % 12);
//        tonToCur += i;
//    }
//    qDebug() << st;

    QVector<int> chords;
    chords.resize(lengthAcc);
    for (int &i: chords)
        i = rand() % lad.size();
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
                p[0][bar].push_back(Note(j[0], (i + 1 - 1) % lad.size(), 0));
                p[0][bar].push_back(Note(j[0], (i + 3 - 1) % lad.size(), 1));
                p[0][bar].push_back(Note(j[0], (i + 5 - 1) % lad.size(), 1));
            }
            else
                for (int k = 1; k < j.size(); ++k)
                {
                    bool ch = true;
                    if (k == 1) ch = false;
                    p[0][bar].push_back(Note(j[0], (i + j[k] - 1) % lad.size(), ch));

                }
            barPos+=j[0];
        }
    }
}
