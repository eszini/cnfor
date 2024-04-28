/*       
 *	search:
 *      =============================================================
 *	"header"		header del programa
 *	"ejemplos"		ejemplos de uso (lineas de comando )
 *	"documentacion" 	alguna documentacion
 *	"ojo"			cosas a tener en cuenta !!!!!
 *	"programa"		programa
 *
 *
 */



/*
 *	//header//
 *
 *	2024_04_09
 *
 *	ppg_prg01.c
 *	
 *	programa de proposito general - base para otros programas
 *
 *	tiene:
 *	- manejo general de opciones gp
 *	- manejo de errores / informativo / verbose
 *	- apertura y cierre de archivos
 *	- base para un parser 
 *
 *
 * 	Opciones:
 * 	-h   		forma de uso
 *	
 *	-v		verbose
 *
 *
 *	Changes pending...
 *	
 *
 *
 */



/*
 *	//ejemplos//
 *
 * 	Ejemplos de uso:
 *
 *	1) Mostrar uso
 *
 *	ppg_prg01
 *	ppg_prg01 -h
 *
 *
 *	2) Opciones de debug
 *
 *	ppg_prg01 -v                     activa debug, nivel full ... equivalente a d5 
 *	ppg_prg01 -v -opciones=Ln        letra L (i informativo d debug e no_me_acuerdo)  
 *	                                  Nro n nivel 1 a 5 ... 5 full
 *
 *
 */


/*
 * 	nivel de verbose
 *
 * 	-v	activa verbose (por defecto, se pone en 'd5' )
 * 	-v -opciones=XX
 *
 * 		XX puede ser d0 d1 d2 d3 d4 
 *
 *
 * 	d0	no imprime nada
 *
 * 	d1	muestra lo minimo indispensable, 
 * 		- comienzo y finalizacion de procesos
 * 		- resultados generales
 * 		- estadisticas
 *
 *	d2,d3	distintos niveles de debug / informacion
 *
 *	d4	imprime todo
 *	
 *	d5	especial para funciones gp
 *
 */




/*
 *	errores
 *
 *	101	no pudo abrir archivo de input 
 *	102	no pudo abrir archivo de output 
 *	103	no 
 *	104	no 
 *	105	no 
 *
 *	999	error debug
 */


/*
 *	//programa//
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define	DEBUG 0

#define	MAXD	16	/* buffer de juguete */
#define	MAXV	64	/* buffer chico */
#define	MAXR	128	/* buffer razonable */
#define	MAXB	1024	/* buffer grande */
#define	MAXT	200 	/* maximo de tokens en tabla */
#define	MAXF	64	/* largo de archivos de input - output - marcas etc */
#define	MAXP	128	/* maximo de palabras en general */

/*
 *
 *	Funciones, variables y estructuras para manejor de parametros globales
 *
 */

#define	GP_SET 1
#define	GP_GET 0

int	gp_default();
int	gp_init(int ,char **);
int	gp_test();
int	gp_print();
int	gp_parser();
int	gp_fq(int,int);
int	gp_fverbose(char *);
char	*gp_tm();
char	*gp_fp(int,int,char **);

int	gp_q_partype1=0;	/* parametero tipo "name" */
int	gp_q_partype2=0;	/* parametero tipo "-something" */
int	gp_q_partype3=0;	/* parametero tipo "-someoption=somename" */


int	gp_verbose=0;		/* verbose 0 no 1 si */

int	gp_minusculas=0;	/* output en minuscula 0 no 1 si */
int	gp_fsentencia=0;	/* archivo de salida en formato sentencias 0 no 1 si */
int	gp_eol=0;		/* fuerzo string EOL al final de la linea ... a veces hay . en medio de la linea */
int	gp_reidx;		/* re indexar archivo de transacciones */
int	gp_pause;		/* pausa al mostrar ... */
int	gp_niveldes=0;		/* nivel de descripcion que se vuelca en archivo de salida (solo con fsentencia = 0 ) */
				/* 0 normal 1 sentencia y numero de token 2 .... agrego cosas del diccionario si se usa */

int	gp_help=0;		/* help 0 no 1 si */
int	gp_uso(int);		/* usage */
				/* 0 normal 1 sentencia y numero de token 2 .... agrego cosas del diccionario si se usa */

int	gp_tpar[3];		/* vector con cantidad de parametros de cada tipo */

char	gp_opciones[MAXV];	/* opciones adicionales, informadas de la forma -opciones=[letras]  */
char	gp_pruebas[MAXV];	/* pruebas ...    -prue=[nro]   ej:  -prue=1    */
char	gp_exec[MAXV];		/* execs ...      -exec=[rnp]   ej:  -exec=1    */
char	gp_proc[MAXV];		/* procs ...      -proc=[rnp]   ej:  -proc=1    */
char	gp_fyh[MAXR];		/* fecha y hora */



/*
 *
 *	Funciones, variables y estructuras globales en el programa
 *
 */

int	abro_files();
int	cierro_files();
int	mostrar_cargas();
int	mostrar_reportes();
int	cantidad_n1();

int	build_idx1(FILE *);


int	gna(int,int);
char	*gnf(int);			/* genera fecha al azar */
char	*gnh(int,int);			/* genera hora al azar */
char	*gsf(char *);			/* string para imprimir fecha */
char	*gsh(char *);			/* string para imprimir hora */
int	determina_elegibles();
int	determina_vector_elegibles();
int	cambio_persona(int);
int	calcular_atrib_trx(int);


int	bpmp_print();
int	btb1_print();
int	btb2_print();
int	btb3_print();
int	btb4_print();


char	*desde_igual(char *s);
char	*pasar_a_minusc(char *s);
char	*df(char *);
char	*espero_enter(int);
int	clear_screen();


int	tiene_igual(char *);
int	linea_vacia(char *);
int	tipo_char(char );
int	es_numero(char);
int	es_num_tk(char *);
int	es_word(char *);
int	es_puntuacion(char *);
int	char_demed(char);
int	mostrar(int,int,char *);
int	separar_seg(char *);
int	error(int);
int	m_estado();

int	proceso_principal();
int	proceso_prueba();
int	proceso_stat();
int	proceso_fxa();
int	nnparse();
int	nxt_tkn(int);

int	pro_prue1();
int	pro_prue2();
int	pro_prue3();

int	pro_exec1();
int	pro_exec2();
int	pro_exec3();




#define	TC_EOL	0
#define	TC_BLA	1
#define	TC_CCE	2	/* algunos caracteres especiales  ',;:/' */
#define	TC_PNT	3	/* punto '.' */
#define	TC_PAA	4	/* parent '([{' */
#define TC_PAC	5	/* parent ')]}' */
#define	TC_LET	6	/* letras */
#define	TC_NUM	7	/* numero */
#define	TC_CVR	8	/* caracteres varios ' % */
#define	TC_GBJ	9	/* guion bajo '_' */
#define	TC_RST	99


char	finp[MAXF];
char	fout[MAXF];
char	fou2[MAXF];
char	faux[MAXF];	/* archivo aux para salidas segun necesidad */
char	flog[MAXF];	/* archivo log para salidas segun necesidad */


int	ffinp;
int	ffout;
int	ffou2;
int	ffaux;		/* archivo aux para output segun necesidad */
int	fflog;		/* archivo log para output segun necesidad */

int	ffprb;		/* utilizo -prueba=1 ... 2 .. 3 etc */
int	ffexc;		/* utilizo -exec=1 .. 2  .. 3 etc   */
int	ffpro;		/* utilizo -proceso=1 .. 2 .. 3 etc */

int	fftb1;
int	fftb2;
int	fftb3;
int	fftb4;


FILE	*hfinp;
FILE	*hfout;
FILE	*hfou2;
FILE	*hfaux;
FILE	*hflog;



int	flag_caracteres;
int	flag_before_exit;


/*
 *	Estructuras y variables para tokens de las lineas procesadas
 *
 */

int	q_tk;
char	tk[MAXT][MAXB];











/* definicion de funcion como parametro */
#if 0

int	csv_parser(char *, int (*)(int,int,char *));

int	bcvs_load(char *, FILE *, int (*)(int,int,char *));
int	fx(int,int,char *);

#endif
/* definicion de funcion como parametro */









/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	main
 *
 * -----------------------------------------------------------------------------------
 */

int	main(argc,argv)
int	argc;
char	**argv;
{
	int	n;

	/* miscelaneas gobales */
	flag_before_exit = 0;
	srand (time(NULL));

	/* init varios */
	gp_default();
	gp_init(argc,argv);
	gp_parser();

	/* shit finger ? */
	if (gp_help)
	 	gp_uso(0);


	/* programa */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a programa principal \n\n",gp_tm());
		gp_print();
	}


	/* opciones ingresadas  */
	if (gp_fverbose("d2"))
	{	gp_test();
	}


	/* abrir files */
	abro_files();


	/* proceso principal */
	proceso_principal();

	/* cerrar files */
	cierro_files();


	/* reportes ... */
	if (gp_fverbose("i1"))
	{
		mostrar_reportes();
	}

	/* si hay algo que hacer antes de salir, es aca ! */
	if (flag_before_exit)
	{	
		printf ("Atencion: .... \n");
	}

	/* programa */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de programa principal \n\n",gp_tm());
	}

}




/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 * 	reportes 
 *
 * 	muestra reportes al finalizar todos los procesos
 *
 *
 * -----------------------------------------------------------------------------------
 */



int	mostrar_reportes()
{
	int	n;

	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a mostrar reportes \n\n",gp_tm());
	}



	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de mostrar reportes \n\n",gp_tm());
	}
}


/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 * 	proceso_principal
 *
 * 	procesa zonas definidas en el mapa
 *
 *
 * -----------------------------------------------------------------------------------
 */

int	proceso_principal()
{

	int	i;
	int	px,py;

	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a proceso principal \n\n",gp_tm());
	}


	/* muestro resultado de cargas, si las hubo */
	if (gp_fverbose("d3"))
	{
		mostrar_cargas();
	}



	if ( ffprb)
	{
		if (ffprb == 1)
			pro_prue1();
		if (ffprb == 2)
			pro_prue2();
	}	

	if ( ffexc)
	{
		if (ffexc == 1)	
			pro_exec1();
		if (ffexc == 2)
			pro_exec2();
	}



	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de proceso principal \n\n",gp_tm());
	}

}




/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_exec 1
 *
 *	exec aparte ...
 *
 * -----------------------------------------------------------------------------------
 */


int	pro_exec1()
{

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra proceso exec 1 \n\n",gp_tm());
	}
		

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale proceso exec 1 \n\n",gp_tm());
	}
}




/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_exec 2
 *
 *	exec aparte ...
 *
 * -----------------------------------------------------------------------------------
 */




int	pro_exec2()
{

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a proceso exec 2 \n\n",gp_tm());
	}
		


	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de proceso exec 2 \n\n",gp_tm());
	}

}







/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_prueba 1
 *
 *	pruebas ...
 *
 * -----------------------------------------------------------------------------------
 */




int	pro_prue1()
{

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra proceso prueba 1 \n\n",gp_tm());
	}
		

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale proceso prueba 1 \n\n",gp_tm());
	}
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_prueba 2
 *
 *	pruebas ...
 *
 * -----------------------------------------------------------------------------------
 */




int	pro_prue2()
{

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra proceso prueba 2\n\n",gp_tm());
	}
		
	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale proceso prueba 2 \n\n",gp_tm());
	}
}









/*
 * -----------------------------------------------------------------------------------
 *
 *	abro_files
 *
 *	
 *
 * -----------------------------------------------------------------------------------
 */

int	abro_files()
{


	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a abro_files \n\n",gp_tm());
	}

	if ( ffinp && ((hfinp = fopen (finp,"r")) == NULL) )
	{
		error(101);
	}

	if ( ffout && ((hfout = fopen (fout,"w")) == NULL) )
	{
		error(102);
	}

	if ( ffou2 && ((hfou2 = fopen (fou2,"w")) == NULL) )
	{
		error(103);
	}

	if ( ffaux && ((hfaux = fopen (faux,"w")) == NULL) )
	{
		error(104);
	}
	
	if ( fflog && ((hflog = fopen (flog,"w")) == NULL) )
	{
		error(105);
	}




	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de abro_files \n\n",gp_tm());
	}


}



/*
 * -----------------------------------------------------------------------------------
 *
 *	cierro_files
 *
 *	
 *
 * -----------------------------------------------------------------------------------
 */


int	cierro_files()
{

	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entro a cierro_files \n\n",gp_tm());
	}


	if ( ffinp)
		fclose(hfinp);

	if ( ffout)
		fclose(hfout);

	if ( ffou2)
		fclose(hfou2);

	if ( ffaux)
		fclose(hfaux);

	if ( fflog)
		fclose(hflog);



	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de cierro_files \n\n",gp_tm());
	}



}






/*
 * -----------------------------------------------------------------------------------
 *
 *	mostrar_cargas
 *
 *	mostrar resultados de cargas, si los hubo
 *
 * -----------------------------------------------------------------------------------
 */

int	mostrar_cargas()
{

	int px,py;

	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a mostrar cargas \n\n",gp_tm());
	}

	/* si hubo cargas, las muestro aca */

	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de mostrar cargas \n\n",gp_tm());
	}

}








/*
 * -----------------------------------------------------------------------------------
 *
 *	gna
 *
 *	genera numero al azar
 *	numero = rand () % (N-M+1) + M;   // Este está entre M y N
 *
 * -----------------------------------------------------------------------------------
 */


