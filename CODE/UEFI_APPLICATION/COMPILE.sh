gcc -I ../../LIB/inc -w -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -c main.c -o main.o
ld -shared -Bsymbolic -L ../../LIB -T ../../LIB/elf_x86_64_efi.lds ../../LIB/crt0-efi-x86_64.o main.o -o main.so -lgnuefi -lefi
objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym  -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc --target efi-app-x86_64 --subsystem=10 main.so main.efi
cp main.efi bootx64.efi
mv main.o ./OUT; mv main.so ./OUT; mv main.efi ./OUT; mv bootx64.efi ./OUT
cp ./OUT/bootx64.efi ../../DEP/DIR/efi/boot

