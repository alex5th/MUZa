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
    p[0].resize(accSize / 8 * lengthAcc);
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

    QVector<int> melody;
    for (int i = 0; i < accSize / 8; ++i)
    {
        barPos = 0;
        while (barPos < 8)
        {
            int temp;
            do
                temp = pow(2, rand() % 3);
            while (temp + barPos > 8);
            barPos += temp;
            melody.push_back(temp);
        }
    }
    qDebug() << melody;

    barPos = 0;
    for (auto &i: acc)
    {
        int temp = barPos;
        barPos += i[0];
        i[0] = temp;

    }

    barPos = 0;
    bar = 0;
    for (int i: chords)
    {
        int getPosAcc = 0;
        for (int j: melody)
        {
            if (barPos == 8)
            {
                bar++;
                barPos = 0;
            }

            bool flag = false;
            for (int k = getPosAcc; k < acc.size(); ++k)
            {
                if ((bar * 8 + barPos) % accSize == acc[k][0])
                {
                    flag = true;
                    getPosAcc = k;
                    break;
                }
            }
            if (flag)
            {
                if (acc[getPosAcc].size() == 1)
                    p[1][bar].push_back(Note(j,(i + (rand() % 3) * 2) % ladSize, 0));
                else
                    p[1][bar].push_back(Note(j,(i + acc[getPosAcc][(rand() % (acc[getPosAcc].size() - 1)) + 1] - 1) % ladSize, 0));
            }
            else
                p[1][bar].push_back(Note(j, rand() % ladSize, 0));
            barPos+=j;
        }
    }
    p[1][getCountBars() - 1][getCountNote(1, getCountBars() - 1) - 1].degree = 0;
}
