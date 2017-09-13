#include "output.h"

QString Output::getFileName()
{
    return file.fileName().remove("files/");
}

void Output::instrument(int p, QString n)
{
    stream.writeStartElement("score-part");
    stream.writeAttribute("id", "P" + QString::number(p));
    stream.writeTextElement("part-name", n);
    stream.writeTextElement("part-abbreviation", QString(n[0]));
    stream.writeStartElement("midi-instrument");
    stream.writeAttribute("id", "P" + QString::number(p));
    stream.writeTextElement("midi-channel", "1");
    stream.writeTextElement("midi-program", "1");
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
            if (p == 0)
            {
                stream.writeTextElement("sign", "F");
                stream.writeTextElement("line", "4");
            }
            else
            {
                stream.writeTextElement("sign", "G");
                stream.writeTextElement("line", "2");
            }
            stream.writeEndElement();
            stream.writeEndElement();
            if (p == 1)
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
        {            stream.writeStartElement("note");
            if (song(p,i,j).chord)
            {
                stream.writeStartElement("chord");
                stream.writeEndElement();
            }
            stream.writeStartElement("pitch");
            stream.writeTextElement("step", steps[song(p,i,j).degree].left(1));
            if (steps[song(p,i,j).degree].size() > 1)
                stream.writeTextElement("alter", steps[song(p,i,j).degree].right(2));
            stream.writeTextElement("octave", QString::number(p + 3));
            stream.writeEndElement();
            stream.writeTextElement("duration", QString::number(song(p,i,j).duration));
            QString type;
            if (song(p,i,j).duration == 1) type = "eighth";
            if (song(p,i,j).duration == 2 || song(p,i,j).duration == 3) type = "quarter";
            if (song(p,i,j).duration == 4 || song(p,i,j).duration == 6) type = "half";
            if (song(p,i,j).duration == 8) type = "whole";
            stream.writeTextElement("type", type);
            if (song(p,i,j).dot)
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

Output::Output(Song s, QList<int> lad, int tonic, int tempo):song(s), tonic(tonic), tempo(tempo)
{
    int tonToCur = 0;
    for(int i: lad)
    {
        int temp = (tonic + tonToCur) % 12;
        if (temp == 0) steps.push_back("C");
        if (temp == 1) steps.push_back("C+1");
        if (temp == 2) steps.push_back("D");
        if (temp == 3) steps.push_back("D+1");
        if (temp == 4) steps.push_back("E");
        if (temp == 5) steps.push_back("F");
        if (temp == 6) steps.push_back("F+1");
        if (temp == 7) steps.push_back("G");
        if (temp == 8) steps.push_back("G+1");
        if (temp == 9) steps.push_back("A");
        if (temp == 10) steps.push_back("A+1");
        if (temp == 11) steps.push_back("B");
        tonToCur += i;
    }

    mkdir("files");
    int fileNumber = 0;
    do
    {
        file.setFileName("files/song" + QString::number(fileNumber) + ".xml");
        ++fileNumber;
    }
    while (file.exists());

    if(file.open(QIODevice::WriteOnly))
    {
        stream.setDevice(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("score-partwise");
        stream.writeAttribute("version", "2.0");
        stream.writeStartElement("identification");
        stream.writeStartElement("encoding");
        stream.writeTextElement("encoding-date", QDate::currentDate().toString("yyyy-MM-dd"));
        stream.writeTextElement("software", "МУЗа");
        stream.writeEndElement();
        stream.writeEndElement();

        stream.writeStartElement("part-list");

        instrument(1,"Melody");
        instrument(0,"Rhythm");

        stream.writeEndElement();

        createPart(1);
        createPart(0);

        stream.writeEndDocument();
        file.close();
    }
}
