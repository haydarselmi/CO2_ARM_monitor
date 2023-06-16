#include "co2_sensor.h"

/**
 * @brief Intialise le capteur CO2 SGP30 à l'adresse 0x58 du bus I2C
 * par une commande d'initialisation Init_air_quality qui va renvoyer pendant 15s 
 * la valeur de CO2.
 *
 * @param le bus I2C sur lequel est branché le capteur CO2 SGP30.
 */
void init_co2_sensor(LPC_I2C_TypeDef *i2c_bus) {
	// Allocation et initialisation du buffer d'écriture pour une commande
	// au capteur de Init air quality
	I2C_master_write_buffer[0] = 0x3;
	I2C_master_write_buffer[1] = 0x20;
	
	// configuration de la structure afin d'initialiser le capteur CO2 SGP30
	I2C_M_init_cfg.sl_addr7bit = 0x58;
	
	I2C_M_init_cfg.tx_data = I2C_master_write_buffer;
	I2C_M_init_cfg.tx_length = 2;
	I2C_M_init_cfg.tx_count = 0
	;
	
	I2C_M_init_cfg.rx_data = NULL;
	I2C_M_init_cfg.rx_data = 0;
	I2C_M_init_cfg.rx_count = 0;
	
	I2C_M_init_cfg.retransmissions_max = 10;
	I2C_M_init_cfg.retransmissions_count = 0;
	I2C_M_init_cfg.status = 0;
	I2C_M_init_cfg.callback = NULL;
	
	I2C_MasterTransferData(i2c_bus, &I2C_M_init_cfg, I2C_TRANSFER_POLLING);
}

/**
 * @brief Va demander par l'intérmediaire du bus I2C au capteur CO2 SGP30
 * de lire la qualité de l'air, puis après réception des données de l'esclave
 * elle va venir modifier le buffer I2C_master_read_buffer qui contient un tableau
 * de 2 uint8_t ou le premier tableau contient la valeur du taux de CO2 en ppm
 * (particules par million).
 *
 * @param le bus I2C sur lequel est branché le capteur CO2 SGP30.
 */
void measure_read_co2_levels(LPC_I2C_TypeDef *i2c_bus) {
	I2C_master_write_buffer[1] = 0x8;
	I2C_master_write_buffer[0] = 0x20;
	
	// configuration de la structure afin d'initialiser le capteur CO2 SGP30
	I2C_M_init_cfg.sl_addr7bit = 0x58;
	
	I2C_M_init_cfg.tx_data = I2C_master_write_buffer;
	I2C_M_init_cfg.tx_length = 2;
	I2C_M_init_cfg.tx_count = 0;
	
	I2C_M_init_cfg.rx_data = NULL;
	I2C_M_init_cfg.rx_length = 0;
	I2C_M_init_cfg.rx_count = 0;
	
	I2C_M_init_cfg.retransmissions_max = 5;
	I2C_M_init_cfg.retransmissions_count = 0;
	I2C_M_init_cfg.status = 0;
	I2C_M_init_cfg.callback = NULL;
	
	I2C_MasterTransferData(i2c_bus, &I2C_M_init_cfg, I2C_TRANSFER_POLLING);
	LPC_TIM2->TC = 0;
	while(LPC_TIM2->TC < 14) {}
		
	I2C_M_init_cfg.sl_addr7bit = 0x58;
	I2C_M_init_cfg.tx_data = NULL;
	I2C_M_init_cfg.tx_length = 0;
	I2C_M_init_cfg.tx_count = 0;
	I2C_M_init_cfg.rx_data = I2C_master_read_buffer;
	I2C_M_init_cfg.rx_length = 6;
	I2C_M_init_cfg.rx_count = 0;
	I2C_M_init_cfg.retransmissions_max = 5;
	I2C_M_init_cfg.retransmissions_count = 0;
	I2C_M_init_cfg.status = 0;
	I2C_M_init_cfg.callback = NULL;
	
	I2C_MasterTransferData(i2c_bus, &I2C_M_init_cfg, I2C_TRANSFER_POLLING);	
}

void test_sensor_co2_getId(LPC_I2C_TypeDef *i2c_bus) {
	I2C_master_write_buffer[1] = 0x82;
	I2C_master_write_buffer[0] = 0x36;
	
	// configuration de la structure afin d'initialiser le capteur CO2 SGP30
	I2C_M_init_cfg.sl_addr7bit = 0x58;
	
	I2C_M_init_cfg.tx_data = I2C_master_write_buffer;
	I2C_M_init_cfg.tx_length = 2;
	I2C_M_init_cfg.tx_count = 0;
	
	I2C_M_init_cfg.rx_data = NULL;
	I2C_M_init_cfg.rx_length = 0;
	I2C_M_init_cfg.rx_count = 0;
	
	I2C_M_init_cfg.retransmissions_max = 1;
	I2C_M_init_cfg.retransmissions_count = 0;
	I2C_M_init_cfg.status = 0;
	I2C_M_init_cfg.callback = NULL;
	
	I2C_MasterTransferData(i2c_bus, &I2C_M_init_cfg, I2C_TRANSFER_POLLING);
	LPC_TIM2->TC = 0;	
	while(LPC_TIM2->TC < 9) {}
	
	// configuration de la structure afin d'initialiser le capteur CO2 SGP30
	I2C_M_init_cfg.sl_addr7bit = 0x58;
	
	I2C_M_init_cfg.tx_data = NULL;
	I2C_M_init_cfg.tx_length = 0;
	I2C_M_init_cfg.tx_count = 0;
	
	I2C_M_init_cfg.rx_data = I2C_master_read_buffer;
	I2C_M_init_cfg.rx_length = 6;
	I2C_M_init_cfg.rx_count = 0;
	
	I2C_M_init_cfg.retransmissions_max = 1;
	I2C_M_init_cfg.retransmissions_count = 0;
	I2C_M_init_cfg.status = 0;
	I2C_M_init_cfg.callback = NULL;
	I2C_MasterTransferData(i2c_bus, &I2C_M_init_cfg, I2C_TRANSFER_POLLING);
}

void soft_reset_co2_sensor(LPC_I2C_TypeDef *i2c_bus) {
	I2C_master_write_buffer[0] = 0x6;
	I2C_master_write_buffer[1] = 0x6;
	
	// configuration de la structure afin d'initialiser le capteur CO2 SGP30
	I2C_M_init_cfg.sl_addr7bit = 0x0;
	
	I2C_M_init_cfg.tx_data = I2C_master_write_buffer;
	I2C_M_init_cfg.tx_length = 1;
	I2C_M_init_cfg.tx_count = 0;
	
	I2C_M_init_cfg.rx_data = NULL;
	I2C_M_init_cfg.rx_length = 0;
	I2C_M_init_cfg.rx_count = 0;
	
	I2C_M_init_cfg.retransmissions_max = 10;
	I2C_M_init_cfg.retransmissions_count = 0;
	I2C_M_init_cfg.status = 0;
	I2C_M_init_cfg.callback = NULL;
	
	I2C_MasterTransferData(i2c_bus, &I2C_M_init_cfg, I2C_TRANSFER_POLLING);
}
