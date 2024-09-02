extern void clear_screen();
extern void draw_bar();
extern void disable_cursor();
extern void draw_mouse_cursor(int x, int y);
extern void process_mouse_input();

extern int mouse_x; // Global mouse_x değişkenini tanımlayın
extern int mouse_y; // Global mouse_y değişkenini tanımlayın

void main() {
    disable_cursor();  
    clear_screen();    
    draw_bar();
    
    while (1) {
        process_mouse_input();  

        // Ekranı güncellemek için önce imleci temizleyin
        draw_mouse_cursor(mouse_x, mouse_y);
    }
}
