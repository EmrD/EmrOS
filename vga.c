void set_vga_mode() {
    // VGA modunu ayarlamak için gerekli kodlar (eğer gerekiyorsa).
}

void clear_screen() {
    unsigned char *vga_buffer = (unsigned char *)0xb8000;
    unsigned int size = 80 * 25 * 2;
    for (unsigned int i = 0; i < size; i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i + 1] = 0x01; // Arka plan rengini mavi yap
    }
}

void draw_bar() {
    unsigned char *vga_buffer = (unsigned char *)0xb8000;
    int bar_height = 1;
    int bar_y = 25 - bar_height;
    for (int y = bar_y; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            int index = (y * 80 + x) * 2;
            vga_buffer[index] = ' ';
            vga_buffer[index + 1] = 0x07; // Beyaz renk
        }
    }

    const char *text = "EmrOS";
    int text_length = 5;
    int text_start = (80 - text_length) / 2;
    for (int i = 0; i < text_length; i++) {
        int index = ((25 - 1) * 80 + (text_start + i)) * 2;
        vga_buffer[index] = text[i];
        vga_buffer[index + 1] = 0x07; // Beyaz renk
    }
}
