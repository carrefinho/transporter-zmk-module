/*
 * Copyright (c) 2026 carrefinho
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>

#include <dt-bindings/zmk/hid_indicators.h>
#include <zmk/event_manager.h>
#include <zmk/events/hid_indicators_changed.h>

static const struct gpio_dt_spec caps_led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static int caps_led_init(void)
{
	if (!gpio_is_ready_dt(&caps_led)) {
		return -ENODEV;
	}

	return gpio_pin_configure_dt(&caps_led, GPIO_OUTPUT_INACTIVE);
}

SYS_INIT(caps_led_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

static int caps_led_event(const zmk_event_t *eh)
{
	const struct zmk_hid_indicators_changed *ev = as_zmk_hid_indicators_changed(eh);

	if (ev != NULL) {
		gpio_pin_set_dt(&caps_led, (ev->indicators & HID_INDICATOR_CAPS_LOCK) != 0);
	}

	return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(caps_led, caps_led_event);
ZMK_SUBSCRIPTION(caps_led, zmk_hid_indicators_changed);
