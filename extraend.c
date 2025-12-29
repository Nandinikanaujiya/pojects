#include <stdio.h>
#include <string.h>

void extraEnd(char str[], char result[]) {
    int len = strlen(str);

    for (int i = 0; i < 3; i++) {
        result[i*2]     = str[len - 2];
        result[i*2 + 1] = str[len - 1];
    }
    result[6] = '\0';
}

int main() {
    char result[10];

    extraEnd("Hello", result);
    printf("%s", result);

    return 0;
}
