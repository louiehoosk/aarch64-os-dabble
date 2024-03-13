#include <stdint.h>

extern char __heap_base;
extern char __heap_top;
extern char __stack_base;
extern char __stack_top;
extern char __startup;
extern char __ramrom;

const int PAGE_SIZE = 128;

int page_count = 0;

void chee_init() {
    for(uint8_t* ptr = &__heap_base; ptr < (uint8_t*)&__heap_top; ptr += PAGE_SIZE) {
	*ptr = 0;
    }
}

void* chee_malloc(int bytecount){
    int max_page_count = (&__heap_top - &__heap_base) / PAGE_SIZE;
    int req_page_count = (bytecount + 1) / PAGE_SIZE + 1;
    
    uint8_t* dest_ptr = &__heap_base;
    do {
	// find new pages start canidate
	while (*dest_ptr != 0) {
	    dest_ptr += PAGE_SIZE;
	}

	// check if necessary num of free contiguous pages fits
	for ( int i = 1; i < req_page_count; ++i ) {
	    if ( dest_ptr[i*PAGE_SIZE] != 0 ) {
		dest_ptr += i*PAGE_SIZE;
		break;
	    }
	}
    } while (*dest_ptr != 0);

    *dest_ptr = req_page_count;

    return ++dest_ptr;
}

void chee_free(uint8_t* mem) {
    mem[-1] = 0;
}
