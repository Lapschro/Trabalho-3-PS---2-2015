/*
 * Palestrante_Manager.c
 *
 *  Created on: 01/11/2015
 *      Author: Guilherme
 */

#include <stdlib.h>
#include <stdio.h>
#include "../Headers/Palestrante_Manager.h"

void PalestranteManager_Initialize(){
	if(filaPalestrante == NULL)
	    filaPalestrante = FilaPalestrante_New();
}

void PalestranteManager_Read(char* filename){
	char nome[30];
	char data[13];
	char d_sem[6];
	char hinicio[9], hfim[9];
	char c;
	int i, hora, minuto, horafim, minutofim, diaS;

	FILE *file;

	file = fopen(filename, "r");

	PalestranteManager_Initialize();

	while(!feof(file)){
		for(i = 0; i < 6; i++)
			fscanf(file, "%c", &c);

		c = fgetc(file);
		i = 0;
		while(c != '.'){
			if(c != ' '){
			    nome[i] = c;
			    i++;
			}
			c = fgetc(file);
		}
		nome[i] = 0;

		FilaPalestrante_Add(NodePalestrante_New(Palestrante_New(nome)), filaPalestrante);

		for(i = 0; i < 17; i++)
			fscanf(file, "%c", &c);

        c = 'a';

        while(c != '.'){
        	c = 'a';
        	c = fgetc(file);
        	while(c != ';' && c != '.'){
        		i = 0;
        		c = fgetc(file);
        		while(c != ','){
        			if(c != ' '){
        			    d_sem[i] = c;
        			    i++;
        			}
        			c = fgetc(file);
        		}
        		d_sem[i] = 0;

        		switch(d_sem[2]){
        		 case 'm':
        			 diaS = 0;
        			 break;
        		 case 'g':
        			 diaS = 1;
        			 break;
        		 case 'r':
        			 diaS = 2;
        			 break;
        		 case 'a':
        			 diaS = 3;
        			 break;
        		 case 'i':
        			 diaS = 4;
        			 break;
        		 case 'x':
        			 diaS = 5;
        			 break;
        		 case 'b':
        			 diaS = 6;
        			 break;
        		 }

        		i = 0;
        		c = fgetc(file);
        		while(c != ','){
        			if(c != ' '){
        			    data[i] = c;
        			    i++;
        			}
        			c = fgetc(file);
        		}
        		data[i] = 0;

        		i = 0;
        		c = fgetc(file);
        		while(c != '-'){
        			hinicio[i] = c;
        			c = fgetc(file);
        			i++;
        		}
        		hinicio[i] = 0;

        		i = 0;
        		do{
        			c = fgetc(file);
        			hfim[i] = c;
        			i++;
        		}while(c != ';' && c != '.');

        		hfim[i] = 0;

        		hora = atoi(&hinicio[0]);
        		minuto = atoi(&hinicio[3]);
        		horafim = atoi(&hfim[0]);
        		minutofim = atoi(&hfim[3]);
        		Palestrante_Add_Disp(NodePalestrante_Get(FilaPalestrante_Get_Last(filaPalestrante)), Disponibilidade_New(data, d_sem, hora, minuto, horafim, minutofim));
        	}
        }
        c = fgetc(file);
	}
	fclose(file);
}

int PalestranteManager_PopFila(){
	filaPalestrante = FilaPalestrante_Pop(filaPalestrante);

	return filaPalestrante == NULL;
}

void PalestranteManager_Print(){
	FilaPalestrante_Print(filaPalestrante);
}

FilaPalestrante* PalestranteManager_GetPalestrante(){
	return filaPalestrante;
}

