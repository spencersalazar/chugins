
public class GeneralMidi extends Chubgraph
{
    AudioUnit.list();
    // setup patch
    AudioUnit au => outlet;
    // open General MIDI synth
    au.open("DLSMusicDevice");
    
    setProgram(0);
    
    fun void send(int a, int b, int c)
    {
        au.send(a, b, c);
    }
    
    fun void setProgram(int p, int c)
    {
        // set program (voice)
        au.send(0xC0 | c, p, 0);
    }
    
    fun void setProgram(int p)
    {
        // set program (voice)
        for(int c; c < 16; c++)
            au.send(0xC0 | c, p, 0);
    }
    
    fun void noteOn(int note, int velocity)
    {
        au.send(0x90, note, velocity);
    }
    
    fun void noteOff(int note)
    {
        au.send(0x80, note, 0);
    }
}
