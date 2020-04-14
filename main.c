#include <atmel_start.h>
#include <atomic.h>
#include <util/delay.h>



int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
		
	
	uint8_t writeI2C(uint8_t slave_addr, uint8_t dat1, uint8_t dat2, uint8_t slave_reg)
	{
		
		uint8_t timeout = 0;
				
				
		TWI0.MSTATUS |= (TWI_RIF_bm | TWI_WIF_bm);
		
		if((TWI0.MSTATUS & 0x01 == 0x01) || (TWI0.MSTATUS & 0x02 == 0x02))
		{
			TWI0.MADDR = slave_addr;			
			
			while(!(TWI0.MSTATUS & TWI_CLKHOLD_bm))
			{
				_delay_ms(10);
				if(timeout > 100) return 1;
				timeout++;				
			}
			
			
			TWI0.MDATA = slave_reg;
			
			timeout = 0;
			while(!(TWI0.MSTATUS & TWI_CLKHOLD_bm))
			{				
				_delay_ms(10);
				if(timeout > 100) return 2;
				timeout++;				
			}
			
			
			TWI0.MDATA = dat1;
			
			timeout = 0;
			while(!(TWI0.MSTATUS & TWI_CLKHOLD_bm))
			{					
				_delay_ms(10);
				if(timeout > 100) return 3;
				timeout++;				
			}
			
			
			TWI0.MDATA = dat2;
			
			timeout = 0;
			while(!(TWI0.MSTATUS & TWI_CLKHOLD_bm))
			{				
				_delay_ms(10);
				if(timeout > 100) return 4;
				timeout++;				
			}
			
						
			I2C_stop();
			return 0;
		}else return 5;
		
		
	}
	
	while (1) 
	{			
		int i;
		
		for (i=0; i < 1024; i++)
		{			
			writeI2C(0x90, i>>2, i<<6, 0x00);
			_delay_ms(500);				
		}
			
		
	}	
	
}


