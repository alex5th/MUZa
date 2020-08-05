#include "output.h"

QString Output::getFileName()
{
    return m_file.fileName().remove("files/");
}

void Output::createInstrument(const int &numInstrument, const QString &name)
{
    m_stream.writeStartElement("score-part");
    m_stream.writeAttribute("id", "P" + QString::number(numInstrument));
    m_stream.writeTextElement("part-name", name);
    m_stream.writeTextElement("part-abbreviation", QString(name[0]));
    m_stream.writeStartElement("midi-instrument");
    m_stream.writeAttribute("id", "P" + QString::number(numInstrument));
    m_stream.writeTextElement("midi-channel", "1");
    m_stream.writeTextElement("midi-program", "1");
    m_stream.writeEndElement();
    m_stream.writeEndElement();
}

void Output::createPart(const int &part)
{
    m_stream.writeStartElement("part");
    m_stream.writeAttribute("id", "P" + QString::number(part));
    for(int i = 0; i < m_song.getCountBars(); ++i)
    {
        m_stream.writeStartElement("measure");
        m_stream.writeAttribute("number", QString::number(i));
        if (i == 0)
        {
            //общие данные по песне
            m_stream.writeStartElement("attributes");
            m_stream.writeTextElement("divisions", "2");
            m_stream.writeStartElement("time");
            m_stream.writeTextElement("beats", "4");
            m_stream.writeTextElement("beat-type", "4");
            m_stream.writeEndElement();
            m_stream.writeStartElement("clef");
            m_stream.writeTextElement("sign", (part == 0) ? "F" : "G");
            m_stream.writeTextElement("line", (part == 0) ? "4" : "2");
            m_stream.writeEndElement();
            m_stream.writeEndElement();
            if (part == 1)
            {
                m_stream.writeStartElement("direction");
                m_stream.writeStartElement("direction-type");
                m_stream.writeStartElement("metronome");
                m_stream.writeTextElement("beat-unit", "quarter");
                m_stream.writeTextElement("per-minute", QString::number(m_tempo));
                m_stream.writeEndElement();
                m_stream.writeEndElement();
                m_stream.writeStartElement("sound");
                m_stream.writeAttribute("tempo", QString::number(m_tempo));
                m_stream.writeEndElement();
                m_stream.writeEndElement();
            }
        }
        //тут вставляешь ноты
        for (int j = 0; j < m_song.getCountNote(part, i); ++j)
        {            m_stream.writeStartElement("note");
            if (m_song(part, i, j).m_chord)
            {
                m_stream.writeStartElement("chord");
                m_stream.writeEndElement();
            }
            m_stream.writeStartElement("pitch");
            m_stream.writeTextElement("step", m_steps[m_song(part, i, j).m_degree].left(1));
            if (m_steps[m_song(part, i, j).m_degree].size() > 1)
                m_stream.writeTextElement("alter", m_steps[m_song(part, i, j).m_degree].right(2));
            m_stream.writeTextElement("octave", QString::number(part + 3));
            m_stream.writeEndElement();
            m_stream.writeTextElement("duration", QString::number(m_song(part, i, j).m_duration));
            QString type;
            if (m_song(part, i, j).m_duration == 1) type = "eighth";
            if (m_song(part, i, j).m_duration == 2 || m_song(part, i, j).m_duration == 3) type = "quarter";
            if (m_song(part, i, j).m_duration == 4 || m_song(part, i, j).m_duration == 6) type = "half";
            if (m_song(part, i, j).m_duration == 8) type = "whole";
            m_stream.writeTextElement("type", type);
            if (m_song(part, i, j).m_dot)
            {
                m_stream.writeStartElement("dot");
                m_stream.writeEndElement();
            }
            m_stream.writeEndElement();
        }
        m_stream.writeEndElement();
    }
    m_stream.writeEndElement();
}

Output::Output(const Song &song, const QList<int> &lad, const int &tonic, const int &tempo)
    :m_song(song), m_tonic(tonic), m_tempo(tempo)
{
    //steps for current song
    int tmp_absolutNote = 0;
    for(int i: lad)
    {
        int tmp_currentNote = (tonic + tmp_absolutNote) % 12;
        if (tmp_currentNote == 0) m_steps.push_back("C");
        if (tmp_currentNote == 1) m_steps.push_back("C+1");
        if (tmp_currentNote == 2) m_steps.push_back("D");
        if (tmp_currentNote == 3) m_steps.push_back("D+1");
        if (tmp_currentNote == 4) m_steps.push_back("E");
        if (tmp_currentNote == 5) m_steps.push_back("F");
        if (tmp_currentNote == 6) m_steps.push_back("F+1");
        if (tmp_currentNote == 7) m_steps.push_back("G");
        if (tmp_currentNote == 8) m_steps.push_back("G+1");
        if (tmp_currentNote == 9) m_steps.push_back("A");
        if (tmp_currentNote == 10) m_steps.push_back("A+1");
        if (tmp_currentNote == 11) m_steps.push_back("B");
        tmp_absolutNote += i;
    }

    QDir().mkdir("files");
    int tmp_fileNumber = 0;
    do
    {
        m_file.setFileName("files/song" + QString::number(tmp_fileNumber) + ".xml");
        ++tmp_fileNumber;
    }
    while (m_file.exists());

    //write stream for MusicXML
    if(m_file.open(QIODevice::WriteOnly))
    {
        m_stream.setDevice(&m_file);
        m_stream.setAutoFormatting(true);
        m_stream.writeStartDocument();
        m_stream.writeStartElement("score-partwise");
        m_stream.writeAttribute("version", "2.0");
        m_stream.writeStartElement("identification");
        m_stream.writeStartElement("encoding");
        m_stream.writeTextElement("encoding-date", QDate::currentDate().toString("yyyy-MM-dd"));
        m_stream.writeTextElement("software", "МУЗа");
        m_stream.writeEndElement();
        m_stream.writeEndElement();

        m_stream.writeStartElement("part-list");

        createInstrument(1,"Melody");
        createInstrument(0,"Rhythm");

        m_stream.writeEndElement();

        createPart(1);
        createPart(0);

        m_stream.writeEndDocument();
        m_file.close();
    }
}
