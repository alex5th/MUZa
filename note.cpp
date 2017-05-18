#include "note.h"

Note::Note()
{

}

Note::Note(int d, int n, bool ch):degree(n), chord(ch), duration(d)
{
    dot = (d == 6) || (d == 3) ? true : false;
}
