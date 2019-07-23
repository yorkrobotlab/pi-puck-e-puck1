/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define FOSC   7.3728e6     // 7.3728Mhz crystal in XTL mode 
#define PLL    8.0       	// 8x PLL
#define FCY     ((FOSC*PLL)/(4.0))	// Instruction cycle frequency 

//#define SYS_FREQ        7370000L
//#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

