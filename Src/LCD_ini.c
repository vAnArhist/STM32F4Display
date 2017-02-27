#include "LCD_ini.h"

void LCD_write_reg(uint16_t reg,uint16_t dat){
	CMD_ADR = reg;
	DAT_ADR = dat;
}

void LCD_write_dat(uint16_t dat){
	DAT_ADR = dat;
}

void LCD_dat_ready(void){
	CMD_ADR = ILI9325_DATA_REG;
}

uint16_t Lcd_Read_Data()
{
	uint16_t data = * (uint16_t *)(DAT_ADR);
	return data;	
}

void LCD_Clear(uint16_t color){
	uint32_t i;
	LCD_dat_ready();
	for (i=0;i<76800;i++){
		DAT_ADR = color;
	}
}

//Инициализация
void LCD_ini(void){
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6, GPIO_PIN_SET);
	
        LCD_write_reg(0x00e7,0x0010);      
        LCD_write_reg(0x0000,0x0001);  	/* start internal osc */
	LCD_write_reg(0x0001,0x0100);     
	LCD_write_reg(0x0002,0x0700); 	/* power on sequence */
        LCD_write_reg(0x0003,(1<<12)|(1<<5)|(1<<4)|(0<<3) ); 	/* importance Entry Mode*/
	LCD_write_reg(0x0004,0x0000);                                   
	LCD_write_reg(0x0008,0x0207);	           
	LCD_write_reg(0x0009,0x0000);         
	LCD_write_reg(0x000a,0x0000); 	/* display setting */        
	LCD_write_reg(0x000c,0x0001);	/* display setting */        
	LCD_write_reg(0x000d,0x0000); 			        
	LCD_write_reg(0x000f,0x0000);
	/* Power On sequence */
	LCD_write_reg(0x0010,0x0000);   
	LCD_write_reg(0x0011,0x0007);
	LCD_write_reg(0x0012,0x0000);                                                                 
	LCD_write_reg(0x0013,0x0000);                 
	HAL_Delay(50);  /* delay 50 ms */		
	LCD_write_reg(0x0010,0x1590);   
	LCD_write_reg(0x0011,0x0227);
	HAL_Delay(50);  /* delay 50 ms */		
	LCD_write_reg(0x0012,0x009c);                  
	HAL_Delay(50);  /* delay 50 ms */		
	LCD_write_reg(0x0013,0x1900);   
	LCD_write_reg(0x0029,0x0023);
	LCD_write_reg(0x002b,0x000e);
	HAL_Delay(50);  /* delay 50 ms */		
	LCD_write_reg(0x0020,0x0000);                                                            
	LCD_write_reg(0x0021,0x0000);           
	HAL_Delay(50);  /* delay 50 ms */		
	LCD_write_reg(0x0030,0x0007); 
	LCD_write_reg(0x0031,0x0707);   
	LCD_write_reg(0x0032,0x0006);
	LCD_write_reg(0x0035,0x0704);
	LCD_write_reg(0x0036,0x1f04); 
	LCD_write_reg(0x0037,0x0004);
	LCD_write_reg(0x0038,0x0000);        
	LCD_write_reg(0x0039,0x0706);     
	LCD_write_reg(0x003c,0x0701);
	LCD_write_reg(0x003d,0x000f);
	HAL_Delay(50);  /* delay 50 ms */		
	LCD_write_reg(0x0050,0x0000);        
	LCD_write_reg(0x0051,0x00ef);   
	LCD_write_reg(0x0052,0x0000);     
	LCD_write_reg(0x0053,0x013f);
	LCD_write_reg(0x0060,0xa700);        
	LCD_write_reg(0x0061,0x0001); 
	LCD_write_reg(0x006a,0x0000);
	LCD_write_reg(0x0080,0x0000);
	LCD_write_reg(0x0081,0x0000);
	LCD_write_reg(0x0082,0x0000);
	LCD_write_reg(0x0083,0x0000);
	LCD_write_reg(0x0084,0x0000);
	LCD_write_reg(0x0085,0x0000);
		  
	LCD_write_reg(0x0090,0x0010);     
	LCD_write_reg(0x0092,0x0000);  
	LCD_write_reg(0x0093,0x0003);
	LCD_write_reg(0x0095,0x0110);
	LCD_write_reg(0x0097,0x0000);        
	LCD_write_reg(0x0098,0x0000);  
	/* display on sequence */    
	LCD_write_reg(0x0007,0x0133);
		
	LCD_write_reg(0x0020,0x0000);
	LCD_write_reg(0x0021,0x0000);
        
