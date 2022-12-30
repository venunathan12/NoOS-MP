#include <noOSMP_structs.h>

#define NUM_THREADS 8

struct Data
{

};
typedef struct Data Data;

Config config;
Data data =
{

};

void process_main(ThreadInfo *threadInfo, System *system, Data *data)
{
    unsigned int id = threadInfo->threadIdx;
    unsigned short idS[2];

    idS[0] = '0' + id; idS[1] = 0;

    system->misc->stall(2000000 * id);
    system->io->log(idS);
    
    while (true);
}

void process_setup()
{
    config.numThreads = NUM_THREADS;
    config.mainBytesSize = CONFIG_SIZE_AUTO;
    config.externalDataSize = CONFIG_SIZE_AUTO;
    config.redirectOutput = false;
    config.redirectInput = false;
    config.externalDataLoadMethod = CONFIG_externalDataLoadMethod_AsParam;
}

#include <noOSMP_finalize.c>
