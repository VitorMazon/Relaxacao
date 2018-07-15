/*
 * relax.c
 * 
 * Copyright 2018 Vitor <vitor@vitor-mazon>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void condContorno(double **M, int idim, int jdim, double xi, double xf, double yi, double yf) {
	int i, j;
	double hx, hy, t;
	
	hx=(xf-xi)/jdim;
	hy=(yf-yi)/idim;
	
	t=xi;
	for(i=0; i<idim; i++) {
		M[i][0]=t*t;
		M[i][jdim-1]= pow((t-2),2);
		t+=hx;
	}
	
	t=yi;
	for(j=0; j<jdim; j++) {
		M[0][j]=t*t;
		M[idim-1][j]=pow((t-1),2);
		t+=hy;
	}
	return;
}

int relax(double **M, int idim, int jdim, double h) {
	int i, j, cont=0;
	int x, y;
	double var=h, aux;
	
	x=idim-1;
	y=jdim-1;
	
	while(var>=h) {
		var=0.;
		for(i=1; i<x; i++) {
			for(j=1; j<y; j++) {
				aux=M[i][j];
				M[i][j]=(M[i-1][j]+M[i+1][j]+M[i][j-1]+M[i][j+1]-1)/4;
				if(fabs(aux-M[i][j])>var)
					var=fabs(aux-M[i][j]);
			}
		}
		cont++;
	}
	return cont;
}

void imprime(double **N, int x, int y){
	int i, j;
	for(i=0;i<x;i++) {
		for(j=0;j<y;j++) { 
			printf("%5.2lf\t",N[i][j]);
		}	  
		puts("");
	}
}

int main(int argc, char **argv) {
	int idim, jdim, it, i;
	double **L, err, xi, xf, yi, yf;

	//condiçoes iniciais
	xi=0;
	xf=1;
	yi=0;
	yf=2;
	
	err=atof(argv[1]);
	idim=102*(yf-yi);
	jdim=102*(xf-xi);
	
	L=malloc(idim*sizeof(double *));
	for(i=0; i<idim; i++)
		L[i]=(double *)malloc(jdim*sizeof(double *));
		
	condContorno(L, idim, jdim, xi, xf, yi, yf);
	it=relax(L, idim, jdim, err);
	imprime(L, idim, jdim);
	printf("# %d iterações\n", it);
	return 0;
}

