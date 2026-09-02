#include <stdio.h>
#include <stdint.h>




// Simulated "hardware" - in real firmware, this array wouldn't exist;
// instead you'd point directly at a fixed physical address like 0xFED81500


uint32_t FAKE_HARDWARE_REGISTER[4] ; // automatically the array values are intialised as zero 
    #define ENABLE_BIT            (1 << 0)        // giving nameing to the bits 
    #define RESET_BIT             (1 << 1)
    #define INTERRUPT_ENABLE_BIT  (1 << 2)
    #define POWER_ENABLE_BIT      (1 << 3)
    #define SOME_THING            (1 << 4 )
    

void set_bit (uint32_t *reg , uint32_t bit)      // void becoz no return direct modify // pointer becuase direct modify needed 
{

    *reg |= (1 << bit );

}

void clear_bit(uint32_t *reg, uint32_t bit)        // argumnets which takes the register address and modify it , so we taken args as a pointer 
{
    *reg &= ~(1 << bit);
}

void read_bit(uint32_t reg , uint32_t bit )       // no need to mdofiy so taken as normal varibale 
{
    if( reg & (1 << bit)) 
    {
        printf("set ") ;
    }
    else 
    {
        printf("not set ") ;
    }

}


int main()
{

    volatile uint32_t *CONTROL_REG = &FAKE_HARDWARE_REGISTER[0];  
    // pointer to the first element of the array     // volatile + datatype + pointer varible = which take 1st elment as a value // same as cmtrl reg = 0 ; // just pointer uasge 


    


    printf(" BEFORE CONTROL_REG = 0x%08X\n", *CONTROL_REG);      // instead of CONTROL_REG we can use *CONTROL_REG to get the value of the register
    //CONTROL_REG = CONTROL_REG | (1  >> 0) ; 

    *CONTROL_REG |= ENABLE_BIT ; 
    printf(" AFTER1 CONTROL_REG = 0x%08X\n", *CONTROL_REG);
   

    
    *CONTROL_REG |= RESET_BIT ;  
    printf(" AFTER2 CONTROL_REG = 0x%08X\n", *CONTROL_REG);
     

    // the previous state of the register does matter  in reg value 
    *CONTROL_REG |= SOME_THING ;  
    printf(" AFTER3 CONTROL_REG = 0x%08X\n", *CONTROL_REG);
    

    *CONTROL_REG  |= ENABLE_BIT ; 
    printf(" set the bit 0 enable  CONTROL_REG = 0x%08X\n", *CONTROL_REG);

    //CONTROL_REG  & ENABLE_BIT ;   // when no need of modification just checking no need of opration applying to reg value 
    //printf(" checking the bit 0  CONTROL_REG = 0x%08X\n", CONTROL_REG);
    // my clear mistake is checking but printing the checked value but printed register current value  

    //printf("checking bit 0 = 0x%08X\n", CONTROL_REG & ENABLE_BIT);  > ok to use 

    if (*CONTROL_REG & ENABLE_BIT)  
{
    printf("ENABLE bit is SET\n");
}
else
{
    printf("ENABLE bit is CLEAR\n");
}
  


    *CONTROL_REG  &= ~ENABLE_BIT ; 
    printf(" clearing the bit 0  CONTROL_REG = 0x%08X\n", *CONTROL_REG);


// using same above functions with the help of functions 


    set_bit( (uint32_t*)CONTROL_REG,0);
    printf(" set bit0 using function again CONTROL_REG = 0x%08X\n", *CONTROL_REG);

   

    clear_bit((uint32_t *)CONTROL_REG , 0 );
    printf("clear  bit0 using function again CONTROL_REG = 0x%08X\n", *CONTROL_REG);
    


    read_bit(*CONTROL_REG , 0); 






    return 0;

}