int	gna(min,max)
int	min;
int	max;
{
	int nro;

	nro = rand() % (max-min+1) + min;

	return nro;
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gnf
 *
 *	genera numero al azar
 *	numero = rand () % (N-M+1) + M;   // Este está entre M y N
 *
 * -----------------------------------------------------------------------------------
 */


char	*gnf(mes)
int	mes;
{
	static	char	fecha[16];
	int	a,m,d;

	a = 2018;

	m = mes+1;

	if ( m == 2 )		
		d = gna(1,28);

	if ( m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		d = gna(1,31);

	if ( m == 4 || m == 6 || m == 9 || m == 11 )
		d = gna(1,30);


	sprintf (fecha,"%04d%02d%02d",a,m,d);

	return fecha;
}





/*
 * -----------------------------------------------------------------------------------
 *
 *	gnh
 *
 *	genera hora al azar
 *	numero = rand () % (N-M+1) + M;   // Este está entre M y N
 *
 * -----------------------------------------------------------------------------------
 */


char	*gnh(desde,hasta)
int	desde;
int	hasta;
{
	static	char	hora[16];
	int	h,m,s;

	h = gna(desde,hasta);
	m = gna(0,59);
	s = gna(0,59);

	sprintf (hora,"%02d%02d%02d",h,m,s);

	return hora;
}






/*
 * -----------------------------------------------------------------------------------
 *
 *	gsf 
 *
 *	fecha en formato mas 'readabily' para imprimir
 *
 * -----------------------------------------------------------------------------------
 */



char	*gsf(f)
char	*f;
{
	static	char	fecha[16];
	int	a,m,d;

	char	s[16];

	
	memset (s,0,16);
	strncpy(s,f,4);
	a = atoi(s);

	memset (s,0,16);
	strncpy(s,f+4,2);
	m = atoi(s);

	memset (s,0,16);
	strncpy(s,f+6,2);
	d = atoi(s);


	sprintf (fecha,"%04d/%02d/%02d",a,m,d);

	return fecha;
}





/*
 * -----------------------------------------------------------------------------------
 *
 *	gsh
 *
 *	Genera string con hora para imprimir
 *
 *
 * -----------------------------------------------------------------------------------
 */


char	*gsh(sh)
char	*sh;
{
	static	char	hora[16];
	int	h,m,s;

	int	h1,m1;
	int	ext;

	char	b[16];

	
	memset (b,0,16);
	strncpy(b,sh,2);
	h = atoi(b);

	memset (b,0,16);
	strncpy(b,sh+2,2);
	m = atoi(b);

	memset (b,0,16);
	strncpy(b,sh+4,2);
	s = atoi(b);

	sprintf (hora,"%02d:%02d:%02d",h,m,s);

	return hora;
}










/*
 * -----------------------------------------------------------------------------------
 *
 *	csv_parser
 *
 *	
 *	parser string tipo csv
 *
 * -----------------------------------------------------------------------------------
 */


/*
 *	
 *	fx		funcion a llamar con cada campo procesado
 *
 */


int	csv_parser(str,fx)
char	*str;
int	(*fx)(int,int,char *);
{
	char	b1[MAXB];
	char	b2[MAXB];
	char	b3[MAXB];

	int	p1,p2;
	int	k;
	int	f1;


	strcpy(b1,str);

	k=0;

		
	f1=1;

	if (f1)
	{
		p1=0;
		p2=0;
		k=0;

		while (b1[p1] )
		{	
			b2[k++] = b1[p1];

			if (b1[p1] == ',' || b1[p1] == '\n')
			{	
				b2[k-1]=0;

				strcpy(b3,b2);
				if (gp_fverbose("d4"))
					printf ("=%02d= %s\n",p2,b3);

				fx(0,p2,b3);

				p2++;
				k=0;
			}

			p1++;
		}
		
		/* termino la linea */
		fx(1,p2," ");
	}
}









/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	Rutinas generales gp_xxxxxx
 *
 *
 * -----------------------------------------------------------------------------------
 */


/* general gp algo */
#if 1




/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_print
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_print()
{
	int i;

	printf ("\n");
	printf ("Cantidad de par   : %2d\n",gp_fq(GP_GET,0) - 1 );
	for (i=0; i<3; i++)
		printf ("Cantidad de par %d : %2d\n",i+1,gp_tpar[i]);
	printf ("\n");

}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_parser
 *
 *	parser general de parametros de input al programa
 * 
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_parser()
{

	int i,j;
	char	prm[MAXV];

	/* excepcion con verbose, por si lo pusieron al final de la linea, por defecto d5 !!! */

	for (i=0; i < gp_fq(GP_GET,0); i++  )
	{	if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v' )
#if 0
	/* si hay parametro -vac=algo ...
	 * esto no funca
	 * aca hay que agregar el 'y no tiene igual. ... '
	 */
		if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v' && !tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
#endif
		{	gp_verbose = 1;
			strcpy(gp_opciones,"d5");
		}
		if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"opciones",6) )
		{	strcpy(gp_opciones,desde_igual( gp_fp(GP_GET,i,(char **)0)));
		}


	}

	for (i=0; i < gp_fq(GP_GET,0);  )
	{

		/* parameter type 1 ... "name" */
		if ( i &&  *( gp_fp(GP_GET,i,(char **)0) + 0) != '-')
		{
			gp_q_partype1++;
			gp_tpar[0]++;

			if (gp_q_partype1 == 1)
			{
				strcpy(finp, gp_fp(GP_GET,i,(char **)0));
				ffinp=1;
			}

			if (gp_q_partype1 == 2)
			{
				strcpy(fout, gp_fp(GP_GET,i,(char **)0));
				ffout=1;
			}

			if (gp_fverbose("d5"))
			{
				printf ("Param tipo 1: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 2 ... "-something" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && !tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype2++;
			gp_tpar[1]++;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v'  )
				gp_verbose = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'h'  )
				gp_help = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'm'  )
				gp_minusculas = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'f'  )
				gp_fsentencia = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'e'  )
				gp_eol = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'i'  )
				gp_reidx = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'p'  )
				gp_pause = 1;

			if (gp_fverbose("d5"))
			{
				printf ("Param tipo 2: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 3 ... "-someoption=somename" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype3++;
			gp_tpar[2]++;

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"inp",3) )
			{
				strcpy(finp,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffinp=1;
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"out",3) )
			{
				strcpy(fout,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffout=1;
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"aux",3) )
			{	
				strcpy(faux,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffaux=1;
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"log",3) )
			{	
				strcpy(flog,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				fflog=1;
			}





			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"nvd",3) )
				gp_niveldes = *desde_igual( gp_fp(GP_GET,i,(char **)0)) - '0';


			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"opciones",6) )
			{	
				strcpy(gp_opciones,desde_igual( gp_fp(GP_GET,i,(char **)0)));
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"prue",4) )
			{	
				strcpy(gp_pruebas,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffprb=gp_pruebas[0]-'0';
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"exec",4) )
			{	
				strcpy(gp_exec,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffexc=gp_exec[0]-'0';
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"proc",4) )
			{	
				strcpy(gp_proc,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffpro=gp_proc[0]-'0';
			}



			if (gp_fverbose("d5"))
			{
				printf ("Param tipo 3: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* program name */
		if (i==0)
		{	
			if (gp_fverbose("d5"))
			{
				printf ("Programa    : %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* next ... */
		i++;
	}

	/* futuro ...
	 * Hacer una gramatica para la combinacion de comandos
	 * posibles !!
	 *
	 * Por ahora, revisamos combinaciones basicas que
	 * son necesarias entre parametros ...
	 *
	 */

	/* si no pone parametros ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype2 + gp_q_partype3 == 0 )
		gp_help = 1;

#if 0
	/* si no indico ningun  archivo ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype3 == 0 )
		gp_help = 1;
#endif 

	if (gp_fverbose("d5"))
	{
		printf ("\n\n");
	}
} 




/*
 * -----------------------------------------------------------------------------------
 *
 *	tiene_igual
 *
 * -----------------------------------------------------------------------------------
 */


int	tiene_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return flag;
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	desde_igual
 *
 * -----------------------------------------------------------------------------------
 */


char	*desde_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return s+i;
}




/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_init
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_init(vpar_q,vpar_p)
int	vpar_q;
char	**vpar_p;
{
	int i;

	gp_fq(GP_SET,vpar_q);
	gp_fp(GP_SET,0,vpar_p);


}


/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_fp
 *
 * -----------------------------------------------------------------------------------
 */

char	*gp_fp(action,offset,value)
int	action;
int	offset;
char	**value;
{
	static char **gp_value;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return 	*(gp_value+offset);
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_fq(action,value)
 *	
 *	int action
 *	int value
 *	
 *	value:
 *	on fist call, value is a number (typically argc )
 *	after first call, value can be any number, and is not used
 *
 *	returns:
 *	value
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_fq(action,value)
int	action;
int	value;
{
	static int gp_value=0;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return gp_value;
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_test 
 *
 *	
 *
 * -----------------------------------------------------------------------------------
 */


int	gp_test()
{
	int i;

	printf ("Cantidad de par   : %2d\n",gp_fq(GP_GET,0) - 1 );
	for (i=0; i<3; i++)
		printf ("Cantidad de par %d : %2d\n",i+1,gp_tpar[i]);

	printf ("\n");
	for (i=0; i< gp_fq(GP_GET,0); i++)
		printf ("Parametro  %2d     : %s\n",i,gp_fp(GP_GET,i,(char **)0)  );
			
	printf ("\n");
	printf ("\n");
}

/*
 * -----------------------------------------------------------------------------------
 *
 * 	linea_vacia
 *
 *	Determina si una linea esta vacia (generalmente, para lineas leidas de files)
 *	La linea NO esta vacia si contiene al menos 1 caracter distinto de
 *	' ' 	blanco
 *	'\t' 	tab
 *	'\n'	new line
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	linea_vacia(s)
char	*s;
{
	int i,flag;

	i=0;
	flag=1;

	for (i=0; flag && i< strlen(s); i++)
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' )
			flag=0;

	return flag;
}



/*
 * -----------------------------------------------------------------------------------
 *
 * 	error
 *
 *	display de errores
 *	en esta version es display de un numero
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	error(value)
int	value;
{
	printf ("Error: %d\n",value);
	printf ("usar -h para help\n");
	exit(0);
}





/*
 * -----------------------------------------------------------------------------------
 *
 *	tipo_char
 *
 *	ATENCION:
 *	Falta contemplar que hacemos con el caracter '_' !!!!
 *	Por ahora lo incluyo en letras, porque si no, me separa el tag de las palabras
 *	Si voy a parsear corpus sin tag ... lo tengo que sacar de la lista !!!
 *
 *	0	fin de linea
 *	1	blanco o tab
 *	2	otra cosa ( x ahora ... )
 *
 * -----------------------------------------------------------------------------------
 */




int	tipo_char(c)
char	c;
{
	int x;

	x=TC_RST;

	/* para archivos fortran de hita */
	if (c == '\n' || c == 13 )
		x = TC_EOL;

	if (c == ' ' || c == '\t' )
		x = TC_BLA;

	if (c == '_' )
		x = TC_GBJ;

	if (c == ',' || c == ';' || c == ':' || c == '-' || c == '/' )
		x = TC_CCE;

	if (c == '.' )
		x = TC_PNT;

	if (c == '(' || c == '[' || c == '{' )
		x = TC_PAA;

	if (c == ')' || c == ']' || c == '}' )
		x = TC_PAC;

	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z' )
		x = TC_LET;

	/* fortran */
	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z' || c == '_')
		x = TC_LET;

	if (c >= '0' && c <= '9' )
		x = TC_NUM;

	/* agrego los que vienen de analizar fuentes fortran */
	if (c == '\'' || c == '%' || c == '!' || c == '*' )
		x = TC_CVR;

	if (c == '"' || c == '&' || c == '+' || c == '=' || c == '>' || c == '<' || c == '?' )
		x = TC_CVR;

	return x;
}







#if 0

int	tipo_char(c)
char	c;
{
	int x;

	x=TC_RST;

	if (c == '\n' )
		x = TC_EOL;

	if (c == ' ' || c == '\t' )
		x = TC_BLA;

	if (c == '_' )
		x = TC_GBJ;

	if (c == ',' || c == ';' || c == ':' || c == '-' || c == '/' )
		x = TC_CCE;

	if (c == '.' )
		x = TC_PNT;

	if (c == '(' || c == '[' || c == '{' )
		x = TC_PAA;

	if (c == ')' || c == ']' || c == '}' )
		x = TC_PAC;

#if 0
	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z' || c == '_')
		x = TC_LET;
#endif
	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z' )
		x = TC_LET;

	if (c >= '0' && c <= '9' )
		x = TC_NUM;

	if (c == '\'' || c == '%' )
		x = TC_CVR;

	return x;
}


#endif


/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_numero
 *
 *	funcion para determinar si caracter es numero
 *
 *
 * -----------------------------------------------------------------------------------
 */




int	es_numero(c)
char	c;
{
	int x;

	x=0;
	if ( c >= '0' && c <= '9' )
		x=1;

	return x;
}


/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_num_tk
 *
 *	funcion para determinar si string es numero
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	es_num_tk(s)
char	*s;
{
	int i,x;

	x=1;
	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < '0' || s[i] > '9' )
			x=0;

	}

	return x;
}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_puntuacion
 *
 *	funcion para determinar si es simbolo de puntuacion
 *
 *
 * -----------------------------------------------------------------------------------
 */




int	es_puntuacion(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] != '.' && s[i] != ',' && s[i] != ':' && s[i] != ';' )
			x=0;
	}

	return x;

}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_word
 *
 *	funcion para determinar si es word o no
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	es_word(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < 'A' || s[i] > 'z' || ( s[i] > 'Z' && s[i] < 'a')  )
			x=0;
	}

	return x;

}

/*
 * -----------------------------------------------------------------------------------
 *
 * 	char_demed
 *
 *	caracteres utilizados normalmente en frases de medidas 
 *	1 cm x 1 cm ( 'x' ) y similares
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	char_demed(c)
char	c;
{
	int	x;

	x=0;
	if ( c == 'e' || c == 'E' || c == 'x' || c == 'X' )
		x=1;

	return x;
}



/*
 * -----------------------------------------------------------------------------------
 *
 * 	uso
 *
 *	texto para describir el uso de la herramienta
 *
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_uso(x)
int	x;
{
	printf ("Usage: \n\n");
	printf ("inp_file out_file                   inp_file: texto input  out_file: archivo de salida         \n");
	printf ("-inp=inp_file -out=out_file         inp_file: texto input  out_file: archivo de salida         \n");
	printf ("-h                                  help                                                       \n");
	printf ("-v                                  verbose ... muestra cierta informacion de proceso          \n");
	printf ("                                                                                               \n");
	printf ("-inp=f1 -out=f2 -pruebas=6          f1 es ordenado por PER - Va cargando todas las trx x per   \n");
	printf ("                                                                                               \n");
	printf ("-opciones=AABBCC...                 AA es del formato: letra-numero  ej:  -opciones=d4         \n");
	printf ("          dN     (va con -v )       (debug) Muestra distintos niveles de informacion           \n");
	printf ("                                    0 no imprime, 1 basico, 2 y 3 debug, 4 full debug          \n");
	printf ("\n\n\n");

	exit(x);
}


/*
 * -----------------------------------------------------------------------------------
 *
 * 	gp_default
 *
 * 	inicializa parametros de funcionamiento default
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_default()
{
	gp_help=0;
	gp_verbose=0;

	ffinp=0;
	ffout=0;
	ffou2=0;
	ffaux=0;
	fflog=0;


	sprintf (gp_opciones,"%s","______");
	sprintf (gp_pruebas, "%s","______");
	sprintf (gp_exec   , "%s","______");
	sprintf (gp_proc   , "%s","______");

	memset(gp_tpar,0,sizeof(gp_tpar));

}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	pasar_a_minusc
 *
 *
 * -----------------------------------------------------------------------------------
 */

char	*pasar_a_minusc(s)
char	*s;
{
	static char b[MAXB];

	int i,j,k;

	strcpy(b,s);

	for (i=0; i<MAXB && b[i]; i++)
	{
		if ( b[i] >= 'A' && b[i] <= 'Z' )
			b[i] += 32;
	}

	return b;
}







/*
 * -----------------------------------------------------------------------------------
 *
 * 	gp_fverbose
 *
 * -----------------------------------------------------------------------------------
 */




/*
 *	gp_fverbose
 *
 *
 *	Devuelve 1 o 0 si aplica la condicion de verbose
 *	
 *	Las opciones involucradas son:
 *	-v               activa el verbose
 *	-opciones=str    string de condiciones de verbose  (requiere -v )
 *	                 
 *	El string de opciones es del tipo "Ln...(1 o 3)"
 *	Donde:
 *	L       Es la letra (I informativo, D debug, y E ... no me acuerdo
 *	n       Es el nivel
 *	        0 no imprime nada   ( es lo mismo que no poner nada !!! )
 *	        1    imprime cosas basicos, por que rutinas paso etc
 *	        2,3  niveles de debug intermedios
 *	        4    full debug
 *	        5    incluye debug de gp_parse
 *
 * 
 *
 *	
 */


int	gp_fverbose(situacion)
char	*situacion;
{
	int	i,j,k;
	int	sit;

	static	int	f_p=1;
	static	int	f_i=0;
	static	int	f_e=0;
	static	int	f_d=0;

	if ( f_p == 1 && gp_opciones[0] != '_' )
	{	f_p = 0;

		for (i=0; i<strlen(gp_opciones)-1; i=i+2)
		{
			if (*(gp_opciones+i) == 'i' || *(gp_opciones+i) == 'I' )
				f_i = (int) *(gp_opciones+i+1) - '0';
			if (*(gp_opciones+i) == 'e' || *(gp_opciones+i) == 'E' )
				f_e = (int) *(gp_opciones+i+1) - '0';
			if (*(gp_opciones+i) == 'd' || *(gp_opciones+i) == 'D' )
				f_d = (int) *(gp_opciones+i+1) - '0';
		}
	}


	sit = 0;

	if (gp_verbose)
	{

		/* determino si hay que devolver 0 o 1
		 * en base a situacion informada, y 
		 * conjunto de flags y '-opcion=vN'   
		 *
		 */
	
		for (sit=0, i=0; i<strlen(situacion); i=i+2)
		{


#if 0
			printf ("X1 f_P: %d i:%d situaci: %s  opcion: %s f_d: %d sit: %d\n",
				f_p,i,situacion,gp_opciones,f_d,sit);
#endif
	
			if (*(situacion+i) == 'i')
				if ( *(situacion+i+1)-'0' <= f_i )
					sit = 1;
	
			if (*(situacion+i) == 'e')
				if ( *(situacion+i+1)-'0' <= f_e )
					sit = 1;
	
			if (*(situacion+i) == 'd')
				if ( *(situacion+i+1)-'0' <= f_d )
					sit = 1;

#if 0
			printf ("X2 f_P: %d i:%d situaci: %s  opcion: %s f_d: %d sit: %d\n",
				f_p,i,situacion,gp_opciones,f_d,sit);
#endif
		}
	}

	return	sit;
}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	gp_tm
 *
 * -----------------------------------------------------------------------------------
 */




char	*gp_tm()
{
	time_t t;
  	struct tm *tm;

	t=time(NULL);
	tm=localtime(&t);
	strftime(gp_fyh, MAXR , "[%Y/%m/%d %H:%M:%S]", tm);

	return(gp_fyh);
}



/*
 * -----------------------------------------------------------------------------------
 *
 * 	df
 *
 * -----------------------------------------------------------------------------------
 */




char	*df(s)
char	*s;
{
	static	char	nf[MAXF];

	int	i,j,k,f1;

	for ( f1=1, i=0; f1 && i<strlen(s); i++)
		if (s[i] != '.')
			nf[i]=s[i];
		else
			nf[i]=0,f1=0;

	strcat(nf,".dif");


	return nf;
}


#endif
/* general gp algo */




/*
 * -----------------------------------------------------------------------------------
 *
 *	end of source
 *	end of source
 *	end of source
 *	end of source
 *	end of source
 *
 * -----------------------------------------------------------------------------------
 */





/* cnv_f07 */
#if 0

/*       
 *	search:
 *      =============================================================
 *	"header"		header del programa
 *	"ejemplos"		ejemplos de uso (lineas de comando )
 *	"documentacion" 	alguna documentacion
 *	"ojo"			cosas a tener en cuenta !!!!!
 *	"programa"		programa
 *
 *
 */



/*
 *	//header//
 *
 *	cnv_f07.c
 *	
 *
 *	2024_04_09
 *
 *
 *	conversores de codigo fuente de fortran
 *
 * 	Opciones:
 * 	-h   		forma de uso
 *	
 *	-v		verbose
 *
 *
 *	Changes pending...
 *	
 *
 *
 */



/*
 *	//ejemplos//
 *
 * 	Ejemplos de uso:
 *
 *	1) Mostrar uso
 *
 *	cnv_f07
 *	cnv_f07 -h
 *
 *
 *	2) Opciones de debug
 *
 *	cnv_f07 -v                     activa debug, nivel full ... equivalente a d5 
 *	cnv_f07 -v -opciones=Ln        letra L (i informativo d debug e no_me_acuerdo)  
 *	                                  Nro n nivel 1 a 5 ... 5 full
 *	3) parser
 *
 *	parsea programa.for, output a copia.for en mismo formato, 
 *	si parser no reconoce caracter, lo pone en log2
 *	
 *	cnv_f07 -v -f -opciones=d5 -inp=programa.for -out=copia.for -aux=log2  
 *
 *	4) contar caracteres
 * 
 *	para comparar si programa1.for y p2.for tienen la misma cantidad de caracteres "utiles"
 *
 *	./cnv_f07 -v -opciones=d5 -inp=programa1.for -out=p1.chr -exec=1 > log1
 * 	./cnv_f07 -v -opciones=d5 -inp=p2.for -out=p2.chr -exec=1 > log2
 *
 *
 */


/*
 * 	nivel de verbose
 *
 * 	-v	activa verbose (por defecto, se pone en 'd5' )
 * 	-v -opciones=XX
 *
 * 		XX puede ser d0 d1 d2 d3 d4 
 *
 *
 * 	d0	no imprime nada
 *
 * 	d1	muestra lo minimo indispensable, 
 * 		- comienzo y finalizacion de procesos
 * 		- resultados generales
 * 		- estadisticas
 *
 *	d2,d3	distintos niveles de debug / informacion
 *
 *	d4	imprime todo
 *	
 *	d5	especial para funciones gp
 *
 */




/*
 *	errores
 *
 *	101	no pudo abrir archivo de input 
 *	102	no pudo abrir archivo de output 
 *	103	no 
 *	104	no 
 *	105	no 
 *
 *	999	error debug
 */


/*
 *	//programa//
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define	DEBUG 0

#define	MAXD	16	/* buffer de juguete */
#define	MAXV	64	/* buffer chico */
#define	MAXR	128	/* buffer razonable */
#define	MAXB	1024	/* buffer grande */
#define	MAXT	200 	/* maximo de tokens en tabla */
#define	MAXF	64	/* largo de archivos de input - output - marcas etc */
#define	MAXP	128	/* maximo de palabras en general */

/*
 *
 *	Funciones, variables y estructuras para manejor de parametros globales
 *
 */

#define	GP_SET 1
#define	GP_GET 0

int	gp_default();
int	gp_init(int ,char **);
int	gp_test();
int	gp_print();
int	gp_parser();
int	gp_fq(int,int);
int	gp_fverbose(char *);
char	*gp_tm();
char	*gp_fp(int,int,char **);

int	gp_q_partype1=0;	/* parametero tipo "name" */
int	gp_q_partype2=0;	/* parametero tipo "-something" */
int	gp_q_partype3=0;	/* parametero tipo "-someoption=somename" */


int	gp_verbose=0;		/* verbose 0 no 1 si */

int	gp_minusculas=0;	/* output en minuscula 0 no 1 si */
int	gp_fsentencia=0;	/* archivo de salida en formato sentencias 0 no 1 si */
int	gp_eol=0;		/* fuerzo string EOL al final de la linea ... a veces hay . en medio de la linea */
int	gp_reidx;		/* re indexar archivo de transacciones */
int	gp_pause;		/* pausa al mostrar ... */
int	gp_niveldes=0;		/* nivel de descripcion que se vuelca en archivo de salida (solo con fsentencia = 0 ) */
				/* 0 normal 1 sentencia y numero de token 2 .... agrego cosas del diccionario si se usa */

int	gp_help=0;		/* help 0 no 1 si */
int	gp_uso(int);		/* usage */
				/* 0 normal 1 sentencia y numero de token 2 .... agrego cosas del diccionario si se usa */

int	gp_tpar[3];		/* vector con cantidad de parametros de cada tipo */

char	gp_opciones[MAXV];	/* opciones adicionales, informadas de la forma -opciones=[letras]  */
char	gp_pruebas[MAXV];	/* pruebas ...    -prue=[nro]   ej:  -prue=1    */
char	gp_exec[MAXV];		/* execs ...      -exec=[rnp]   ej:  -exec=1    */
char	gp_proc[MAXV];		/* procs ...      -proc=[rnp]   ej:  -proc=1    */
char	gp_fyh[MAXR];		/* fecha y hora */



/*
 *
 *	Funciones, variables y estructuras globales en el programa
 *
 */

int	abro_files();
int	cierro_files();
int	mostrar_cargas();
int	mostrar_reportes();
int	cantidad_n1();



int	gna(int,int);
char	*gnf(int);			/* genera fecha al azar */
char	*gnh(int,int);			/* genera hora al azar */
char	*gsf(char *);			/* string para imprimir fecha */
char	*gsh(char *);			/* string para imprimir hora */
int	determina_elegibles();
int	determina_vector_elegibles();
int	cambio_persona(int);
int	calcular_atrib_trx(int);


int	bpmp_print();
int	btb1_print();
int	btb2_print();
int	btb3_print();
int	btb4_print();


char	*desde_igual(char *s);
char	*pasar_a_minusc(char *s);
char	*df(char *);
char	*espero_enter(int);
int	clear_screen();


int	tiene_igual(char *);
int	linea_vacia(char *);
int	tipo_char(char );
int	es_numero(char);
int	es_num_tk(char *);
int	es_word(char *);
int	es_puntuacion(char *);
int	char_demed(char);
int	mostrar(int,int,char *);
int	separar_seg(char *);
int	error(int);
int	m_estado();

int	proceso_principal();
int	proc_principal();
int	nnparse();
int	nxt_tkn(int);

int	pro_prue1();
int	pro_prue2();
int	pro_prue3();

int	pro_exec1();
int	pro_exec2();
int	pro_exec3();




