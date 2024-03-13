#include <stdint.h>
#include "stchee.h"
 
volatile char *uart = (char *) 0x09000000;
extern char __heap_base;

void putchar(char c) {
    *uart = c;
}
 
void print(const char *s) {
    while(*s != '\0') {
        putchar(*s);
        s++;
    }
}

void printaddr(intptr_t num)
{
    char hexstr[16];
    char hex_chars[] = "0123456789ABCDEF";
    int i = 0;
    
    putchar('0');
    putchar('x');
    
    while ( num / 16 != 0 ) {
	hexstr[i++] = hex_chars[num % 16];
	num /= 16;
    }
    hexstr[i] = hex_chars[num];

    for(; i >= 0; i--) {
	putchar(hexstr[i]);
    }
}

void printsxn(const char* s1, int num) {
    print(s1);
    printaddr(num);
    print("\n");
}

void strcpy(char* dest, const char* s) {
    int i = 0;
    while(s[i] != '\0') {
	dest[i] = s[i];
	++i;
    }
}


typedef struct {
    char firstname[10];
    char lastname[10];
} fullname;

typedef struct {
    char firstname[70];
    char lastname[70];
} bigname;

typedef struct {
    char* firstname;
    char* lastname;
} fullname_ptr;


void kmain(void) {
    chee_init();
    
    printsxn("__head_base: ", (intptr_t)&__heap_base);
    
    fullname name = {"Cheetopaws", "Peeto\n"};
    print(name.firstname);

    fullname* name1 = (fullname*)chee_malloc(sizeof(fullname));
    fullname* name2 = (fullname*)chee_malloc(sizeof(fullname));
    fullname* name3 = (fullname*)chee_malloc(sizeof(fullname));
    printsxn("   name1 addr: ", (intptr_t)name1);
    printsxn("   name2 addr: ", (intptr_t)name2);
    printsxn("   name3 addr: ", (intptr_t)name3);

    chee_free((uint8_t*)name1);

    bigname* bigname1 = (bigname*)chee_malloc(sizeof(bigname));
    printsxn("bigname1 addr: ", (intptr_t)bigname1);

    chee_free((uint8_t*)name2);

    bigname* bigname2 = (bigname*)chee_malloc(sizeof(bigname));
    printsxn("bigname2 addr: ", (intptr_t)bigname2);
}
