/*
 * LIN.h
 *
 *  Created on: 6 may. 2025
 *      Author: hecto
 */

#ifndef LIN_H_
#define LIN_H_


#define USART_BASE            USART0
#define USART_CLK_SRC    	  kCLOCK_Flexcomm0
#define USART_CLK_FREQ   	  CLOCK_GetFlexCommClkFreq(0U)
#define USART_IRQHandler 	  FLEXCOMM0_IRQHandler
#define USART_IRQn       	  FLEXCOMM0_IRQn

#define MSG_IDS 			{0x7, 0xB, 0xF}
#define TOTAL_MSGS			(3)


typedef void (*lin_msg_callback)(void*, uint8_t);
typedef bool (*lin_msgframe_callback)(bool);

typedef struct
{
	uint8_t Break;
	uint8_t SynchByte;
	uint8_t Buffer[8];
}stLinMsg;

extern void LIN_vInit(void);
extern void LIN_vTxMsg(uint8_t *data, size_t length);
extern void LIN_vSendMsgFrame(uint8_t MsgId);
extern void LIN_vInstallMsgRxCB(lin_msg_callback callback_user);
extern void LIN_vInstallMsgFrameCB(lin_msgframe_callback callback_user);

#endif /* LIN_H_ */
