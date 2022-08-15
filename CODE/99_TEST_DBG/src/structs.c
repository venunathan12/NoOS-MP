#define bool unsigned char
#define true 1
#define false 0

struct Config
{
    unsigned int numThreads;
    unsigned int mainBytesSize;
    unsigned int externalDataSize;
    unsigned char redirectOutput;
    unsigned char redirectInput;
};
typedef struct Config Config;

struct ThreadInfo
{
    unsigned int threadIdx;
    unsigned int threadNum;
};
typedef struct ThreadInfo ThreadInfo;

struct System
{
    struct System_Mem
    {
        unsigned long (*malloc)();
        unsigned long (*free)();
    };
    struct System_Mem *mem;

    struct System_IO
    {
        unsigned int (*log)();
        unsigned long (*scan)();
    };
    struct System_IO *io;

    struct System_Efi
    {

    };
    struct System_Efi *efi;
};
typedef struct System System;

struct InputKey
{
    unsigned short scanCode;
    unsigned short charCode;
};
typedef struct InputKey InputKey;

// Custom
struct Data
{
    unsigned short text0[32];
    unsigned short text1[32];
    unsigned long field[4];
};
typedef struct Data Data;