#define	TC_EOL	0
#define	TC_BLA	1
#define	TC_CCE	2	/* algunos caracteres especiales  ',;:/' */
#define	TC_PNT	3	/* punto '.' */
#define	TC_PAA	4	/* parent '([{' */
#define TC_PAC	5	/* parent ')]}' */
#define	TC_LET	6	/* letras */
#define	TC_NUM	7	/* numero */
#define	TC_CVR	8	/* caracteres varios ' % */
#define	TC_GBJ	9	/* guion bajo '_' */
#define	TC_RST	99


char	finp[MAXF];
char	fout[MAXF];
char	fou2[MAXF];
char	faux[MAXF];	/* archivo aux para salidas segun necesidad */
char	flog[MAXF];	/* archivo log para salidas segun necesidad */


int	ffinp;
int	ffout;
int	ffou2;
int	ffaux;		/* archivo aux para output segun necesidad */
int	fflog;		/* archivo log para output segun necesidad */

int	ffprb;		/* utilizo -prueba=1 ... 2 .. 3 etc */
int	ffexc;		/* utilizo -exec=1 .. 2  .. 3 etc   */
int	ffpro;		/* utilizo -proceso=1 .. 2 .. 3 etc */

int	fftb1;
int	fftb2;
int	fftb3;
int	fftb4;


FILE	*hfinp;
FILE	*hfout;
FILE	*hfou2;
FILE	*hfaux;
FILE	*hflog;



int	flag_caracteres;
int	flag_before_exit;


/*
 *	Estructuras y variables para tokens de las lineas procesadas
 *
 */

int	q_tk;
char	tk[MAXT][MAXB];











/* definicion de funcion como parametro */
#if 0

int	csv_parser(char *, int (*)(int,int,char *));

int	bcvs_load(char *, FILE *, int (*)(int,int,char *));
int	fx(int,int,char *);

#endif
/* definicion de funcion como parametro */




/*  variables quue vienen de tes_cpar04.c */

int yyparse();
int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead );

static int globalReadOffset;

int	gc_pal_e;		/* palabra encontrada */

int	gc_si;
int	gc_no;
int	v_flag;
int	l_flag;
int	tok;
int	tok_si;
int	tok_no;

char   *spp      = "                            ";

char 	*globalInputText;
char	buffer[4096];
char	global_ref[MAXP];

char	yy_buffer[64];
char	*yy_ptr;

int	gramatik(char *,int);

int	f_cneg;			/* flag si parser encontro negacion en la linea */
int	f_sneg;			/* flag si parser NO encontro negacion en la linea */

int	f_cb;			/* flag continuo buscando ... (en el abol que arma yacc ) */
int	f_pe_lin;		/* flag palabra encontrada en linea  (en yacc ) */
int	f_pe_ora;		/* flag palabra encontrada en frase nomimal (en yacc) */



/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	main
 *
 * -----------------------------------------------------------------------------------
 */

int	main(argc,argv)
int	argc;
char	**argv;
{
	int	n;

	/* miscelaneas gobales */
	flag_before_exit = 0;
	srand (time(NULL));

	/* init varios */
	gp_default();
	gp_init(argc,argv);
	gp_parser();

	/* shit finger ? */
	if (gp_help)
	 	gp_uso(0);


	/* programa */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a programa principal \n\n",gp_tm());
		gp_print();
	}


	/* opciones ingresadas  */
	if (gp_fverbose("d2"))
	{	gp_test();
	}


	/* abrir files */
	abro_files();


	/* proceso principal */
	proceso_principal();

	/* cerrar files */
	cierro_files();


	/* reportes ... */
	if (gp_fverbose("i1"))
	{
		mostrar_reportes();
	}

	/* si hay algo que hacer antes de salir, es aca ! */
	if (flag_before_exit)
	{	
		printf ("Atencion: .... \n");
	}

	/* programa */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de programa principal \n\n",gp_tm());
	}

}




/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 * 	reportes 
 *
 * 	muestra reportes al finalizar todos los procesos
 *
 *
 * -----------------------------------------------------------------------------------
 */



int	mostrar_reportes()
{
	int	n;

	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a mostrar reportes \n\n",gp_tm());
	}



	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de mostrar reportes \n\n",gp_tm());
	}
}


/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 * 	proceso_principal
 *
 * 	procesa zonas definidas en el mapa
 *
 *
 * -----------------------------------------------------------------------------------
 */

int	proceso_principal()
{

	int	i;
	int	px,py;

	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a proceso principal \n\n",gp_tm());
	}


#if 0
	/* muestro resultado de cargas, si las hubo */
	if (gp_fverbose("d3"))
	{
		mostrar_cargas();
	}
#endif


	/* proceso por defecto */
	if (!ffprb && !ffexc )
		proc_principal();



	if ( ffprb)
	{
		if (ffprb == 1)
			pro_prue1();
		if (ffprb == 2)
			pro_prue2();
	}	

	if ( ffexc)
	{
		if (ffexc == 1)	
			pro_exec1();
		if (ffexc == 2)
			pro_exec2();
	}



	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de proceso principal \n\n",gp_tm());
	}

}




/*
 * -----------------------------------------------------------------------------------
 *
 *
 * 	proc_principal
 *
 * 	parser1
 * 	parser de linea de texto
 *
 *
 * -----------------------------------------------------------------------------------
 */

int	proc_principal()
{

	int	px,py;


	int	i,j,k;
	int	m1,m2,m3;
	int	f1,f2,f3,f4;
	int	q_lin;
	int	q_tk;
	int	p1,p2,p3,p4;

	char	b1[MAXB];
	char	b2[MAXB];
	char	b3[MAXB];
	char	tk[MAXT][MAXB];


	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a proc principal \n\n",gp_tm());
	}



/* parser */
/* parser */
#if 1



	/* init de valores para lex yacc */
	globalInputText = buffer;
	gc_si    = 0;
	gc_no    = 0;
	v_flag   = 1;
	l_flag   = 1;
	gc_pal_e = 0;




	/* si encuentro caracteres no considerados para el parser, avisar al final de todo el proceso */
	flag_caracteres = 0;


	q_lin=0;
	while (fgets(b1, MAXB, hfinp) != NULL)
	{

	    /* procesar solo lineas no vacias */
#if 0
	    /* opcion - no proceso lineas vacias */
	    if ( !linea_vacia(b1))
#endif

	    /* opcion - proceso lineas vacias */
	    if ( 1 )
	    {
		/* blancos al final */
		for (i=strlen(b1)-1, f4=1 ; i && f4 ; i-- )
			if (b1[i] == ' ' || b1[i] == '\n' )
				b1[i]=0;
			else
				b1[i+1]='\n', b1[i+2]=0, f4=0;

 
		f1=1;

		if (gp_verbose)
		{
			printf ("Linea  : %d \n\n",q_lin);
			printf ("Buffer :|%s|\n\n",b1);
		}



		/* comienzo parser de tokens */
		p1=0;
		q_tk=0;

		while ( f1 )
		{
			/* controlamos cantidad de tokens ... */
			if (q_tk > MAXT-10)
			{	error(501);
			} 

			j=tipo_char(b1[p1]);

			switch (j)
			{
				/* otro caracter !!! */
				case TC_RST:
					flag_caracteres=1;
					if (gp_verbose)
					{
						printf ("Caracter no definido para parser: %c %d\n",b1[p1],b1[p1]);
						if (ffaux)
							fprintf (hfaux,"Caracter no definido %d %c\n",b1[p1],b1[p1]);
							
					}
					p1++; 
					break; 

				/* letras */
				case TC_LET:
					p2=0;
					while ( (j=tipo_char(b1[p1])) == TC_LET || \
					        (j == TC_NUM && !char_demed(b1[p1-1])  ) )
						tk[q_tk][p2++]=b1[p1++];
					tk[q_tk][p2]=0;
					q_tk++;
					break;

				/* numeros tenemos que contemplar 3.3 o 3,3 !! */
				case TC_NUM:
					p2=0;
					while ( (j=tipo_char(b1[p1])) == TC_NUM || \
						(tipo_char(b1[p1]) == TC_PNT && tipo_char(b1[p1+1]) == TC_NUM ) || \
						( (b1[p1]) == ',' && tipo_char(b1[p1+1]) == TC_NUM ) )
					{	tk[q_tk][p2]=b1[p1];
						p1++;
						p2++;
					}
					tk[q_tk][p2]=0;
					q_tk++;
					break;

				/* blanco o tab */
				case TC_BLA:
#if 0
					/* opcion: no los guardo */
					while ( (j=tipo_char(b1[p1])) == TC_BLA)
					       p1++;	
#endif
					/* opcion: los guardo */
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;

					break;

				/* coma */
				case TC_CCE:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* punto */
				case TC_PNT:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* parentesis abre */
				case TC_PAA:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* parentesis cierra */
				case TC_PAC:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* fin de linea */
				case TC_EOL:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					p1++;
					f1=0;
					break;

				/* caracteres varios */
				case TC_CVR:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* fin de linea */
				default:
					printf ("Default, algo salio mal  !!!\n\n");
					f1=0;
					break;
			}

		} /* while */



		if (gp_verbose)
			printf ("termine de parsear file \n");


		/* verifico si hay que sacar output  en minusculas */
		if (gp_minusculas)
		{
			for (j=0; j< q_tk; j++)
				strcpy(tk[j],pasar_a_minusc(tk[j]));
		}

#if 0
		/* si esta usando tabla de marcas ... verificar si hay que taggear */
		if (gp_tabmrk)
		{
			for (j=0; j< q_tk; j++)
				if (es_word(tk[j]) || es_puntuacion(tk[j]) )
					strcpy(tk[j],bm_tag(tk[j]));
		}
#endif



		/* hay que forzar  string EOL al final de la linea */
		if (gp_eol)
			strcpy(tk[q_tk++],"EOL");


		/* salida en formato token columnar */
		if (gp_fsentencia == 0)
		{


			/* pidio nivel de descripcion en salida ... agrego la sentencia */
			if (gp_niveldes)
				fprintf (hfout,"%s\n",b1);


			/* grabo los tokens encontrados */
			for (j=0; j< q_tk; j++)
			{
				switch (gp_niveldes)
				{

					case 0:
						fprintf (hfout,"%s\n",tk[j]);
						break;

					case 1:
						fprintf (hfout,"%3d,%s\n",j,tk[j]);
						break;

					default:
						fprintf (hfout,"%s\n",tk[j]);
						break;
				}


				if (gp_verbose)
					printf ("%3d,%s\n",j,tk[j]);

			}



#if 0
			/* agrego termino EOL para indentificar donde termino
			 * esto ya que tal vez haya un . en mitad de linea 
			 */
			if (gp_eol)
				fprintf (hfout,"%s\n","EOL");

#endif
		}



		/* salida en formato sentencia */
		if (gp_fsentencia == 1)
		{


			/* grabo los tokens encontrados */
#if 0
			fprintf (hfout,"%s\n",b1);
#endif

			for (j=0; j< q_tk; j++)
			{
#if 0
				fprintf (hfout,"%3d,%s\n",j,tk[j]);
#endif
				fprintf (hfout,"%s",tk[j]);

				if (gp_verbose)
					printf ("%3d,%s\n",j,tk[j]);

			}

#if 0
			/* agrego termino EOL para indentificar donde termino
			 * esto ya que tal vez haya un . en mitad de linea 
			 */
			if (gp_eol)
				fprintf (hfout,"%s\n","EOL");
			else
				fprintf (hfout,"\n");
#endif


			/* se termino la linea */
			fprintf (hfout,"\n");

		}


		if (gp_niveldes)
			fprintf (hfout,"\n\n");


		if (gp_verbose)
		{
			printf ("\n");
		}




		/* 
		 * Termine todo lo que tenia que hacer con esta linea,
		 * sumo lineas 
		 *
		 */

		q_lin++;


	    } /* if ... no esta vacia la linea */

	}  /* while fgets ... */


	
	if (gp_verbose)
	{
		printf ("Cant de lineas procesadas %d\n",q_lin);
		printf ("Cant de encuentros de pal %d\n",gc_pal_e);
		printf ("\n");
		printf ("Cant de parseadas bien    %d\n",tok_si);
		printf ("Cant de parseadas mal     %d\n",tok_no);
		printf ("\n\n\n");
	}


	/* parser1 */




#endif
/* parser */
/* parser */




	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de proc principal \n\n",gp_tm());
	}

}




/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_exec 1
 *
 *	exec aparte ...
 *
 * -----------------------------------------------------------------------------------
 */


/* 
 *	pro_exec1
 *
 *	cuenta caracteres
 *
 */


int	pro_exec1()
{
	int	px,py;
	int	i,j,k;
	int	m1,m2,m3;
	int	f1,f2,f3,f4;
	int	q_lin;
	int	q_tk;
	int	p1,p2,p3,p4;
	
	int	tabla[256];

	char	b1[MAXB];
	char	b2[MAXB];
	char	b3[MAXB];
	char	tk[MAXT][MAXB];

	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra proceso exec 1 \n\n",gp_tm());
	}
		


	/* init de valores */
	for (i=0; i<256; i++)
		tabla[i]=0;

	/* si encuentro caracteres no considerados para el parser, avisar al final de todo el proceso */
	flag_caracteres = 0;


	q_lin=0;
	while (fgets(b1, MAXB, hfinp) != NULL)
	{

	    /* opcion - proceso lineas vacias */
	    if ( 1 )
	    {
 
		if (gp_verbose)
		{
			printf ("Linea  : %d \n\n",q_lin);
			printf ("Buffer :|%s|\n\n",b1);
		}

		f1=1;


		/* comienzo parser de tokens */
		p1=0;
		q_tk=0;

		while ( f1 )
		{
			j=tipo_char(b1[p1]);
			tabla[b1[p1]]++;
			
			if (b1[p1] == 0)
				f1=0;
			else
				p1++;

		} /* while */


		if (gp_verbose)
			printf ("termine de parsear fila \n");
	   }

	   q_lin++;
	}


	/* grabo resultados */

	for (j=0; j< 256; j++)
	{
		fprintf (hfout,"Char %3d %5d \n",j,tabla[j]);

		if (gp_verbose)
			printf ("Char %3d %5d \n",j,tabla[j]);
	}


	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale proceso exec 1 \n\n",gp_tm());
	}


}




/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_exec 2
 *
 *	exec aparte ...
 *
 * -----------------------------------------------------------------------------------
 */




int	pro_exec2()
{

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a proceso exec 2 \n\n",gp_tm());
	}
		


	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de proceso exec 2 \n\n",gp_tm());
	}

}







/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_prueba 1
 *
 *	pruebas ...
 *
 * -----------------------------------------------------------------------------------
 */




int	pro_prue1()
{

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra proceso prueba 1 \n\n",gp_tm());
	}
		

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale proceso prueba 1 \n\n",gp_tm());
	}
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	pro_prueba 2
 *
 *	pruebas ...
 *
 * -----------------------------------------------------------------------------------
 */




int	pro_prue2()
{

	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra proceso prueba 2\n\n",gp_tm());
	}
		
	/* prueba */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale proceso prueba 2 \n\n",gp_tm());
	}
}









/*
 * -----------------------------------------------------------------------------------
 *
 *	abro_files
 *
 *	
 *
 * -----------------------------------------------------------------------------------
 */

int	abro_files()
{


	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a abro_files \n\n",gp_tm());
	}

	if ( ffinp && ((hfinp = fopen (finp,"r")) == NULL) )
	{
		error(101);
	}

	if ( ffout && ((hfout = fopen (fout,"w")) == NULL) )
	{
		error(102);
	}

	if ( ffou2 && ((hfou2 = fopen (fou2,"w")) == NULL) )
	{
		error(103);
	}

	if ( ffaux && ((hfaux = fopen (faux,"w")) == NULL) )
	{
		error(104);
	}
	
	if ( fflog && ((hflog = fopen (flog,"w")) == NULL) )
	{
		error(105);
	}




	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de abro_files \n\n",gp_tm());
	}


}



/*
 * -----------------------------------------------------------------------------------
 *
 *	cierro_files
 *
 *	
 *
 * -----------------------------------------------------------------------------------
 */


int	cierro_files()
{

	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Entro a cierro_files \n\n",gp_tm());
	}


	if ( ffinp)
		fclose(hfinp);

	if ( ffout)
		fclose(hfout);

	if ( ffou2)
		fclose(hfou2);

	if ( ffaux)
		fclose(hfaux);

	if ( fflog)
		fclose(hflog);



	/* proceso */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de cierro_files \n\n",gp_tm());
	}



}






/*
 * -----------------------------------------------------------------------------------
 *
 *	mostrar_cargas
 *
 *	mostrar resultados de cargas, si los hubo
 *
 * -----------------------------------------------------------------------------------
 */

int	mostrar_cargas()
{

	int px,py;

	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Entra a mostrar cargas \n\n",gp_tm());
	}

	/* si hubo cargas, las muestro aca */

	/* proceso  */
	if (gp_fverbose("d1"))
	{	printf ("%s Sale de mostrar cargas \n\n",gp_tm());
	}

}








/*
 * -----------------------------------------------------------------------------------
 *
 *	gna
 *
 *	genera numero al azar
 *	numero = rand () % (N-M+1) + M;   // Este está entre M y N
 *
 * -----------------------------------------------------------------------------------
 */


