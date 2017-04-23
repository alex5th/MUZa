#ifndef NOTE_H
#define NOTE_H
#include <rest.h>
#include <QString>

class Note : public Rest
{
    QString degree;
    int octave;
    bool chord;
public:
    Note();
};

#endif // NOTE_H
