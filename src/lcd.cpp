#include "lcd.hpp"
#include "utility.hpp"
#include <string.h>

namespace {
    uint8_t y = 0;
    uint8_t user_defined = 7;
	
	inline void rs_high()  { LCD_RS_PORT  |=  _BV(LCD_RS_PIN);  }
	inline void rs_low()   { LCD_RS_PORT  &= ~_BV(LCD_RS_PIN);  }
	inline void e_high()   { LCD_E_PORT   |=  _BV(LCD_E_PIN);   }
	inline void e_low()    { LCD_E_PORT   &= ~_BV(LCD_E_PIN);   }
    inline void vo_high()  { LCD_VO_PORT  |=  _BV(LCD_VO_PIN);  }
    inline void vo_low()   { LCD_VO_PORT  &= ~_BV(LCD_VO_PIN);  }
	inline void db4_high() { LCD_DB4_PORT |=  _BV(LCD_DB4_PIN); }
	inline void db4_low()  { LCD_DB4_PORT &= ~_BV(LCD_DB4_PIN); }
	inline void db5_high() { LCD_DB5_PORT |=  _BV(LCD_DB5_PIN); }
	inline void db5_low()  { LCD_DB5_PORT &= ~_BV(LCD_DB5_PIN); }
	inline void db6_high() { LCD_DB6_PORT |=  _BV(LCD_DB6_PIN); }
	inline void db6_low()  { LCD_DB6_PORT &= ~_BV(LCD_DB6_PIN); }
	inline void db7_high() { LCD_DB7_PORT |=  _BV(LCD_DB7_PIN); }
	inline void db7_low()  { LCD_DB7_PORT &= ~_BV(LCD_DB7_PIN); }

    inline void data_output() {
        DDR(LCD_DB4_PORT) |= _BV(LCD_DB4_PIN);
        DDR(LCD_DB5_PORT) |= _BV(LCD_DB5_PIN);
        DDR(LCD_DB6_PORT) |= _BV(LCD_DB6_PIN);
        DDR(LCD_DB7_PORT) |= _BV(LCD_DB7_PIN);
    }

    inline void data_set(uint8_t data) {
        if (data & 0x1) db4_high();
        else db4_low();

        if (data & 0x2) db5_high();
        else db5_low();

        if (data & 0x4) db6_high();
        else db6_low();

        if (data & 0x8) db7_high();
        else db7_low();
    }

    void e_toggle() {
        e_low();
        e_high();
        e_low();
        _delay_us(LCD_DELAY_CMD);
    }

    void write(uint8_t data, bool rs) {
        if (rs) rs_high();
        else rs_low();

        data_set(data >> 4);
        e_toggle();

        data_set(data);
        e_toggle();
    }

    void command(uint8_t cmd) {
        write(cmd, LCD_RS_INSTRUCTION);
    }

    void data(uint8_t data) {
        write(data, LCD_RS_DATA);
    }
}

void LCD::init() {
    DDR(LCD_RS_PORT) |= _BV(LCD_RS_PIN);
    DDR(LCD_E_PORT)  |= _BV(LCD_E_PIN);
    DDR(LCD_VO_PORT) |= _BV(LCD_VO_PIN);
    data_output();
    
    vo_low();
    _delay_us(LCD_DELAY_BOOTUP);

    data_set(0b0011);
    e_toggle();
    _delay_us(LCD_DELAY_INIT);

    e_toggle();
    _delay_us(LCD_DELAY_INIT_REP);

    e_toggle();
    _delay_us(LCD_DELAY_INIT_REP);

    data_set(0b0010);
    e_toggle();
    _delay_us(LCD_DELAY_INIT_4BIT);

    command(LCD_FUNCTION_DEFAULT);
    command(LCD_DISP_OFF);
    clear();
    command(LCD_MODE_DEFAULT);
    command(LCD_DISP_ON);
}

void LCD::pos(uint8_t x, uint8_t y) {
    ::y = y == 1;

    command(
        _BV(LCD_DDRAM) +
        (y == 0 ? LCD_START_LINE1 : LCD_START_LINE2) +
        x
    );
}

void LCD::clear() {
    y = 0;
    command(_BV(LCD_CLR));
    _delay_us(LCD_DELAY_CLEAR);
}

void LCD::clear(uint8_t line) {
    pos(0, line);
    put_space(LCD_DISP_LENGTH);
    pos(0, line);
}

void LCD::home() {
    y = 0;
    command(_BV(LCD_HOME));
    _delay_us(LCD_DELAY_CLEAR);
}

void LCD::newline() {
    pos(0, y + 1);
}

void LCD::putc(char ch) {
    if (ch == '\n')
        newline();
    else
        data(ch);
}

void LCD::puts(const char* str) {
    while (*str)
        putc(*str++);
}

void LCD::puts(const char* str, uint8_t line, bool also_clear) {
    if (also_clear)
        clear(line);
    pos((LCD_DISP_LENGTH - strlen(str)) / 2, line);
    puts(str);
}

void LCD::puts_P(PGM_P str) {
    char ch;

    while (true) {
        ch = pgm_read_byte(str++);
        if (ch == '\0')
            break;
        putc(ch);
    }
}

void LCD::put_space(uint8_t len) {
    while (len--)
        putc(' ');
}

uint8_t LCD::put_def(const uint8_t* ch, uint8_t x, uint8_t y) {
    uint8_t id = define_char(ch);
    pos(x, y);
    putc(id);

    return id;
}

uint8_t LCD::put_def_P(PGM_P ch, uint8_t x, uint8_t y) {
    uint8_t id = define_char_P(ch);
    pos(x, y);
    putc(id);

    return id;
}

uint8_t LCD::get_next_char_id() {
    if (++user_defined == 8)
        user_defined = 0;

    return user_defined;
}

uint8_t LCD::define_char(const uint8_t* ch) {
    return define_char(ch, get_next_char_id());
}

uint8_t LCD::define_char(const uint8_t* ch, uint8_t id) {
    command(_BV(LCD_CGRAM) | (id << 3));
    for (uint8_t i = 0; i < 8; i++)
        data(ch[i]);

    return id;
}

uint8_t LCD::define_char_P(PGM_P ch) {
    return define_char_P(ch, get_next_char_id());
}

uint8_t LCD::define_char_P(PGM_P ch, uint8_t id) {
    command(_BV(LCD_CGRAM) | (id << 3));
    for (uint8_t i = 0; i < 8; i++)
        data(pgm_read_byte(ch + i));

    return id;
}

void LCD::shift_left() {
    command(LCD_MOVE_DISP_LEFT);
}

void LCD::shift_right() {
    command(LCD_MOVE_DISP_RIGHT);
}

void LCD::cursor_left() {
    command(LCD_MOVE_CURSOR_LEFT);
}

void LCD::cursor_right() {
    command(LCD_MOVE_CURSOR_RIGHT);
}

void LCD::mode(bool on, bool cursor, bool blink) {
    uint8_t cmd = _BV(LCD_ON);
    if (on) cmd |= _BV(LCD_ON_DISPLAY);
    if (cursor) cmd |= _BV(LCD_ON_CURSOR);
    if (blink) cmd |= _BV(LCD_ON_BLINK);
    command(cmd);
}
