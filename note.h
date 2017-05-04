#ifndef NOTE_H
#define NOTE_H
#include <rest.h>

class Note : public Rest
{
    int degree;
    bool chord;
public:
    Note(int d, int n, bool ch);
};

#endif // NOTE_H
