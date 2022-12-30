#include <stdio.h>

int main()
{
    bool success = true;
    FILE *mainFile = NULL, *configFile = NULL, *dataFile = NULL;

    mainFile = fopen("files/main.bin", "wb");
    configFile = fopen("files/config.bin", "wb");
    if (sizeof(Data) > 0) dataFile = fopen("files/data.bin", "wb");

    if (mainFile == NULL)
    {
        success = false;
        printf("[ERROR] Could not create file files/main.bin\n");
    }
    if (configFile == NULL)
    {
        success = false;
        printf("[ERROR] Could not create file files/config.bin\n");
    }
    if (dataFile == NULL && sizeof(Data) > 0)
    {
        success = false;
        printf("[ERROR] Could not create file files/data.bin\n");
    }
    if (! success) return -1;

    process_setup();

    fwrite(process_main, 1, (char *) process_setup - (char *) process_main, mainFile), fclose(mainFile);

    if (config.mainBytesSize == CONFIG_SIZE_AUTO)
        config.mainBytesSize = (char *) process_setup - (char *) process_main;
    if (config.externalDataSize == CONFIG_SIZE_AUTO)
        config.externalDataSize = sizeof(Data);

    fwrite(&config, 1, sizeof(Config), configFile), fclose(configFile);

    if (sizeof(Data) > 0) fwrite(&data, 1, sizeof(Data), dataFile), fclose(dataFile);

    if (config.externalDataLoadMethod == CONFIG_externalDataLoadMethod_ByPointerReplacement)
    {
        unsigned int addrSignaturesSeen = 0;
        unsigned long addrSignature = config.externalDataLoadReplacementPointerValue;
        unsigned long currentSignature = 0;
        unsigned char *mainBytesStart = process_main;

        if (addrSignature >> 32 == 0)
            printf("[WARNING] config.externalDataLoadReplacementPointerValue must be larger than 4 bytes !\n");

        for (int i = 0; i < config.mainBytesSize; i++)
        {
            currentSignature = (currentSignature >> 8) | ((unsigned long) mainBytesStart[i] << 56);
            if (i >= 7 && currentSignature == addrSignature)
                addrSignaturesSeen ++;
        }

        if (addrSignaturesSeen != config.externalDataLoadReplacementPointerCount)
            printf("[WARNING] Expected to see config.externalDataLoadReplacementPointerValue %d times. But it was seen %d times.\n", config.externalDataLoadReplacementPointerCount, addrSignaturesSeen);
    }

    return 0;
}
