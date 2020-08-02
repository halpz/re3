/*
 * Debug handling
 *
 ****************************************************************************
 *
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd. or
 * Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. will not, under any
 * circumstances, be liable for any lost revenue or other damages arising
 * from the use of this file.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 * All Rights Reserved.
 *
 * RenderWare is a trademark of Canon Inc.
 *
 ****************************************************************************/

/****************************************************************************
 Includes
 */


#include <stdlib.h>
#include <string.h>

#include <rwcore.h>
#include <rpdbgerr.h>

static const char rcsid[] __RWUNUSED__ = "@@(#)$Id: rpdbgerr.c,v 1.2 2004/08/31 17:40:34 gtristram Exp $";

#ifdef RWDEBUG

/****************************************************************************
 Defines
 */

 /****************************************************************************
 Local (static) Globals
 */

/* The strings used in the debug error reporting are derived from the 
 * .def files
 */

#define RWECODE(a,b) RWSTRING(b),

static const RwChar *rw_err_str[] =
{
#include "rperror.def"
    RWSTRING("Last Error")
};

#undef RWECODE
#define RWECODE(a,b) RWSTRING(#a),

static const RwChar *rw_err_cstr[] =
{
#include "rperror.def"
    RWSTRING("E_RW_LAST")
};

#undef RWECODE

static RwChar   dberr[512];

RwChar         *
rwPLUGIN_ERRFUNC(RwInt32 code,...)
{
    va_list         ap;

#if (0)
    RWFUNCTION(RWSTRING("rwPLUGIN_ERRFUNC"));
#endif /* (0) */

    va_start(ap, code);

    rwstrcpy(dberr, rw_err_cstr[code]);
    rwstrcat(dberr, RWSTRING(" : "));
    rwvsprintf(&dberr[rwstrlen(dberr)], rw_err_str[code], ap);
    va_end(ap);
    return dberr;
}

#endif /* RWDEBUG */

