#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
  FILE * fp = fopen("formula", "w") ;
  FILE * fpc = fopen(argv[1],"r");
  int **a=NULL;
    char buffer[100];


    int row=0,col=0;

    while(1){
      fgets(buffer, sizeof(buffer), fpc);
      if(feof(fpc))break;
        row++;
        for (int i =0; (row == 0) &&i < sizeof(buffer); i++){
            if(!((buffer[i] == ' ')||(buffer[i]== '\n'))) col++;
        }
          col ++;
     }
    //printf("%d %d\n", row, col); // Debugging - 1
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
                if(c=='?'){
                    //printf("-1 ");
                    a[k][l]=0;
                    //l++;
                }else{
                    //printf("%d ",atoi(&c));
                    a[k][l]*=10;
                    a[k][l]+=atoi(&c);
                    already = 1;
                }

        }
    }


    printf("\n \n");
    for(int i=0;i<row+2;i++){
      for(int j=0;j<col+2;j++)
        printf("%d ",a[i][j]);
      printf("\n");
      }
    printf("\n \n");
}
