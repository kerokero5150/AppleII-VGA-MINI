#include <pico/stdlib.h>
#include "hires_color_patterns.h"
#include "hires_dot_patterns.h"
#include "render.h"
#include "vga.h"


static void render_hires_line(uint8_t *page, uint line);


static uint hires_line_to_mem_offset(uint line) {
    return ((line & 0x07) << 10) | ((line & 0x38) << 4) | (((line & 0xc0) >> 6) * 40);
}


void __time_critical_func(render_hires)(uint8_t *page) {
    vga_prepare_frame();

    // Skip 48 lines to center vertically
    struct vga_scanline *skip_sl = vga_prepare_scanline();
    for(int i=0; i < 48; i++) {
        skip_sl->data[i] = (uint32_t)THEN_WAIT_HSYNC << 16;
    }
    skip_sl->length = 48;
    vga_submit_scanline(skip_sl);

    for(uint line=0; line < 192; line++) {
        render_hires_line(page, line);
    }
}


void __time_critical_func(render_mixed_hires)(uint8_t *hires_page, uint8_t *text_page) {
    vga_prepare_frame();

    // Skip 48 lines to center vertically
    struct vga_scanline *skip_sl = vga_prepare_scanline();
    for(int i=0; i < 48; i++) {
        skip_sl->data[i] = (uint32_t)THEN_WAIT_HSYNC << 16;
    }
    skip_sl->length = 48;
    vga_submit_scanline(skip_sl);

    for(uint line=0; line < 160; line++) {
        render_hires_line(hires_page, line);
    }

    for(uint line=20; line < 24; line++) {
        render_text_line(text_page, line);
    }
}


static void __time_critical_func(render_hires_line)(uint8_t *page, uint line) {
    const uint8_t *line_mem = page + hires_line_to_mem_offset(line);

    struct vga_scanline *sl = vga_prepare_scanline();
    uint sl_pos = 0;

    // Each hires byte contains 7 pixels which may be shifted right 1/2 a pixel. That is
    // represented here by 14 'dots' to precisely describe the half-pixel positioning.
    //
    // For each pixel, inspect a window of 8 dots around the pixel to determine the
    // precise dot locations and colors.
    //
    // Dots would be scanned out to the CRT from MSB to LSB (left to right here):
    //
    //              previous      |        next
    //                dots        |        dots
    //        +-------------------+--------------------------------------------------+
    // dots:  | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 | 23 | ... | 14 | 13 | 12 | ...
    //             |              |         |              |
    //             \______________|_________|______________/
    //                            |         |
    //                            \_________/
    //                              current
    //                               pixel
    uint32_t dots = 0;
    uint oddness = 0;

    // Load in the first 14 dots
    dots |= (uint32_t)hires_dot_patterns[line_mem[0]] << 14;

    for(uint i=1; i < 41/*FIXME: handle the last 7 dots better*/; i++) {
        // Load in the next 14 dots
        uint b = line_mem[i];
        if((b & 0x80) && (dots & (1u << 14))) {
            // Extend the last 1 from the previous byte
            dots |= (1u << 13);
        }
        dots |= (uint32_t)hires_dot_patterns[b];

        // Consume 14 dots
        for(uint j=0; j < 7; j++) {
            uint dot_pattern = oddness | ((dots >> 23) & 0xff);
            sl->data[sl_pos] = hires_color_patterns[dot_pattern];
            sl_pos++;
            dots <<= 2;
            oddness ^= 0x100;
        }
    }

    sl->length = sl_pos;
    sl->repeat_count = 1;
    vga_submit_scanline(sl);
}