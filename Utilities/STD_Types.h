/**
 * STD_Types.h
 * Jan 24th 2024
 * @auther : Mostafa Asaad
*/
#ifndef STD_TYPES_H
#define STD_TYPES_H

/* --------------- Section : Disable The Deprecation Warning --------------- */
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
/* --------------- Section : Includes --------------- */
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
/* --------------- Section: Data Type Declarations --------------- */
typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t;
typedef uint8_t			STD_ReturnType;
/* --------------- Section: Macro Declarations --------------- */
#define	E_OK			(STD_ReturnType)1
#define	E_NOT_OK		(STD_ReturnType)0

#endif // !STD_TYPES_H
