# gVent Contributor Guidelines

The gVent source code is divided into two layers of abstraction: 1) the Application Layer, and 2) the Platform Layer. The Platform Layer abstracts the details of hardware interaction and presents a consistent interface to the Application Layer. Source code in the Application Layer focuses on control of specific actuators or sensors to faciliate ventilation. Source code in the Platform Layer focuses on writing/read the appropriate hardware addresses.

There is also the hardware abstraction layer (HAL). The platform layer interacts directly with the HAL. The application layer should never interact with the HAL. The HAL is a copy of the generated code from the STMCubeMX IDE.

These layers organized in the respository as follows:

```
./
    src/                /* .c files go here... */
        main.c          /* the startup code for gVent */
        application/    /* application layer source code */
        platform/       /* platform layer source code */

    include/            /* .h files go here... */
        main.h
        application/    /* definitions/headers for application layer */
        platform/       /* definitions/headers for the platform layer */

    device/             /* stm32f401re device specific files */

    lib/                /* additional libraries go here... */
        stm32/          /* HAL definitions and source code for STM32 targets */
```

## Application Layer Development
TODO

### Running Application Layer Unit Tests
TODO - something about to run GoogleTest.

## Platform Layer Development
TODO

### Building for STM32F4 Microprocessor Target
The Makefile in the root of this repository contains the relevant compilation, linking to produce a binary that can be uploaded ("flashed") onto the the STM32F401RE microprocessor (the "target").

#### Dependencies
Building and flashing the target requires the following dependencies:

* Standard C build packages - `build-essential`
* USB interface package - `libusb-1.0-0-dev`
* GCC for ARM targets - `gcc-arm-none-eabi`
* ST-Link for flashing the target - `stlink-tools` (on Ubuntu 20.x or above), see the [ST-Link GitHub page](https://github.com/stlink-org/stlink) for details.

This procedure has been tested and validated on a Ubuntu 20.04 LTS Virtual Machine running on a Windows 10 host. Other platforms/setups might require special configurations or dependencies.

#### Command Reference

To build an executable (`gvent.bin`), run the following command from within the project root directory:

```
make clean all
```

To upload or flash the STM32 Nucleo-64 board, use the following command from within the project root directory:

```
make flash
```

#### Additional References

* [Basics of building for STM32F4](https://github.com/sdiemert/stm32f4-basic)
* [Compiling STM32F4 blink using make](https://github.com/sdiemert/stm32f4-blink)
* [Compilinig STM32F4 blink with a timer peripheral using make](https://github.com/sdiemert/stm32f4-timer-blink)