int	gna(min,max)
int	min;
int	max;
{
	int nro;

	nro = rand() % (max-min+1) + min;

	return nro;
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gnf
 *
 *	genera numero al azar
 *	numero = rand () % (N-M+1) + M;   // Este está entre M y N
 *
 * -----------------------------------------------------------------------------------
 */


char	*gnf(mes)
int	mes;
{
	static	char	fecha[16];
	int	a,m,d;

	a = 2018;

	m = mes+1;

	if ( m == 2 )		
		d = gna(1,28);

	if ( m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		d = gna(1,31);

	if ( m == 4 || m == 6 || m == 9 || m == 11 )
		d = gna(1,30);


	sprintf (fecha,"%04d%02d%02d",a,m,d);

	return fecha;
}





/*
 * -----------------------------------------------------------------------------------
 *
 *	gnh
 *
 *	genera hora al azar
 *	numero = rand () % (N-M+1) + M;   // Este está entre M y N
 *
 * -----------------------------------------------------------------------------------
 */


char	*gnh(desde,hasta)
int	desde;
int	hasta;
{
	static	char	hora[16];
	int	h,m,s;

	h = gna(desde,hasta);
	m = gna(0,59);
	s = gna(0,59);

	sprintf (hora,"%02d%02d%02d",h,m,s);

	return hora;
}






/*
 * -----------------------------------------------------------------------------------
 *
 *	gsf 
 *
 *	fecha en formato mas 'readabily' para imprimir
 *
 * -----------------------------------------------------------------------------------
 */



char	*gsf(f)
char	*f;
{
	static	char	fecha[16];
	int	a,m,d;

	char	s[16];

	
	memset (s,0,16);
	strncpy(s,f,4);
	a = atoi(s);

	memset (s,0,16);
	strncpy(s,f+4,2);
	m = atoi(s);

	memset (s,0,16);
	strncpy(s,f+6,2);
	d = atoi(s);


	sprintf (fecha,"%04d/%02d/%02d",a,m,d);

	return fecha;
}





/*
 * -----------------------------------------------------------------------------------
 *
 *	gsh
 *
 *	Genera string con hora para imprimir
 *
 *
 * -----------------------------------------------------------------------------------
 */


char	*gsh(sh)
char	*sh;
{
	static	char	hora[16];
	int	h,m,s;

	int	h1,m1;
	int	ext;

	char	b[16];

	
	memset (b,0,16);
	strncpy(b,sh,2);
	h = atoi(b);

	memset (b,0,16);
	strncpy(b,sh+2,2);
	m = atoi(b);

	memset (b,0,16);
	strncpy(b,sh+4,2);
	s = atoi(b);

	sprintf (hora,"%02d:%02d:%02d",h,m,s);

	return hora;
}










/*
 * -----------------------------------------------------------------------------------
 *
 *	csv_parser
 *
 *	
 *	parser string tipo csv
 *
 * -----------------------------------------------------------------------------------
 */


/*
 *	
 *	fx		funcion a llamar con cada campo procesado
 *
 */


int	csv_parser(str,fx)
char	*str;
int	(*fx)(int,int,char *);
{
	char	b1[MAXB];
	char	b2[MAXB];
	char	b3[MAXB];

	int	p1,p2;
	int	k;
	int	f1;


	strcpy(b1,str);

	k=0;

		
	f1=1;

	if (f1)
	{
		p1=0;
		p2=0;
		k=0;

		while (b1[p1] )
		{	
			b2[k++] = b1[p1];

			if (b1[p1] == ',' || b1[p1] == '\n')
			{	
				b2[k-1]=0;

				strcpy(b3,b2);
				if (gp_fverbose("d4"))
					printf ("=%02d= %s\n",p2,b3);

				fx(0,p2,b3);

				p2++;
				k=0;
			}

			p1++;
		}
		
		/* termino la linea */
		fx(1,p2," ");
	}
}









/*
 * -----------------------------------------------------------------------------------
 *
 *	(MMM)
 *
 *	Rutinas generales gp_xxxxxx
 *
 *
 * -----------------------------------------------------------------------------------
 */


/* general gp algo */
#if 1




/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_print
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_print()
{
	int i;

	printf ("\n");
	printf ("Cantidad de par   : %2d\n",gp_fq(GP_GET,0) - 1 );
	for (i=0; i<3; i++)
		printf ("Cantidad de par %d : %2d\n",i+1,gp_tpar[i]);
	printf ("\n");

}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_parser
 *
 *	parser general de parametros de input al programa
 * 
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_parser()
{

	int i,j;
	char	prm[MAXV];

	/* excepcion con verbose, por si lo pusieron al final de la linea, por defecto d5 !!! */

	for (i=0; i < gp_fq(GP_GET,0); i++  )
	{	if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v' )
#if 0
	/* si hay parametro -vac=algo ...
	 * esto no funca
	 * aca hay que agregar el 'y no tiene igual. ... '
	 */
		if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v' && !tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
#endif
		{	gp_verbose = 1;
			strcpy(gp_opciones,"d5");
		}
		if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"opciones",6) )
		{	strcpy(gp_opciones,desde_igual( gp_fp(GP_GET,i,(char **)0)));
		}


	}

	for (i=0; i < gp_fq(GP_GET,0);  )
	{

		/* parameter type 1 ... "name" */
		if ( i &&  *( gp_fp(GP_GET,i,(char **)0) + 0) != '-')
		{
			gp_q_partype1++;
			gp_tpar[0]++;

			if (gp_q_partype1 == 1)
			{
				strcpy(finp, gp_fp(GP_GET,i,(char **)0));
				ffinp=1;
			}

			if (gp_q_partype1 == 2)
			{
				strcpy(fout, gp_fp(GP_GET,i,(char **)0));
				ffout=1;
			}

			if (gp_fverbose("d5"))
			{
				printf ("Param tipo 1: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 2 ... "-something" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && !tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype2++;
			gp_tpar[1]++;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v'  )
				gp_verbose = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'h'  )
				gp_help = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'm'  )
				gp_minusculas = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'f'  )
				gp_fsentencia = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'e'  )
				gp_eol = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'i'  )
				gp_reidx = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'p'  )
				gp_pause = 1;

			if (gp_fverbose("d5"))
			{
				printf ("Param tipo 2: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 3 ... "-someoption=somename" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype3++;
			gp_tpar[2]++;

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"inp",3) )
			{
				strcpy(finp,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffinp=1;
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"out",3) )
			{
				strcpy(fout,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffout=1;
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"aux",3) )
			{	
				strcpy(faux,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffaux=1;
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"log",3) )
			{	
				strcpy(flog,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				fflog=1;
			}





			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"nvd",3) )
				gp_niveldes = *desde_igual( gp_fp(GP_GET,i,(char **)0)) - '0';


			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"opciones",6) )
			{	
				strcpy(gp_opciones,desde_igual( gp_fp(GP_GET,i,(char **)0)));
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"prue",4) )
			{	
				strcpy(gp_pruebas,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffprb=gp_pruebas[0]-'0';
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"exec",4) )
			{	
				strcpy(gp_exec,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffexc=gp_exec[0]-'0';
			}

			if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"proc",4) )
			{	
				strcpy(gp_proc,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				ffpro=gp_proc[0]-'0';
			}



			if (gp_fverbose("d5"))
			{
				printf ("Param tipo 3: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* program name */
		if (i==0)
		{	
			if (gp_fverbose("d5"))
			{
				printf ("Programa    : %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* next ... */
		i++;
	}

	/* futuro ...
	 * Hacer una gramatica para la combinacion de comandos
	 * posibles !!
	 *
	 * Por ahora, revisamos combinaciones basicas que
	 * son necesarias entre parametros ...
	 *
	 */

	/* si no pone parametros ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype2 + gp_q_partype3 == 0 )
		gp_help = 1;

#if 0
	/* si no indico ningun  archivo ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype3 == 0 )
		gp_help = 1;
#endif 

	if (gp_fverbose("d5"))
	{
		printf ("\n\n");
	}
} 




/*
 * -----------------------------------------------------------------------------------
 *
 *	tiene_igual
 *
 * -----------------------------------------------------------------------------------
 */


int	tiene_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return flag;
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	desde_igual
 *
 * -----------------------------------------------------------------------------------
 */


char	*desde_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return s+i;
}




/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_init
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_init(vpar_q,vpar_p)
int	vpar_q;
char	**vpar_p;
{
	int i;

	gp_fq(GP_SET,vpar_q);
	gp_fp(GP_SET,0,vpar_p);


}


/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_fp
 *
 * -----------------------------------------------------------------------------------
 */

char	*gp_fp(action,offset,value)
int	action;
int	offset;
char	**value;
{
	static char **gp_value;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return 	*(gp_value+offset);
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_fq(action,value)
 *	
 *	int action
 *	int value
 *	
 *	value:
 *	on fist call, value is a number (typically argc )
 *	after first call, value can be any number, and is not used
 *
 *	returns:
 *	value
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_fq(action,value)
int	action;
int	value;
{
	static int gp_value=0;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return gp_value;
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_test 
 *
 *	
 *
 * -----------------------------------------------------------------------------------
 */


int	gp_test()
{
	int i;

	printf ("Cantidad de par   : %2d\n",gp_fq(GP_GET,0) - 1 );
	for (i=0; i<3; i++)
		printf ("Cantidad de par %d : %2d\n",i+1,gp_tpar[i]);

	printf ("\n");
	for (i=0; i< gp_fq(GP_GET,0); i++)
		printf ("Parametro  %2d     : %s\n",i,gp_fp(GP_GET,i,(char **)0)  );
			
	printf ("\n");
	printf ("\n");
}

/*
 * -----------------------------------------------------------------------------------
 *
 * 	linea_vacia
 *
 *	Determina si una linea esta vacia (generalmente, para lineas leidas de files)
 *	La linea NO esta vacia si contiene al menos 1 caracter distinto de
 *	' ' 	blanco
 *	'\t' 	tab
 *	'\n'	new line
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	linea_vacia(s)
char	*s;
{
	int i,flag;

	i=0;
	flag=1;

	for (i=0; flag && i< strlen(s); i++)
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' )
			flag=0;

	return flag;
}



/*
 * -----------------------------------------------------------------------------------
 *
 * 	error
 *
 *	display de errores
 *	en esta version es display de un numero
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	error(value)
int	value;
{
	printf ("Error: %d\n",value);
	printf ("usar -h para help\n");
	exit(0);
}





/*
 * -----------------------------------------------------------------------------------
 *
 *	tipo_char
 *
 *	ATENCION:
 *	Falta contemplar que hacemos con el caracter '_' !!!!
 *	Por ahora lo incluyo en letras, porque si no, me separa el tag de las palabras
 *	Si voy a parsear corpus sin tag ... lo tengo que sacar de la lista !!!
 *
 *	0	fin de linea
 *	1	blanco o tab
 *	2	otra cosa ( x ahora ... )
 *
 * -----------------------------------------------------------------------------------
 */



int	tipo_char(c)
char	c;
{
	int x;

	x=TC_RST;

	/* para archivos fortran de hita */
	if (c == '\n' || c == 13 )
		x = TC_EOL;

	if (c == ' ' || c == '\t' )
		x = TC_BLA;

	if (c == '_' )
		x = TC_GBJ;

	if (c == ',' || c == ';' || c == ':' || c == '-' || c == '/' )
		x = TC_CCE;

	if (c == '.' )
		x = TC_PNT;

	if (c == '(' || c == '[' || c == '{' )
		x = TC_PAA;

	if (c == ')' || c == ']' || c == '}' )
		x = TC_PAC;

	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z' )
		x = TC_LET;

	/* fortran */
	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z' || c == '_')
		x = TC_LET;

	if (c >= '0' && c <= '9' )
		x = TC_NUM;

	/* agrego los que vienen de analizar fuentes fortran */
	if (c == '\'' || c == '%' || c == '!' || c == '*' )
		x = TC_CVR;

	if (c == '"' || c == '&' || c == '+' || c == '=' || c == '>' || c == '<' || c == '?' )
		x = TC_CVR;

	return x;
}





/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_numero
 *
 *	funcion para determinar si caracter es numero
 *
 *
 * -----------------------------------------------------------------------------------
 */




int	es_numero(c)
char	c;
{
	int x;

	x=0;
	if ( c >= '0' && c <= '9' )
		x=1;

	return x;
}


/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_num_tk
 *
 *	funcion para determinar si string es numero
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	es_num_tk(s)
char	*s;
{
	int i,x;

	x=1;
	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < '0' || s[i] > '9' )
			x=0;

	}

	return x;
}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_puntuacion
 *
 *	funcion para determinar si es simbolo de puntuacion
 *
 *
 * -----------------------------------------------------------------------------------
 */




int	es_puntuacion(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] != '.' && s[i] != ',' && s[i] != ':' && s[i] != ';' )
			x=0;
	}

	return x;

}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	es_word
 *
 *	funcion para determinar si es word o no
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	es_word(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < 'A' || s[i] > 'z' || ( s[i] > 'Z' && s[i] < 'a')  )
			x=0;
	}

	return x;

}

/*
 * -----------------------------------------------------------------------------------
 *
 * 	char_demed
 *
 *	caracteres utilizados normalmente en frases de medidas 
 *	1 cm x 1 cm ( 'x' ) y similares
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	char_demed(c)
char	c;
{
	int	x;

	x=0;
	if ( c == 'e' || c == 'E' || c == 'x' || c == 'X' )
		x=1;

	return x;
}



/*
 * -----------------------------------------------------------------------------------
 *
 * 	uso
 *
 *	texto para describir el uso de la herramienta
 *
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_uso(x)
int	x;
{
	printf ("Usage: \n\n");
	printf ("inp_file out_file                   inp_file: texto input  out_file: archivo de salida         \n");
	printf ("-inp=inp_file -out=out_file         inp_file: texto input  out_file: archivo de salida         \n");
	printf ("-h                                  help                                                       \n");
	printf ("-v                                  verbose ... muestra cierta informacion de proceso          \n");
	printf ("                                                                                               \n");
	printf ("-inp=f1 -out=f2 -pruebas=6          f1 es ordenado por PER - Va cargando todas las trx x per   \n");
	printf ("                                                                                               \n");
	printf ("-opciones=AABBCC...                 AA es del formato: letra-numero  ej:  -opciones=d4         \n");
	printf ("          dN     (va con -v )       (debug) Muestra distintos niveles de informacion           \n");
	printf ("                                    0 no imprime, 1 basico, 2 y 3 debug, 4 full debug          \n");
	printf ("\n\n\n");

	exit(x);
}


/*
 * -----------------------------------------------------------------------------------
 *
 * 	gp_default
 *
 * 	inicializa parametros de funcionamiento default
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_default()
{
	gp_help=0;
	gp_verbose=0;

	ffinp=0;
	ffout=0;
	ffou2=0;
	ffaux=0;
	fflog=0;


	sprintf (gp_opciones,"%s","______");
	sprintf (gp_pruebas, "%s","______");
	sprintf (gp_exec   , "%s","______");
	sprintf (gp_proc   , "%s","______");

	memset(gp_tpar,0,sizeof(gp_tpar));

}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	pasar_a_minusc
 *
 *
 * -----------------------------------------------------------------------------------
 */

char	*pasar_a_minusc(s)
char	*s;
{
	static char b[MAXB];

	int i,j,k;

	strcpy(b,s);

	for (i=0; i<MAXB && b[i]; i++)
	{
		if ( b[i] >= 'A' && b[i] <= 'Z' )
			b[i] += 32;
	}

	return b;
}







/*
 * -----------------------------------------------------------------------------------
 *
 * 	gp_fverbose
 *
 * -----------------------------------------------------------------------------------
 */




/*
 *	gp_fverbose
 *
 *
 *	Devuelve 1 o 0 si aplica la condicion de verbose
 *	
 *	Las opciones involucradas son:
 *	-v               activa el verbose
 *	-opciones=str    string de condiciones de verbose  (requiere -v )
 *	                 
 *	El string de opciones es del tipo "Ln...(1 o 3)"
 *	Donde:
 *	L       Es la letra (I informativo, D debug, y E ... no me acuerdo
 *	n       Es el nivel
 *	        0 no imprime nada   ( es lo mismo que no poner nada !!! )
 *	        1    imprime cosas basicos, por que rutinas paso etc
 *	        2,3  niveles de debug intermedios
 *	        4    full debug
 *	        5    incluye debug de gp_parse
 *
 * 
 *
 *	
 */


int	gp_fverbose(situacion)
char	*situacion;
{
	int	i,j,k;
	int	sit;

	static	int	f_p=1;
	static	int	f_i=0;
	static	int	f_e=0;
	static	int	f_d=0;

	if ( f_p == 1 && gp_opciones[0] != '_' )
	{	f_p = 0;

		for (i=0; i<strlen(gp_opciones)-1; i=i+2)
		{
			if (*(gp_opciones+i) == 'i' || *(gp_opciones+i) == 'I' )
				f_i = (int) *(gp_opciones+i+1) - '0';
			if (*(gp_opciones+i) == 'e' || *(gp_opciones+i) == 'E' )
				f_e = (int) *(gp_opciones+i+1) - '0';
			if (*(gp_opciones+i) == 'd' || *(gp_opciones+i) == 'D' )
				f_d = (int) *(gp_opciones+i+1) - '0';
		}
	}


	sit = 0;

	if (gp_verbose)
	{

		/* determino si hay que devolver 0 o 1
		 * en base a situacion informada, y 
		 * conjunto de flags y '-opcion=vN'   
		 *
		 */
	
		for (sit=0, i=0; i<strlen(situacion); i=i+2)
		{


#if 0
			printf ("X1 f_P: %d i:%d situaci: %s  opcion: %s f_d: %d sit: %d\n",
				f_p,i,situacion,gp_opciones,f_d,sit);
#endif
	
			if (*(situacion+i) == 'i')
				if ( *(situacion+i+1)-'0' <= f_i )
					sit = 1;
	
			if (*(situacion+i) == 'e')
				if ( *(situacion+i+1)-'0' <= f_e )
					sit = 1;
	
			if (*(situacion+i) == 'd')
				if ( *(situacion+i+1)-'0' <= f_d )
					sit = 1;

#if 0
			printf ("X2 f_P: %d i:%d situaci: %s  opcion: %s f_d: %d sit: %d\n",
				f_p,i,situacion,gp_opciones,f_d,sit);
#endif
		}
	}

	return	sit;
}




/*
 * -----------------------------------------------------------------------------------
 *
 * 	gp_tm
 *
 * -----------------------------------------------------------------------------------
 */




char	*gp_tm()
{
	time_t t;
  	struct tm *tm;

	t=time(NULL);
	tm=localtime(&t);
	strftime(gp_fyh, MAXR , "[%Y/%m/%d %H:%M:%S]", tm);

	return(gp_fyh);
}



/*
 * -----------------------------------------------------------------------------------
 *
 * 	df
 *
 * -----------------------------------------------------------------------------------
 */




char	*df(s)
char	*s;
{
	static	char	nf[MAXF];

	int	i,j,k,f1;

	for ( f1=1, i=0; f1 && i<strlen(s); i++)
		if (s[i] != '.')
			nf[i]=s[i];
		else
			nf[i]=0,f1=0;

	strcat(nf,".dif");


	return nf;
}


#endif
/* general gp algo */




/*
 * -----------------------------------------------------------------------------------
 *
 *	end of source
 *	end of source
 *	end of source
 *	end of source
 *	end of source
 *
 * -----------------------------------------------------------------------------------
 */





/* tes_cpar04 */
#if 0

/*
 *	tes_cpar04.c
 *	
 *	update:		24-09-2018
 *
 *	Incluye funciones:
 *
 *	1) tokenizador
 *	   lee lineas del archivo de input (corpus) y genera listado de tokens 
 *
 *	parser - tokenizador
 *
 * 	Opciones:
 * 	-h   		forma de uso
 *
 * 	( mas ejemplos abajo )
 *
 *
 */


/*
 * 	Ejemplos de uso:
 *
 * 	para el ejemplo ...
 *
 *
 *
 *	1) Generar en salida, todos los tokens del archivo de input, sin modificar texto, en formato columnar ( 1 tkn x lina )
 *
 *	./cpar04 -inp=

 *
 *
 *
 *
 *
 *
 *	1) Generar en salida, todos los tokens del archivo de input, sin modificar, en formato columnar ( 1 tkn x linea)
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt
 *
 * 	./cpar05 f04_neg.txt f04_neg_tkn.txt
 *
 * 	2) Idem, pero forzar al final de cada linea, el token "EOL"
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e
 *
 * 	3) Idem, forzando token "EOL" y pasando todo a minuscula
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m
 *
 * 	4) Idem, forzando token "EOL" , pasando todo a minuscula, y generando formato sentencia ( no columnar )
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m -f
 *
 * 	5) Idem anterior, con alguna informacion de salida 
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m -f -v
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m -f -v  >  ver
 * 	cat ver ... etc
 *
 * 	6) Solamente SIN -f  ...  Agrega informacion en archivo de salida para controlar funcionamiento
 *
 * 	./cpar05 f04_neg.txt f04_neg_tkn.txt -nvd=1
 *
 * 	7) Para usar con un archivo de "marcas" ( para taggear ... )  Al final de este fuente, ejemplo de marcas !!!
 *
 * 	   Atencion !!!  La busqueda en la tabla de marcas NO es case sensitivo ... considerar el uso de -m 
 *
 * 	./cpar05 f04_neg.txt f04_neg_tag.txt -mrk=f04_t1.mrk -f -m -v
 *
 * 	8) Para usar con marcas, pero salida en formato un token por fila, con tag incluido ...
 *
 * 	./cpar05 f04_neg.txt f04_neg_tag.txt -mrk=f04_t1.mrk -m -v
 *
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	DEBUG 0


#define	GP_SET 1
#define	GP_GET 0


int	gp_default();
int	gp_init(int ,char **);
int	gp_test();
int	gp_print();
int	gp_parser();
int	gp_fq(int,int);
char	*gp_fp(int,int,char **);

int	gp_q_partype1=0;	/* parameter type "name" */
int	gp_q_partype2=0;	/* parameter type "-something" */
int	gp_q_partype3=0;	/* parameter type "-someoption=somename" */


int	gp_verbose=0;		/* verbose 0 no 1 si */
int	gp_help=0;		/* help 0 no 1 si */
int	gp_diccionario=0;	/* diccionario 0 no 1 si */
int	gp_minusculas=0;	/* output en minuscula 0 no 1 si */
int	gp_fsentencia=0;	/* archivo de salida en formato sentencias 0 no 1 si */
int	gp_eol=0;		/* fuerzo string EOL al final de la linea ... a veces hay . en medio de la linea */
int	gp_niveldes=0;		/* nivel de descripcion que se vuelca en archivo de salida (solo con fsentencia = 0 ) */
				/* 0 normal 1 sentencia y numero de token 2 .... agrego cosas del diccionario si se usa */
int	gp_tabmrk=0;		/* usar archivo de marcas 0 no 1 si */
int	gp_detneg=0;		/* detectar negacion */
int	gp_tipneg=0;		/* tipo de negacion */


char	*desde_igual(char *s);
char	*pasar_a_minusc(char *s);

