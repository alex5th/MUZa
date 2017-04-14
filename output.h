#ifndef OUTPUT_H
#define OUTPUT_H

#include <QXmlStreamWriter>
#include <QFile>
#include <QString>
class output
{
    QXmlStreamWriter stream;
public:
    output();
    void instrument(QString p, QString n, int m);
};

#endif // OUTPUT_H
