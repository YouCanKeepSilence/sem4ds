#ifndef TOOLS_H
#define TOOLS_H
namespace Tools {
    enum States
    {
        zero=0,//[0,255]
        one,//[256,511]
        two,//[512,1023]
        three,//[1024,2047]
        four,//[2048,4095]
        five,//[4096,8191]
        six,//[8192,16383]
        seven,//[16384,32767]
        eight //[32768,65535]
    };
}


#endif // TOOLS_H
