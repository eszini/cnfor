

# la primera corrida, genero file igual al input
./tfor -v -f -opcion=d5 -inp=programa1.for -out=programa2.for -aux=parser.log > log1



# miro si el parser encontro caracteres que no tiene en la tabla
cat parser.log


# check basico
wc programa1.for programa2.for
