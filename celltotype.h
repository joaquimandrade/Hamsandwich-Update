/* Ham Sandwich
 *   Copyright 2007-2012
 *   By the AMX Mod X Development Team
 *
 *  Ham Sandwich is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  Ham Sandwich is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ham Sandwich; if not, write to the Free Software Foundation,
 *  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  In addition, as a special exception, the author gives permission to
 *  link the code of Ham Sandwich with the Half-Life Game Engine ("HL
 *  Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *  L.L.C ("Valve"). You must obey the GNU General Public License in all
 *  respects for all of the code used other than the HL Engine and MODs
 *  from Valve. If you modify this file, you may extend this exception
 *  to your version of the file, but you are not obligated to do so. If
 *  you do not wish to do so, delete this exception statement from your
 *  version.
 */

#ifndef CELLTOTYPE_H
#define CELLTOTYPE_H

#include <extdll.h>
#include "amxxmodule.h"

#include "CVector.h"

#include "hook.h"
#include "forward.h"

#include "ham_const.h"	
#include "ham_utils.h"

inline void CellToType(const AMX*& amx, const cell& in, int& out)
{
	out=static_cast<int>(in);
}

inline void CellToType(const AMX*& amx, const cell& in, float& out)
{
	out=amx_ctof2(in);
}

inline void CellToType(const AMX*& amx, const cell& in, edict_t*& out)
{
	out=INDEXENT_NEW(in);
}

inline void CellToType(const AMX*& amx, const cell& in, entvars_t*& out)
{
	out=&(INDEXENT_NEW(in)->v);
}

inline void CellToType(const AMX*& amx, const cell& in, HLBaseEntity*& out)
{
	out=(HLBaseEntity *)(INDEXENT_NEW(in)->pvPrivateData);
}

inline void CellToType(const AMX*& amx, const cell& in, Vector& out)
{
	float *v=(float *)MF_GetAmxAddr(amx, in);

	out.x=v[0];
	out.y=v[1];
	out.z=v[2];
}

inline void CellToType(const AMX*& amx, const cell& in, TraceResult*& out)
{
	out=reinterpret_cast<TraceResult*>(in);
}

#endif
