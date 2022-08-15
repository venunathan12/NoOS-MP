#include <efi.h>
#include <efilib.h>

#include "LIB/structures.c"
#include "LIB/lib.c"

UINTN numTotalThreads, numEnabledThreads;
Config *configData;
void (*sourceData)();
unsigned char *extData;
System *fullContext;

EFI_GUID fileSystemGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID; EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fileSystem;
EFI_GUID mpServiceGUID = EFI_MP_SERVICES_PROTOCOL_GUID; EFI_MP_SERVICES_PROTOCOL *mpService;

void process_start()
{
    ThreadInfo threadInfo;
    efi_call2(mpService->WhoAmI, mpService, &threadInfo.threadIdx);
    threadInfo.threadNum = configData->numThreads;

    sourceData(&threadInfo, fullContext, extData);
}

EFI_STATUS
EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);
    efiImageHandle = ImageHandle; efiSystemTable = SystemTable;

    efi_call4(SystemTable->BootServices->SetWatchdogTimer, 0, 0, 0, NULL);    
    efi_call2(SystemTable->ConOut->SetMode, SystemTable->ConOut, 0);
    efi_call1(SystemTable->ConOut->ClearScreen, SystemTable->ConOut);
    efi_call3(SystemTable->ConOut->SetCursorPosition, SystemTable->ConOut, 0, 0);
    efi_call2(SystemTable->ConOut->EnableCursor, SystemTable->ConOut, 0);

    
    if (efi_call3(BS->LocateProtocol, &fileSystemGUID, NULL, &fileSystem)){print(L"[ERROR] Hardware does not support EFI_SIMPLE_FILE_SYSTEM_PROTOCOL\n"); while(true);} print(L"[INFO] EFI_SIMPLE_FILE_SYSTEM_PROTOCOL detected on hardware\n");
    if (efi_call3(BS->LocateProtocol, &mpServiceGUID, NULL, &mpService)){print(L"[ERROR] Hardware does not support EFI_MP_SERVICES_PROTOCOL\n"); while(true);} print(L"[INFO] EFI_MP_SERVICES_PROTOCOL detected on hardware\n");
    if (efi_call3(mpService->GetNumberOfProcessors, mpService, &numTotalThreads, &numEnabledThreads)){print(L"[ERROR] Unable to get Processor information\n"); while(true);}; print(L"[INFO] Hardware supports %d threads\n", numTotalThreads);

    EFI_FILE_HANDLE volumeRoot, srcBytesFile, configBytesFile, extDataBytesFile;
    if (efi_call2(fileSystem->OpenVolume, fileSystem, &volumeRoot)){print(L"[ERROR] Unable to open volume\n");while(true);};
    if (efi_call5(volumeRoot->Open, volumeRoot, &configBytesFile, L"mp\\config.bin", EFI_FILE_MODE_READ, EFI_FILE_VALID_ATTR)){print(L"[ERROR] Unable to open config bytes file (/mp/config.bin)\n"); while(true);};
    if (efi_call5(volumeRoot->Open, volumeRoot, &srcBytesFile, L"mp\\main.bin", EFI_FILE_MODE_READ, EFI_FILE_VALID_ATTR)){print(L"[ERROR] Unable to open source bytes file (/mp/main.bin)\n"); while(true);};

    print(L"\n[INFO] Attempting to read config bytes file\n");
    if (efi_malloc(&configData, sizeof(Config))){print(L"[ERROR] [INTERNAL] malloc failed !\n"); while(true);} UINT64 configDataSize = sizeof(Config);
    if (efi_call3(configBytesFile->Read, configBytesFile, &configDataSize, configData)){print(L"[ERROR] Unable to read config bytes file (/mp/config.bin)\n"); while(true);};
    print(L"[INFO] Read %d bytes from config bytes file\n", configDataSize);
    if (configDataSize != sizeof(Config)) print(L"[WARNING] Expected %d bytes from config bytes file, got %d\n", sizeof(Config), configDataSize);
    
    print(L"\n[INFO] Attempting to read source bytes file\n");
    if (efi_malloc(&sourceData, configData->mainBytesSize)){print(L"[ERROR] [INTERNAL] malloc failed !\n"); while(true);} UINT64 sourceDataSize = configData->mainBytesSize;
    if (efi_call3(srcBytesFile->Read, srcBytesFile, &sourceDataSize, sourceData)){print(L"[ERROR] Unable to read source bytes file (/mp/main.bin)\n"); while(true);};
    print(L"[INFO] Read %d bytes from source bytes file\n", sourceDataSize);
    if (sourceDataSize != configData->mainBytesSize) print(L"[WARNING] Expected %d bytes from source bytes file, got %d\n", configData->mainBytesSize, sourceDataSize);

    if (configData->numThreads > numTotalThreads){print(L"\n[ERROR] This hardware cannot run a process requiring %d threads", configData->numThreads); while(true);}
    
    if (configData->externalDataSize > 0)
    {
        print(L"\n[INFO] Attempting to read external data file\n");
        if (efi_call5(volumeRoot->Open, volumeRoot, &extDataBytesFile, L"mp\\data.bin", EFI_FILE_MODE_READ, EFI_FILE_VALID_ATTR)){print(L"[ERROR] Unable to open external data file (/mp/data.bin)\n"); while(true);};
        if (efi_malloc(&extData, configData->externalDataSize)){print(L"[ERROR] [INTERNAL] malloc failed !\n"); while(true);} UINT64 extDataSize = configData->externalDataSize;
        if (efi_call3(extDataBytesFile->Read, extDataBytesFile, &extDataSize, extData)){print(L"[ERROR] Unable to read external data file (/mp/data.bin)\n"); while(true);};
        print(L"[INFO] Read %d bytes from external data file\n", extDataSize);
        if (extDataSize != configData->externalDataSize) print(L"[WARNING] Expected %d bytes from external data file, got %d\n", configData->externalDataSize, extDataSize);
    }

    print(L"\nReady to start process on %d threads\nPress Enter to continue ...\n", configData->numThreads);
    while (true)
    {
        InputKey Key;
        while(scan(&Key));
        if (Key.charCode == CHAR_CARRIAGE_RETURN || Key.charCode == CHAR_LINEFEED)
            break;
    }

    efi_call1(SystemTable->ConOut->ClearScreen, SystemTable->ConOut);
    efi_call3(SystemTable->ConOut->SetCursorPosition, SystemTable->ConOut, 0, 0);
    efi_call2(SystemTable->ConOut->EnableCursor, SystemTable->ConOut, 0);
    
    efi_malloc(&fullContext, sizeof(System));
    efi_malloc(&fullContext->mem, sizeof(struct System_Mem));
    fullContext->mem->malloc = efi_malloc;
    fullContext->mem->free = efi_free;
    efi_malloc(&fullContext->io, sizeof(struct System_IO));
    fullContext->io->log = print;
    fullContext->io->scan = scan;
    fullContext->efi = NULL;

    EFI_EVENT threadRunEvent; efi_call5(BS->CreateEvent, 0, EFI_TPL_APPLICATION, NULL, NULL, &threadRunEvent);
    for (int i = 1; i < numTotalThreads; i++)
        efi_call4(mpService->EnableDisableAP, mpService, i, (i < configData->numThreads ? true : false), NULL);
    efi_call7(mpService->StartupAllAPs, mpService, process_start, false, threadRunEvent, 0, NULL, NULL);
    process_start();

    while (true);
    return EFI_SUCCESS;
}