////===========================================================//
//// But: Init UART0 pour module bluetooth HC-05
////===========================================================//


#include "lpc17xx_uart.h"
#include "lpc17xx_gpio.h"
#include "globaldecimport.h"
#include "bluetoothCommands.h"


void UART0_Init(void){
	
	/* Structures de Config */
	UART_CFG_Type UART_Config_Structure;
	UART_FIFO_CFG_Type FIFO_Config_Structure;
	
	/* Config UART0 */
	UART_Config_Structure.Baud_rate = 38400;
	UART_Config_Structure.Parity = UART_PARITY_NONE;
	UART_Config_Structure.Databits = UART_DATABIT_8;
	UART_Config_Structure.Stopbits = UART_STOPBIT_1;
	
	/* Config FIFO UART0 */
	FIFO_Config_Structure.FIFO_ResetRxBuf = DISABLE;
	FIFO_Config_Structure.FIFO_ResetTxBuf = DISABLE;
	FIFO_Config_Structure.FIFO_DMAMode = DISABLE;
	FIFO_Config_Structure.FIFO_Level = UART_FIFO_TRGLEV2;
	
	/* Init UART0 */
	UART_Init(LPC_UART0, &UART_Config_Structure);

	/* Interruption sur RBR pour la rception de donnes */
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);
		
	/* Autoriser l'envoi de donnes */
	UART_TxCmd(LPC_UART0, ENABLE);

	/* Init Fifo*/
	UART_FIFOConfig(LPC_UART0, &FIFO_Config_Structure);
	
	// Autoriser les interruption provenant de UART0
	NVIC->ISER[0] |= (1<<5);
}

/**
	* @brief Procedure sendData to send information via UART0
	* @param[in] data The buffer. It contains the information to send
	* @param[in] l The size of the buffer data
*/
void sendData(char data[], int lenght) {
	if (data[0] != '\n'){
		UART_Send(LPC_UART0, (uint8_t *)data, lenght, NONE_BLOCKING);
	}
}

/**
	* @brief Notifier à l'utilisateur qu'il peut envoyer une commande via le terminal bluetooth
*/
void waitForRequest(){
	sendData("request : ", 10);
}

/**
	* @brief Envoyer un message de confirmation de conection via le terminal bluetooth
*/
void confirmConnection(){
	sendData("Device is ready\n", 16);
}


