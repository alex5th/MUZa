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
    QXmlStreamWriter m_stream;
    QStringList m_steps;
    QFile m_file;
    Song m_song;
    int m_tonic;
    int m_tempo;
public:
    Output(const Song &song, const QList<int> &lad, const int &tonic, const int &tempo);
    void createInstrument(const int &numInstrument, const QString &name);
    void createPart(const int &part);
    QString getFileName();
};

#endif // OUTPUT_H
