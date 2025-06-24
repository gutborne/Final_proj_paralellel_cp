#include <stdio.h>

int add(int a, int b){ return a + b; }
int sub(int a, int b){ return a - b; }

int (*Code(char code))(int, int){
    if(code == '+'){
        return add;
    }else{
        return sub;
    }
}
    
int main(){
    //                          function pointers
    int (*ptr_func)(int, int);
    ptr_func = add;

    int sum = ptr_func(2,3); //implicit dereference
    int sum1 = (*ptr_func)(4,5); //explicit dereference
    printf("%d %d\n", sum, sum1);
    ptr_func = Code('-');
    printf("%d \n", ptr_func(7,3));
    int (*ptr_f[])(int, int) = {add, sub};
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
    
    return 0;
}
