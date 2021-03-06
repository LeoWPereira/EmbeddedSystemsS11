/**
 * @file	: lpc13xx_wdt.c
 * @brief	: Contains all functions support for WDT firmware library on LPC13xx
 * @version	: 1.0
 * @date	: 27. Nov. 2009
 * @author	: ThieuTrinh
 *----------------------------------------------------------------------------
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup WDT
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc13xx_wdt.h"
#include "lpc13xx_clkpwr.h"
#include "lpc13xx_pinsel.h"


/* If this source file built with example, the LPC13xx FW library configuration
 * file in each example directory ("lpc13xx_libcfg.h") must be included,
 * otherwise the default FW library configuration file must be included instead
 */


/* Private Functions ---------------------------------------------------------- */
/** @defgroup WDT_Private_Functions
 * @{
 */

/********************************************************************//**
 * @brief 		Set WDT time out value and WDT mode
 * @param[in]	timeout value of time-out for WDT (us)
 * @return		None
 *********************************************************************/
uint8_t WDT_SetTimeOut (uint32_t timeout)
{

	uint32_t pclk_wdt = 0;
	uint32_t tempval = 0;
    	pclk_wdt = SystemCoreClock;
    	// Calculate TC in WDT
    	tempval  = (((pclk_wdt) / WDT_US_INDEX) * (timeout/4));
    	// Check if it valid
    	if ((tempval >= WDT_TIMEOUT_MIN) && (tempval <= WDT_TIMEOUT_MAX))
    	{
    		LPC_WWDT->TC = tempval;
    		return	SUCCESS;
    	}

	return ERROR;
}

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup WDT_Public_Functions
 * @{
 */


/*********************************************************************//**
* @param[in]	WDTMode WDT mode
* 				-	0: Use WDT to generate interrupt only
* 				-	1:WDT_MODE_RESET
* @return 		None
 **********************************************************************/

void WDT_Init (uint32_t WDTMode)
{
	//Set WDT mode
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<15);

	if (WDTMode == WDT_MODE_RESET){
		LPC_WWDT->MOD |= WDT_WDMOD(WDTMode);
	}
}


/**
 * @brief		Start WDT activity with given timeout value
 * @param[in]   TimeOut WDT reset after timeout if it is not feed
 * @return		None
 */
void WDT_Start(uint32_t TimeOut)
{
	WDT_SetTimeOut(TimeOut);
	//enable watchdog
	LPC_WWDT->MOD |= WDT_WDMOD_WDEN;
	WDT_Feed();
}


/********************************************************************//**
 * @brief 		Read WDT Time out flag
 * @param		None
 * @return		Time out flag status of WDT
 *********************************************************************/
FlagStatus WDT_ReadTimeOutFlag (void)
{
	return ((FlagStatus)((LPC_WWDT->MOD & WDT_WDMOD_WDTOF) >>2));
}

/********************************************************************//**
 * @brief 		Clear WDT Time out flag
 * @param		None
 * @return		None
 *********************************************************************/
void WDT_ClrTimeOutFlag (void)
{
	LPC_WWDT->MOD &=~WDT_WDMOD_WDTOF;
}

/********************************************************************//**
 * @brief 		Update WDT timeout value and feed
 * @param[in]	TimeOut	TimeOut value to be updated
 * @return		None
 *********************************************************************/
void WDT_UpdateTimeOut ( uint32_t TimeOut)
{
	WDT_SetTimeOut(TimeOut);
	WDT_Feed();
}


/********************************************************************//**
 * @brief 		After set WDTEN, call this function to start Watchdog
 * 				or reload the Watchdog timer
 * @param	None
 *
 * @return		None
 *********************************************************************/
void WDT_Feed (void)
{
	// Disable irq interrupt
	__disable_irq();
	LPC_WWDT->FEED = 0xAA;
	LPC_WWDT->FEED = 0x55;
	// Then enable irq interrupt
	__enable_irq();
}

/********************************************************************//**
 * @brief 		Get the current value of WDT
 * @param		None
 * @return		current value of WDT
 *********************************************************************/
uint32_t WDT_GetCurrentCount(void)
{
	return LPC_WWDT->TV;
}
/********************************************************************//**
 * @brief 		Setup clock for WDT
 * @param[in]	clksrc: WDT clock source selection
 * @return		None
 *********************************************************************/
void WDT_CLKSetup (uint32_t clksrc )
{
  /* Watchdog configuration. */
  LPC_SYSCON->WDTCLKSEL = clksrc;        /* Select clock source */
  LPC_SYSCON->WDTCLKUEN = 0x01;          /* Update clock */
  LPC_SYSCON->WDTCLKUEN = 0x00;          /* Toggle update register once */
  LPC_SYSCON->WDTCLKUEN = 0x01;
  while ( !(LPC_SYSCON->WDTCLKUEN & 0x01) );  /* Wait until updated */
  LPC_SYSCON->WDTCLKDIV = 1;            /* Divided by 1 */
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    /* Let WDT clock run */
  return;
}

/**
 * @}
 */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
