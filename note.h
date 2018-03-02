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
    Note(const int &d, const int &n, const bool &ch);
};

#endif // NOTE_H
