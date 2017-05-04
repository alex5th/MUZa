#include "note.h"
#include <QDebug>

Note::Note(int d, int n, bool ch):degree(n), chord(ch)
{
    basic(d);
    qDebug() << degree << chord;
}
