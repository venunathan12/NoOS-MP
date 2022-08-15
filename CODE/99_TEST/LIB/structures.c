struct Config
{
    UINT32 numThreads;
    UINT32 mainBytesSize;
    UINT32 externalDataSize;
    BOOLEAN redirectOutput;
    BOOLEAN redirectInput;
};
typedef struct Config Config;

struct ThreadInfo
{
    UINT32 threadIdx;
    UINT32 threadNum;
};
typedef struct ThreadInfo ThreadInfo;

struct System
{
    struct System_Mem
    {
        UINT64 (*malloc)();
        UINT64 (*free)();
    };
    struct System_Mem *mem;

    struct System_IO
    {
        UINTN (*log)();
        UINT64 (*scan)();
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
    UINT16 scanCode;
    UINT16 charCode;
};
typedef struct InputKey InputKey;