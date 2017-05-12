#include "note.h"

Note::Note()
{

}

Note::Note(int d, int n, bool ch):degree(n), chord(ch)
{
    dot = false;
    if (d == 1 || d==2 || d==4 || d==8)
        duration = d;
    else
    {
        duration = d / 3 * 2;
        dot = true;
    }
    qDebug() << degree << chord << duration;
}
