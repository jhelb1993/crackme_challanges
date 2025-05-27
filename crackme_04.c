#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <unistd.h>

void segfault_handler(int sig) {
    (void)sig;
    puts("\U0001F47B You triggered the secret path. You win.");
    exit(0);
}

int check_debugger() {
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) {
        puts("Debugger detected. Bye.");
        exit(1);
    }
    return 0;
}

int xor_check(const char *input) {
    if (strlen(input) != 8) return 0;
    const uint8_t expected[] = { 0x23, 0x2F, 0x0C, 0x34, 0x5B, 0x6E, 0x42, 0x77 };
    for (int i = 0; i < 8; i++) {
        if ((input[i] ^ (i * 3 + 7)) != expected[i]) return 0;
    }
    return 1;
}

uint8_t win_code[] = {
    0x48, 0x31, 0xc0,                          // xor    rax,rax
    0x48, 0x89, 0xc7,                          // mov    rdi,rax
    0x48, 0x8d, 0x35, 0x0a, 0x00, 0x00, 0x00,  // lea    rsi,[rip+0xa] (msg)
    0xb0, 0x01,                                // mov    al,0x1
    0x0f, 0x05,                                // syscall
    0xb0, 0x3c,                                // mov    al,0x3c (exit)
    0x48, 0x31, 0xff,                          // xor    rdi,rdi
    0x0f, 0x05,                                // syscall
    // msg:
    'Y','o','u',' ','w','i','n','!','\n'
};

int main(int argc, char *argv[]) {
    signal(SIGSEGV, segfault_handler);
    check_debugger();

    if (argc != 2) {
        puts("Usage: ./crackme_ultimate <key>");
        return 1;
    }
    
    if (!xor_check(argv[1])) {
        puts("Invalid key.");
        // cause segfault if someone bruteforces:
        int *p = NULL; *p = 42;
        return 1;
    }
    
    void *mem = mmap(NULL, 4096, PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, win_code, sizeof(win_code));
    
    ((void(*)())mem)();
    return 0;
}
