#define reverse(x) ((!(x))||reverse_helper((x),(x),*(x))) 

char * reverse_helper(char *str, char *rts, char sv) 
{ 
    if (!sv) 
    { 
         return rts; 
    } 

    char *ed = reverse_helper(str + 1, rts, *(str+1)); 
    *ed = sv; 
    return ed + 1; 
}


