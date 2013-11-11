
NRev reverb => dac;
0.01 => reverb.mix;

57 => int voice;

MidiFileIn min;
MidiMsg msg;

string filename;
if(me.args() == 0)
    me.sourceDir() + "/bwv772.mid" => filename;
else
    me.arg(0) => filename;

if(!min.open(filename))
{
    cherr <= "unable to open MIDI file: '" <= filename <= "'\n";
    me.exit();
}

chout <= filename <= ": " <= min.numTracks() <= " tracks\n";

int done;

for(int t; t < min.numTracks(); t++)
    spork ~ track(t);

while(done < min.numTracks())
    1::second => now;

min.close();

fun void track(int t)
{
    GeneralMidi m => reverb;
    m.setProgram(voice);
    
    while(min.read(msg, t))
    {
        if(msg.when > 0::second)
            msg.when => now;
        
        if((msg.data1 & 0xC0) != 0xC0) // skip program change
            m.send(msg.data1, msg.data2, msg.data3);
    }
    
    done++;
}
