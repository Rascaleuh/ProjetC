#include "utils.h"

char *readFile(char *name){
    FILE *fp;
	int taille = 0;
	char* texte;

	fp = fopen(name, "r");
	// On récupère la taille en allant à la fin du fichier 
	fseek(fp, 0, SEEK_END); // on va a la fin du fichier
	taille = ftell(fp); // cb de bits on a parcouru
	rewind(fp); // retour au début

	texte = malloc(taille+1 * sizeof(char));

	fread(texte, taille, 1, fp);
	texte[taille] = '\0';

	fclose(fp);
    return texte;
}

char* stringBinary_to_stringASCII(char *src){
	char* rt = malloc(sizeof(char));
	rt[0] = '\0';
	int t_rt = 1; // taille de la chaine a retourner
	char acompr[8] = ""; // string binaire
	int icompr = 0; // string binaire en dec
	int compt = 0; // compteur de bits

	int taille = strlen(src);
	for(int i=0; i<taille; i++){
		acompr[compt] = src[i];
		compt++;
		if(compt >= 8){
			compt = 0;
			icompr = (int) strtol(acompr, NULL, 2); // transforme un string en long avec un cast int dans sa base 2
			printf("Icompr = %d | %c \n", icompr, ( (char) icompr));
			rt = realloc(rt, sizeof(char) * t_rt+1);
			rt[t_rt-1] = (char) icompr;
			rt[t_rt] = '\0';
			t_rt ++;
		}
	}

	while(compt < 8){
		acompr[compt] = '0';
		compt++;
	}
	icompr = (int) strtol(acompr, NULL, 2); // transforme un string en long avec un cast int dans sa base 2
	printf("Icompr = %d | %c \n", icompr, ( (char) icompr));
	rt = realloc(rt, sizeof(char) * t_rt+1);
	rt[t_rt] = (char) icompr;

	return rt;
}

char* stringASCII_to_stringBinary(char *src){
	char *rt = malloc(sizeof(char));
	rt[0] = '\0';
	int t_rt = 1;
	int codeASCII = 0; // Le décimal récupéré depuis un caractère de la chaîne avec un cast 
	char codeASCII_binaire[8];

	int taille = strlen(src);
	for(int i=0; i<taille; i++){
		codeASCII = (int) src[i];
		int_to_stringBinary(codeASCII, codeASCII_binaire);
		//printf("Binaire de %c (%d) = %s\n", src[i], codeASCII, codeASCII_binaire);
		rt = realloc(rt, sizeof(char) * (t_rt + 9));
		strcat(rt, codeASCII_binaire);
		t_rt = strlen(rt);
		rt[t_rt] = '\0';
	}	

	return rt;
}

void int_to_stringBinary(int n, char* dst){

	int i=7;

	do {
   		if (n & 1) {
       		dst[i] = '1';
   		} else {
       		dst[i] = '0';
   		}
   		n >>= 1;
   		i--;
	} while(n);

	while(i>=0){
		dst[i] = '0';
		i--;
	}
}