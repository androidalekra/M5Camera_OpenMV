/*
 * This file is part of the OpenMV project.
 * Copyright (c) 2013/2014 Ibrahim Abdelkader <i.abdalkader@gmail.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * Board configuration and pin definitions.
 *
 */
#ifndef __OMV_BOARDCONFIG_H__
#define __OMV_BOARDCONFIG_H__

#include "imlib_config.h"
// #include "lcd.h"
// #include "global_config.h"

#define OMV_INIT_BPP 2

// IDE config
#define IDE_DBG_MAX_PACKET  64
#define IDE_DBG_CMD_START_FLAG 0x30

#if !defined(OMV_MINIMUM) || CONFIG_MAIXPY_IDE_SUPPORT
  #define OMV_JPEG_BUF_SIZE 23 * 1024 // IDE JPEG buffer (header + data).
#endif

#ifndef OMV_MINIMUM
#define OMV_FB_ALLOC_SIZE 700 * 1024 // minimum fb alloc size
#define FB_MAX_ALLOC_TIMES    100

#else  //OMV_MINIMUM

#define OMV_FB_ALLOC_SIZE 300 * 1024 // minimum fb alloc size
#define FB_MAX_ALLOC_TIMES    50

#endif //OMV_MINIMUM

// #include "dvp.h"
#define DCMI_RESET_LOW()      dvp->cmos_cfg &= ~DVP_CMOS_RESET
#define DCMI_RESET_HIGH()     dvp->cmos_cfg |= DVP_CMOS_RESET
#define DCMI_PWDN_LOW()       dvp->cmos_cfg &= ~DVP_CMOS_POWER_DOWN
#define DCMI_PWDN_HIGH()      dvp->cmos_cfg |= DVP_CMOS_POWER_DOWN


// Architecture info
#define OMV_ARCH_STR            "K210" // 33 chars max
#define OMV_BOARD_TYPE          "Maix"

// Flash sectors for the bootloader.
// Flash FS sector, main FW sector, max sector.
#define OMV_FLASH_LAYOUT        {1, 2, 15}

#define OMV_XCLK_MCO            (0U)
#define OMV_XCLK_TIM            (1U)

// Sensor external clock source.
#define OMV_XCLK_SOURCE         (OMV_XCLK_TIM)

// Sensor external clock timer frequency.
// #define OMV_XCLK_FREQUENCY      (12000000)
#define OMV_XCLK_FREQUENCY      (CONFIG_SENSOR_FREQ)
// Sensor PLL register value.
#define OMV_OV7725_PLL_CONFIG   (0x41)  // x4
#define OMV_OV7725_BANDING      (0x3F)  //TODO:

// Bootloader LED GPIO port/pin
#define OMV_BOOTLDR_LED_PIN     (GPIO_PIN_1)
#define OMV_BOOTLDR_LED_PORT    (GPIOC)

// RAW buffer size
#define OMV_RAW_BUF_SIZE        (MAIN_FB()->w_max * MAIN_FB()->h_max * OMV_INIT_BPP)

// Enable hardware JPEG
#define OMV_HARDWARE_JPEG       (0)

// Enable MT9V034 and LEPTON sensors
#define OMV_ENABLE_MT9V034      (1)
#define OMV_ENABLE_LEPTON       (1)

// If buffer size is bigger than this threshold, the quality is reduced.
// This is only used for JPEG images sent to the IDE not normal compression.
#define JPEG_QUALITY_THRESH     (320*240*2)

// Low and high JPEG QS.
#define JPEG_QUALITY_LOW        50
#define JPEG_QUALITY_HIGH       90

// Linker script constants (see the linker script template stm32fxxx.ld.S).
// Note: fb_alloc is a stack-based, dynamically allocated memory on FB.
// The maximum available fb_alloc memory = FB_ALLOC_SIZE + FB_SIZE - (w*h*bpp).
#define OMV_FFS_MEMORY          CCM         // Flash filesystem cache memory
#define OMV_MAIN_MEMORY         SRAM1       // data, bss, stack and heap
#define OMV_DMA_MEMORY          AXI_SRAM    // DMA buffers memory.
#define OMV_FB_MEMORY           AXI_SRAM    // Framebuffer, fb_alloc
#define OMV_JPEG_MEMORY         SRAM3       // JPEG buffer memory.
#define OMV_VOSPI_MEMORY        SRAM4       // VoSPI buffer memory.

#define OMV_STACK_SIZE          (7K)
#define OMV_HEAP_SIZE           (240K)

#define OMV_MSC_BUF_SIZE        (12K)       // USB MSC bot data
#define OMV_VFS_BUF_SIZE        (1K)        // VFS sturct + FATFS file buffer (624 bytes)

