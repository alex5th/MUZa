#include "output.h"

void Output::instrument(int p, QString n, int m)
{
    stream.writeStartElement("score-part");
    stream.writeAttribute("id", "P" + QString::number(p));
    stream.writeTextElement("part-name", n);
    stream.writeTextElement("part-abbreviation", QString(n[0]));
    stream.writeStartElement("midi-instrument");
    stream.writeAttribute("id", "P" + QString::number(p));
    stream.writeTextElement("midi-channel", "1");
    stream.writeTextElement("midi-program", QString::number(m));
    stream.writeEndElement();
    stream.writeEndElement();
}

void Output::createPart(int p)
{
    stream.writeStartElement("part");
    stream.writeAttribute("id", "P" + QString::number(p));
    for(int i = 0; i < song.getCountBars(); ++i)
    {
        stream.writeStartElement("measure");
        stream.writeAttribute("number", QString::number(i));
        if (i == 0)
        {
            stream.writeStartElement("attributes");
            stream.writeTextElement("divisions", "2");
            stream.writeStartElement("time");
            stream.writeTextElement("beats", "4");
            stream.writeTextElement("beat-type", "4");
            stream.writeEndElement();
            stream.writeStartElement("clef");
            stream.writeTextElement("sign", "G");
            stream.writeTextElement("line", "2");
            stream.writeEndElement();
            stream.writeEndElement();
            if (p == 0)
            {
                stream.writeStartElement("direction");
                stream.writeStartElement("direction-type");
                stream.writeStartElement("metronome");
                stream.writeTextElement("beat-unit", "quarter");
                stream.writeTextElement("per-minute", QString::number(tempo));
                stream.writeEndElement();
                stream.writeEndElement();
                stream.writeStartElement("sound");
                stream.writeAttribute("tempo", QString::number(tempo));
                stream.writeEndElement();
                stream.writeEndElement();
            }
        }
        //тут вставляешь ноты
        for (int j = 0; j < song.getCountNote(p, i); ++j)
        {
            qDebug() << (song(0,i,j).degree + tonic) % 12;
            stream.writeStartElement("note");
            if (song(0,i,j).chord)
            {
                stream.writeStartElement("chord");
                stream.writeEndElement();
            }
            stream.writeStartElement("pitch");
            stream.writeTextElement("step", "A");
            stream.writeTextElement("octave", "3");
            stream.writeEndElement();
            stream.writeTextElement("duration", QString::number(song(0,i,j).duration));
            stream.writeTextElement("type", "quarter");
            if (song(0,i,j).dot)
            {
                stream.writeStartElement("dot");
                stream.writeEndElement();
            }
            stream.writeEndElement();
        }

        stream.writeEndElement();
    }
    stream.writeEndElement();
}

Output::Output(Song s, int tonic, int tempo):song(s), tonic(tonic), tempo(tempo)
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

        instrument(0,"Rhythm",1);
        instrument(1,"Melody",75);

        stream.writeEndElement();

        createPart(0);
        createPart(1);


        stream.writeEndDocument();
        file.close();
    }

}
