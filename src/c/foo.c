#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    bool is_value = true;

    printf("This line starts at four!\n");
    if (is_value) {
	printf("This line starts at nine!\n");
    }
    else
    {
	printf("Shut the fuck up man\n");
    }

    return 0;
}
