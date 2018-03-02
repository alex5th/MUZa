#ifndef OUTPUT_H
#define OUTPUT_H

#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
#include <QDate>
#include <QMap>
#include <QDir>
#include <song.h>

class Output
{
    QXmlStreamWriter stream;
    QStringList steps;
    QFile file;
    Song song;
    int tonic;
    int tempo;
public:
    Output(const Song &s, const QList<int> &lad, const int &tonic, const int &tempo);
    void instrument(const int &p, const QString &n);
    void createPart(const int &p);
    QString getFileName();
};

#endif // OUTPUT_H
