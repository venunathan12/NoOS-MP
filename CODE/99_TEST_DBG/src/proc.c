#include <stdio.h>

#include "structs.c"

void process_main(ThreadInfo *threadInfo, System *system, Data *data)
{
    if (threadInfo->threadIdx == 1)
    {
        unsigned short msg[5];
        msg[0] = 'H'; msg[1] = 'i'; msg[2] = '1'; msg[3] = '\n'; msg[4] = '\0';
        system->io->log(msg);
        system->io->log(data->text0, 1, 2, 3);
    }

    if (threadInfo->threadIdx == 0)
    {
        while (true)
        {
            InputKey Key;
            while(system->io->scan(&Key));
            system->io->log(data->text1, Key.charCode);
            system->io->log(data->text0, data->field[1], data->field[2], data->field[3]);
        }
    }
    else
    {
        while (true)
            data->field[threadInfo->threadIdx] += 4;
    }
}
void nop(){}

Config config =
{
    4,
    0,
    0,
    false,
    false
};

Data data =
{
    L"%d %d %d\n",
    L"Char code %d\n",
    {0, 1, 2, 3}
};

int main()
{
    FILE *mainFile, *configFile, *dataFile;

    mainFile = fopen("files/main.bin", "wb");
    fwrite(process_main, 1, (char *) nop - (char *) process_main, mainFile);
    fclose(mainFile);

    config.mainBytesSize = (char *) nop - (char *) process_main;
    config.externalDataSize = sizeof(Data);

    configFile = fopen("files/config.bin", "wb");
    fwrite(&config, 1, sizeof(Config), configFile);
    fclose(configFile);

    dataFile = fopen("files/data.bin", "wb");
    fwrite(&data, 1, sizeof(Data), dataFile);
    fclose(dataFile);

    return 0;
}