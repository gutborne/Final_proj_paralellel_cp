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


int main(){
    //                          function pointers
    /*
    int (*ptr_func)(int, int);
    ptr_func = add;

    int sum = ptr_func(2,3); //implicit dereference
    int sum1 = (*ptr_func)(4,5); //explicit dereference
    printf("%d %d\n", sum, sum1);
    ptr_func = Code('-');
    printf("%d \n", ptr_func(7,3));
    int (*ptr_f[])(int, int) = {add, sub};*/
    int num[3] = {1, 0, 1};
    char* code = "101";
    char curr_char = ' ';
    for(int i = 0; i < 3;){
        curr_char = num[i] + '0'; 
        if(curr_char == code[i]) i++;
        else{
            printf("not equal\n");
            break;
        } 
        printf("equals\n");
    }
    
   
    char* f1[] = {"sum", "mov", "afklsdj", "afksdljf"};
    char** ptr_f1 = f1;

    for(int i = 0; i < 4; i++){
        printf("%s\n", f1[i]);
        if(strcmp(f1[i], "sum") == 0){
            printf("Are equal\n");
        }else{
            printf("arent equal\n");
        }
    }
    printf("\n\nsizeof(f1): %d\n", sizeof(ptr_f1));
    printf("\n\nsizeof(f1): %d\n", sizeof(ptr_f1[0]));
    printf("\nlen(f1): %d\n\n", sizeof(ptr_f1)/sizeof(ptr_f1[0]));
    for(int i = 0; i < sizeof(ptr_f1)/sizeof(ptr_f1[0]); i++){
        printf("%s ", ptr_f1[i]);
    }
    int var = 1;
    int* ptr_var = &var;
    if(&var == ptr_var)
        printf("\nvar: %p ptr_var: %p\n", &var, ptr_var);
    char* exp_new = "abc";
   
    int res = 5 > 5;
    printf("res: %d\n", res);
    return 0;
}
