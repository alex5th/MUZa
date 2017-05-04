#include "rest.h"

Rest::Rest()
{

}

void Rest::basic(int d)
{
    dot = false;
    if (d == 1 || d==2 || d==4 || d==8)
        duration = d;
    else
    {
        duration = d / 3 * 2;
        dot = true;
    }
}

Rest::Rest(int d)
{
    basic(d);
}
