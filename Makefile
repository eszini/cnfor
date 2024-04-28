
all:		ppg_prg01 cnv_f07


ppg_prg01:	ppg_prg01.c
		gcc -o ppg_prg01 ppg_prg01.c

cnv_f07:	cnv_f07.c
		gcc -o cnv_f07 cnv_f07.c



