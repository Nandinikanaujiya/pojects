#include<stdio.h>
#include<string.h>
void makeTags(char tag[],char word[],char result[]){
    sprintf(result,"<%s>%s</%s>\n",tag,word,tag);
}
int main(){
    char result[100];
    makeTags("i","Yay",result);
    printf("%s\n",result);
    return 0;
}