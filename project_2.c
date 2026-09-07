// P2 : leanring 


/* 
✅ MMIO register simulation fundamentals (bit set/clear/read)
✅ #define constants for meaningful bit names
✅ Multiple registers via array + pointers, then upgraded to a struct
✅ volatile — why it matters, and where it needs to be declared
✅ gpio_write()   — direction-checked single-bit write
✅ gpio_read()    — direction-checked single-bit read
✅ gpio_toggle()  — XOR-based bit flip
✅ gpio_get_mode() / gpio_set_mode() — multi-bit field read/write (mask+shift)
✅ Struct-based register grouping (GPIO_TypeDef style, matches real vendor headers)
✅ Pointer-to-struct + -> operator
✅ MMIO-style base-address macro (GPIO → &fake_gpio)
✅ A reactive scenario: reading hardware state and acting on it

*/



#include<stdio.h>
#include<stdint.h>

// important when working this multiple bits ,if this is remmebered remaining all will be fine 
#define MODE_MASK (0x3 << 4 ) 


//p2 : using macros & direct address 
#define GPIO (&fake_gpio)


//   using struct instead of arrayS+ pointers for the regitsers declarition ; 
typedef struct
{
    volatile uint32_t DIRECTION;
    volatile uint32_t INPUT;
    volatile uint32_t OUTPUT;

} GPIO_struct_datatype;

GPIO_struct_datatype fake_gpio = {0}; // intialised the varaibles as zero first 



/*
f you ever had a second GPIO peripheral (fake_gpio2) and tried write_struct(&fake_gpio2, ...), it would silently still modify fake_gpio, not fake_gpio2. That's a real, dangerous bug pattern.

Fix — use gpio_ptr (the parameter) everywhere inside the function, not GPIO:
// keep the *gpio same for the pramters 


*/ 


void write_struct( GPIO_struct_datatype *gpio_ptr , int pin, int value )   
{

int is_output_ = (GPIO -> DIRECTION  >> pin ) & 1 ;    note :  // dont use GPIO here   only for main fun() its useful 

if (!is_output_)
{
printf("the output register is not the output mode " ); 
}

if(value)
{
  // if value is poistive intereger set the bit 
GPIO -> OUTPUT  &= ~(1 << pin);      // clear the bit   
GPIO -> OUTPUT  |= (1 << pin);       //set/write  the bit       

}
else {
        GPIO -> OUTPUT  &= ~(1 << pin);     // clear the bit
    }


}



// read fun()
int read_struct( GPIO_struct_datatype *gpio_ptr , int pin  )

{

// check direction register 



int is_output_ = ( GPIO -> DIRECTION  >> pin  ) & 1U ; 
// 

if(!is_output_) 
{
  printf("the direction register is in the input mode " ); 
}

else 

{

GPIO -> DIRECTION |= (0 << pin); 

printf("as it is not in input mode , i have added it to that mode \n ");

}




int pin_status = (GPIO -> INPUT >> pin  ) & 1 ; 

if( !pin_status )
{
return pin_status; 
}
else
 {
return -1 ; 
}




}




//3. toggle is also same > 


void toggle_struct (  GPIO_struct_datatype *gpio_ptr , int pin  )

{

int is_output_ = (GPIO -> DIRECTION  >> pin ) & 1 ;  

if (!is_output_)
{
printf("the direction register is not the output mode " ); 
GPIO -> DIRECTION |= (1 << pin); 
printf("as it is not in output mode , i have added it to that mode \n ");
}


GPIO -> OUTPUT  ^=(1U << pin);       //toggle the bit 


}



// 4, NOW mode bits usage , multiple bits 

int gpio_get_mode(GPIO_struct_datatype *gpio);

void gpio_set_mode(GPIO_struct_datatype *gpio, int new_mode);




// main function 
int main()
{
  
// here lets use the final real -world scenaroi 
/*
1. Configure pin 0 as OUTPUT (the "LED")
2. Configure pin 1 as INPUT (the "button")
3. Simulate the button being pressed (set the INPUT bit high)
4. Use gpio_read() to check the button's state
5. If it's HIGH, call gpio_toggle() on the LED (pin 0)
6. Print the LED's state before and after the toggle, so you can see it actually flipped
*/ 

int pin0 = 0 ; 
int pin1 = 1 ; 
int value  = 1 ; 

printf("\n the current status of direction reg  0x%08X",GPIO -> DIRECTION); 
GPIO -> DIRECTION |= ( 1 <<pin0 );
printf("\n the current status of direction reg  0x%08X",GPIO -> DIRECTION); 


GPIO -> INPUT |= ( 1 <<pin1 );   // like button pressed  

printf("\n the LED is before toggle 0x%08X",GPIO->OUTPUT) ; 
if(read_struct(GPIO , pin1) )         // input button state 
{
  toggle_struct(GPIO , pin0);      

}
printf("\nthe LED is after toggle 0x%08X",GPIO->OUTPUT) ; 






  return 0;
}














