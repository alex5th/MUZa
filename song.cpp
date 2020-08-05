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

QVector<QVector<int>> Song::generateAccomp()
{
    QVector<QVector<int>> res;
    for (int i = 0; i < rand() % 2 + 1; ++i)
    {
        int tmp_currentPosInBar = 0;
        while (tmp_currentPosInBar < 8)
        {
            int tmp_lengthNote;
            QVector<int> tmp_resVector;
            do
            {
                int tmp_rand = rand() % 5;
                if (tmp_rand) tmp_lengthNote = pow(2, rand() % 3);
                else tmp_lengthNote = 3 * (rand() % 2 + 1);
            }
            while (tmp_lengthNote + tmp_currentPosInBar > 8);
            tmp_currentPosInBar += tmp_lengthNote;
            tmp_resVector.push_back(tmp_lengthNote);
            for (int j = 1; j <= 5; j += 2)
            {
                int tmp_rand = rand() % 3;
                if (!tmp_rand) tmp_resVector.push_back(j);
            }
            res.push_back(tmp_resVector);
        }
    }
    return res;
}


Song::Song(int ladSize, QVector<QVector<int>> accomp, int lengthAcc)
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
    if (accomp.isEmpty()) accomp = generateAccomp();
    qDebug() << accomp;

    for (auto i: accomp)
        accSize += i[0];
    p[0].resize(accSize / 8 * lengthAcc);
    p[1].resize(p[0].size());

    int tmp_currentPosInBar = 0;
    int tmp_currentBar = 0;
    for (int i: chords)
    {
        for (auto j: accomp)
        {
            if (tmp_currentPosInBar == 8)
            {
                tmp_currentBar++;
                tmp_currentPosInBar = 0;
            }
            if (j.size() == 1)
            {
                //поиграть потом с рандомностью и флажок, после попадания с 0 на 1
                p[0][tmp_currentBar].push_back(Note(j[0], (i) % ladSize, 0));
                for (int k = 1; k < ladSize / 2; ++k)
                    p[0][tmp_currentBar].push_back(Note(j[0], (i + k * 2) % ladSize, 1));
            }
            else
                for (int k = 1; k < j.size(); ++k)
                {
                    bool ch = true;
                    if (k == 1) ch = false;
                    p[0][tmp_currentBar].push_back(Note(j[0], (i + j[k] - 1) % ladSize, ch));

                }
            tmp_currentPosInBar+=j[0];
        }
    }

    //create rhyth of Melody
    QVector<int> rhythmMelody;
    for (int i = 0; i < accSize / 8; ++i)
    {
        tmp_currentPosInBar = 0;
        while (tmp_currentPosInBar < 8)
        {
            int tmp_lengthNote;
            do
                tmp_lengthNote = pow(2, (rand() % (30 - 9) / 10));
            while (tmp_lengthNote + tmp_currentPosInBar > 8);
            tmp_currentPosInBar += tmp_lengthNote;
            rhythmMelody.push_back(tmp_lengthNote);
        }
    }
    qDebug() << rhythmMelody;

    tmp_currentPosInBar = 0;
    for (auto &i: accomp)
    {
        int temp = tmp_currentPosInBar;
        tmp_currentPosInBar += i[0];
        i[0] = temp;
    }

    tmp_currentPosInBar = 0;
    tmp_currentBar = 0;
    for (int i: chords)
    {
        int getPosAcc = 0;
        for (int j: rhythmMelody)
        {
            if (tmp_currentPosInBar == 8)
            {
                tmp_currentBar++;
                tmp_currentPosInBar = 0;
            }

            bool flag = false;
            for (int k = getPosAcc; k < accomp.size(); ++k)
            {
                if ((tmp_currentBar * 8 + tmp_currentPosInBar) % accSize == accomp[k][0])
                {
                    flag = true;
                    getPosAcc = k;
                    break;
                }
            }
            if (flag)
            {
                if (accomp[getPosAcc].size() == 1)
                    p[1][tmp_currentBar].push_back(Note(j,(i + (rand() % (ladSize / 2)) * 2) % ladSize, 0));
                else
                {
                    int temp;
                    QVector<int> tempV = accomp[getPosAcc];
                    tempV.removeFirst();
                    do
                    {
                        temp = rand() % ladSize;
                    }
                    while((tempV.contains(temp % ladSize == 0 ? ladSize : temp % ladSize)) ||
                          (tempV.contains((temp + 2) % ladSize)));
                    p[1][tmp_currentBar].push_back(Note(j, (i + temp) % ladSize, 0));
                }
            }
            else
                p[1][tmp_currentBar].push_back(Note(j, rand() % ladSize, 0));
            tmp_currentPosInBar+=j;
        }
    }
    p[1][getCountBars() - 1][getCountNote(1, getCountBars() - 1) - 1].m_degree = 0;
}
