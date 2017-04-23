#ifndef PART_H
#define PART_H
#include <measure.h>
#include <QVector>

class Part
{
    QVector<Measure> m;
    int tempo;
public:
    Part();
};

#endif // PART_H
