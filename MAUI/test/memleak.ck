
while(true)
{
    MAUI_View myWinder;
    MAUI_Button butt;
    butt.name("BUTT!");
    myWinder.addElement(butt);
    myWinder.display();
    0.25 :: second => now;
    myWinder.destroy();
    0.25 :: second => now;
}
