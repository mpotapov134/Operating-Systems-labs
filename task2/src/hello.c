#include <stdio.h>
#include <unistd.h>

int main() {
    write(1, "Hello world _sys\n", 17);
}
