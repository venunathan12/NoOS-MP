mkisofs -o ISO.iso DIR
truncate ISO.iso --size=4M
rm NoOS_VDI.vdi; VBoxManage convertfromraw ISO.iso NoOS_VDI.vdi --uuid abcdabcd-abcd-abcd-abcd-abcdabcdabcd