int	tiene_igual(char *);
int	linea_vacia(char *);
int	tipo_char(char );
int	es_numero(char);
int	es_num_tk(char *);
int	es_word(char *);
int	es_puntuacion(char *);
int	char_demed(char);
int	mostrar(int,int,char *);
int	separar_seg(char *);

int	error(int);
int	uso(int);

#define	TC_EOL	0
#define	TC_BLA	1
#define	TC_CCE	2	/* algunos caracteres especiales  ',;:/' */
#define	TC_PNT	3	/* punto '.' */
#define	TC_PAA	4	/* parent '([{' */
#define TC_PAC	5	/* parent ')]}' */
#define	TC_LET	6	/* letras */
#define	TC_NUM	7	/* numero */
#define	TC_CVR	8	/* caracteres varios ' % */
#define	TC_RST	99

int	parser1();

#define	MAXV	64	/* buffer chico */
#define	MAXT	200 
#define	MAXB	1024	/* buffer grande */
#define	MAXF	64
#define	MAXP	128	/* maximo de palabras en general */

char	finp[MAXF];
char	fout[MAXF];
char	fdic[MAXF];
char	fmrk[MAXF];

FILE	*hfinp;
FILE	*hfout;
FILE	*hfdic;
FILE	*hfmrk;


int	flag_caracteres;


/*	Estructuras y variables para la base de marcas */

#define	MAXK	64	/* cantidad de marcas */
#define	MAXM	20	/* tamano maximo de palabra / marca */

int	bm_load();
char	*bm_tag(char *);


char	bm_key[MAXK][MAXM];
char	bm_mrk[MAXK][MAXM];

int	q_bm;		/* cantidad de marcas en base */




/* Estructuras para guardar segmentos de la linea
 * seg 0   nro registro
 * seg 1   aff / neg / pos 
 * seg 2   palabra de referencia
 * seg 3   frase 
 *
 */

char	segmento[4][MAXB];
char	marcas[3][10] = { " t1 ", " t2 ", " t3 " };
int	tipo_marca=0;


/*
 *	Estructuras y variables para diccionario de palabras
 *
 *
 */





int	bd_load();			/* funcion de carga de diccionario */

int	q_wrd;				/* cantidad de palabras en diccionario */

typedef	struct	tnode	*nodeptr;
typedef	struct	tnode
{	char	*wrd;
	int	num;
	struct	tnode	*nx;
}	node;

nodeptr	npx,np1,*npa;








/*
 *	Estructuras y variables para lex / yacc
 *
 */


int yyparse();
int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead );

static int globalReadOffset;

int	gc_pal_e;		/* palabra encontrada */

int	gc_si;
int	gc_no;
int	v_flag;
int	l_flag;
int	tok;
int	tok_si;
int	tok_no;

char   *spp      = "                            ";

char 	*globalInputText;
char	buffer[4096];
char	global_ref[MAXP];

char	yy_buffer[64];
char	*yy_ptr;

int	gramatik(char *,int);

int	f_cneg;			/* flag si parser encontro negacion en la linea */
int	f_sneg;			/* flag si parser NO encontro negacion en la linea */

int	f_cb;			/* flag continuo buscando ... (en el abol que arma yacc ) */
int	f_pe_lin;		/* flag palabra encontrada en linea  (en yacc ) */
int	f_pe_ora;		/* flag palabra encontrada en frase nomimal (en yacc) */





/*
 * -----------------------------------------------------------------------------------
 *
 *	( KKK )
 *	main
 *
 *
 *
 * -----------------------------------------------------------------------------------
 */

int	main(argc,argv)
int	argc;
char	**argv;
{

	gp_default();
	gp_init(argc,argv);
	gp_parser();
	gp_print();

	if (gp_help)
	 	uso(0);


	if (gp_verbose)
	{
		printf ("inp %s\n",finp);
		printf ("out %s\n",fout);
		printf ("\n");
	}

	
	if ( (hfinp = fopen (finp,"r")) == NULL )
	{
		error(101);
	}

	if ( (hfout = fopen (fout,"w")) == NULL )
	{
		error(102);
	}


	if (gp_diccionario)
	{
		if ( (hfdic = fopen (fdic,"r")) == NULL )
		{
			error(103);
		}


		bd_load();
	}

	if (gp_tabmrk)
	{
		if ( (hfmrk = fopen (fmrk,"r")) == NULL )
		{
			error(104);
		}

		bm_load();
	}


	parser1();


	fclose(hfinp);
	fclose(hfout);
	if (gp_diccionario)
		fclose(hfdic);
	if (gp_tabmrk)
		fclose(hfmrk);

	if (gp_verbose)
		printf ("fin proceso \n");

	if (flag_caracteres)
	{	
		printf ("Atencion: caracteres no contemplados para parser encontrados en input  \n");
		printf ("Volver a ejecutar con flag -v y revisar salida (buscar \"Caracteres\" ... ) \n");
	}

}


/*
 * -----------------------------------------------------------------------------------
 *
 * 	parser1
 * 	parser de linea de texto
 *
 *
 * -----------------------------------------------------------------------------------
 */


int	parser1()
{

	int	i,j,k;
	int	m1,m2,m3;
	int	f1,f2,f3,f4;
	int	q_lin;
	int	q_tk;
	int	p1,p2,p3,p4;

	char	b1[MAXB];
	char	b2[MAXB];
	char	b3[MAXB];
	char	tk[MAXT][MAXB];

	/* init de valores para lex / yacc */
	globalInputText = buffer;
	gc_si    = 0;
	gc_no    = 0;
	v_flag   = 1;
	l_flag   = 1;
	gc_pal_e = 0;


	/* zona de intercambio entre lex y yacc */
	memset(yy_buffer,0,sizeof(yy_buffer));
	yy_ptr=yy_buffer;



	/* si encuentro caracteres no considerados para el parser, avisar al final de todo el proceso */
	flag_caracteres = 0;


	q_lin=0;
	while (fgets(b1, MAXB, hfinp) != NULL)
	{

	    /* procesar solo lineas no vacias */
	    if ( !linea_vacia(b1))
	    {
		/* blancos al final */
		for (i=strlen(b1)-1, f4=1 ; i && f4 ; i-- )
			if (b1[i] == ' ' || b1[i] == '\n' )
				b1[i]=0;
			else
				b1[i+1]='\n', b1[i+2]=0, f4=0;
		

 
		f1=1;

		if (gp_verbose)
		{
			printf ("Linea  : %d \n\n",q_lin);
			printf ("Buffer :|%s|\n\n",b1);
		}



		/* Para el corpus de prueba inicial ... 
		 * Los campos son de forma:  nro t1 aff|neg|pos t2 palabra a buscar t3 frase  
		 *
		 * Separo todos los campos para tener en segmentos diferentes la palabra a buscar
		 * y la frase que tenemos que parsear 
		 *
		 * segm1:  nro de linea
		 * segm2:  aff neg pos
		 * segm3:  palabra de referencia ( para ver si esta en el scope de la negacion )
		 * segm4:  frase
		 *
		 *
		 */

		strcpy(b3,b1);
		separar_seg(b3);
		if (gp_verbose)
		{
			printf ("Linea  :  %d \n\n",q_lin);
			printf ("segm1  : >%s<\n",segmento[0]);
			printf ("segm2  : >%s<\n",segmento[1]);
			printf ("segm3  : >%s<\n",segmento[2]);
			printf ("segm4  : >%s<\n",segmento[3]);
			printf ("\n\n");
		}


		/* prep para analizar por tokens */
		memset(b1,0,sizeof(b1));
		strcpy(b1,segmento[3]);

		memset(global_ref,0,sizeof(global_ref));
		strcpy(global_ref,segmento[2]);


		/* prep para analizar la linea con lex / yacc */
		memset(buffer,0,sizeof(buffer));
		strcpy(buffer,segmento[3]);



		/* comienzo parser de tokens */
		p1=0;
		q_tk=0;

		while ( f1 )
		{
			/* controlamos cantidad de tokens ... */
			if (q_tk > MAXT-10)
			{	error(501);
			} 

			j=tipo_char(b1[p1]);

			switch (j)
			{
				/* otro caracter !!! */
				case TC_RST:
					flag_caracteres=1;
					if (gp_verbose)
					{
						printf ("Caracter no definido para parser: %c \n",b1[p1]);
					}
					p1++; 
					break; 

				/* letras */
				/* en los corpus vistos, hay muchas siglas del tipo LD4 ...
				 * que para este caso, deberia ser considerado una palabra o termino
				 */
				case TC_LET:
					p2=0;
					while ( (j=tipo_char(b1[p1])) == TC_LET || \
					        (j == TC_NUM && !char_demed(b1[p1-1])  ) )
						tk[q_tk][p2++]=b1[p1++];
					tk[q_tk][p2]=0;
					q_tk++;
					break;

				/* numeros tenemos que contemplar 3.3 o 3,3 !! */
				case TC_NUM:
					p2=0;
					while ( (j=tipo_char(b1[p1])) == TC_NUM || \
						(tipo_char(b1[p1]) == TC_PNT && tipo_char(b1[p1+1]) == TC_NUM ) || \
						( (b1[p1]) == ',' && tipo_char(b1[p1+1]) == TC_NUM ) )
					{	tk[q_tk][p2]=b1[p1];
						p1++;
						p2++;
					}
					tk[q_tk][p2]=0;
					q_tk++;
					break;

				/* blanco o tab */
				case TC_BLA:
					while ( (j=tipo_char(b1[p1])) == TC_BLA)
					       p1++;	
					break;

				/* coma */
				case TC_CCE:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* punto */
				case TC_PNT:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* parentesis abre */
				case TC_PAA:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* parentesis cierra */
				case TC_PAC:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* fin de linea */
				case TC_EOL:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					p1++;
					f1=0;
					break;

				/* caracteres varios */
				case TC_CVR:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* fin de linea */
				default:
					printf ("Default, algo salio mal  !!!\n\n");
					f1=0;
					break;
			}

		} /* while */


		/* verifico si hay que sacar output  en minusculas */
		if (gp_minusculas)
		{
			for (j=0; j< q_tk; j++)
				strcpy(tk[j],pasar_a_minusc(tk[j]));
		}

		/* si esta usando tabla de marcas ... verificar si hay que taggear */
		if (gp_tabmrk)
		{
			for (j=0; j< q_tk; j++)
				if (es_word(tk[j]) || es_puntuacion(tk[j]) )
					strcpy(tk[j],bm_tag(tk[j]));
		}


		/* hay que forzar  string EOL al final de la linea */
		if (gp_eol)
			strcpy(tk[q_tk++],"EOL");


		/* salida en formato token columnar */
		if (gp_fsentencia == 0)
		{


			/* pidio nivel de descripcion en salida ... agrego la sentencia */
			if (gp_niveldes)
				fprintf (hfout,"%s\n",b1);


			/* grabo los tokens encontrados */
			for (j=0; j< q_tk; j++)
			{
				switch (gp_niveldes)
				{

					case 0:
						fprintf (hfout,"%s\n",tk[j]);
						break;

					case 1:
						fprintf (hfout,"%3d,%s\n",j,tk[j]);
						break;

					default:
						fprintf (hfout,"%s\n",tk[j]);
						break;
				}


				if (gp_verbose)
					printf ("%3d,%s\n",j,tk[j]);

			}



#if 0
			/* agrego termino EOL para indentificar donde termino
			 * esto ya que tal vez haya un . en mitad de linea 
			 */
			if (gp_eol)
				fprintf (hfout,"%s\n","EOL");

#endif
		}



		/* salida en formato sentencia */
		if (gp_fsentencia == 1)
		{


			/* grabo los tokens encontrados */
#if 0
			fprintf (hfout,"%s\n",b1);
#endif

			for (j=0; j< q_tk; j++)
			{
#if 0
				fprintf (hfout,"%3d,%s\n",j,tk[j]);
#endif
				fprintf (hfout,"%s ",tk[j]);

				if (gp_verbose)
					printf ("%3d,%s\n",j,tk[j]);

			}

#if 0
			/* agrego termino EOL para indentificar donde termino
			 * esto ya que tal vez haya un . en mitad de linea 
			 */
			if (gp_eol)
				fprintf (hfout,"%s\n","EOL");
			else
				fprintf (hfout,"\n");
#endif


			/* se termino la linea */
			fprintf (hfout,"\n");

		}


		if (gp_niveldes)
			fprintf (hfout,"\n\n");


		if (gp_verbose)
		{
			printf ("\n");
		}


		if (gp_detneg == 1)
		{




		/*
		 * A este punto, termine de parsear la linea, y guardar todos los 
		 * tokens en vector.
		 *
		 */


		/* parseo la linea entera con lex & yacc */

		if (gp_verbose)
		{
			printf ("Parsing de gramatica ... \n");
			printf ("Palabra que busco ...   |%s|\n",global_ref);
			printf ("|%s|\n\n",buffer);

		}


		/* init de flags e indicadores para detectar negacion y pal en arbol de yacc */
		f_sneg   = 0;
		f_cneg   = 0;
		f_cb     = 1;	/* flag continuo buscando ... (en el abol que arma yacc ) */
		f_pe_lin = 0;	/* flag palabra encontrada en linea  (en yacc ) */
		f_pe_ora = 0;	/* flag palabra encontrada en frase nomimal (en yacc) */


    		globalReadOffset = 0;
    		tok=yyparse();

		/* resgistro para estadistica final */
		if (tok == 0)
			tok_si++;
		else
			tok_no++;

		if (f_sneg)
			gc_no++;
		if (f_cneg)
			gc_si++;

		if (f_pe_lin)
			gc_pal_e++;


		if (gp_verbose)
		{
			if (tok != 0 )
				printf ("ERROR ... No pudo parsear la lin : %d ... Sigue en prox. linea \n\n",q_lin);
		}


		if (gp_verbose)
		{
			printf ("\n\n");

			printf ("Resultado del parser           : %d\n",tok);
			printf ("Palabra  encontrada en linea ? : %d\n",f_pe_lin);
			printf ("Palabra  encontrada en scope ? : %d\n",f_pe_ora);

			printf ("\n\n\n - - - - - - - - - - - - \n\n\n");

		}


		} /* if (detneg ... )


		/* 
		 * Termine todo lo que tenia que hacer con esta linea,
		 * sumo lineas 
		 *
		 */

		q_lin++;


	    } /* if ... no esta vacia la linea */

	}  /* while fgets ... */


	
	if (gp_verbose)
	{
		printf ("Cant de lineas procesadas %d\n",q_lin);
		printf ("Cant de encuentros de pal %d\n",gc_pal_e);
		printf ("\n");
		printf ("Cant de parseadas bien    %d\n",tok_si);
		printf ("Cant de parseadas mal     %d\n",tok_no);
		printf ("\n");
#if 0
		printf ("Cant de frase sin neg     %d\n",gc_no);
		printf ("Cant de frase con neg     %d\n",gc_si);
#endif
		printf ("\n\n\n");
	}


	/* parser1 */
}



/*
 * -----------------------------------------------------------------------------------
 *
 *	separar_seg
 *
 *	separa la linea del corpus en segmentos ...
 *
 * -----------------------------------------------------------------------------------
 */



int	separar_seg(buffer1)
char	*buffer1;
{
	int	i,j,k;
	int	p1,p2,p3,p4;
	int	f1,f2,f3,f4;
	int	m1;

	char	b3[MAXB];


	p1=0;
	p2=0;
	m1=0;

	/* set de marcas */
	if (tipo_marca == 0)
	{	for (i=0, !tipo_marca; i<strlen(buffer1); i++)
		{
			if (!tipo_marca && strncmp(buffer1+i," t1 ",4) == 0)
			{
				strcpy(marcas[0]," t1 ");
				strcpy(marcas[1]," t2 ");
				strcpy(marcas[2]," t3 ");
				tipo_marca = 1;
			}

			if (!tipo_marca && strncmp(buffer1+i," T1 ",4) == 0)
			{
				strcpy(marcas[0]," T1 ");
				strcpy(marcas[1]," T2 ");
				strcpy(marcas[2]," T3 ");
				tipo_marca = 2;
			}

			if (!tipo_marca && strncmp(buffer1+i," TAB1 ",6) == 0)
			{
				strcpy(marcas[0]," TAB1 ");
				strcpy(marcas[1]," TAB2 ");
				strcpy(marcas[2]," TAB3 ");
				tipo_marca = 3;
			}
		}


		if (gp_verbose)
		{
			printf ("\n");
			printf ("Tipo de marca :  %d   |%s|  |%s|  |%s|  \n\n",tipo_marca,marcas[0],marcas[1],marcas[2]);
		}
	}




	/* Busco primer segmento           */
	while ( p1 < MAXB - strlen(marcas[m1])  &&  strncmp(buffer1+p1,marcas[m1],strlen(marcas[m1]))  )
		p1++;

	if ( p1 == MAXB - strlen(marcas[m1]) )
	{	error(701);
	}

	strncpy(segmento[0],buffer1+p2,p1-p2);
	segmento[0][p1-p2]=0;
	p2 = p1 + strlen(marcas[m1]);



	/* Busco segundo segmento           */
	m1=1;

	while ( p1 < MAXB - strlen(marcas[m1])  &&  strncmp(buffer1+p1,marcas[m1],strlen(marcas[m1]))  )
		p1++;

	if ( p1 == MAXB - strlen(marcas[m1]) )
	{	error(702);
	}

	strncpy(segmento[1],buffer1+p2,p1-p2);
	segmento[1][p1-p2]=0;
	p2 = p1 + strlen(marcas[m1]);



	/* Busco tercer segmento           */
	m1=2;

	while ( p1 < MAXB - strlen(marcas[m1])  &&  strncmp(buffer1+p1,marcas[m1],strlen(marcas[m1]))  )
		p1++;

	if ( p1 == MAXB - strlen(marcas[m1]) )
	{	error(703);
	}

	strncpy(segmento[2],buffer1+p2,p1-p2);
	segmento[2][p1-p2]=0;
	p2 = p1 + strlen(marcas[m1]);


	/* Busco cuarto segmento 
 	 * OJO: en cuarto segmento NO hago strlen ... -1 como 
	 * en los anteriors, sino ... saco el ultimo new line 
	 * y tecnicamente modifico el contenido del registro
	 */

	strcpy(segmento[3],buffer1+p2);
	segmento[3][strlen(segmento[3])]=0;

	/* ojo !!
	 * se cuelan blancos al segmentar la palabra de ref a buscar
	 * algo anda mal en el parser original ...
	 */

	for (i=strlen(segmento[2])-1; segmento[2][i] == ' '; i--)
		segmento[2][i] = 0;


	/* Pasar a minuscula la palabra buscada, para compatibilidad en las comparaciones */
	strcpy (b3,segmento[2]);
	strcpy (segmento[2],pasar_a_minusc(b3));



#if 0
	/* tengo los 4 segmentos */
	if (gp_verbose)
	{
		printf ("Separar: \n");
		printf ("0: |%s|\n",segmento[0]);
		printf ("1: |%s|\n",segmento[1]);
		printf ("2: |%s|\n",segmento[2]);
		printf ("3: |%s|\n",segmento[3]);
	}
#endif

}





/*
 * -----------------------------------------------------------------------------------
 *
 *	bd_load
 *	carga la base de datos del diccionario
 *
 * -----------------------------------------------------------------------------------
 */


/*
 *	2018-04-21
 *
 *	bd_load
 *	carga la base de datos del diccionario
 *	diccio base: diccio01.txt
 *
 */

