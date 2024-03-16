#include <sys/syscall.h>

int main() {
    register int syscall_no asm("rax") = SYS_write;
    register int arg1 asm("rdi") = 1;
    register char* arg2 asm("rsi") = "hello asm\n";
    register int arg3 asm("rdx") = 10;
    asm("syscall");
}
