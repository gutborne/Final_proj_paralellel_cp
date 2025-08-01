#include <stdio.h>
#include "final_proj.h"
#include <string.h>
/*
int add(int a, int b){ return a + b; }
int sub(int a, int b){ return a - b; }

int (*Code(char code))(int, int){
    if(code == '+'){
        return add;
    }else{
        return sub;
    }
}
*/
const char* f1[3] = {"sum", "mov", "afklsdj"};


int main(){
   

    int f = 1;
    while(f >= 1 && f <= 3){
        printf("TYPE THE ANSWER: \n");
        fflush(stdout);
        while(scanf("%d", &f) != 1 || f < 1){
            while(getchar() != '\n');
            printf("INVALID OPERATION! PLEASE CHOOSE A VALID NUMBER(1-3): ");
            fflush(stdout);            
        }
        switch(f){
            case 1:
                for(int i = 0; i < 100; i++) printf("inside case %d\n", f);
                break;
                
            case 2:
                for(int i = 0; i < 100; i++) printf("inside case %d\n", f);
                break;
            case 3:
                for(int i = 0; i < 100; i++) printf("inside case %d\n", f);
                break;
            default:
                printf("finish the program!");
                break;
        }
    }
    return 0;
}
