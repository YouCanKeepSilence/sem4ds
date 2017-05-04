#ifndef TOOLS_H
#define TOOLS_H
namespace Tools {
    enum States
    {
        first=0,//[0,255]
        second,//[256,1023]
        third,//[1024,2047]
        fourth,//[2048,4095]
        fifth,//[4096,8191]
        sixth,//[8192,16383]
        seventh,//[16384,32767]
        eight//[32768,65535]
    };
}


#endif // TOOLS_H
