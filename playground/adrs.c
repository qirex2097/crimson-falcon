#include <stdio.h>

void ff(int *i) {
    *i = 20;
}

int main(void) {
    int i;
    i = 10;
    ff(&i);
    printf("%d\n", i);
}

//変数のアドレスを渡すことで、関数内で変数の値を変更することができる