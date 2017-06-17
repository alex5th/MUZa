#ifndef NOTE_H
#define NOTE_H

#include <QDebug>

struct Note
{
    int degree;
    bool chord;
    int duration;
    bool dot;
    Note();
    Note(int d, int n, bool ch);
};

#endif // NOTE_H