int	bd_load()
{
	char	b1[MAXB];
	int	flag,f1;
	int	i,j,k;
	int	ql;

	/* cantidad de palabras en el diccionario */
	q_wrd = 0;

	/* ptr al contenedor de direccion del ultimo nodo de la cadena */
	npa = (nodeptr *) &np1;

	ql=0;
	while (fgets(b1,MAXB,hfdic) != NULL)
	{
		if (!linea_vacia(b1)  && b1[0] != '#' )
		{
			for ( flag=0, j=strlen(b1); !flag && j; j--)
				if (b1[j] == '\n')
					b1[j]=0,flag=1;

			if (gp_verbose)
			{
				printf ("%3d |%s|\n",ql,b1);
			}

			*npa = (nodeptr ) malloc ( sizeof (node));
			(**npa).wrd = ( char *) malloc(strlen(b1)+1);
			sprintf ( (**npa).wrd,"%s",b1);
			(**npa).num = q_wrd+1;
			(**npa).nx = (nodeptr) NULL;
			npa = (nodeptr *) & (*npa)->nx;

			q_wrd++;
			ql++;
		}
	}

	if (gp_verbose)
	{
		printf ("Cantidad de lineas en diccionario   : %6d\n",ql);
		printf ("Cantidad de palabras en diccionario : %6d\n",q_wrd);
	}


	if (gp_verbose)
	{
		printf ("\n\nComprobando integridad del diccionario : \n\n");
	
		i=0;
		npa = (nodeptr *) &np1;

		while ( (*npa) != (nodeptr) NULL )
		{
			printf ("i: %3d  (**npa).num: %3d  (**npa).wrd: |%s|\n",i,(**npa).num,(**npa).wrd);
			npa = (nodeptr *) & (*npa)->nx;
			i++;
		}
	}
}







/*
 *	bm_load
 *	carga la base de datos de marcas
 *
 */

int	bm_load()
{
	char	b1[MAXB];
	char	b2[MAXM];
	int	flag;
	int	p1,p2;
	int	i,j,k;
	int	f1;

	f1=0;
	q_bm=0;
	k=0;

	while (fgets(b1,MAXB,hfmrk) != NULL)
	{
		if (gp_verbose)
		{
			printf ("%3d %s",q_bm,b1);
		}

		if (!linea_vacia(b1)  && b1[0] != '#' )
		{
			f1=1;
		}

		if (f1)
		{
			p1=0;
			p2=0;
			k=0;

			while (b1[p1] )
			{	
				b2[k++] = b1[p1];

				if (b1[p1] == ' ' || b1[p1] == '\n')
				{	
					b2[k-1]=0;

					if (p2 == 0)
					{	strcpy(bm_key[q_bm],b2);

					}

					if (p2 == 4)
					{	strcpy(bm_mrk[q_bm],b2);

					}

					p2++;
					k=0;
				}

				p1++;

			}
		
			/* next ... */
			q_bm++;
			f1=0;

			if (q_bm >= MAXK)
				error(301);
		}
	}

	if (gp_verbose)
	{
		printf ("\n");
		printf ("Cant de lineas en tabla de marcas: %d\n",q_bm);

		for (j=0; j<q_bm; j++)
			printf ("%3d,%-10.10s,%s\n",j,bm_mrk[j],bm_key[j]);

		printf ("\n");

	}

}







/*
 * 	bm_tag
 *
 * 	Concatena a string, el tag correspondiente, si coincide la palabra clave
 *
 */


char	*bm_tag(s)
char	*s;
{
	static char b1[MAXB];

	char	b2[MAXM];
	int	i,j,k;
	int	f1,f2;


	strcpy(b1,s);

	f1=1;

	for ( j=0; f1 && j< q_bm; j++)
	{
		if (strcmp(s,bm_key[j]) == 0)
		{
			f1=0;
			sprintf (b2,"_%s",bm_mrk[j]);
			strcat(b1,b2);
		}
	}

	return b1;
}



/*
 *	gp_print
 *
 */

int	gp_print()
{
	if (gp_verbose)
	{
		printf ("Cant de pars ....  %d\n",gp_fq(GP_GET,0) );
		printf ("Cant de tipo 1 %d\n",gp_q_partype1);
		printf ("Cant de tipo 2 %d\n",gp_q_partype2);
		printf ("Cant de tipo 3 %d\n",gp_q_partype3);
		printf ("\n");
	}
}




/*
 * -----------------------------------------------------------------------------------
 *
 *	gp_parser
 *
 *	parser general de parametros de input al programa
 * 
 *
 * -----------------------------------------------------------------------------------
 */

int	gp_parser()
{

	int i;
	char	prm[MAXV];

	/* verbose on ?, excepcion con verbose, por si lo pusieron al final de la linea !!! */
	for (i=0; i < gp_fq(GP_GET,0); i++  )
		if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v'  )
			gp_verbose = 1;


	for (i=0; i < gp_fq(GP_GET,0);  )
	{

		/* parameter type 1 ... "name" */
		if ( i &&  *( gp_fp(GP_GET,i,(char **)0) + 0) != '-')
		{
			gp_q_partype1++;

			if (gp_q_partype1 == 1)
			{
				strcpy(finp, gp_fp(GP_GET,i,(char **)0));
			}

			if (gp_q_partype1 == 2)
			{
				strcpy(fout, gp_fp(GP_GET,i,(char **)0));
			}

			if (gp_verbose)
			{
				printf ("Param tipo 1: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 2 ... "-something" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && !tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype2++;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v'  )
				gp_verbose = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'h'  )
				gp_help = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'm'  )
				gp_minusculas = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'f'  )
				gp_fsentencia = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'e'  )
				gp_eol = 1;

			if (gp_verbose)
			{
				printf ("Param tipo 2: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 3 ... "-someoption=somename" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype3++;

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"inp",3) )
					strcpy(finp,desde_igual( gp_fp(GP_GET,i,(char **)0)));

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"out",3) )
					strcpy(fout,desde_igual( gp_fp(GP_GET,i,(char **)0)));

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"dic",3) )
				{	gp_diccionario=1;
					strcpy(fdic,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				}

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"mrk",3) )
				{	gp_tabmrk=1;
					strcpy(fmrk,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				}

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"nvd",3) )
					gp_niveldes = *desde_igual( gp_fp(GP_GET,i,(char **)0)) - '0';

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"dng",3) )
				{	gp_detneg = 1;
					gp_tipneg = 1;
					strcpy(prm,desde_igual( gp_fp(GP_GET,i,(char **)0)));
					if (strncmp(pasar_a_minusc(prm),"lex",3) == 0)
						gp_tipneg = 1;
					if (strncmp(pasar_a_minusc(prm),"nga",3) == 0)
						gp_tipneg = 2;
				}


			if (gp_verbose)
			{
				printf ("Param tipo 3: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* program name */
		if (i==0)
		{	
			if (gp_verbose)
			{
				printf ("Name:  %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* next ... */
		i++;
	}

	/* si no pone parametros ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype2 + gp_q_partype3 == 0 )
		gp_help = 1;

	/* si no indico ningun  archivo ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype3 == 0 )
		gp_help = 1;

} 




/*
 *	tiene_igual
 *
 */


int	tiene_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return flag;
}



/*
 *	desde_igual
 *
 */


char	*desde_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return s+i;
}




/*
 *	gp_init
 *
 */

int	gp_init(vpar_q,vpar_p)
int	vpar_q;
char	**vpar_p;
{
	int i;

	gp_fq(GP_SET,vpar_q);
	gp_fp(GP_SET,0,vpar_p);


}


/*
 *	gp_fp
 *
 */

char	*gp_fp(action,offset,value)
int	action;
int	offset;
char	**value;
{
	static char **gp_value;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return 	*(gp_value+offset);
}



/*
 *	gp_fq(action,value)
 *	
 *	int action
 *	int value
 *	
 *	value:
 *	on fist call, value is a number (typically argc )
 *	after first call, value can be any number, and is not used
 *
 *	returns:
 *	value
 */

int	gp_fq(action,value)
int	action;
int	value;
{
	static int gp_value=0;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return gp_value;
}


int	gp_test()
{
	int i;

	printf ("%d\n",gp_fq(GP_GET,0) );
	for (i=0; i< gp_fq(GP_GET,0); i++)
	{
		printf ("%d %s\n",i,gp_fp(GP_GET,i,(char **)0)  );
	}
			
}

int	linea_vacia(s)
char	*s;
{
	int i,flag;

	i=0;
	flag=1;

	for (i=0; flag && i< strlen(s); i++)
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' )
			flag=0;

	return flag;
}


int	error(value)
int	value;
{
	printf ("Error: %d\n",value);
	printf ("usar -h para help\n");
	exit(0);
}

/*
 *	tipo_char
 *
 *	ATENCION:
 *	Falta contemplar que hacemos con el caracter '_' !!!!
 *	Por ahora lo incluyo en letras, porque si no, me separa el tag de las palabras
 *	Si voy a parsear corpus sin tag ... lo tengo que sacar de la lista !!!
 *
 *	0	fin de linea
 *	1	blanco o tab
 *	2	otra cosa ( x ahora ... )
 *
 */

int	tipo_char(c)
char	c;
{
	int x;

	x=TC_RST;

	if (c == '\n' )
		x = TC_EOL;

	if (c == ' ' || c == '\t' )
		x = TC_BLA;

	if (c == ',' || c == ';' || c == ':' || c == '-' || c == '/' )
		x = TC_CCE;

	if (c == '.' )
		x = TC_PNT;

	if (c == '(' || c == '[' || c == '{' )
		x = TC_PAA;

	if (c == ')' || c == ']' || c == '}' )
		x = TC_PAC;

	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z' || c == '_')
		x = TC_LET;

	if (c >= '0' && c <= '9' )
		x = TC_NUM;

	if (c == '\'' || c == '%' )
		x = TC_CVR;

	return x;
}

int	es_numero(c)
char	c;
{
	int x;

	x=0;
	if ( c >= '0' && c <= '9' )
		x=1;

	return x;
}


/*
 * 	es_num_tk
 * 	devuelve true si string esta compuesto solo de numeros
 *
 */

int	es_num_tk(s)
char	*s;
{
	int i,x;

	x=1;
	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < '0' || s[i] > '9' )
			x=0;

	}

	return x;
}








int	es_puntuacion(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] != '.' && s[i] != ',' && s[i] != ':' && s[i] != ';' )
			x=0;
	}

	return x;

}



int	es_word(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < 'A' || s[i] > 'z' || ( s[i] > 'Z' && s[i] < 'a')  )
			x=0;
	}

	return x;

}



int	char_demed(c)
char	c;
{
	int	x;

	x=0;
	if ( c == 'e' || c == 'E' || c == 'x' || c == 'X' )
		x=1;

	return x;
}


int	mostrar(t_case,n_token,s_token)
int	t_case;
int	n_token;
char	*s_token;
{

	if (gp_verbose)
	{
		printf ("t: %3d (%2d)   %s \n", n_token,t_case,s_token);
	}
}


int	uso(x)
int	x;
{
	printf ("Usage: \n");
	printf ("inp_file out_file                   inp_file: texto input  out_file: archivo de salida\n");
	printf ("-inp=inp_file -out=out_file         inp_file: texto input  out_file: archivo de salida\n");
	printf ("-h                                  help                                              \n");
	printf ("-v                                  verbose ... muestra cierta informacion de proceso \n");
	printf ("-m                                  salida a archivo de output en minuscula           \n");
	printf ("-f                                  salida a archivo de output en formato sentencia   \n");
	printf ("-e                                  fuerza string \"EOL\" al final de cada sentencia  \n");
	printf ("-nvd=N                              Nivel de descripcion en archivo de salida (solo sin -f) \n");
	printf ("                                    0 Sin descripcion  \n");
	printf ("                                    1 Agrega la sentencia y numero de token \n");
	printf ("                                    2 Datos del diccionario (tags) \n");


	exit(x);
}


/*
 * 	gp_default
 *
 * 	inicializa parametros de funcionamiento default
 *
 */

int	gp_default()
{
	gp_help=0;
	gp_verbose=0;
	gp_diccionario=0;
	gp_minusculas=0;
	gp_fsentencia=0;
	gp_eol=0;
	gp_niveldes=0;
	gp_tabmrk=0;
	gp_detneg=0;
	gp_tipneg=0;
}




/*
 * 	pasar_a_minusc
 *
 *
 */

char	*pasar_a_minusc(s)
char	*s;
{
	static char b[MAXB];

	int i,j,k;

	strcpy(b,s);

	for (i=0; i<MAXB && b[i]; i++)
	{
		if ( b[i] >= 'A' && b[i] <= 'Z' )
			b[i] += 32;
	}

	return b;
}


/*
 * -----------------------------------------------------------------------------------
 *
 *	ATENCION !!
 *
 *	Aqui van las rutinas de soporte a las actividades de lex & yacc
 *
 *
 * -----------------------------------------------------------------------------------
 *
 */






/*
 * 	readInputForLexer
 *
 *	ajusta funcionamiento del lexer para poder ler de strings
 *
 *
 */



int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead ) 
{
    int numBytesToRead = maxBytesToRead;
    int bytesRemaining = strlen(globalInputText)-globalReadOffset;

    int i;


    if ( numBytesToRead > bytesRemaining ) 
    {    
        numBytesToRead = bytesRemaining; 
    }

    for ( i = 0; i < numBytesToRead; i++ ) 
    {
        buffer[i] = globalInputText[globalReadOffset+i];
    }

    *numBytesRead = numBytesToRead;
    globalReadOffset += numBytesToRead;
    return 0;
}


/*
 * 	gramatik
 *
 *	algunas funciones de apoyo al parser
 *
 *
 */

int	gramatik(s,reduccion_neg)
char	*s;
int	reduccion_neg;
{
	int	f1;

	f1=0;

	if ( strcmp(s,global_ref) == 0)
	{	
		f_pe_lin = 1;
		f1=1;
	}


	if (f_cb)
	{
		if (reduccion_neg == 1)
		{
			if (f_pe_lin)
			{
				f_pe_ora = 1;
				f_cb = 0;
			}
		}
	}

	return f1;
}





/* -------------- end of source --------------------- */
/* -------------- end of source --------------------- */
/* -------------- end of source --------------------- */
/* -------------- end of source --------------------- */





/*
 * 	Archivo de marcas
 *
 * 	ejemplo !!
 *
 */



#if 0

no no RN 0.999297 NEG

ni ni CC 0.834853 CNEG

pero pero CC 0.999902 ENDNEG

sin sin SP 1 TNEG

se ser VMI000 1 VSE

observar observar VMIP3S0 0.989241 OBS
observa observar VMIP3S0 0.989241 OBS
observada observar VMP00SF 1 OBS
observadas observar VMP00PF 1 OBS
observadose observadose VMSP3S0 1 OBS
observan observar VMIP3P0 1 OBS
observando observar VMG0000 1 OBS
observandosse observandosse NCMS000 1 OBS
observaron observar VMIS3P0 1 OBS
observo observar VMIP1S0 1 OBS

detectar detectar VMP00SM 1 DET
detectado detectar VMP00SM 1 DET
detectaron detectar VMIS3P0 1 DET
detecto detectar VMIP1S0 1 DET

evidenciar evidencia NCFS000 0.614458 EVI
evidencia evidencia NCFS000 0.614458 EVI
evidencia evidenciar VMIP3S0 0.373494 EVI
evidencias evidencia NCFP000 0.989726 EVI

visualizar visualizar VMIP3S0 0.989236 VIS
visualiza visualizar VMIP3S0 0.989236 VIS
visualizacin visualizacin NCMS000 0.677562 VIS
visualizacion visualizacion NCFS000 1 VIS
visualizan visualizar VMIP3P0 1 VIS
visualizando visualizar VMG0000 1 VIS
visualizar visualizar VMN0000 1 VIS
visualizo visualizar VMIP1S0 1 VIS

identificar identificar VMN0000 1 IDE
identifica identificar VMIP3S0 0.989241 IDE
identifican identificar VMIP3P0 1 IDE
identificando identificar VMG0000 1 IDE

#endif




/* ----------- end of file tes_cpar04.c ------------- */
/* ----------- end of file tes_cpar04.c ------------- */
/* ----------- end of file tes_cpar04.c ------------- */
/* ----------- end of file tes_cpar04.c ------------- */




#if 0



/*
 *	tes_reglas01.c
 *	
 *	aplica parsing de reglas "laxas"
 *	( al contrario de las lex / yacc que son mas "rigidas" )
 *
 *	parser - tokenizador
 *	(puede usar diccionario)
 *
 * 	Opciones:
 * 	-h   		forma de uso
 *
 * 	( mas ejemplos abajo )
 */


/*
 * 	Ejemplos de uso:
 *
 * 	para el ejemplo ...
 *
 *
 *
 *
 * 	f04_neg.txt               archivo de input, con texto de trabajo original, formato sentencias
 *
 *
 *
 *
 *
 *	1) Generar en salida, todos los tokens del archivo de input, sin modificar, en formato columnar ( 1 tkn x linea)
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt
 *
 * 	./cpar05 f04_neg.txt f04_neg_tkn.txt
 *
 * 	2) Idem, pero forzar al final de cada linea, el token "EOL"
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e
 *
 * 	3) Idem, forzando token "EOL" y pasando todo a minuscula
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m
 *
 * 	4) Idem, forzando token "EOL" , pasando todo a minuscula, y generando formato sentencia ( no columnar )
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m -f
 *
 * 	5) Idem anterior, con alguna informacion de salida 
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m -f -v
 *
 * 	./cpar05 -inp=f04_neg.txt -out=f04_neg_tkn.txt -e -m -f -v  >  ver
 * 	cat ver ... etc
 *
 * 	6) Solamente SIN -f  ...  Agrega informacion en archivo de salida para controlar funcionamiento
 *
 * 	./cpar05 f04_neg.txt f04_neg_tkn.txt -nvd=1
 *
 * 	7) Para usar con un archivo de "marcas" ( para taggear ... )  Al final de este fuente, ejemplo de marcas !!!
 *
 * 	   Atencion !!!  La busqueda en la tabla de marcas NO es case sensitivo ... considerar el uso de -m 
 *
 * 	./cpar05 f04_neg.txt f04_neg_tag.txt -mrk=f04_t1.mrk -f -m -v
 *
 * 	8) Para usar con marcas, pero salida en formato un token por fila, con tag incluido ...
 *
 * 	./cpar05 f04_neg.txt f04_neg_tag.txt -mrk=f04_t1.mrk -m -v
 *
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	DEBUG 0


#define	GP_SET 1
#define	GP_GET 0


int	gp_default();
int	gp_init(int ,char **);
int	gp_test();
int	gp_print();
int	gp_parser();
int	gp_fq(int,int);
char	*gp_fp(int,int,char **);

int	gp_q_partype1=0;	/* parameter type "name" */
int	gp_q_partype2=0;	/* parameter type "-something" */
int	gp_q_partype3=0;	/* parameter type "-someoption=somename" */


int	gp_verbose=0;		/* verbose 0 no 1 si */
int	gp_help=0;		/* help 0 no 1 si */
int	gp_diccionario=0;	/* diccionario 0 no 1 si */
int	gp_minusculas=0;	/* output en minuscula 0 no 1 si */
int	gp_fsentencia=0;	/* archivo de salida en formato sentencias 0 no 1 si */
int	gp_eol=0;		/* fuerzo string EOL al final de la linea ... a veces hay . en medio de la linea */
int	gp_niveldes=0;		/* nivel de descripcion que se vuelca en archivo de salida (solo con fsentencia = 0 ) */
				/* 0 normal 1 sentencia y numero de token 2 .... agrego cosas del diccionario si se usa */
int	gp_tabmrk=0;		/* usar archivo de marcas 0 no 1 si */


char	*desde_igual(char *s);
char	*pasar_a_minusc(char *s);

int	separar_seg(char *);

int	tiene_igual(char *);
int	linea_vacia(char *);
int	tipo_char(char );
int	es_numero(char);
int	es_num_tk(char *);
int	es_word(char *);
int	es_puntuacion(char *);
int	char_demed(char);
int	mostrar(int,int,char *);
int	clasificar(int );

int	error(int);
int	uso(int);

#define	TC_EOL	0
#define	TC_BLA	1
#define	TC_CCE	2	/* algunos caracteres especiales  ',;:/' */
#define	TC_PNT	3	/* punto '.' */
#define	TC_PAA	4	/* parent '([{' */
#define TC_PAC	5	/* parent ')]}' */
#define	TC_LET	6	/* letras */
#define	TC_NUM	7	/* numero */
#define	TC_CVR	8	/* caracteres varios ' % */
#define	TC_EOS	91	/* fin de string en C ... 0 */
#define	TC_RST	99

int	parser1();

#define	MAXT	200
#define	MAXB	1024
#define	MAXF	64

char	finp[MAXF];
char	fout[MAXF];
char	fdic[MAXF];
char	fmrk[MAXF];

