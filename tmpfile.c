#include <stdio.h>
#include <stdlib.h>
int main(void) {
    FILE *fptr = tmpfile(); //内部自动调用unlink()
    int num=0;

    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    printf("Enter num: ");
    scanf("%d", &num);

    fprintf(fptr, "%d", num);
    fclose(fptr);

    return 0;
}