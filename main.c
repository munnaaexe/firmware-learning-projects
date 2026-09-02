#include <stdio.h>
#include <stdint.h>


    #define ENABLE_BIT            (1 << 0)
    #define RESET_BIT             (1 << 1)
    #define INTERRUPT_ENABLE_BIT  (1 << 2)
    #define POWER_ENABLE_BIT      (1 << 3)
    #define SOME_THING            (1 << 4 )
    

void set_bit (uint32_t *reg , uint32_t bit)      // void becoz no return direct modify // pointer becuase direct modify needed 
{

    *reg |= (1 << bit );

}

void clear_bit(uint32_t *reg, uint32_t bit)
{
    *reg &= ~(1 << bit);
}

void read_bit(uint32_t reg , uint32_t bit )
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

    uint32_t CONTROL_REG = 0;
    printf(" BEFORE CONTROL_REG = 0x%08X\n", CONTROL_REG);
    //CONTROL_REG = CONTROL_REG | (1  >> 0) ; 

    CONTROL_REG |= ENABLE_BIT ; 
    printf(" AFTER1 CONTROL_REG = 0x%08X\n", CONTROL_REG);
   

    
    CONTROL_REG |= RESET_BIT ;  
    printf(" AFTER2 CONTROL_REG = 0x%08X\n", CONTROL_REG);
     

    // the previous state of the register does matter  in reg value 
    CONTROL_REG |= SOME_THING ;  
    printf(" AFTER3 CONTROL_REG = 0x%08X\n", CONTROL_REG);
    

    CONTROL_REG  |= ENABLE_BIT ; 
    printf(" set the bit 0 enable  CONTROL_REG = 0x%08X\n", CONTROL_REG);

    //CONTROL_REG  & ENABLE_BIT ;   // when no need of modification just checking no need of opration applying to reg value 
    //printf(" checking the bit 0  CONTROL_REG = 0x%08X\n", CONTROL_REG);
    // my clear mistake is checking but printing the checked value but printed register current value  

    //printf("checking bit 0 = 0x%08X\n", CONTROL_REG & ENABLE_BIT);  > ok to use 

    if (CONTROL_REG & ENABLE_BIT)
{
    printf("ENABLE bit is SET\n");
}
else
{
    printf("ENABLE bit is CLEAR\n");
}
  


    CONTROL_REG  &= ~ENABLE_BIT ; 
    printf(" clearing the bit 0  CONTROL_REG = 0x%08X\n", CONTROL_REG);




    set_bit(&CONTROL_REG,0);
    printf(" set bit0 using function again CONTROL_REG = 0x%08X\n", CONTROL_REG);

   

    clear_bit(&CONTROL_REG , 0 );
    printf("clear  bit0 using function again CONTROL_REG = 0x%08X\n", CONTROL_REG);
    


    read_bit(CONTROL_REG , 0); 



    return 0;

}



