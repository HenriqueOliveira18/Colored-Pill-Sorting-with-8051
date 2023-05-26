@echo off
srec_cat -disable_sequence_warnings %1.ihx -Intel -offset -0x0400 -Output out.bin -Binary
IF EXIST out.bin (
gflash_cli p out.bin
del out.bin
)