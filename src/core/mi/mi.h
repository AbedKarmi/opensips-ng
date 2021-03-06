/*
 * Copyright (C) 2010 OpenSIPS Project
 *
 * This file is part of opensips, a free SIP server.
 *
 * opensips is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * opensips is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

/*!
 * \file 
 * \brief MI :: Management
 * \ingroup mi
 */


#ifndef _MI_MI_H_
#define _MI_MI_H_

#include "../str.h"
#include "tree.h"

#define MI_NO_INPUT_FLAG    (1<<0)


typedef struct mi_root* (mi_cmd_f)(struct mi_root*, void *param);
typedef int (mi_child_init_f)(void);
typedef void (mi_handler_f)(struct mi_root *, struct mi_handler *, int);
typedef int (mi_flush_f)(void *, struct mi_root *);


struct mi_cmd {
	int id;
	str name;
	mi_child_init_f *init_f;
	mi_cmd_f *f;
	unsigned int flags;
	void *param;
};


typedef struct mi_funcs_ {
	char *name;
	mi_cmd_f *cmd;
	unsigned int flags;
	void *param;
	mi_child_init_f *init_f;
}mi_funcs_t;



int register_mi_cmd( mi_cmd_f f, char *name, void *param,
		mi_child_init_f in, unsigned int flags);


int register_mi_mod( char *mod_name, mi_funcs_t *mis);


struct mi_cmd* lookup_mi_cmd( char *name, int len);


static inline struct mi_root* run_mi_cmd(struct mi_cmd *cmd, struct mi_root *t,
										mi_flush_f *f, void *param)
{
	struct mi_root *ret;

	/* set the flush function */
	// FIXME
	//crt_flush_fnct = f;
	//crt_flush_param = param;

	ret = cmd->f( t, cmd->param);

	/* reset the flush function */
	//crt_flush_fnct = 0;
	//crt_flush_param = 0;

	return ret;
}

void get_mi_cmds( struct mi_cmd** cmds, int *size);


void destroy_mi_cmds(void);


static inline int flush_mi_tree(struct mi_root *t)
{
	// FIXME
	//if(crt_flush_fnct)
	//	return crt_flush_fnct(crt_flush_param, t);
	//else
		return 0;
}

#endif

