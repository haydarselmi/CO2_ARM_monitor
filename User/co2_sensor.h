#ifndef CO2_SENSOR_H
#define CO2_SENSOR_H

#include "lpc17XX.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "globaldecimport.h"
#include <stdlib.h>

void init_co2_sensor(LPC_I2C_TypeDef *);
void measure_read_co2_levels(LPC_I2C_TypeDef *);

void test_sensor_co2_getId(LPC_I2C_TypeDef *);

void soft_reset_co2_sensor(LPC_I2C_TypeDef *);
#endif
