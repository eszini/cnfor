
all:		cnv_f08 tfor


clean:
		rm *.exe


cnv_f08:	cnv_f08.c
		gcc -o cnv_f08 cnv_f08.c

tfor:		tfor.c
		gcc -o tfor tfor.c


