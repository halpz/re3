/***************************************************************************
 *                                                                         *
 * Module  : rperror.h                                                     *
 *                                                                         *
 * Purpose : Used to generate error codes                                  *
 *                                                                         *
 **************************************************************************/

#ifndef RPERROR_H
#define RPERROR_H

/****************************************************************************
 Includes
 */

#include "rpplugin.h"

/****************************************************************************
 Defines
 */

#define RWECODE(a,b) a,

enum rwPLUGIN_ERRENUM
{
#include "rperror.def"
    rwPLUGIN_ERRENUMLAST = RWFORCEENUMSIZEINT
};

typedef enum rwPLUGIN_ERRENUM rwPLUGIN_ERRENUM;

#endif /* RPERROR_H */
