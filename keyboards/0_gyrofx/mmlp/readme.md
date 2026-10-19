# gyrofx-mmlp

A handwired 65% keyboard (68 keys) driven by an RP2040 board. Same layout and matrix as the [mml](../mml/readme.md), which uses an STM32F103 Blue Pill.

* Keyboard Maintainer: [gyrofx](https://github.com/gyrofx)
* Hardware Supported: RP2040 board (e.g. Raspberry Pi Pico)
* Hardware Availability: Handwired

## Wiring

Diodes are COL2ROW: the column wire goes to one switch pin, the diode sits on the other pin with its stripe (cathode) towards the row wire.

* Columns 0–15: `GP0 GP1 GP2 GP3 GP4 GP5 GP6 GP9 GP10 GP11 GP12 GP13 GP14 GP15 GP16 GP17`
* Rows 0–4: `GP18 GP19 GP20 GP21 GP22`

See `keyboard.json` for which key sits on which row/column.

Make example for this keyboard (after setting up your build environment):

    make 0_gyrofx/mmlp:default

Flashing example for this keyboard:

    make 0_gyrofx/mmlp:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **BOOTSEL button**: Hold the BOOTSEL button on the RP2040 board while plugging in the USB cable
* **Keycode in layout**: Press Fn + Esc (`QK_BOOT`)
