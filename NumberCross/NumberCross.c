#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
  FILE * fp = fopen("formula", "w") ;
  FILE * fpc = fopen(argv[1],"r");
  int **a=NULL;
    char buffer[500];


    int row=0,col=0;

    while(1){
        fgets(buffer, sizeof(buffer), fpc);
        if(feof(fpc))
            break;
        row++;
        for (int i = 0; (row == 0) &&i < sizeof(buffer); i++){
            if(!((buffer[i] == ' ')||(buffer[i]== '\n')))
                col++;
        }
        col ++;
     }
    printf("%d %d\n", row, col); // Debugging - 1
    fclose(fpc);

  //row 와 column은 알게됨.
    a=(int**)malloc((row) * sizeof (int*));
    for (int j = 0; j < row; j++)
    a[j]=(int*)malloc((col) * sizeof(int));
    //할당

    for (int i =0; i<row; i++){
        for (int j=0; j<col; j++){
            a[i][j] = 0;
            //printf("%d", a[i][j]);
        }
        //printf("\n");
    } // Debugging - 2

    FILE * fpd = fopen(argv[1],"r");
 /*   char buffer2 [90000];
    for (int i =0; i<90000;i ++){
        buffer2[i] = 0;
    }*/
    int k=0,l=0;
    int already = 0;

    char c = 0;
    while(1){
        c = fgetc(fpd);
        if(feof(fpd)) break;
        if(c==' ') {
          l++; already = 0; continue;
        }
        if(c=='\n'){
          k++; l=0; continue;
        }
        if(c!='\0'){
            a[k][l]*=10;
            a[k][l]+=atoi(&c);
            already = 1;
        }
    }

    fclose(fpd);
    
    
    printf("\n \n");
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++)
        printf("%d ",a[i][j]);
      printf("\n");
      }
    printf("\n \n");



    for (int i = 0 ; i < row ; i++)
        for (int j = 0 ; j < col ; j++)
            fprintf(fp, "(declare-const a%d_%d Int)\n", i, j) ;

    
    for (int i = 1 ; i < row ; i++)
        for (int j = 0 ; j < col-1 ; j++)
            fprintf(fp, "(declare-const b%d_%d Int)\n", i, j) ;
    
    
    for (int i =0; i<row; i++){
        for (int j =0; j<col; j++){
            fprintf(fp, "(assert (= a%d_%d %d))\n", i, j, a[i][j]) ;
        }
    }
    
    for (int i =1; i<row; i++){
        for (int j =0; j<col-1; j++){
            fprintf(fp, "(assert (or (= b%d_%d %d) (= b%d_%d %d)))\n", i, j, 0, i, j, 1) ;
        }
    }
    
    
    
    for (int j =0; j<col-1; j++){
        fprintf(fp, "(assert (= a0_%d (+ ", j);
        for (int i =1; i<row; i++){
            fprintf(fp, "(* a%d_%d b%d_%d)", i, j, i, j);
            if(i == row -1)
                continue;
            fprintf(fp, " ");
        }
        fprintf(fp, ")))\n");
    }
    
    
    
    for (int i =1; i<row; i++){
        fprintf(fp, "(assert (= a%d_%d (+ ", i, col-1);
        for (int j =0; j<col-1; j++){
            fprintf(fp, "(* a%d_%d (- 1 b%d_%d))", i, j, i, j);
            if(j == col-2)
                continue;
            fprintf(fp, " ");
        }
        fprintf(fp, ")))\n");
    }
    
    
    /*
    for (int i =0; i<row-1; i++){
        for (int j =1; j<col; j++){
            fprintf(fp, "(assert(or (= (a%d_%d %d) (+ (* (a%d_%d %d) (b%d_%d %d))) (= (a%d_%d %d) (+ (* (a%d_%d %d) (- 1 (b%d_%d %d)))))\n", row, j, a[row][j], i, j, a[i][j], i, j, 0, row, j, a[row][j], i, j, a[i][j], i, j, 1) ;
        }
    }
    */
    
    fprintf(fp,"(check-sat)\n(get-model)\n");
    
    fclose(fp);


    FILE * fin = popen("z3 formula", "r") ; //FIXME
        
    int board[row-1][col-1] ;
    int i, j, z;

    char b[128] ;
    char s[128] ;
    char position, close ;
    int where=0, value = 0;
    
    fscanf(fin, "%s %s", b, s) ;
    if(strcmp(b,"unsat")==0){
        printf("No solution!\n");
        exit(-1);
    }
    
    for (z = 0 ; z < (row-1)*(col-1) ; z++) {
        fscanf(fin,"%s %c%d%c%d %s %s", b, &position, &i, &position, &j, b, b);
        fscanf(fin, " %d%c", &value, &close );
        //printf("%c%d %d%c\n",  position, where, value, close);
        //printf("%d %d %d\n", i, j, value);
        //if(position == 'b')
            board[i-1][j] = value;
        
    }
    
    for (i = 0 ; i < row - 1 ; i++) {
            for (j = 0 ; j < col - 1 ; j++) {
                    printf("%d ", board[i][j]) ;
            }
            printf("\n") ;
    }
    pclose(fin) ;
    
    
    


} //end of this program


