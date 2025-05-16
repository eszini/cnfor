
      SUBROUTINE CALCULA(X, Y)
      USE VARIABLES
      IMPLICIT NONE
      REAL X, Y, Z
      Z = X + Y
      ENTRY CALCULA_ALT(X, Y)
      Z = X * Y
      END