#define OMV_BOOT_ORIGIN         0x08000000
#define OMV_BOOT_LENGTH         128K
#define OMV_TEXT_ORIGIN         0x08040000
#define OMV_TEXT_LENGTH         1792K
#define OMV_CCM_ORIGIN          0x20000000  // Note accessible by CPU and MDMA only.
#define OMV_CCM_LENGTH          128K
#define OMV_SRAM1_ORIGIN        0x30000000
#define OMV_SRAM1_LENGTH        256K
#define OMV_SRAM3_ORIGIN        0x30040000
#define OMV_SRAM3_LENGTH        32K
#define OMV_SRAM4_ORIGIN        0x38000000
#define OMV_SRAM4_LENGTH        64K
#define OMV_AXI_SRAM_ORIGIN     0x24000000
#define OMV_AXI_SRAM_LENGTH     512K

// Use the MPU to set an uncacheable memory region.
#define OMV_DMA_REGION_BASE     (OMV_AXI_SRAM_ORIGIN+(496*1024))
#define OMV_DMA_REGION_SIZE     MPU_REGION_SIZE_16KB

/* SCCB/I2C */
#define SCCB_I2C                (I2C1)
#define SCCB_AF                 (GPIO_AF4_I2C1)
#define SCCB_CLK_ENABLE()       __I2C1_CLK_ENABLE()
#define SCCB_CLK_DISABLE()      __I2C1_CLK_DISABLE()
#define SCCB_PORT               (GPIOB)
#define SCCB_SCL_PIN            (GPIO_PIN_8)
#define SCCB_SDA_PIN            (GPIO_PIN_9)

/* DCMI */
#define DCMI_TIM                (TIM1)
#define DCMI_TIM_PIN            (GPIO_PIN_8)
#define DCMI_TIM_PORT           (GPIOA)
#define DCMI_TIM_AF             (GPIO_AF1_TIM1)
#define DCMI_TIM_CHANNEL        (TIM_CHANNEL_1)
#define DCMI_TIM_CLK_ENABLE()   __TIM1_CLK_ENABLE()
#define DCMI_TIM_CLK_DISABLE()  __TIM1_CLK_DISABLE()
#define DCMI_TIM_PCLK_FREQ()    HAL_RCC_GetPCLK2Freq()

#define DCMI_RESET_PIN          (GPIO_PIN_10)
#define DCMI_RESET_PORT         (GPIOA)

#define DCMI_PWDN_PIN           (GPIO_PIN_7)
#define DCMI_PWDN_PORT          (GPIOD)

#define DCMI_FSIN_PIN           (GPIO_PIN_5)
#define DCMI_FSIN_PORT          (GPIOB)

#define DCMI_D0_PIN             (GPIO_PIN_6)
#define DCMI_D1_PIN             (GPIO_PIN_7)
#define DCMI_D2_PIN             (GPIO_PIN_0)
#define DCMI_D3_PIN             (GPIO_PIN_1)
#define DCMI_D4_PIN             (GPIO_PIN_4)
#define DCMI_D5_PIN             (GPIO_PIN_6)
#define DCMI_D6_PIN             (GPIO_PIN_5)
#define DCMI_D7_PIN             (GPIO_PIN_6)

#define DCMI_D0_PORT            (GPIOC)
#define DCMI_D1_PORT            (GPIOC)
#define DCMI_D2_PORT            (GPIOE)
#define DCMI_D3_PORT            (GPIOE)
#define DCMI_D4_PORT            (GPIOE)
#define DCMI_D5_PORT            (GPIOB)
#define DCMI_D6_PORT            (GPIOE)
#define DCMI_D7_PORT            (GPIOE)

#define DCMI_HSYNC_PIN          (GPIO_PIN_4)
#define DCMI_VSYNC_PIN          (GPIO_PIN_7)
#define DCMI_PXCLK_PIN          (GPIO_PIN_6)

#define DCMI_HSYNC_PORT         (GPIOA)
#define DCMI_VSYNC_PORT         (GPIOB)
#define DCMI_PXCLK_PORT         (GPIOA)

#define DCMI_FSIN_LOW()         HAL_GPIO_WritePin(DCMI_FSIN_PORT, DCMI_FSIN_PIN, GPIO_PIN_RESET)
#define DCMI_FSIN_HIGH()        HAL_GPIO_WritePin(DCMI_FSIN_PORT, DCMI_FSIN_PIN, GPIO_PIN_SET)

#define DCMI_VSYNC_IRQN         EXTI9_5_IRQn
#define DCMI_VSYNC_IRQ_LINE     (7)

#define WINC_SPI                (SPI2)
#define WINC_SPI_AF             (GPIO_AF5_SPI2)
#define WINC_SPI_TIMEOUT        (1000)
// SPI1/2/3 clock source is PLL2 (160MHz/4 == 40MHz).
#define WINC_SPI_PRESCALER      (SPI_BAUDRATEPRESCALER_4)
#define WINC_SPI_CLK_ENABLE()   __HAL_RCC_SPI2_CLK_ENABLE()