FILE	*hfinp;
FILE	*hfout;
FILE	*hfdic;
FILE	*hfmrk;


int	flag_caracteres;


/*	Estructuras y variables para la base de marcas */

#define	MAXK	64	/* cantidad de marcas */
#define	MAXM	20	/* tamano maximo de palabra / marca */

int	bm_load();
char	*bm_tag(char *);


char	bm_key[MAXK][MAXM];
char	bm_mrk[MAXK][MAXM];

int	q_bm;		/* cantidad de marcas en base */



/*	Estructuras y variables para base de datos (diccionario ) */



int	q_wrd;				/* palabras en diccionario */

int	bd_load();


typedef	struct	tnode	*nodeptr;
typedef	struct	tnode
{	char	*wrd;
	int	num;
	struct	tnode	*nx;
}	node;

nodeptr	npx,np1,*npa;



/*
 * definicion antigua ...
 *
 */

typedef	struct
{	struct	palabra	*nx;
	int	ty;
	char	*tx;	
}	bd_type;


bd_type	*bd_first ;











/* Estructuras para guardar segmentos de la linea
 * seg 0   nro registro
 * seg 1   aff / neg / pos 
 * seg 2   palabra de referencia
 * seg 3   frase 
 *
 */

char	segmento[4][MAXB];
char	*marcas[3] = { " T1 ", " T2 ", " T3 " };



int	q_mkc;
char	mkc[][64] = { "no/ST 3 se/ST 2 obser/SN 3 REF" };

/*
 * Reglas de clasificacion
 */
 
int	nregla;
int	fregla;

int	pres_reglas();

int	cant_reglas = 7;

char	*regla1 = " no/ST   <tk ... >  se/ST    <tk ... >  obser/SN | visua/SN | ident/SN | detec/SN | evide/SN | ven/ST | produ/SN  <tk ... >  REF " ;

char	*regla2 = " no/ST   <tk ... >  obser/SN | prese/SN <tk ... >  REF ";

char	*regla3 = " sin/ST  <tk ... >  evide/SN <tk ... >  REF ";

char	*regla4 = " no/ST   <tk ... >  se/ST    <tk ... >  obser/SN | visua/SN | ident/SN | detec/SN   <tk ... > ni/ST | compat/SN  <tk ... >  REF ";

char	*regla5 = " sin/ST  <tk ... >  obser/SN | visua/SN   <tk ... >   ni/ST  <tk ... >  REF ";

char	*regla6 = " no/ST | sin/ST  REF ";

char	*regla7 = " no/ST   <tk ... >  se/ST    <tk ... >   logra/SN  <tk ... > obser/SN | visua/SN | ident/SN | detec/SN   <tk ... >   REF ";


/*
 *	Estructuras para guardar "reglas" de gramatica "mas laxa"
 *
 */


#if 0



int	q_reg;				/*  cantidad de reglas */

int	bd_load();


typedef	struct	tnode	*nodeptr;
typedef	struct	tnode
{	char	*wrd;
	int	num;
	struct	tnode	*nx;
}	node;

nodeptr	npx,np1,*npa;



/*
 * definicion antigua ...
 *
 */

typedef	struct
{	struct	palabra	*nx;
	int	ty;
	char	*tx;	
}	bd_type;


bd_type	*bd_first ;


#endif


/*
 * Estadisticas
 *
 */


int	q_reg_total;
int	q_reg_clasificado0;
int	q_reg_clasificado1;




/*----------------------------------------------------------------------------
 *
 *	main
 *
 */

int	main(argc,argv)
int	argc;
char	**argv;
{

	gp_default();
	gp_init(argc,argv);
	gp_parser();
	gp_print();

	if (gp_help)
	 	uso(0);


	if (gp_verbose)
	{
		printf ("inp %s\n",finp);
		printf ("out %s\n",fout);
		printf ("\n");
	}

	
	if ( (hfinp = fopen (finp,"r")) == NULL )
	{
		error(101);
	}

	if ( (hfout = fopen (fout,"w")) == NULL )
	{
		error(102);
	}


	if (gp_diccionario)
	{
		if ( (hfdic = fopen (fdic,"r")) == NULL )
		{
			error(103);
		}


		bd_load();
	}

	if (gp_tabmrk)
	{
		if ( (hfmrk = fopen (fmrk,"r")) == NULL )
		{
			error(104);
		}

		bm_load();
	}


	parser1();


	fclose(hfinp);
	fclose(hfout);
	if (gp_diccionario)
		fclose(hfdic);
	if (gp_tabmrk)
		fclose(hfmrk);

	if (gp_verbose)
		printf ("fin proceso \n");

	if (flag_caracteres)
	{	
		printf ("Atencion: caracteres no contemplados para parser encontrados en input  \n");
		printf ("Volver a ejecutar con flag -v y revisar salida (buscar \"Caracteres\" ... ) \n");
	}

}


/*
 * 	parser1
 * 	parser de linea de texto
 *
 *
 */

	char	tk[MAXT][MAXB];

int	parser1()
{

	int	i,j,k;
	int	m1,m2,m3;
	int	f1,f2,f3;
	int	q_lin;
	int	q_tk;
	int	p1,p2,p3,p4;
	int	tclas;

	char	b1[MAXB];
	char	b2[MAXB];


	/* inicializo estadisticas */
	q_reg_total = 0;
	q_reg_clasificado0 = 0;
	q_reg_clasificado1 = 0;


	/* si encuentro caracteres no considerados para el parser, avisar al final de todo el proceso */
	flag_caracteres = 0;


	q_lin=0;
	while (fgets(b1, MAXB, hfinp) != NULL)
	{
		/* procesar solo lineas no vacias */
		if ( !linea_vacia(b1))
		{
			f1=1;

			if (gp_verbose)
			{
				printf ("%s\n\n",b1);
			}
		}


		/* descomponemos la linea de entrada en los 3 segmentos */
		if (f1)
		{
			strcpy(b2,b1);
			separar_seg(b2);
			if (gp_verbose)
			{
				printf ("Linea:  %d \n",q_lin);
				printf ("segm1: >%s<\n",segmento[0]);
				printf ("segm2: >%s<\n",segmento[1]);
				printf ("segm3: >%s<\n",segmento[2]);
				printf ("segm4: >%s<\n",segmento[3]);
				printf ("\n");
			}
		}

		p1=0;
		q_tk=0;

		while ( f1 )
		{

			/* controlamos cantidad de tokens ... */
			if (q_tk > MAXT-10)
			{	error(501);
			} 

	


			/* parseamos solo la frase */
			strcpy(b1,segmento[3]);


			/* caracter p1 del buffer */
			j=tipo_char(b1[p1]);


			switch (j)
			{
				/* otro caracter !!! */
				case TC_RST:
					flag_caracteres=1;
					if (gp_verbose)
					{
						printf ("Caracter no definido para parser: %c %d \n",b1[p1],(int)b1[p1]);
					}
					p1++; 
					break; 

				/* si por alguna causa llega un 0 de c, fin de string ...*/
				case TC_EOS:
					if (gp_verbose)
					{
						printf ("Caracter fin de string !!       : %c %d \n",b1[1],(int)b1[p1]);
					}
					f1=0;
					break; 

				/* letras */
				/* en los corpus vistos, hay muchas siglas del tipo LD4 ...
				 * que para este caso, deberia ser considerado una palabra o termino
				 */
				case TC_LET:
					p2=0;
					while ( (j=tipo_char(b1[p1])) == TC_LET || \
					        (j == TC_NUM && !char_demed(b1[p1-1])  ) )
						tk[q_tk][p2++]=b1[p1++];
					tk[q_tk][p2]=0;
					q_tk++;
					break;

				/* numeros tenemos que contemplar 3.3 o 3,3 !! */
				case TC_NUM:
					p2=0;
					while ( (j=tipo_char(b1[p1])) == TC_NUM || \
						(tipo_char(b1[p1]) == TC_PNT && tipo_char(b1[p1+1]) == TC_NUM ) || \
						( (b1[p1]) == ',' && tipo_char(b1[p1+1]) == TC_NUM ) )
					{	tk[q_tk][p2]=b1[p1];
						p1++;
						p2++;
					}
					tk[q_tk][p2]=0;
					q_tk++;
					break;

				/* blanco o tab */
				case TC_BLA:
					while ( (j=tipo_char(b1[p1])) == TC_BLA)
					       p1++;	
					break;

				/* coma */
				case TC_CCE:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* punto */
				case TC_PNT:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* parentesis abre */
				case TC_PAA:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* parentesis cierra */
				case TC_PAC:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* fin de linea */
				case TC_EOL:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					p1++;
					f1=0;
					break;

				/* caracteres varios */
				case TC_CVR:
					tk[q_tk][0]=b1[p1];
					tk[q_tk][1]=0;
					q_tk++;
					p1++;
					break;

				/* fin de linea */
				default:
					printf ("Default, algo salio mal  !!!\n\n");
					f1=0;
					break;
			}
		}

		/* verifico si hay que sacar output  en minusculas */
		if (gp_minusculas)
		{
			for (j=0; j< q_tk; j++)
				strcpy(tk[j],pasar_a_minusc(tk[j]));
		}

		/* si esta usando tabla de marcas ... verificar si hay que taggear */
		if (gp_tabmrk)
		{
			for (j=0; j< q_tk; j++)
				if (es_word(tk[j]) || es_puntuacion(tk[j]) )
					strcpy(tk[j],bm_tag(tk[j]));
		}


		/* hay que forzar  string EOL al final de la linea */
		if (gp_eol)
			strcpy(tk[q_tk++],"EOL");


		/* salida en formato token columnar */
		if (gp_fsentencia == 0)
		{


			/* pidio nivel de descripcion en salida ... agrego la sentencia */
			if (gp_niveldes)
				fprintf (hfout,"%s\n",b1);


			/* grabo los tokens encontrados */
			for (j=0; j< q_tk; j++)
			{
				switch (gp_niveldes)
				{

					case 0:
						fprintf (hfout,"%s\n",tk[j]);
						break;

					case 1:
						fprintf (hfout,"%3d,%s\n",j,tk[j]);
						break;

					default:
						fprintf (hfout,"%s\n",tk[j]);
						break;
				}


				if (gp_verbose)
					printf ("%3d,%s\n",j,tk[j]);

			}



#if 0
			/* agrego termino EOL para indentificar donde termino
			 * esto ya que tal vez haya un . en mitad de linea 
			 */
			if (gp_eol)
				fprintf (hfout,"%s\n","EOL");

#endif
		}



		/* salida en formato sentencia */
		if (gp_fsentencia == 1)
		{


			/* grabo los tokens encontrados */
#if 0
			fprintf (hfout,"%s\n",b1);
#endif

			for (j=0; j< q_tk; j++)
			{
#if 0
				fprintf (hfout,"%3d,%s\n",j,tk[j]);
#endif
				fprintf (hfout,"%s ",tk[j]);

				if (gp_verbose)
					printf ("%3d,%s\n",j,tk[j]);

			}

#if 0
			/* agrego termino EOL para indentificar donde termino
			 * esto ya que tal vez haya un . en mitad de linea 
			 */
			if (gp_eol)
				fprintf (hfout,"%s\n","EOL");
			else
				fprintf (hfout,"\n");
#endif


			/* se termino la linea */
			fprintf (hfout,"\n");

		}


		if (gp_niveldes)
			fprintf (hfout,"\n\n");


		if (gp_verbose)
		{
			printf ("\n");
		}


		/*
		 * En este punto tengo ...
		 * a) b1            la linea completa que cargue del archivo
		 * b) q_lin         el numero de lineas que procese hasta el momento
		 * c) q_tk          cantidad de tokens de esa linea
		 * d) tk[i]         token numero i de esa linea
		 * e) segmento[0]   nro de registro
		 * f) segmento[1]   aff neg o pos
		 * g) segmento[2]   la palabra de referencia a utilizar para ver en la negacion
		 * h) segmento[3]   la frase
		 *
		 */
		if (gp_verbose)
		{
			printf ("Resumen de la linea: \n");
			printf ("b1        : |%s|\n",b1);
			printf ("q_lin     :  %d \n",q_lin);
			printf ("q_tk      :  %d \n",q_tk);
			printf ("nro       :  %s \n",segmento[0]);
			printf ("clasific  :  %s \n",segmento[1]);
			printf ("palabra   :  %s \n",segmento[2]);
			printf ("frase     :  %s \n",segmento[3]);
			printf ("-----\n\n");
		}

		tclas = clasificar(q_tk);

		if (tclas == 0)
			q_reg_clasificado0++;
		else
			q_reg_clasificado1++;

		if (gp_verbose)
		{

			printf ("Clasificar:   %d  regla: %d  nro:%s pal:%s lin:%s \n\n\n",tclas,nregla,segmento[0],segmento[2],segmento[3]);
			printf ("Sentencia :  \n");
			printf ("nro       :  %s \n",segmento[0]);
			printf ("clasific  :  %s \n",segmento[1]);
			printf ("palabra   :  %s \n",segmento[2]);
			printf ("frase     :  %s \n",segmento[3]);
			printf ("\n\n\n");
			printf ("-----------------------------------------------------\n");
			printf ("\n\n\n");

		}


		/* sumo lineas */
		q_lin++;


	}

	
	if (gp_verbose)
		printf ("Cant de lineas %d\n",q_lin);


	/* Imprimo algunas estadisticas */
	q_reg_total = q_lin;


	if (gp_verbose)
	{
		printf ("\n\n\n\n");
		printf ("Estadisticas: \n");
		printf ("Cant de registros       :  %4d\n",q_reg_total);
		printf ("Cant de reg clasif en 0 :  %4d\n",q_reg_clasificado0);
		printf ("Cant de reg clasif en 1 :  %4d\n",q_reg_clasificado1);
		printf ("\n");
	}


}


/*
 *	clasficar 
 *	Aplica tipo de gramatica "in casa"
 *	para aproximar si la frase es neg o aff 
			

	printf ("nro       :  %s \n",segmento[0]);
	printf ("clasific  :  %s \n",segmento[1]);
	printf ("palabra   :  %s \n",segmento[2]);
	printf ("frase     :  %s \n",segmento[3]);
 *
 */


int	clasificar(q_tk)
int	q_tk;
{

	int	i,j,k,l,m;
	int	n1,n2,n3,n4;
	int	f1,f2,f3;
	int	tclas;

	printf ("CLASIFICO %d toks !!!!!!!!!! \n",q_tk);





	pres_reglas();

	/* asumimos que NO clasifica */
	tclas = 0;
	nregla = 0;


	/* Regla 1 */
	/* las del tipo ...  " no  <tk .. >  se  <tk ... >  obser|visua|ident   <tk ... >  PALABRA  "   */
	printf ("\nCLA: Regla 1 \n\n");


	f1=0;
	for ( j=0; j<q_tk && !f1 && !tclas; j++)
	{

		/* no  .. se .. obser / visua / ident ... REF  */

		if (!f1 && !tclas)
		{
			printf ("CLA: comparo con : %d  %s\n",j,tk[j]);

			if (strcmp(tk[j],"no") == 0)
			{


				printf ("CLA:  pase el 'no ' \n");


				for (i=j+1,n1=0; i< q_tk && n1<1 && !tclas ; i++,n1++   )
				{
					if (strcmp(tk[i],"se") == 0 )
					{	
						for (k=i+1,n2=0, f2=0; k< q_tk && n2<1 && !tclas ; k++,n2++   )
						{
							
							printf ("CLA Entro a 4 ifs seguidos ... |%s| \n",tk[k]);


							if (!f2 && strncmp(tk[k],"obser",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"visua",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"ident",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"detec",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"evide",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"produ",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"ven",3) == 0 )
							{
								f2=1;
							}

							if (f2)
							{
								for (l=k+1, n3=0; l< q_tk && n3 < 4 && !tclas ; l++,n3++ )
								{
									if (strcmp(tk[l],segmento[2]) == 0 )
										tclas=1,nregla=1;
								}
							}
						}
					}



				}
			}
		}


	}  /* for */




	printf ("\nCLA: Regla 2 \n\n");

	for ( j=0; j<q_tk && !f1 && !tclas; j++)
	{
		/* no  .. obser / prese ... REF  */

		if (!f1 && !tclas)
		{
			printf ("CLA: comparo con : %d  %s\n",j,tk[j]);

			if (strcmp(tk[j],"no") == 0)
			{


				printf ("CLA:  pase el 'no ' \n");


				for (i=j+1,n1=0, f3=0; i< q_tk && n1<1 && !tclas ; i++,n1++   )
				{
					if (!f3 && strncmp (tk[i],"obser",5) == 0)
					{	
						f3 = 1;
					}

					if (!f3 && strncmp (tk[i],"prese",5) == 0)
					{	
						f3 = 1;
					}


					if ( f3 )
					{	
						for (k=i+1,n2=0, f2=0; k< q_tk && n2<1 && !tclas ; k++,n2++   )
						{

							if (strcmp(tk[k],segmento[2]) == 0 )
								tclas=1,nregla=2;
						}
					}



				}
			}
		}
	}





	printf ("\nCLA: Regla 3 \n\n");

	for ( j=0; j<q_tk && !f1 && !tclas; j++)
	{
		/* sin   .. edviden ... REF  */

		if (!f1 && !tclas)
		{
			printf ("CLA: comparo con : %d  %s\n",j,tk[j]);

			if (strcmp(tk[j],"sin") == 0)
			{


				printf ("CLA:  pase el 'sin ' \n");


				for (i=j+1,n1=0; i< q_tk && n1<1 && !tclas ; i++,n1++   )
				{
					if (strncmp(tk[i],"eviden",6) == 0 )
					{	
						for (k=i+1,n2=0, f2=0; k< q_tk && n2<2 && !tclas ; k++,n2++   )
						{

							if (strcmp(tk[k],segmento[2]) == 0 )
								tclas=1,nregla=3;
						}
					}

				}
			}
		}
	}




	printf ("\nCLA: Regla 4 \n\n");


	for ( j=0; j<q_tk && !f1 && !tclas; j++)
	{

		/* no  .. se .....  obser / visua / ident ...   ni ... REF  */

		if (!f1 && !tclas)
		{
			printf ("CLA: comparo con : %d  %s\n",j,tk[j]);

			if (strcmp(tk[j],"no") == 0)
			{

				printf ("CLA:  pase el 'no ' \n");


				for (i=j+1,n1=0; i< q_tk && n1<1 && !tclas ; i++,n1++   )
				{
					if (strcmp(tk[i],"se") == 0 )
					{	
						for (k=i+1,n2=0, f2=0; k< q_tk && n2<1 && !tclas ; k++,n2++   )
						{
							
							printf ("CLA Entro a 4 ifs seguidos ... |%s| \n",tk[k]);


							if (!f2 && strncmp(tk[k],"obser",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"visua",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"ident",5) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[k],"detec",5) == 0 )
							{
								f2=1;
							}

							if (f2)
							{
								for (l=k+1, n3=0, f3=0; l< q_tk && n3 < 6 && !tclas ; l++,n3++ )
								{

									if (!f3 && strncmp(tk[l],"ni",2) == 0)
									{
										f3 = 1;
									}
									if (!f3 && strncmp(tk[l],"compat",6) == 0)
									{
										f3 = 1;
									}

								
									if (f3)
									{

										for (m=l+1, n4=0; m < q_tk && n4 < 2 &&  !tclas; m++,n4++)
										{

											if (strcmp(tk[m],segmento[2]) == 0 )
												tclas=1,nregla=4;
										}

									}
								}
							}
						}
					}



				}
			}
		}


	}  /* for */




	printf ("\nCLA: Regla 5 \n\n");



	for ( j=0; j<q_tk && !f1 && !tclas; j++)
	{

		/* sin  ....  obser / visua  ...   ni ... REF  */

		if (!f1 && !tclas)
		{
			printf ("CLA: comparo con : %d  %s\n",j,tk[j]);

			if (strcmp(tk[j],"sin") == 0)
			{


				printf ("CLA:  pase el 'sin' \n");


				for (i=j+1,n1=0; i< q_tk && n1<1 && !tclas ; i++,n1++   )
				{
							
							printf ("CLA Entro a 2 ifs seguidos ... |%s| \n",tk[k]);


							if (!f2 && strncmp(tk[i],"eviden",6) == 0 )
							{
								f2=1;
							}
							if (!f2 && strncmp(tk[i],"visual",6) == 0 )
							{
								f2=1;
							}

							if (f2)
							{
								for (l=i+1, n3=0, f3=0; l< q_tk && n3 < 6 && !tclas ; l++,n3++ )
								{

									if (strcmp(tk[l],"ni") == 0)
									{

										for (m=l+1, n4=0; m < q_tk && n4 < 2 &&  !tclas; m++,n4++)
										{

											if (strcmp(tk[m],segmento[2]) == 0 )
												tclas=1,nregla=5;
										}

									}
								}
							}


				}
			}
		}


	}  /* for */




	/* Regla 6 */
	/* las del tipo ...  " no  PALABRA  "   */
	printf ("\nCLA: Regla 6 \n\n");


	for ( j=0; j<q_tk && !f1 && !tclas; j++)
	{

		/* no REF  */

		if (!f1 && !tclas)
		{
			printf ("CLA: comparo con : %d  %s\n",j,tk[j]);

			if (strcmp(tk[j],"no") == 0 || strcmp(tk[j],"sin") == 0 )
			{


				printf ("CLA:  pase el 'no/sin ' \n");


				for (i=j+1,n1=0; i< q_tk && n1<1 && !tclas ; i++,n1++   )
				{
					
					printf ("Comparando:  |%s|  |%s|   \n",tk[i],segmento[2]);
					if (strcmp(tk[i],segmento[2]) == 0 )
						tclas=1,nregla=6;

				}
			}
		}


	}  /* for */






	printf ("\nCLA: Regla 7 \n\n");


	for ( j=0; j<q_tk && !f1 && !tclas; j++)
	{

		/* no  .. se ..... logra/logrado ...  obser / visua / ident ...  REF  */

		if (!f1 && !tclas)
		{
			printf ("CLA: comparo con : %d  %s\n",j,tk[j]);

			if (strcmp(tk[j],"no") == 0)
			{

				printf ("CLA:  pase el 'no ' \n");


				for (i=j+1,n1=0; i< q_tk && n1<1 && !tclas ; i++,n1++   )
				{
					if (strcmp(tk[i],"se") == 0 )
					{	
						for (k=i+1,n2=0, f2=0; k< q_tk && n2<2 && !tclas ; k++,n2++   )
						{
							
							printf ("CLA Entro a 1 ifs seguidos ... |%s| \n",tk[k]);


							if (!f2 && strncmp(tk[k],"logra",5) == 0 )
							{
								f2=1;
							}

							if (f2)
							{
								for (l=k+1, n3=0, f3=0; l< q_tk && n3 < 4 && !tclas ; l++,n3++ )
								{

									if (!f3 && strncmp(tk[l],"ident",5) == 0)
									{
										f3 = 1;
									}
									if (!f3 && strncmp(tk[l],"obser",5) == 0)
									{
										f3 = 1;
									}
									if (!f3 && strncmp(tk[l],"detec",5) == 0)
									{
										f3 = 1;
									}

								
									if (f3)
									{

										for (m=l+1, n4=0; m < q_tk && n4 < 2 &&  !tclas; m++,n4++)
										{

											if (strcmp(tk[m],segmento[2]) == 0 )
												tclas=1,nregla=7;
										}

									}
								}
							}
						}
					}



				}
			}
		}


	}  /* for */

















	/* Devolvemos true o false segun se pudo clasificar la sentencia en positivo */
	return tclas;
}



