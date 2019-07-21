// Add RESET codes to reboot the chip
#define RESTART_ADDR       0xE000ED0C
#define READ_RESTART()     (*(volatile uint32_t *)RESTART_ADDR)
#define WRITE_RESTART(val) ((*(volatile uint32_t *)RESTART_ADDR) = (val))

/**
 * This method resets the chip. Call with caution!
 */
void RESET_CHIP() {
    // 0000101111110100000000000000100
    // Assert [2]SYSRESETREQ
    WRITE_RESTART(0x5FA0004);
}