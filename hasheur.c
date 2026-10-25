#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool d=false;

int error(int argc,char *args[]){
char buffer[255];
if(argc>1){
	if((strcmp(args[1],"G")==0)){	
		if(argc >=6){
			if(((strcmp(args[2],"-i")==0)||(strcmp(args[2],"--input")==0))&&((strcmp(args[4],"-o")==0)||(strcmp(args[4],"--output")==0))){
				if(argc==8){
					if(((strcmp(args[6],"-a")==0) ||(strcmp(args[6],"--algo")==0))){
						return 0;	
					}
				}else if(argc==6){
					return 0;
				}
			}else{
				return 1;
			}
		}else{
			return 1;
		}

	}else if(strcmp(args[1],"L")==0){	
		if(argc==4){
	 		if(strcmp(args[2],"-t")==0){
				return 0;
			}else{
				return 2;
			} 
		}else{
			return 2;
		}
		}
	}else{
		return 3;
	}
}
			



int main(int argc ,char *argv[]){
	int r = error(argc,argv);
	switch (r) {
		case 1:printf("./hasheur G -i <dictionnaire> -o <t3c_output> [-a <algo>]\n\n    -i / --input <path> : dictionnaire (obligatoire)\n    -o / --output <path> : sortie T3C (obligatoire)\n    -a / --algo <nom> : algorithme (optionnel).\n");
			break;
		case 2:printf("./hasheur L -t <t3c_path>\n\n-t / --table <path>\n");
			break;
		case 3:	printf("./t3c <G|L> [options]\n");
			break;
	}
	if(r!=0){
		return r;
	}else{
		//Si c'est le mode G 
		//On va générer les condensats à partir du dictionnaire.
		//On lit le dictionnaire (on ouvre un fichier en lecture si il existe)
		//Puis on cree et/ou ouvre un fichier en ecriture
		//On ecrit le duo mot-condensat dans le fichier 
		FILE *fp;
		fp = fopen(argv[1],"r");
		char* buffer=malloc(255*sizeof(char));
		int nb=0;
		nb = fscanf(fp,"%s",buffer);
		while(nb != EOF){
			printf("%s\n",buffer);
			nb = fscanf(fp,"%s",buffer);
			
		}
	}

	
}
		

	
/*
	char dictionnary[255];
	char salt[255];
	if (d==true){
		strcpy(salt,argv[4]);
		strcpy(dictionnary,argv[2]);
	}else{
		strcpy(dictionnary,argv[1]);
	}
	

}*/
