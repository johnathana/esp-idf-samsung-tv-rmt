
#ifndef IR_SAMSUNG_TV_H
#define IR_SAMSUNG_TV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/gpio.h>
#include <esp_err.h>
#include <driver/rmt.h>

#define TV_SAMSUNG_ON       0xE0E09966
#define TV_SAMSUNG_OFF      0xE0E019E6
#define TV_SAMSUNG_CH_UP    0xE0E048B7
#define TV_SAMSUNG_CH_DOWN  0xE0E008F7
#define TV_SAMSUNG_VOL_UP   0xE0E0E01F
#define TV_SAMSUNG_VOL_DOWN 0xE0E0D02F
#define TV_SAMSUNG_SOURCE   0xE0E0807F
#define TV_SAMSUNG_MUTE     0xE0E0F00F
#define TV_SAMSUNG_1        0xE0E020DF
#define TV_SAMSUNG_2        0xE0E0A05F
#define TV_SAMSUNG_3        0xE0E0609F
#define TV_SAMSUNG_4        0xE0E010EF
#define TV_SAMSUNG_5        0xE0E0906F
#define TV_SAMSUNG_6        0xE0E050AF
#define TV_SAMSUNG_7        0xE0E030CF
#define TV_SAMSUNG_8        0xE0E0B04F
#define TV_SAMSUNG_9        0xE0E0708F
#define TV_SAMSUNG_0        0xE0E08877
#define TV_SAMSUNG_TXT      0xE0E034CB
#define TV_SAMSUNG_PRE_CH   0xE0E0C837
#define TV_SAMSUNG_CH_LIST  0xE0E0D629
#define TV_SAMSUNG_MENU     0xE0E058A7
#define TV_SAMSUNG_MEDIA    0xE0E031CE
#define TV_SAMSUNG_GUIDE    0xE0E0F20D
#define TV_SAMSUNG_INFO     0xE0E0F807
#define TV_SAMSUNG_TOOLS    0xE0E0D22D
#define TV_SAMSUNG_UP       0xE0E006F9
#define TV_SAMSUNG_LEFT     0xE0E0A659
#define TV_SAMSUNG_RIGHT    0xE0E046B9
#define TV_SAMSUNG_DOWN     0xE0E08679
#define TV_SAMSUNG_ENTER    0xE0E016E9
#define TV_SAMSUNG_RETURN   0xE0E01AE5
#define TV_SAMSUNG_EXIT     0xE0E0B44B
#define TV_SAMSUNG_E_MANUAL 0xE0E0FC03
#define TV_SAMSUNG_PIC_SIZE 0xE0E07C83
#define TV_SAMSUNG_AD_SUBT  0xE0E0A45B
#define TV_SAMSUNG_STOP     0xE0E0629D
#define TV_SAMSUNG_PLAY     0xE0E0E21D
#define TV_SAMSUNG_PAUSE    0xE0E052AD
#define TV_SAMSUNG_REWIND   0xE0E0A25D
#define TV_SAMSUNG_FORWARD  0xE0E012ED
#define TV_SAMSUNG_A        0xE0E036C9
#define TV_SAMSUNG_B        0xE0E028D7
#define TV_SAMSUNG_C        0xE0E0A857
#define TV_SAMSUNG_D        0xE0E06897


typedef struct {
    gpio_num_t gpio;
    rmt_channel_t channel;
} ir_samsung_t;

extern ir_samsung_t ir_samsung_config;


esp_err_t ir_samsung_tv_init();

esp_err_t ir_samsung_tv_send(unsigned long data);


#ifdef __cplusplus
} // extern C
#endif

#endif
