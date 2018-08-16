extern int liballoc_lock() {
	asm volatile ("cli");
}

extern int liballoc_unlock() {
	asm volatile("sti");
}

extern void* liballoc_alloc(int pages) {
	uintptr_t first_frame_addr;
	for(int i = 0; i < pages; i++) {
		uint32_t new_frame = allocate_frame();
		if(i == 0) {
			 first_frame_addr = (uintptr_t)mmap_read(new_frame, MMAP_GET_ADDR);
		}
		int32_t new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
	} return (void*)first_frame_addr;
}

extern int liballoc_free(void* page_addr,int pages) {
	return 1;
}
