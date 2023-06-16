#ifndef BLUETOOTH_H
#define BLUETOOTH_H

// EN-TETE : BLUETOOTH

void UART0_Init(void);
void bluetoothPinConfig(void);
void sendData(char data[], int l);
void confirmConnection(void);
void waitForRequest(void);
void emptyReceivedBuffer(void);

#endif

