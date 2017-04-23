#include "output.h"
#include <QDate>

void Output::instrument(QString p, QString n, int m)
{
    stream.writeStartElement("score-part");
    stream.writeAttribute("id", p);
    stream.writeTextElement("part-name", n);
    stream.writeTextElement("part-abbreviation", QString(n[0]));
    stream.writeStartElement("midi-instrument");
    stream.writeAttribute("id", p);
    stream.writeTextElement("midi-channel", "1");
    stream.writeTextElement("midi-program", QString::number(m));
    stream.writeEndElement();
    stream.writeEndElement();
}

void Output::createPart(QString p)
{
    stream.writeStartElement("part");
    stream.writeAttribute("id", p);
    stream.writeStartElement("measure");
    stream.writeAttribute("number", "0");
    stream.writeEndElement();
    stream.writeEndElement();
}

Output::Output()
{
    QFile file("song.xml");
    if(file.open(QIODevice::WriteOnly)) {
        stream.setDevice(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("score-partwise");
        stream.writeAttribute("version", "2.0");
        stream.writeStartElement("identification");
        stream.writeStartElement("encoding");
        stream.writeTextElement("encoding-date", QDate::currentDate().toString("yyyy-MM-dd"));
        stream.writeTextElement("software", "Генератор хитов 3000");
        stream.writeEndElement();
        stream.writeEndElement();

        stream.writeStartElement("part-list");

        instrument("P0","Rhythm",1);
        instrument("P1","Melody",75);

        stream.writeEndElement();

        createPart("P0");
        createPart("P1");


        stream.writeEndDocument();
        file.close();
    }

}
