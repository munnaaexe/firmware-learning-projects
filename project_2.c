#include<stdio.h>
#include<stdint.h>

#define MODE_MASK (0x3 << 4 ) 
// now we need three default for 3 registers so we do declaration 


uint32_t fake_hardware_registers[3]  ; 


//   using struct instead of arrayS+ pointers for the regitsers declarition ; 
typedef struct
{
    volatile uint32_t DIRECTION;
    volatile uint32_t INPUT;
    volatile uint32_t OUTPUT;

} GPIO_struct_datatype;

GPIO_struct_datatype fake_gpio = {0}; // intialised the varaibles as zero first 




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








// mode bits usage now : upto now we checked for only 1 bit : 

int gpio_get_mode( volatile uint32_t *direction_reg)

{

  //wrong precedence ex: int mode = *CONTROL_REG & (MODE_MASK >> 4) ;

  int mode  = (*direction_reg & MODE_MASK ) >> 4 ;
  return mode ;  

}

void gpio_set_mode(volatile uint32_t *direction_reg,  int new_mode )
{
 // for writing we have to clear the two bits 4,5 first next we have to write it 

 *direction_reg =  (*direction_reg &  ~MODE_MASK)  |  (new_mode << 4) ; // using this we can clear the bits  | setting the nw mode to the register 

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



printf(" \n dreiction register sttaus currntly 0x%08X" , *direction_reg); 




// setting the register_mode 

int new_mode = 3 ;
gpio_set_mode(direction_reg,new_mode );

// reaing the register mode 

int dir_reg_status = gpio_get_mode(direction_reg); 
printf("\n the new status of direction_reg for 4,5 bits   0x%08X",dir_reg_status); 

printf(" \n dreiction register after mode  sttaus currntly 0x%08X" , *direction_reg);




// here , we see the struct accesss 


// Set pin 0 as OUTPUT
    fake_gpio.DIRECTION |= (1U << 0);
    printf("DIRECTION after setting pin 0: 0x%08X\n",
           fake_gpio.DIRECTION);

    // Set OUTPUT pin 0 HIGH
    fake_gpio.OUTPUT |= (1U << 0);
    printf("OUTPUT after setting pin 0:    0x%08X\n",
           fake_gpio.OUTPUT);

    // Set pin 1 as INPUT
    fake_gpio.DIRECTION &= ~(1U << 1);
    printf("DIRECTION after clearing pin 1: 0x%08X\n",
           fake_gpio.DIRECTION);

     // Simulate hardware making INPUT pin 1 HIGH
    fake_gpio.INPUT |= (1U << 1);
    printf("INPUT after hardware sets pin 1: 0x%08X\n",
           fake_gpio.INPUT);

    // Read pin 1
    int pin1_status_new = (fake_gpio.INPUT >> 1) & 1U;

    printf("Pin 1 input status: %d\n", pin1_status_new);


    return 0;



}














