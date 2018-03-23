#include "song.h"


int Song::getCountBars()
{
    return p[0].size();
}

int Song::getCountNote(const int &p, const int &x)
{
    return this->p[p][x].size();
}

const Note Song::operator ()(const int &p, const int &x, const int &y)
{
    return this->p[p][x][y];
}

QVector<QVector<int>> Song::generateAcc()
{
    QVector<QVector<int>> vvtemp;
    for (int i = 0; i < rand() % 2 + 1; ++i)
    {
        int barPos = 0;
        while (barPos < 8)
        {
            int temp;
            QVector<int> vtemp;
            do
            {
                int r = rand() % 5;
                if (r) temp = pow(2, rand() % 3);
                else temp = 3 * (rand() % 2 + 1);
            }
            while (temp + barPos > 8);
            barPos += temp;
            vtemp.push_back(temp);
            for (int j = 1; j <= 5; j += 2)
            {
                int r = rand() % 3;
                if (!r) vtemp.push_back(j);
            }
            vvtemp.push_back(vtemp);
        }
    }
    return vvtemp;
}


Song::Song(int ladSize, QVector<QVector<int>> acc, int lengthAcc)
{

    QVector<int> chords(lengthAcc);
    chords[0] = rand() % ladSize;
    for (int i = 1; i < lengthAcc - 1; ++i)
    {
        do chords[i] = rand() % ladSize;
        while ((i % 2 == 0) && (chords[i-1] == chords[i]));
    }
    chords[lengthAcc - 1] = 0;
    qDebug() << chords;

    int accSize = 0;
    if (acc.isEmpty()) acc = generateAcc();
    qDebug() << acc;

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
                //поиграть потом с рандомностью и флажок, после попадания с 0 на 1
                p[0][bar].push_back(Note(j[0], (i) % ladSize, 0));
                for (int k = 1; k < ladSize / 2; ++k)
                    p[0][bar].push_back(Note(j[0], (i + k * 2) % ladSize, 1));
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

    QVector<int> rhythmMelody;
    for (int i = 0; i < accSize / 8; ++i)
    {
        barPos = 0;
        while (barPos < 8)
        {
            int temp;
            do
                temp = pow(2, (rand() % (30 - 9) / 10));
            while (temp + barPos > 8);
            barPos += temp;
            rhythmMelody.push_back(temp);
        }
    }
    qDebug() << rhythmMelody;

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
        for (int j: rhythmMelody)
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
                    p[1][bar].push_back(Note(j,(i + (rand() % (ladSize / 2)) * 2) % ladSize, 0));
                else
                {
                    int temp;
                    QVector<int> tempV = acc[getPosAcc];
                    tempV.removeFirst();
                    do
                    {
                        temp = rand() % ladSize;
                    }
                    while((tempV.contains(temp % ladSize == 0 ? ladSize : temp % ladSize)) ||
                          (tempV.contains((temp + 2) % ladSize)));
                    p[1][bar].push_back(Note(j, (i + temp) % ladSize, 0));
                }
            }
            else
                p[1][bar].push_back(Note(j, rand() % ladSize, 0));
            barPos+=j;
        }
    }
    p[1][getCountBars() - 1][getCountNote(1, getCountBars() - 1) - 1].degree = 0;
}
