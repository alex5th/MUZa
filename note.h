#ifndef NOTE_H
#define NOTE_H

#include <QDebug>

struct Note
{
    int m_degree;
    bool m_chord;
    int m_duration;
    bool m_dot;
    Note();
    Note(const int &d, const int &n, const bool &ch);
};

#endif // NOTE_H
