#ifndef MINECRAFTLEVEL_H
#define MINECRAFTLEVEL_H

class MinecraftLevel
{
public:
    virtual int width() = 0;
    virtual int height() = 0;
    virtual int length() = 0;

    virtual char block(int x, int y, int z) = 0;
};

#endif // MINECRAFTLEVEL_H
