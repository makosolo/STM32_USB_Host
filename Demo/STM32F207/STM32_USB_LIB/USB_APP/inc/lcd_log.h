/**
  ******************************************************************************
  * @file    lcd_log.h
  * @author  MCD Application Team
  * @version V5.1.0
  * @date    31-July-2015
  * @brief   header for the lcd_log.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __LCD_LOG_H__
#define  __LCD_LOG_H__

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/**
  * @}
  */ 
#define USBH_DEBUG_LEVEL                      3 //调试等级控制

/** @defgroup LCD_LOG_Exported_Macros
  * @{
  */ 
/* DEBUG macros */   
#if (USBH_DEBUG_LEVEL > 0)
#define LCD_UsrLog(...)   printf(__VA_ARGS__);\

#else
#define LCD_UsrLog(...)   
#endif 
                            
                            
#if (USBH_DEBUG_LEVEL > 1)

#define LCD_ErrLog(...)   printf("ERROR: ") ;\
                           printf(__VA_ARGS__);\

#else
#define LCD_ErrLog(...)   
#endif 
                                                      
#if (USBH_DEBUG_LEVEL > 2)                         
#define LCD_DbgLog(...)   printf("DEBUG : ") ;\
                           printf(__VA_ARGS__);\

#else
#define LCD_DbgLog(...)                         
#endif

#endif //__LCD_LOG_H__

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
