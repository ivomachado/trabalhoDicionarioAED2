/*
 * leitura.c
 *
 *  Created on: 4 de ago de 2016
 *      Author: cesar
 */

//funcao que le as palavras do arquivo;
#include "string.h"
#include "parser.h"

int lerPalavra(FILE *fp, char *word)
{
	short typing=1;

	//auxiliares do tipo char;
	char *del = " \t\r\n`~!@#$%^&*()-_+=\\|][{}'\":;/?.>,<\"1234567890";

	int i = 0; word[i] = '\0';
	do{
		int c = fgetc(fp);
		if(c == EOF){
			word[i] = '\0'; typing=0;
			return 0;
		}
		c = tolower(c);
		if (strchr(del,c)==NULL){
			word[i++] = c;
		}else if(c == '-' && i){
			word[i++]=c;
		}else if(c == '\n'){
			word[i] = '\0'; typing=0;
		}else if(c == ' ' && i ){
			word[i] = '\0'; typing=0;
		}
	}while(typing);
	return 1;
}
