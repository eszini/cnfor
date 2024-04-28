

# la primera corrida, genero file igual al input
./cnv_f07 -v -f -opcion=d5 -inp=programa1.for -out=p2.for  -aux=p2.lo1 > log1


# la segunda, dejo los tokens a ver como separa el progama
./cnv_f07 -v  -opcion=d5 -inp=programa1.for -out=p2.tkn  -aux=p2.lo2 > log2


# miro si el parser encontro caracteres que no tiene en la tabla
cat p2.lo2

