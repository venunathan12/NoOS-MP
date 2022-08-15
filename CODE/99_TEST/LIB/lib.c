#include "MpService.h"

#define bool unsigned char
#define true 1
#define false 0

EFI_HANDLE *efiImageHandle;
EFI_SYSTEM_TABLE *efiSystemTable;

UINT64 efi_malloc(void **dst, UINTN poolSize)
{
    return efi_call3(BS->AllocatePool, EfiLoaderData, poolSize, dst);
}
UINT64 efi_memcpy(void *dst, void *src, UINTN size)
{
    return efi_call3(BS->CopyMem, dst, src, size);
}
UINT64 efi_free(void *pool)
{
    return efi_call1(BS->FreePool, pool);
}

UINTN (*print)() = Print;
void (*input)() = Input;
UINT64 scan(InputKey *Key)
{
    return efi_call2(efiSystemTable->ConIn->ReadKeyStroke, efiSystemTable->ConIn, Key);
}

