#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>

void win() {
    puts("🧠 Elite cracked! You win.");
    exit(0);
}

void xor_decrypt(uint8_t *data, size_t len, uint8_t key) {
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("Usage: ./crackme_elite <key>");
        return 1;
    }

    char *user_input = argv[1];

    if (strlen(user_input) != 6) {
        puts("Wrong length!");
        return 1;
    }

    uint8_t key = 0x5A;
    char expected[] = { 'k'^key, 'r'^key, '4'^key, 'c'^key, 'k'^key, 'z'^key }; // = "kr4ckz"
    
    for (int i = 0; i < 6; i++) {
        if ((user_input[i] ^ key) != expected[i]) {
            puts("Access denied.");
            return 1;
        }
    }

    // prepare self-modifying win code
    void *ptr = (void*) win;
    size_t win_size = 64; // for simplicity

    // make memory writable
    if (mprotect((void *)((uintptr_t)ptr & ~0xFFF), 4096, 0x7) != 0) {
        perror("mprotect");
        return 1;
    }

    xor_decrypt((uint8_t*)win, win_size, 0xAA); // decrypt
    ((void(*)())win)();                         // call
}

