/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define FOSC 7.3728e6 // 7.3728 MHz crystal in XTL mode 
#define PLL 8.0 // 8x PLL
#define FCY ((FOSC * PLL) / (4.0)) // Instruction cycle frequency 
#define TCY (1e9 / FCY) // Instruction cycle period (in nanoseconds)
#define MILLISECOND (FCY / 1.0e3) // 1 millisecond delay constant
#define MICROSECOND (FCY / 1.0e6) // 1 microsecond delay constant
#define NANOSECOND  (FCY / 1.0e9) // 1 nanosecond delay constant

#define OUTPUT_PIN 0

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
