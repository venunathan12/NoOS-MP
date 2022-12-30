#define bool unsigned char
#define true 1
#define false 0

#define CONFIG_SIZE_AUTO -1
#define CONFIG_externalDataLoadMethod_AsParam 0x0000
#define CONFIG_externalDataLoadMethod_ByPointerReplacement 0x1000

struct Config
{
    unsigned int numThreads;
    unsigned int mainBytesSize;
    unsigned int externalDataSize;
    unsigned char redirectOutput;
    unsigned char redirectInput;
    unsigned int externalDataLoadMethod;
    unsigned int externalDataLoadReplacementPointerCount;
    unsigned long externalDataLoadReplacementPointerValue;
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
        unsigned long (*memset)();
        unsigned long (*memcpy)();
    };
    struct System_Mem *mem;

    struct System_IO
    {
        unsigned int (*log)();
        unsigned long (*scan)();
        void (*output)();
        void (*input)();
    };
    struct System_IO *io;

    struct System_Misc
    {
        unsigned long (*stall)();
    };
    struct System_Misc *misc;

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
