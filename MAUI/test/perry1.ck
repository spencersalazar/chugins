MAUI_View myWinder;
MAUI_Button butt;
butt.name("BUTT!");
myWinder.addElement(butt);
myWinder.display();
while (butt.state()==0)  {
    0.01 :: second => now;
}
myWinder.destroy();
