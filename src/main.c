#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/rtc.h>
#include <stdint.h>

/* A new reading is taken every time main() is entered. */
int main(void)
{
    uint32_t boot_id = rtc_ticks();

    dclear(C_WHITE);
    dtext(20, 20, C_BLACK, "gint EX-word EXIT test");
    dprint(20, 50, C_BLACK, "BOOT ID: %08x", (unsigned)boot_id);
    dtext(20, 80, C_BLACK, "Press EXIT once.");
    dupdate();

    for(;;) {
        key_event_t ev = waitevent(NULL);
        if(ev.type != KEYEV_DOWN || ev.key != KEY_EXIT)
            continue;

        dtext(20, 115, C_RED, "EXIT RECEIVED");
        dupdate();

        /* Make the received event visible before returning to the OS. */
        uint32_t start = rtc_ticks();
        while((uint32_t)(rtc_ticks() - start) < 64) {}

        return -2;
    }
}
