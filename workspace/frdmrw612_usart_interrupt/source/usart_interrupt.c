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
#include "LIN.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static stLinMsg BufferRxFrame = {0U};
static uint8_t BufferRxData[16] = {0U};

static bool Header_flag = false;
static bool Data_flag = false;
static stResponseData Msgs[TOTAL_MSGS_RX_RESP] = MSG_RESPONSE_TABLE;
static uint8_t Msgs_Storage[TOTAL_MSGS_RX_STORE] = MSG_STORAGE_TABLE;
static bool Found_Flag = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
void MsgRx_Callback(void* data, uint8_t length)
{
	stLinMsg* Buff = (stLinMsg*)data;
	uint8_t* BuffData = (uint8_t*)data;
	uint8_t BufferIndex = 0U;

	if(length == 1)
	{
		BufferRxFrame.Break = Buff->Break;
		BufferRxFrame.SynchByte = Buff->SynchByte;
		BufferRxFrame.IDMsg = Buff->IDMsg;

		Header_flag = true;
	}
	else
	{
		for(BufferIndex = 0U; BufferIndex < length; BufferIndex++)
		{
			BufferRxData[BufferIndex] = BuffData[BufferIndex];
		}

		Data_flag = true;
	}
}

/*!
 * @brief Main function
 */
int main(void)
{
	uint8_t MsgId = 0U;
	uint8_t CheckSum_State = 0U;

    BOARD_InitHardware();
    LIN_vInit();

    LIN_vInstallMsgRxCB((lin_msg_callback)&MsgRx_Callback);
    while(1)
    {
    	if(Header_flag)
    	{
    		Header_flag = false;
    		MsgId = LIN_u8GetMsgId(BufferRxFrame.IDMsg);

    		for(uint8_t u8i = 0; u8i < TOTAL_MSGS_RX_STORE; u8i++)
    		{
    			if(MsgId == Msgs_Storage[u8i])
				{
					Found_Flag = true;
					break;
				}
    		}

    		if(Found_Flag == false)
    		{
    			for(uint8_t u8i = 0; u8i < TOTAL_MSGS_RX_RESP; u8i++)
				{
					if(MsgId == Msgs[u8i].Id)
					{
						PRINTF("Respuesta enviada: %s\r\n", Msgs[u8i].Response);
						LIN_vTxMsg(Msgs[u8i].Response, sizeof(Msgs[u8i].Response));
						break;
					}
				}
    			Data_flag = false;
    		}
    	}
    	else if((Found_Flag)&&(Data_flag))
		{
	       	Data_flag = false;
	       	Found_Flag = false;

			CheckSum_State = LIN_u8Checksum(BufferRxData, 8);

			if(CheckSum_State)
			{
				PRINTF("Respuesta recibida: %s \r\n", BufferRxData);
			}
		}
    }
}
