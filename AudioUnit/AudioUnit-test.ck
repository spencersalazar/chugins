MAUI_Slider slider;
slider.display();

// synchronize to period
1.25::second => dur T;
T - (now % T) => now;

// list available AUs
AudioUnit.list() @=> string aus[];

//while(true) { 1::second => now; }

for(int i; i < aus.cap(); i++)
{
    chout <= aus[i] <= IO.newline();
}

// setup patch
AudioUnit au => NRev reverb => dac;
// open General MIDI synth
//au.open("DLSMusaicDevice");
au.open("Massive");
// set reverb
0.1 => reverb.mix;
// display UI
au.display();

// set program (voice)
if(me.args())
    au.send(0xC0, Std.atoi(me.arg(0))-1, 0);

// scale (from otf_06.ck)
[ 0, 2, 4, 7, 9 ] @=> int scale[];

while(true)
{
    34 + Math.random2(0,1)*12 + scale[Math.random2(0,4)] => int note;
    // noteOn
    au.send(0x90, note, 127);
    
    if( Math.randomf() > .25 ) .25::T => now;
    else .5::T => now;
    
    // noteOff
    au.send(0x80, note, 0);
}
