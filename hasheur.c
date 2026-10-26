#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define TAILLE_MAX 1000

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
		if(strcmp(argv[1],"G")==0){
		char alg[128];
		strcpy(alg,"md5");
		if(argc==8){
			strcpy(alg,argv[7]);
		}
//		printf("algo::%s",alg);
		FILE *fp=NULL;
		char ligne[TAILLE_MAX];
		fp = fopen(argv[3],"r");
//		printf("fichier::%s\n",argv[3]);
		//char* buffer=malloc(255*sizeof(char));
		int nb=0;
		FILE *n=fopen(argv[5],"w");
		//nb = fscanf(fp,"%s",buffer);
		while(fgets(ligne,sizeof(ligne),fp)!=NULL){
			//printf("%s\n",ligne);
			char *cmd="";
			char debut_cmd[TAILLE_MAX*2]="echo ";
			char ligne2[TAILLE_MAX]="";
			strncpy(ligne2,ligne,strlen(ligne)-1);
			strcat(debut_cmd,ligne2);
			strcat(debut_cmd,"|");
			strcat(debut_cmd,"openssl ");
			strcat(debut_cmd,alg);
			FILE *f=popen(debut_cmd,"r");
			char retour[1024];
			char retour2[1024];
			while(fgets(retour,sizeof(retour),f)!=NULL){
			//	printf("%s\n",retour);
				char algo[128];
				sscanf(retour,"%[^=]= %[^=]",algo,retour2);
				memset(retour,'\0',strlen(retour)+1);
				strncpy(retour,retour2,strlen(retour2)-1);
				strcat(retour," ");
				strcat(retour,ligne);
//				printf("test:::%s",retour);
				fputs(retour,n);
			}
	//		printf("yoyo:::%s",retour2);
			pclose(f);

//			printf("cmd::::%s::::\n",debut_cmd);
//			system(debut_cmd);
		//	nb = fscanf(fp,"%s",buffer);
		}
		fclose(fp);
		fclose(n);
		return 0;
		}else{
			char alg[128];
			FILE *fp=NULL;
			char mot[TAILLE_MAX]="";
			fp = fopen(argv[3],"r");
			char trouve[TAILLE_MAX]="";
			char claire[TAILLE_MAX];
			char retour[TAILLE_MAX];
			bool trouv= false;
			while(strcmp(mot,"end")!=0){
			    	scanf( "%[^\n]", mot );
//				char debut_cmd[TAILLE_MAX*2]="sort ";
//				strcat(debut_cmd,argv[3]);
//				FILE *f=popen(debut_cmd,"r");
				while(fgets(retour,sizeof(retour),fp)!=NULL){
					char hash[128]="";
					sscanf(retour,"%s  %s",hash,claire);
					printf("%s\n",hash);
					if(strcmp(hash,mot)==0){
						strcpy(trouve,claire);
						printf("mot trouvée: %s",claire);
						trouv=true;
						break;
					}
						//printf("yoyo\n");
				}
				//pclose(f);
			if(trouv){
				trouv=false;
			}
			}
			fclose(fp);
			return 0;
			}
	}

}
