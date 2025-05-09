/*
 * LIN.c}
 *
 *  Created on: 6 may. 2025
 *      Author: hecto
 */

#include "fsl_usart.h"
#include "LIN.h"


#define HEADER_BYTES 	(2)


static lin_msg_callback message_callback = NULL;
static lin_msgframe_callback messageFrame_callback = NULL;


const usart_config_t FLEXCOMM0_config = {
  .baudRate_Bps = 19200UL,
  .syncMode = kUSART_SyncModeDisabled,
  .parityMode = kUSART_ParityDisabled,
  .stopBitCount = kUSART_OneStopBit,
  .bitCountPerChar = kUSART_8BitsPerChar,
  .loopback = false,
  .txWatermark = kUSART_TxFifo0,
  .rxWatermark = kUSART_RxFifo1,
  .rxTimeout = {
    .enable = false,
    .resetCounterOnEmpty = true,
    .resetCounterOnReceive = true,
    .counter = 0U,
    .prescaler = 0U
  },
  .enableRx = true,
  .enableTx = true,
  .enableHardwareFlowControl = false,
  .enableMode32k = false,
  .clockPolarity = kUSART_RxSampleOnFallingEdge,
  .enableContinuousSCLK = false,
  .enableLinMode = true
};

void USART_IRQHandler(void)
{
    static bool FlagBreak = false;
    static uint8_t byte = 0U;
	uint8_t data;
    uint8_t buffer[8];

    if((kUSART_BreakDetectChangeFlag) & USART_GetStatusFlags(USART_BASE))
    {
    	FlagBreak = true;
    	USART_ClearStatusFlags(USART_BASE, kUSART_BreakDetectChangeFlag);
    }
    else if((kUSART_RxIdleFlag) & USART_GetStatusFlags(USART_BASE))
	{
		buffer[byte] = USART_ReadByte(USART_BASE);
		byte++;

    	if((FlagBreak)&&(byte == 3))
    	{
    		if(message_callback != NULL)
			{
				message_callback((void*)buffer, (byte-HEADER_BYTES));
			}
    		FlagBreak = false;
    		byte = 0U;
    	}
    	else if(byte == 8)
		{
			if(message_callback != NULL)
			{
				message_callback((void*)buffer, byte);
			}
			byte = 0U;
    	}
	}
    SDK_ISR_EXIT_BARRIER;
}

static uint8_t LIN_s_u8CalculateParity(uint8_t MsgId)
{
	uint8_t HeaderMsgId = 0U;
	bool EvenParity = false;
	bool OddParity = false;

	EvenParity = ((MsgId & 0x20) >> 5) ^ ((MsgId & 0x10) >> 4) ^ ((MsgId & 0x8) >> 3) ^ ((MsgId & 0x2) >> 1);
	OddParity = ((MsgId & 0x10) >> 4) ^ ((MsgId & 0x4) >> 2) ^ ((MsgId & 0x2) >> 1) ^ ((MsgId & 0x1) >> 0);

	HeaderMsgId = (MsgId << 2);
	HeaderMsgId |= (EvenParity << 1);
	HeaderMsgId |= (OddParity << 0);

	return HeaderMsgId;
}

void LIN_vInit(void)
{
	USART_Init(USART_BASE, &FLEXCOMM0_config, USART_CLK_FREQ);

    /* Enable RX interrupt. */
    USART_EnableInterrupts(USART_BASE, kUSART_RxLevelInterruptEnable | kUSART_RxBreakChangeInterruptEnable);
    EnableIRQ(USART_IRQn);
}

void LIN_vTxMsg(uint8_t *data, size_t length)
{
	USART_WriteBlocking(USART_BASE, data, length);
}

void LIN_vSendMsgFrame(uint8_t MsgId)
{
	USART_Type* base = USART_BASE;
	uint8_t DummyChar = 0xFF;
	uint8_t SyncByte = 0x55;
	uint8_t HeaderMsgId = 0U;
	bool State = true;

	HeaderMsgId = LIN_s_u8CalculateParity(MsgId);

	base->CTL |= USART_CTL_TXBRKEN_MASK;

	USART_WriteBlocking(USART0, &DummyChar, 1);

	base->CTL &= ~USART_CTL_TXBRKEN_MASK;

	USART_WriteBlocking(USART0, &SyncByte, 1);

	USART_WriteBlocking(USART0, &HeaderMsgId, 1);

//	USART_EnableInterrupts(USART_BASE, kUSART_TxIdleInterruptEnable);
}

void LIN_vInstallMsgRxCB(lin_msg_callback callback_user)
{
	message_callback = callback_user;
}

void LIN_vInstallMsgFrameCB(lin_msgframe_callback callback_user)
{
	messageFrame_callback = callback_user;
}
