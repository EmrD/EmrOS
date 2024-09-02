// kernel.c

extern void clear_screen();
extern void draw_bar();
extern void disable_cursor();

void main() {
    disable_cursor();  // Cursoru gizle
    clear_screen();    // Ekranı temizle ve arka planı mavi yap
    draw_bar();        // Alt kısmına bar ekle
    while (1) {
        __asm__("hlt"); // Sonsuz döngü
    }
}