/*
 *	Presentacion de reglas
 *
 */



int	pres_reglas()
{
	int i;
	char	*regla;
	
	for (i=0; i< cant_reglas; i++)
	{	switch (i)
		{
			case 0:
				regla = regla1;
				break;
			case 1:
				regla = regla2;
				break;
			case 2:
				regla = regla3;
				break;
			case 3:
				regla = regla4;
				break;
			case 4:
				regla = regla5;
				break;
			case 5:
				regla = regla6;
				break;
			case 6:
				regla = regla7;
				break;

			default:
				printf ("error en reglas !!! \n");
				error(901);
				break;

		}
		printf ("Regla nro %2d:  \"%s\"  \n",i,regla);
	}

}




/*
 *	separar_seg
 *	Separa en segmentos la linea de entrada
 *
 *
 */



int	separar_seg(buffer1)
char	*buffer1;
{
	int	i,j,k;
	int	p1,p2,p3,p4;
	int	f1,f2,f3,f4;
	int	m1;

	char	b3[MAXB];


	p1=0;
	p2=0;
	m1=0;

	/* Busco primer segmento           */
	while ( p1 < MAXB - strlen(marcas[m1])  &&  strncmp(buffer1+p1,marcas[m1],strlen(marcas[m1]))  )
		p1++;

	if ( p1 == MAXB - strlen(marcas[m1]) )
	{	error(701);
	}

	strncpy(segmento[0],buffer1+p2,p1-p2);
	segmento[0][p1-p2]=0;
	p2 = p1 + strlen(marcas[m1]);



	/* Busco segundo segmento           */
	m1=1;

	while ( p1 < MAXB - strlen(marcas[m1])  &&  strncmp(buffer1+p1,marcas[m1],strlen(marcas[m1]))  )
		p1++;

	if ( p1 == MAXB - strlen(marcas[m1]) )
	{	error(702);
	}

	strncpy(segmento[1],buffer1+p2,p1-p2);
	segmento[1][p1-p2]=0;
	p2 = p1 + strlen(marcas[m1]);



	/* Busco tercer segmento           */
	m1=2;

	while ( p1 < MAXB - strlen(marcas[m1])  &&  strncmp(buffer1+p1,marcas[m1],strlen(marcas[m1]))  )
		p1++;

	if ( p1 == MAXB - strlen(marcas[m1]) )
	{	error(703);
	}

	strncpy(segmento[2],buffer1+p2,p1-p2);
	segmento[2][p1-p2]=0;
	p2 = p1 + strlen(marcas[m1]);


	/* Busco cuarto segmento 
 	 * OJO: en cuarto segmento NO hago strlen ... -1 como 
	 * en los anteriors, sino ... saco el ultimo new line 
	 * y tecnicamente modifico el contenido del registro
	 */

	strcpy(segmento[3],buffer1+p2);
	segmento[3][strlen(segmento[3])]=0;

	/* ojo !!
	 * se cuelan blancos al segmentar la palabra de ref a buscar
	 * algo anda mal en el parser original ...
	 */

	for (i=strlen(segmento[2])-1; segmento[2][i] == ' '; i--)
		segmento[2][i] = 0;


	/* Pasar a minuscula la palabra buscada, para compatibilidad en las comparaciones */
	strcpy (b3,segmento[2]);
	strcpy (segmento[2],pasar_a_minusc(b3));



	/* tengo los 4 segmentos */
	if (gp_verbose)
	{
		printf ("Separar: \n");
		printf ("0: |%s|\n",segmento[0]);
		printf ("1: |%s|\n",segmento[1]);
		printf ("2: |%s|\n",segmento[2]);
		printf ("3: |%s|\n",segmento[3]);
	}

}





/*
 *	2018-04-21
 *
 *	bd_load
 *	carga la base de datos del diccionario
 *	diccio base: diccio01.txt
 *
 */

int	bd_load()
{
	char	b1[MAXB];
	int	flag;
	int	i,j,k;
	int	ql;

	/* cantidad de palabras en el diccionario */
	q_wrd = 0;

	/* ptr al contenedor de direccion del ultimo nodo de la cadena */
	npa = (nodeptr *) &np1;

	ql=0;
	while (fgets(b1,MAXB,hfdic) != NULL)
	{

		if (gp_verbose)
		{
			printf ("%3d |%s|\n",ql,b1);
		}

		for ( flag=0, j=strlen(b1); !flag && j; j--)
			if (b1[j] == '\n')
				b1[j]=0,flag=1;

		*npa = (nodeptr ) malloc ( sizeof (node));
		(**npa).wrd = ( char *) malloc(strlen(b1)+1);
		sprintf ( (**npa).wrd,"%s",b1);
		(**npa).num = q_wrd+1;
		(**npa).nx = (nodeptr) NULL;
		npa = (nodeptr *) & (*npa)->nx;


		q_wrd++;
		ql++;

	}

	if (gp_verbose)
	{
		printf ("Cant de lineas en diccionario   : %6d\n",ql);
		printf ("Cant de palabras en diccionario : %6d\n",q_wrd);
	}


	if (gp_verbose)
	{
		printf ("\n\nComprobando integridad del diccionario : \n\n");
	
		i=0;
		npa = (nodeptr *) &np1;

		while ( (*npa) != (nodeptr) NULL )
		{
			printf ("Contador ..i : %3d\n",i);
			printf ("(**npa).wrd  : |%s|\n",  (**npa).wrd );
			printf ("(**npa).num  : %3d\n", (**npa).num );
			printf ("\n");

			npa = (nodeptr *) & (*npa)->nx;
			i++;
		}

	}
}












/*
 *	bm_load
 *	carga la base de datos de marcas
 *
 */

int	bm_load()
{
	char	b1[MAXB];
	char	b2[MAXM];
	int	flag;
	int	p1,p2;
	int	i,j,k;
	int	f1;

	f1=0;
	q_bm=0;
	k=0;

	while (fgets(b1,MAXB,hfmrk) != NULL)
	{
		for ( flag=0, j=strlen(b1); !flag && j; j--)
			if (b1[j] == '\n')
				b1[j]=0,flag=1;

		if (!linea_vacia(b1)  && b1[0] != '#' )
		{
			f1=1;
		}

		if (f1)
		{
			p1=0;
			p2=0;
			k=0;

			while (b1[p1] )
			{	
				b2[k++] = b1[p1];

				if (b1[p1] == ' ' || b1[p1] == '\n')
				{	
					b2[k-1]=0;


					if (p2 == 0)
					{	strcpy(bm_key[q_bm],b2);

					}

					if (p2 == 4)
					{	strcpy(bm_mrk[q_bm],b2);

					}

					p2++;
					k=0;
				}

				p1++;

			}
		
			/* next ... */
			q_bm++;
			f1=0;


			if (q_bm >= MAXK)
				error(301);
		}


		if (gp_verbose)
		{
			printf ("%3d %s\n",q_bm,b1);
		}


	}

	if (gp_verbose)
	{
		printf ("Cant de lineas en tabla de marcas: %d\n",q_bm);
		for (j=0; j<q_bm; j++)
			printf ("%3d,%-10.10s,%s\n",j,bm_mrk[j],bm_key[j]);

		printf ("\n");

	}

}


/*
 * 	bm_tag
 *
 * 	Concatena a string, el tag correspondiente, si coincide la palabra clave
 *
 */


char	*bm_tag(s)
char	*s;
{
	static char b1[MAXB];

	char	b2[MAXM];
	int	i,j,k;
	int	f1,f2;


	strcpy(b1,s);

	f1=1;

	for ( j=0; f1 && j< q_bm; j++)
	{
		if (strcmp(s,bm_key[j]) == 0)
		{
			f1=0;
			sprintf (b2,"_%s",bm_mrk[j]);
			strcat(b1,b2);
		}
	}

	return b1;
}



/*
 *	gp_print
 *
 */

int	gp_print()
{
	if (gp_verbose)
	{
		printf ("Cant de pars ....  %d\n",gp_fq(GP_GET,0) );
		printf ("Cant de tipo 1 %d\n",gp_q_partype1);
		printf ("Cant de tipo 2 %d\n",gp_q_partype2);
		printf ("Cant de tipo 3 %d\n",gp_q_partype3);
		printf ("\n");
	}
}


/*
 *	r
 *
 */

int	gp_parser()
{

	int i;

	/* verbose on ?, excepcion con verbose, por si lo pusieron al final de la linea !!! */
	for (i=0; i < gp_fq(GP_GET,0); i++  )
		if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v'  )
			gp_verbose = 1;


	for (i=0; i < gp_fq(GP_GET,0);  )
	{

		/* parameter type 1 ... "name" */
		if ( i &&  *( gp_fp(GP_GET,i,(char **)0) + 0) != '-')
		{
			gp_q_partype1++;

			if (gp_q_partype1 == 1)
			{
				strcpy(finp, gp_fp(GP_GET,i,(char **)0));
			}

			if (gp_q_partype1 == 2)
			{
				strcpy(fout, gp_fp(GP_GET,i,(char **)0));
			}

			if (gp_verbose)
			{
				printf ("Param tipo 1: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 2 ... "-something" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && !tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype2++;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'v'  )
				gp_verbose = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'h'  )
				gp_help = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'm'  )
				gp_minusculas = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'f'  )
				gp_fsentencia = 1;

			if ( *( gp_fp(GP_GET,i,(char **)0) + 1) == 'e'  )
				gp_eol = 1;

			if (gp_verbose)
			{
				printf ("Param tipo 2: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* parameter type 3 ... "-someoption=somename" */
		if ( i && *( gp_fp(GP_GET,i,(char **)0) + 0) == '-' && tiene_igual( gp_fp(GP_GET,i,(char **)0) ) )
		{
			gp_q_partype3++;

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"inp",3) )
					strcpy(finp,desde_igual( gp_fp(GP_GET,i,(char **)0)));

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"out",3) )
					strcpy(fout,desde_igual( gp_fp(GP_GET,i,(char **)0)));

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"dic",3) )
				{	gp_diccionario=1;
					strcpy(fdic,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				}

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"mrk",3) )
				{	gp_tabmrk=1;
					strcpy(fmrk,desde_igual( gp_fp(GP_GET,i,(char **)0)));
				}

				if (!strncmp(gp_fp(GP_GET,i,(char **)0)+1,"nvd",3) )
					gp_niveldes = *desde_igual( gp_fp(GP_GET,i,(char **)0)) - '0';



			if (gp_verbose)
			{
				printf ("Param tipo 3: %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* program name */
		if (i==0)
		{	
			if (gp_verbose)
			{
				printf ("Name:  %s\n", gp_fp(GP_GET,i,(char **)0 ) );
			}
		}

		/* next ... */
		i++;
	}

	/* si no pone parametros ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype2 + gp_q_partype3 == 0 )
		gp_help = 1;

	/* si no indico ningun  archivo ... mandar a uso */
	if ( gp_q_partype1 + gp_q_partype3 == 0 )
		gp_help = 1;

} 



/*
 *	tiene_igual
 *
 */


int	tiene_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return flag;
}



/*
 *	desde_igual
 *
 */


char	*desde_igual(s)
char	*s;
{
	int i,flag;

	for (i=0, flag=0; i< strlen(s) && !flag; i++ )
		if ( *(s+i) == '=')
			flag=1;

	return s+i;
}




/*
 *	gp_init
 *
 */

int	gp_init(vpar_q,vpar_p)
int	vpar_q;
char	**vpar_p;
{
	int i;

	gp_fq(GP_SET,vpar_q);
	gp_fp(GP_SET,0,vpar_p);


}


/*
 *	gp_fp
 *
 */

char	*gp_fp(action,offset,value)
int	action;
int	offset;
char	**value;
{
	static char **gp_value;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return 	*(gp_value+offset);
}



/*
 *	gp_fq(action,value)
 *	
 *	int action
 *	int value
 *	
 *	value:
 *	on fist call, value is a number (typically argc )
 *	after first call, value can be any number, and is not used
 *
 *	returns:
 *	value
 */

int	gp_fq(action,value)
int	action;
int	value;
{
	static int gp_value=0;

	if (action == GP_SET)
	{	
		gp_value=value;
	}

	return gp_value;
}


int	gp_test()
{
	int i;

	printf ("%d\n",gp_fq(GP_GET,0) );
	for (i=0; i< gp_fq(GP_GET,0); i++)
	{
		printf ("%d %s\n",i,gp_fp(GP_GET,i,(char **)0)  );
	}
			
}

int	linea_vacia(s)
char	*s;
{
	int i,flag;

	i=0;
	flag=1;

	for (i=0; flag && i< strlen(s); i++)
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' )
			flag=0;

	return flag;
}


int	error(value)
int	value;
{
	printf ("Error: %d\n",value);
	printf ("usar -h para help\n");
	exit(0);
}

/*
 *	0	fin de linea
 *	1	blanco o tab
 *	2	otra cosa ( x ahora ... )
 *
 */

int	tipo_char(c)
char	c;
{
	int x;

	x=TC_RST;

	if (c == '\n' )
		x = TC_EOL;

	if (c == ' ' || c == '\t' )
		x = TC_BLA;

	if (c == ',' || c == ';' || c == ':' || c == '-' || c == '/' )
		x = TC_CCE;

	if (c == '.' )
		x = TC_PNT;

	if (c == '(' || c == '[' || c == '{' )
		x = TC_PAA;

	if (c == ')' || c == ']' || c == '}' )
		x = TC_PAC;

	if (c >= 'a' && c <= 'z' || c>= 'A' && c <= 'Z')
		x = TC_LET;

	if (c >= '0' && c <= '9' )
		x = TC_NUM;

	if (c == '\'' || c == '%' )
		x = TC_CVR;

	if (c == 0 )
		x = TC_EOS;

	return x;
}

int	es_numero(c)
char	c;
{
	int x;

	x=0;
	if ( c >= '0' && c <= '9' )
		x=1;

	return x;
}


/*
 * 	es_num_tk
 * 	devuelve true si string esta compuesto solo de numeros
 *
 */

int	es_num_tk(s)
char	*s;
{
	int i,x;

	x=1;
	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < '0' || s[i] > '9' )
			x=0;

	}

	return x;
}








int	es_puntuacion(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] != '.' && s[i] != ',' && s[i] != ':' && s[i] != ';' )
			x=0;
	}

	return x;

}



int	es_word(s)
char	*s;
{
	int i,x;

	x=1;

	for (i=0; x && i<strlen(s); i++)
	{	if (s[i] < 'A' || s[i] > 'z' || ( s[i] > 'Z' && s[i] < 'a')  )
			x=0;
	}

	return x;

}



int	char_demed(c)
char	c;
{
	int	x;

	x=0;
	if ( c == 'e' || c == 'E' || c == 'x' || c == 'X' )
		x=1;

	return x;
}


int	mostrar(t_case,n_token,s_token)
int	t_case;
int	n_token;
char	*s_token;
{

	if (gp_verbose)
	{
		printf ("t: %3d (%2d)   %s \n", n_token,t_case,s_token);
	}
}


int	uso(x)
int	x;
{
	printf ("Usage: \n");
	printf ("inp_file out_file                   inp_file: texto input  out_file: archivo de salida\n");
	printf ("-inp=inp_file -out=out_file         inp_file: texto input  out_file: archivo de salida\n");
	printf ("-h                                  help                                              \n");
	printf ("-v                                  verbose ... muestra cierta informacion de proceso \n");
	printf ("-m                                  salida a archivo de output en minuscula           \n");
	printf ("-f                                  salida a archivo de output en formato sentencia   \n");
	printf ("-e                                  fuerza string \"EOL\" al final de cada sentencia  \n");
	printf ("-nvd=N                              Nivel de descripcion en archivo de salida (solo sin -f) \n");
	printf ("                                    0 Sin descripcion  \n");
	printf ("                                    1 Agrega la sentencia y numero de token \n");
	printf ("                                    2 Datos del diccionario (tags) \n");


	exit(x);
}


/*
 * 	gp_default
 *
 * 	inicializa parametros de funcionamiento default
 *
 */

int	gp_default()
{
	gp_help=0;
	gp_verbose=0;
	gp_diccionario=0;
	gp_minusculas=0;
	gp_fsentencia=0;
	gp_eol=0;
	gp_niveldes=0;
	gp_tabmrk=0;
}




/*
 * 	pasar_a_minusc
 *
 *
 */

char	*pasar_a_minusc(s)
char	*s;
{
	static char b[MAXB];

	int i,j,k;

	strcpy(b,s);

	for (i=0; i<MAXB && b[i]; i++)
	{
		if ( b[i] >= 'A' && b[i] <= 'Z' )
			b[i] += 32;
	}

	return b;
}



#endif


#endif
/* tes_cpar04 */



#endif
/* cnv_f07 */

