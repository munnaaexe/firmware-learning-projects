#include<stdio.h>
#include<stdint.h>


// now we need three default for 3 registers so we do declaration 


uint32_t fake_hardware_registers[3]  ; 



// first set the bit 0 of the register direction next make it out 

int main()
{
volatile uint32_t *direction_reg = &fake_hardware_registers[0];
volatile  uint32_t *input_reg = &fake_hardware_registers[1];
volatile uint32_t *output_reg = &fake_hardware_registers[2] ; 




//set dir bit 0 to 1 
*direction_reg |= (1 << 0 ) ;   // set as output done
*output_reg |= (1 <<0) ; 
printf("the sattus after setting thereg =  0x%08X\n ", *output_reg ); 



// set the sirection for bit 1 to 0 

*direction_reg &= ~(1 << 1 ) ; // by defualt its like this only 0  buy 
*input_reg |= ( 1 << 1  ) ;       // actaully this hsould be a hw input but here we are giving it manually EX: suddnetly someone poweron the switch 


int pin1_status = (*input_reg >>1 ) &1 ;          // shift right the so bit come at end ppston and do & opertaion 

printf("%d",pin1_status);
return 0 ; 
}












