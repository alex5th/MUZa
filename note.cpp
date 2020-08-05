#include "note.h"

Note::Note()
{

}

Note::Note(const int &d, const int &n, const bool &ch):m_degree(n), m_chord(ch), m_duration(d)
{
    m_dot = (d == 6) || (d == 3) ? true : false;
}
