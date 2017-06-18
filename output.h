#ifndef OUTPUT_H
#define OUTPUT_H

#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
#include <QDate>
#include <QMap>
#include <song.h>
#include <dir.h>

class Output
{
    QXmlStreamWriter stream;
    QStringList steps;
    QFile file;
    Song song;
    int tonic;
    int tempo;
public:
    Output(Song s, QList<int> lad, int tonic, int tempo);
    void instrument(int p, QString n);
    void createPart(int p);
    QString getFileName();
};

#endif // OUTPUT_H
