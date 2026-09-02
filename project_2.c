#include<stdio.h>
#include<stdint.h>


// now we need three default for 3 registers so we do declaration 


uint32_t fake_hardware_registers[3]  ; 









// first set the bit 0 of the register direction next make it out 

//func that cheks direction and later checks if output 
void gpio_write(volatile uint32_t *direction_reg,
                 volatile uint32_t *output_reg,
                 int pin,
                 int value)
{

//just check the direction re 


int is_output = (*direction_reg >> pin ) & 1 ;    /// use pin to check ,, 

if (!is_output)
{
  printf(" this direction_reg is not set\n ");

}

// if user reuqeseted for pin =3 and value =1 it means he neee pin 3 to be high , we use this operation & up set the bit after checking the direction register thats it  
if (value) {
        *output_reg |= (1 << pin);      // set the bit
    } else {
        *output_reg &= ~(1 << pin);     // clear the bit
    }


}

int gpio_read(volatile uint32_t *direction_reg,
                 volatile uint32_t *input_reg,
                 int pin)
{ 


int is_input = (*direction_reg >> pin ) & 1 ;    /// use pin to check ,,

if (!is_input)
{
  printf(" this direction_reg is set for read \n ");
  
}
else 
{
  printf(" this direction_reg is not set for read \n");
  return -1 ; 
}
  int pin_status = (*input_reg >> pin) & 1;
  return pin_status;



}


void gpio_toggle ( volatile uint32_t *direction_reg , volatile uint32_t *output_reg  , int pin )
{
  
  // check the direction reg 

  int is_output = (*direction_reg >> pin ) & 1 ;    /// use pin to check ,, 

if (!is_output)
{
  printf(" this direction_reg is not set\n ");

}
else 
{
*output_reg ^= (1 << pin); 
}



}

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

printf("%d\n",pin1_status);




gpio_write( direction_reg, output_reg, 0, 1) ;
printf("output register status after direction check 0x%08X\n",*output_reg) ;   // print the derefence value not address  becuase all 3 register vraibles are pointers 



// valid read: pin 1 is INPUT
    int val = gpio_read(direction_reg, input_reg, 1);
    printf("pin 1 read = %d\n", val);

    // invalid read: pin 0 is OUTPUT, not INPUT
    int bad_val = gpio_read(direction_reg, input_reg, 0);
    printf("pin 0 read = %d\n", bad_val);









    gpio_toggle(direction_reg, output_reg, 0) ; 
printf( "the output_reg sttaus after toggle 0x%08X" ,*output_reg  ); 





    return 0;

}












