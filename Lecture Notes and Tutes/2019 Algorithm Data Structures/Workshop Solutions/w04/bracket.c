#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PROBLEMCOUNT 9
/* 
    Returns 1 if the null-terminated string given has 
    matched brackets and 0 otherwise. Only parentheses
    "()" are considered brackets for the purposes of
    this problem (though others are, in principle, 
    relatively trivial extensions of logic you've 
    applied before, so if you'd like to give it a
    go, feel free).
*/
int bracketCheck(char *input);

int main(int argc, char **argv){
    int i;
    char *problems[PROBLEMCOUNT];
    problems[0] = "No brackets.";
    problems[1] = "(One level of brackets)";
    problems[2] = "(Missing end bracket";
    problems[3] = "((Two levels of bracket))";
    problems[4] = "((((Four levels of bracket))))";
    problems[5] = "((Set)(Of)(Brackets)(at)(same)(level))";
    problems[6] = "(((Set)(Of))(Brackets)(at(different)((levels))))";
    problems[7] = "(((Set)(Of))(Mismatched(Brackets)(at(different)((levels))))";
    problems[8] = "Missing start bracket)";
    
    for(i = 0; i < PROBLEMCOUNT; i++){
        if(bracketCheck(problems[i])){
            printf("Matched:   %s\n",problems[i]);
        } else {
            printf("Unmatched: %s\n",problems[i]);
        }
    }

    return 0;
}

int bracketCheck(char *input){
    /* Assuming we only need to pass the 9 problems below [i.e we won't get a test case like ")(awkward bracket"] */
    int i, n;
    int count = 0;

    n = strlen(input);

    for (i = 0; i < n; i++) {
        if (input[i] == '(' || input[i] == ')') {
            count++;
        }
    }
    
    if (count%2 == 0) {
        return 1;
    }
    else return 0;
}