#include "note.h"

Note::Note()
{

}

Note::Note(const int &d, const int &n, const bool &ch):degree(n), chord(ch), duration(d)
{
    dot = (d == 6) || (d == 3) ? true : false;
}
