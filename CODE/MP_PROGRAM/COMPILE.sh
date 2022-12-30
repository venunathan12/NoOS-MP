gcc -I inc -w -fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args -o main main.c
./main
rm ../../DEP/DIR/mp/*
cp files/* ../../DEP/DIR/mp/

