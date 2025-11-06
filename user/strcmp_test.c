#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    char *x = "foo";
    char *y = "foo";

    int result = strcmp(x, y);

    printf("result = %d\n", result);

    exit(0);
}