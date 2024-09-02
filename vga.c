#include <stdint.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Global mouse konumları
int mouse_x = SCREEN_WIDTH / 2;
int mouse_y = SCREEN_HEIGHT / 2;

// Port'a veri göndermek için kullanılan outb fonksiyonu
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// VGA modunu ayarlamak için kullanılabilir bir fonksiyon
void set_vga_mode() {
    // Eğer VGA modunu değiştirecek bir kod gerekiyorsa, buraya ekleyebilirsiniz.
}

// Ekranı temizleme ve arka planı açık mavi yapma
void clear_screen() {
    unsigned char *vga_buffer = (unsigned char *)0xb8000;
    unsigned int size = 80 * 25 * 2;
    for (unsigned int i = 0; i < size; i += 2) {
        vga_buffer[i] = ' ';             
        vga_buffer[i + 1] = 0x1F;        
    }
}

// Alt kısma bir bar çizme ve ortasına metin yerleştirme
void draw_bar() {
    unsigned char *vga_buffer = (unsigned char *)0xb8000;
    int bar_height = 1;  
    int bar_y = 25 - bar_height;

    for (int y = bar_y; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            int index = (y * 80 + x) * 2;
            vga_buffer[index] = ' ';        
            vga_buffer[index + 1] = 0x1F;   
        }
    }

    const char *text = "EmrOS";
    int text_length = 5;
    int text_start = (80 - text_length) / 2;
    for (int i = 0; i < text_length; i++) {
        int index = ((25 - 1) * 80 + (text_start + i)) * 2;
        vga_buffer[index] = text[i];       
        vga_buffer[index + 1] = 0x1F;      
    }
}

void disable_cursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void draw_mouse_cursor(int x, int y) {
    unsigned char *vga_buffer = (unsigned char *)0xb8000;
    int index = (y * SCREEN_WIDTH + x) * 2;
    vga_buffer[index] = 0xDB;          
    vga_buffer[index + 1] = 0x0F;      
}

void update_mouse_position(int dx, int dy) {
    mouse_x += dx;
    mouse_y += dy;

    if (mouse_x < 0) mouse_x = 0;
    if (mouse_x >= SCREEN_WIDTH) mouse_x = SCREEN_WIDTH - 1;
    if (mouse_y < 0) mouse_y = 0;
    if (mouse_y >= SCREEN_HEIGHT) mouse_y = SCREEN_HEIGHT - 1;
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void process_mouse_input() {
    uint8_t status = inb(0x64);
    if (status & 0x01) {
        uint8_t mouse_byte = inb(0x60);
        int dx = (int8_t)mouse_byte;
        mouse_byte = inb(0x60);
        int dy = (int8_t)mouse_byte;

        update_mouse_position(dx, dy);
    }
}
