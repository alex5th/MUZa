#ifndef OUTPUT_H
#define OUTPUT_H

#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
#include <QDate>
#include <QMap>
#include <song.h>

class Output
{
    QXmlStreamWriter stream;
    QStringList steps;
    Song song;
    int tonic;
    int tempo;
public:
    Output(Song s, QVector<int> lad, int tonic, int tempo);
    void instrument(int p, QString n, int m);
    void createPart(int p);
};

#endif // OUTPUT_H
