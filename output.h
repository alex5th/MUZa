#ifndef OUTPUT_H
#define OUTPUT_H

#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
#include <QDate>
#include <song.h>

class Output
{
    QXmlStreamWriter stream;
    int countBars;
    int tempo;
public:
    Output(Song s, int tonic, int tempo);
    void instrument(int p, QString n, int m);
    void createPart(int p);
};

#endif // OUTPUT_H
