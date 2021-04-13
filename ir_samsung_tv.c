
#include "esp_log.h"
#include "driver/rmt.h"
#include "ir_samsung_tv.h"

#define RMT_TX_CARRIER_EN           1
#define RMT_CARRIER_FREQ_38         38000
#define RMT_CARRIER_DUTY            33

#define RMT_CLK_DIV                 80
#define RMT_TICK_10_US              (80000000/RMT_CLK_DIV/100000)

#define SAMSUNG_BITS                32

#define SAMSUNG_HEADER_HIGH_US      4480
#define SAMSUNG_HEADER_LOW_US       4480

#define SAMSUNG_BIT_ONE_HIGH_US     560
#define SAMSUNG_BIT_ONE_LOW_US      1680

#define SAMSUNG_BIT_ZERO_HIGH_US    560
#define SAMSUNG_BIT_ZERO_LOW_US     560

#define SAMSUNG_END_HIGH_US         560
#define SAMSUNG_END_LOW_US          0x7fff

#define SAMSUNG_ITEM_COUNT          34

#define CHECK(x) do { esp_err_t __; if ((__ = x) != ESP_OK) return __; } while (0)
#define CHECK_ARG(VAL) do { if (!(VAL)) return ESP_ERR_INVALID_ARG; } while (0)


const char *SAMSUNG_TAG = "[ir_samsung_tv]";

static rmt_item32_t samsung_bit0 = {0};
static rmt_item32_t samsung_bit1 = {0};
static rmt_item32_t samsung_header = {0};
static rmt_item32_t samsung_end = {0};


esp_err_t ir_samsung_tv_init() {

    samsung_header.duration0 = SAMSUNG_HEADER_HIGH_US / 10 * RMT_TICK_10_US;
    samsung_header.level0 = 1;
    samsung_header.duration1 = SAMSUNG_HEADER_LOW_US / 10 * RMT_TICK_10_US;
    samsung_header.level1 = 0;

    samsung_end.duration0 = SAMSUNG_END_HIGH_US / 10 * RMT_TICK_10_US;
    samsung_end.level0 = 1;
    samsung_end.duration1 = SAMSUNG_END_LOW_US / 10 * RMT_TICK_10_US;
    samsung_end.level1 = 0;

    samsung_bit0.duration0 = SAMSUNG_BIT_ZERO_HIGH_US / 10 * RMT_TICK_10_US;
    samsung_bit0.level0 = 1;
    samsung_bit0.duration1 = SAMSUNG_BIT_ZERO_LOW_US / 10 * RMT_TICK_10_US;
    samsung_bit0.level1 = 0;

    samsung_bit1.duration0 = SAMSUNG_BIT_ONE_HIGH_US / 10 * RMT_TICK_10_US;
    samsung_bit1.level0 = 1;
    samsung_bit1.duration1 = SAMSUNG_BIT_ONE_LOW_US / 10 * RMT_TICK_10_US;
    samsung_bit1.level1 = 0;

    rmt_config_t rmt_tx;
    rmt_tx.channel = ir_samsung_config.channel;
    rmt_tx.gpio_num = ir_samsung_config.gpio;
    rmt_tx.mem_block_num = 1;
    rmt_tx.clk_div = RMT_CLK_DIV;
    rmt_tx.tx_config.loop_en = false;
    rmt_tx.tx_config.carrier_duty_percent = RMT_CARRIER_DUTY;
    rmt_tx.tx_config.carrier_freq_hz = RMT_CARRIER_FREQ_38;
    rmt_tx.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH;
    rmt_tx.tx_config.carrier_en = RMT_TX_CARRIER_EN;
    rmt_tx.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
    rmt_tx.tx_config.idle_output_en = true;
    rmt_tx.rmt_mode = RMT_MODE_TX;

    CHECK(rmt_config(&rmt_tx));
    CHECK(rmt_driver_install(rmt_tx.channel, 0, 0));

    return ESP_OK;
}

esp_err_t ir_samsung_tv_send(unsigned long data) {

    CHECK_ARG(data);

    ESP_LOGI(SAMSUNG_TAG, "code = 0x%lx", data);

    rmt_item32_t items[SAMSUNG_ITEM_COUNT];
    items[0] = samsung_header;

    uint32_t mask = 0x01 << (SAMSUNG_BITS - 1);
    for (int i = 1; i <= SAMSUNG_BITS; i++) {
        items[i] = (data & mask) ? samsung_bit1 : samsung_bit0;
        mask >>= 1;
    }
    items[SAMSUNG_ITEM_COUNT - 1] = samsung_end;

    return rmt_write_items(ir_samsung_config.channel, items, SAMSUNG_ITEM_COUNT, true);
}