#define WINC_SPI_SCLK_PIN       (GPIO_PIN_13)
#define WINC_SPI_MISO_PIN       (GPIO_PIN_14)
#define WINC_SPI_MOSI_PIN       (GPIO_PIN_15)

#define WINC_SPI_SCLK_PORT      (GPIOB)
#define WINC_SPI_MISO_PORT      (GPIOB)
#define WINC_SPI_MOSI_PORT      (GPIOB)

#define WINC_EN_PIN             (GPIO_PIN_5)
#define WINC_CS_PIN             (GPIO_PIN_12)
#define WINC_RST_PIN            (GPIO_PIN_12)
#define WINC_IRQ_PIN            (pin_D13)

#define WINC_EN_PORT            (GPIOA)
#define WINC_CS_PORT            (GPIOB)
#define WINC_RST_PORT           (GPIOD)

#define WINC_CS_LOW()           HAL_GPIO_WritePin(WINC_CS_PORT, WINC_CS_PIN, GPIO_PIN_RESET)
#define WINC_CS_HIGH()          HAL_GPIO_WritePin(WINC_CS_PORT, WINC_CS_PIN, GPIO_PIN_SET)

#define I2C_PORT                GPIOB
#define I2C_SIOC_PIN            GPIO_PIN_10
#define I2C_SIOD_PIN            GPIO_PIN_11

#define I2C_SIOC_H()            HAL_GPIO_WritePin(I2C_PORT, I2C_SIOC_PIN, GPIO_PIN_SET)
#define I2C_SIOC_L()            HAL_GPIO_WritePin(I2C_PORT, I2C_SIOC_PIN, GPIO_PIN_RESET)

#define I2C_SIOD_H()            HAL_GPIO_WritePin(I2C_PORT, I2C_SIOD_PIN, GPIO_PIN_SET)
#define I2C_SIOD_L()            HAL_GPIO_WritePin(I2C_PORT, I2C_SIOD_PIN, GPIO_PIN_RESET)

#define I2C_SIOD_READ()         HAL_GPIO_ReadPin(I2C_PORT, I2C_SIOD_PIN)
#define I2C_SIOD_WRITE(bit)     HAL_GPIO_WritePin(I2C_PORT, I2C_SIOD_PIN, bit);

#define I2C_SPIN_DELAY          32

#define LEPTON_SPI                  (SPI3)
#define LEPTON_SPI_AF               (GPIO_AF6_SPI3)
// SPI1/2/3 clock source is PLL2 (160MHz/8 == 20MHz).
#define LEPTON_SPI_PRESCALER        (SPI_BAUDRATEPRESCALER_8)

#define LEPTON_SPI_IRQn             (SPI3_IRQn)
#define LEPTON_SPI_IRQHandler       (SPI3_IRQHandler)

#define LEPTON_SPI_DMA_IRQn         (DMA1_Stream0_IRQn)
#define LEPTON_SPI_DMA_STREAM       (DMA1_Stream0)

#define LEPTON_SPI_DMA_REQUEST      (DMA_REQUEST_SPI3_RX)
#define LEPTON_SPI_DMA_IRQHandler   (DMA1_Stream0_IRQHandler)

#define LEPTON_SPI_RESET()          __HAL_RCC_SPI3_FORCE_RESET()
#define LEPTON_SPI_RELEASE()        __HAL_RCC_SPI3_RELEASE_RESET()

#define LEPTON_SPI_CLK_ENABLE()     __HAL_RCC_SPI3_CLK_ENABLE()
#define LEPTON_SPI_CLK_DISABLE()    __HAL_RCC_SPI3_CLK_DISABLE()

#define LEPTON_SPI_SCLK_PIN         (GPIO_PIN_3)
#define LEPTON_SPI_MISO_PIN         (GPIO_PIN_4)
#define LEPTON_SPI_MOSI_PIN         (GPIO_PIN_5)
#define LEPTON_SPI_SSEL_PIN         (GPIO_PIN_15)

#define LEPTON_SPI_SCLK_PORT        (GPIOB)
#define LEPTON_SPI_MISO_PORT        (GPIOB)
#define LEPTON_SPI_MOSI_PORT        (GPIOB)
#define LEPTON_SPI_SSEL_PORT        (GPIOA)

// For K210
#define __CLZ(n) __builtin_clz(n)
/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in two unsigned short values.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
#define __REV16          __builtin_bswap16                           /* ToDo:  ARMCC_V6: check if __builtin_bswap16 could be used */

#endif //__OMV_BOARDCONFIG_H__
