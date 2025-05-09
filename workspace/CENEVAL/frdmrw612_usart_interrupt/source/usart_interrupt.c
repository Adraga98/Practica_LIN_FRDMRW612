/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "app.h"
#include "fsl_usart.h"
#include "fsl_gpio.h"
#include "LIN.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t Msgs[TOTAL_MSGS] = MSG_IDS;
static bool SendMsg = false;
static uint8_t Index = 0U;
static uint32_t counter = 0U;
static uint32_t counter2 = 0U;
static stLinMsg BufferRxFrame = {0U};
static uint8_t BufferRxData[16] = {0U};

/*******************************************************************************
 * Code
 ******************************************************************************/
void GPIO_INTA_DriverIRQHandler(void)
{
    /* clear the interrupt status */
    GPIO_PinClearInterruptFlag(GPIO, 0, 20, 0);
    /* Change state of switch. */

    if(counter > counter2)
    {
    	if((counter - counter2) > 10)
		{
			SendMsg = true;

			Index = Index < (TOTAL_MSGS - 1) ? Index+1 : 0U;

			counter2 = counter;
		}
    }
    else
    {
    	counter2 = counter;
    }

    SDK_ISR_EXIT_BARRIER;
}

void SysTick_Handler(void)
{
	if(counter < 500000)
	{
		counter++;
	}
	else
	{
		counter = 0;
	}
}

static void SysTick_Init(void)
{
	uint32_t coreClock = 0U;
	uint32_t tickRate = 0U;

	coreClock = CLOCK_GetCoreSysClkFreq();
	tickRate = coreClock / 1000;

    SysTick_Config(tickRate);
}

bool MsgFrameSent_callback(bool State)
{
	return State;
}

void MsgRx_Callback(void* data, uint8_t length)
{
	stLinMsg* Buff = (stLinMsg*)data;
	uint8_t* BuffData = (uint8_t*)data;
	uint8_t BufferIndex = 0U;

	if(length == 1)
	{
		BufferRxFrame.Break = Buff->Break;
		BufferRxFrame.SynchByte = Buff->SynchByte;
		for(BufferIndex = 0U; BufferIndex < length; BufferIndex++)
		{
			BufferRxFrame.Buffer[BufferIndex] = Buff->Buffer[BufferIndex];
		}
	}
	else
	{
		for(BufferIndex = 0U; BufferIndex < length; BufferIndex++)
		{
			BufferRxData[BufferIndex] = BuffData[BufferIndex];
		}
	}


	asm("NOP");
}


/*!
 * @brief Main function
 */
int main(void)
{
    usart_config_t config;

    BOARD_InitHardware();

    SysTick_Init();

    LIN_vInit();

    LIN_vInstallMsgRxCB((lin_msg_callback)&MsgRx_Callback);
    LIN_vInstallMsgFrameCB((lin_msgframe_callback)&MsgFrameSent_callback);

    while(1)
    {
        if(SendMsg == true)
        {
        	SendMsg = false;

        	LIN_vSendMsgFrame(Msgs[Index]);

        	asm("NOP");
        }
    }
}
