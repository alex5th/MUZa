#ifndef OUTPUT_H
#define OUTPUT_H

#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
class Output
{
    QXmlStreamWriter stream;
public:
    Output();
    void instrument(QString p, QString n, int m);
    void createPart(QString p);
};

#endif // OUTPUT_H
