#include <unistd.h>
#include <sys/syscall.h>

void Hello() {
    syscall(SYS_write, 1, "hello call\n", 11);
}

int main() {
    Hello();
}
