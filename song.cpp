#include "song.h"
#include <QDebug>


Song::Song(QVector<int> lad, QVector<QVector<int> > acc, int tempo, int lengthAcc, int tonic):tempo(tempo)
{
    int tonToCur = 0;
    for(int i: lad)
    {
        st.push_back((tonic + tonToCur) % 12);
        tonToCur += i;
    }

    qDebug() << st;

    chords.resize(lengthAcc);
    for (int &i: chords)
        i = rand() % st.size();
    chords[lengthAcc - 1] = 0;


    qDebug() << chords;

    int accSize = 0;
    for (auto i: acc)
        accSize += i[0];
    p0.resize(accSize/8.0 * lengthAcc);
    p1.resize(p0.size());

    int barPos = 0;
    int bar = 0;
    for (int i: chords)         //думай думай как заполнять, учти такт и шаблон не зависимы по размеру
    {
        for (auto j: acc)
        {
            barPos+=j[0];
            if (j.size() == 1)
            {
                p0[bar].push_back(Rest(j[0]));
            }
            else for (int k = 1; k < j.size(); ++k)
            {
                bool ch = true;
                if (k == 1) ch = false;
            p0[bar].push_back(Note(j[0], (i + j[k] - 1) % st.size(), ch));
            }
        }
    }
}
