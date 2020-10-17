/*
 * pin.h
 *
 * This is a middleware file to abstraction the task's
 * interaction with devices so it doesn't have to
 * deal with hardware directly.
 *
 * To be reimplemented on COSMIC hooks up devices.
 *
 *  Created on: Sep. 22, 2020
 *      Author: sdiemert
 */

#ifndef SRC_PLATFORM_PIN_H_
#define SRC_PLATFORM_PIN_H_

#include <platform/configuration.h>

void pin13_up() {
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, SET);
}

void pin13_down() {
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, RESET);
}

void pin12_up() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
}

void pin12_down() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
}

void pin11_up() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
}

void pin11_down() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
}

void pin10_up() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);
}

void pin10_down() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET);
}

void wait(uint32_t delay_ms) {
	HAL_Delay(delay_ms);
}

#endif /* SRC_PLATFORM_PIN_H_ */
