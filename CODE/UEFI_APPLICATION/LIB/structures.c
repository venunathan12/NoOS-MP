#define CONFIG_SIZE_AUTO -1
#define CONFIG_externalDataLoadMethod_AsParam 0x0000
#define CONFIG_externalDataLoadMethod_ByPointerReplacement 0x1000

struct Config
{
    UINT32 numThreads;
    UINT32 mainBytesSize;
    UINT32 externalDataSize;
    BOOLEAN redirectOutput;
    BOOLEAN redirectInput;
    UINT32 externalDataLoadMethod;
    UINT32 externalDataLoadReplacementPointerCount;
    UINT64 externalDataLoadReplacementPointerValue;
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
        UINT64 (*memset)();
        UINT64 (*memcpy)();
    };
    struct System_Mem *mem;

    struct System_IO
    {
        UINTN (*log)();
        UINT64 (*scan)();
        void (*output)();
        void (*input)();
    };
    struct System_IO *io;

    struct System_Misc
    {
        UINT64 (*stall)();
    };
    struct System_Misc *misc;

    struct System_Efi
    {
        EFI_SYSTEM_TABLE *efiSystemTable;
        EFI_HANDLE *efiImageHandle;

        struct System_Efi_Callers
        {
            UINT64 (*call0)();
            UINT64 (*call1)();
            UINT64 (*call2)();
            UINT64 (*call3)();
            UINT64 (*call4)();
            UINT64 (*call5)();
            UINT64 (*call6)();
            UINT64 (*call7)();
            UINT64 (*call8)();
            UINT64 (*call9)();
            UINT64 (*call10)();
        };
        struct System_Efi_Callers *efiCallers;
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