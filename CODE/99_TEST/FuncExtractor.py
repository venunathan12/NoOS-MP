import os, sys

with open("main.efi" if len(sys.argv) != 2 else sys.argv[1], "rb") as F:
    D = bytearray(F.read())
    SP = bytearray(8); SP[:] = [0x01, 0x02, 0x03, 0x04, 0x02, 0x00, 0x00, 0x00]

    for i in range(len(D)):
        if i + 8 >= len(D):
            break
        
        if D[i:i+8] == SP:
            print('Match at: ', i)
            Start = None; End = None
            St = bytearray(4); St[:] = [0xf3, 0x0f, 0x1e, 0xfa]
            Sn = bytearray(2); Sn[:] = [0xc9, 0xc3]
            for st in range(i, -1, -1):
                if D[st:st+4] == St:
                    Start = st
                    break
            for sn in range(i, len(D)-2):
                if D[sn:sn+2] == Sn:
                    End = sn+2
                    break
            for j in range(Start, End):
                print(j, hex(D[j]))
    
print("Write from? (start, end)")
st, en = map(int, input().strip().split())
with open("ext.bytes", "wb") as F:
    F.write(D[st:en])