
GLine g => GGen.fbd();
g.position(0, 0, 0);
g.color(1, 1, 1, 1);

0.25 => float freq;
1 => float tick;

while(true)
{
    now / second => float phase;
    g.endpoint(Math.sin(2*pi*phase*freq), Math.cos(2*pi*phase*freq), 0);
    
    if(phase > tick)
    {
        1 +=> tick;
        GLine c => g;
        Math.random2f(0,2*pi) => float theta;
        0.2 => float radius;
        c.position(0, 0, 0);
        c.color(1, 0.25, 0.33, 1);
        c.endpoint(radius*Math.cos(theta), radius*Math.sin(theta), 0);
    }
    
    2::ms => now;
}

 