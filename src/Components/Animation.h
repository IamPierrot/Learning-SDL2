#pragma once

struct Animation
{
     int index;
     int frames;
     int delay;


     Animation() {}
     Animation(int i, int f, int d) : index(i), frames(f), delay(d)
     {    
     }
};
