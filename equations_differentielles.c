#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(){
    float a, b, c;/* a*y''(x)+b*y'(x)+c*y(x)=0 */
	float d;/* descriminant */
	float A, B;/* les constantes */
	float R1, R2;/* les racines */
	float r, img;/* parties reelle et imaginaire*/
    
    FILE *f;
    //ouverture du fichier ra
    f = fopen ("equations differentielles.txt", "w");
    if (f==NULL) fprintf(stderr,"erreur d'ouverture du fichier");
    
/*y(0)=0 et y'(0)=1 */
    
    //saisie des coefficients par l'utilisateur 
    printf("entrez les valeurs pour a, b, et c : \n");
    scanf("%f %f %f", &a, &b, &c);
    
    //S'assurer que c'est une equation differentielle
    if (a==0 && b==0 && c==0){
        printf("error de saisir\n");
        while(a==0 && b==0 && c==0) scanf("%f %f %f", &a, &b, &c); 
    }
    
    if (a==0){
        printf("Ce n'est pas une equation diff de second ordre pour a==0\n");
        while(a==0) scanf("%f", &a);
    }
    
    //calcul du delta
    d=pow(b,2) - 4*a*c;
    
    //Le cas d=0
    if (d==0){
        printf("La solution est : y(t)= exp(r*t)*(At*B)\t avec A= 1 et B=0 \n");
        R1=-b/(2*a);
        A=1;
        printf("y(t)=exp(%f*t)*t\n",R1);
        
        for (int i=0; i<50; i++){
            fprintf(f,"%d\t", i);
            fprintf(f,"%f\n", (A*exp(R1*i)) );            
        }
                    
    }
    //Le cas de d<0
    else if (d<0){
        printf("La solution est : y(t)= exp(r*t)*(A*cos(i*t)+B*sin(i*t))\n avec A= 0 et B=1/i \n");
        r=(-b)/(2*a);
        img=sqrt(-d)/(2*a);
        B=1/img;
        printf("y(t)=exp(%f*t)*%f*sin(%f*t)\n",r,B,img);
        
        for (int i=0; i<50; i++){
            fprintf(f,"%d\t", i);
            fprintf (f,"%f\n", (exp(r*i)*(B*sin(i*img))));
        }
    }
    
    //Le cas de d>0
    else {
        printf("La solution est : y(t)= A*exp(R1*t)+B*exp(R2*t)\n où A= 1/(R1-R2) et B=-A selon les conditions \n");
        R1=(-b-sqrt(d))/(2*a);
        R2=(-b+sqrt(d))/(2*a);
        if (R1==R2)
		printf("racines egales\n");
        A=1/(R1-R2);
        B=-A;
        printf("y(t)=%f*exp(%f*t) + %fexp(%f*t)\n",A,R1,B,R2);
        for (int i=0; i<50; i++){
            fprintf(f,"%d\t", i);
            fprintf(f,"%f\n", (A*exp(R1*i)+B*exp(R2*i)) );            
        }    
    }
    //fermeture du fichier
    fclose(f);
    return 0;
}