//            //************* Start Initial Sequence **********// 
//LCD_write_reg(0x00E3,  0x3008);      //  Set  internal  timing  
//LCD_write_reg(0x00E7,  0x0012);      //  Set  internal  timing  
//LCD_write_reg(0x00EF,  0x1231);      //  Set  internal  timing  
//        LCD_write_reg(0x0001,  0x0100);         //  set  SS  and  SM  bit  
//        LCD_write_reg(0x0002,  0x0700);         //  set  1  line  inversion  
//        LCD_write_reg(0x0003,  0x1030);         //  set  GRAM  write  direction  and  BGR=1.    
//        LCD_write_reg(0x0004,  0x0000);         //  Resize  register  
//        LCD_write_reg(0x0008, 0x0207);        // set the back porch and front porch 
//        LCD_write_reg(0x0009,  0x0000);         //  set  non-display  area  refresh  cycle  ISC[3:0]  
//        LCD_write_reg(0x000A,  0x0000);        //  FMARK  function  
//        LCD_write_reg(0x000C,  0x0000);        //  RGB  interface  setting  
//        LCD_write_reg(0x000D,  0x0000);        //  Frame  marker  Position  
//        LCD_write_reg(0x000F,  0x0000);          //  RGB  interface  polarity  
//    //*************Power  On  sequence  ****************//  
//        LCD_write_reg(0x0010,  0x0000);            //  SAP,  BT[3:0],  AP,  DSTB,  SLP,  STB  
//        LCD_write_reg(0x0011,  0x0007);            //  DC1[2:0],  DC0[2:0],  VC[2:0]  
//        LCD_write_reg(0x0012,  0x0000);            //  VREG1OUT  voltage  
//        LCD_write_reg(0x0013,  0x0000);            //  VDV[4:0]  for  VCOM  amplitude  
//        HAL_Delay(200);                            //  Dis-charge  capacitor  power  voltage  
//        LCD_write_reg(0x0010,  0x1290);            //  SAP,  BT[3:0],  AP,  DSTB,  SLP,  STB  
//        LCD_write_reg(0x0011,  0x0227);            //  DC1[2:0],  DC0[2:0],  VC[2:0]  
//      HAL_Delay(50);  
//                    // Delay 50ms   
//        LCD_write_reg(0x0012,  0x0019);            //  Internal  reference  voltage=  Vci;  
//      HAL_Delay(50);  
//                    // Delay 50ms 
//        LCD_write_reg(0x0013,  0x1D00);            //  Set  VDV[4:0]  for  VCOM  amplitude  
//        LCD_write_reg(0x0029,  0x0028);            //  Set  VCM[5:0]  for  VCOMH  
//        LCD_write_reg(0x002B,  0x000C);            //  Set  Frame  Rate    
//      HAL_Delay(50);                              // Delay 50ms 
//        LCD_write_reg(0x0020,  0x0000);            //  GRAM  horizontal  Address  
//        LCD_write_reg(0x0021,  0x0000);            //  GRAM  Vertical  Address    
//    // ----------- Adjust the Gamma    Curve ----------// 
//        LCD_write_reg(0x0030,  0x0000);  
//        LCD_write_reg(0x0031,  0x0603);  
//        LCD_write_reg(0x0032,  0x0206);  
//        LCD_write_reg(0x0035,  0x0206);  
//        LCD_write_reg(0x0036,  0x0004);  
//        LCD_write_reg(0x0037,  0x0105);  
//        LCD_write_reg(0x0038,  0x0401);  
//        LCD_write_reg(0x0039,  0x0707);  
//        LCD_write_reg(0x003C,  0x0602);  
//        LCD_write_reg(0x003D,  0x0004);  
//    //------------------ Set GRAM area ---------------// 
//        LCD_write_reg(0x0050,  0x0000);           //  Horizontal  GRAM  Start  Address  
//        LCD_write_reg(0x0051,  0x00EF);          //  Horizontal  GRAM  End  Address  
//        LCD_write_reg(0x0052,  0x0000);           //  Vertical  GRAM  Start  Address  
//        LCD_write_reg(0x0053,  0x013F);          //  Vertical  GRAM  Start  Address  
//        LCD_write_reg(0x0060,  0xA700);          //  Gate  Scan  Line  
//                LCD_write_reg(0x0061,  0x0001);           //  NDL,VLE,  REV  
//        LCD_write_reg(0x006A,  0x0000);          //  set  scrolling  line  
//    //-------------- Partial Display Control ---------// 
//        LCD_write_reg(0x0080,  0x0000);  
//        LCD_write_reg(0x0081,  0x0000);  
//        LCD_write_reg(0x0082,  0x0000);  
//        LCD_write_reg(0x0083,  0x0000);  
//        LCD_write_reg(0x0084,  0x0000);  
//        LCD_write_reg(0x0085,  0x0000);  
//    //-------------- Panel Control -------------------// 
//        LCD_write_reg(0x0090,  0x0010);  
//        LCD_write_reg(0x0092,  0x0600);  
//        LCD_write_reg(0x0007,  0x0133);           //  262K  color  and  display  ON  
} 

