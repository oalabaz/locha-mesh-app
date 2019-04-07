/**
 * @Copyright:
 * (c) Copyright 2019 locha.io project developers
 * Licensed under a MIT license, see LICENSE file in the root folder
 * for a full text
 */

#include <Arduino.h>
#include "hal/hardware.h"
#include "button.h"

unsigned long timerButton;

void irq_button(void)
{
    int currentButtonState = digitalRead(BTN_GPIO);

    switch (currentButtonState)
    {
    case LOW:
        timerButton = millis();
        break;
    case HIGH:
        timerButton = millis() - timerButton;
        if (timerButton > 50 && timerButton <= 1000)
        {
            cb_next_option();
        }
        if (timerButton > 1000)
        {
            cb_confirm_option();
        }
        break;
    }
}