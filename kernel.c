// kernel.c

extern void clear_screen();
extern void draw_bar();

void main() {
    clear_screen();
    draw_bar();
    while (1) {
        __asm__("hlt"); // Sonsuz döngü
    }
}
