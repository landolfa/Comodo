#ifndef WSF2EX6_H
#define WSF2EX6_H
/*******************************************************************************
*    E.S.O. - VLT project
*
*    "@(#) $Id$"
*
* who                when       what
* ----------------  ----------  ----------------------------------------------
* COMODO            -           Created.
* 
*/

#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif


/******************************************************************************
 * Global Constant Definitions
 ******************************************************************************/
#define wsf2ex6MOD "wsf2ex6"


/******************************************************************************
 * Macros used to build the string Id 
 ******************************************************************************/

/* Support macros to handle parameters substitution */
#define wsf2ex6REPLACE_IT(date,time) "@(#) $WSF Compile Id - Date: " date " Time: " time " $"
#define wsf2ex6TARGET_IT(date,time)  wsf2ex6REPLACE_IT(date,time)

/* Real macro to be used in the code */
/* 
 * It MUST be called in the following way:
 *      wsf2ex6WSF_RCSID("@(#) $Id: wsf2ex6.h 593 2012-04-22 12:12:12Z landolfa $")
 * to be concatenated with rcsId and with version strings
 */
#define wsf2ex6WSF_RCSID(id)                                                       \
   static const char *rcsId = id wsf2ex6TARGET_IT(__DATE__, __TIME__);             \
   static const void *use_rcsId = ((const void)&use_rcsId,(const void *) &rcsId);


#endif // !WSF2EX6_H

