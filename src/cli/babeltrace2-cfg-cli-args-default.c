/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2016 Jérémie Galarneau <jeremie.galarneau@efficios.com>
 * Copyright 2017 Philippe Proulx <pproulx@efficios.com>
 */

#include <babeltrace2/babeltrace.h>
#include "babeltrace2-cfg.h"
#include "babeltrace2-cfg-cli-args.h"
#include "babeltrace2-cfg-cli-args-default.h"

enum bt_config_cli_args_status bt_config_cli_args_create_with_default(int argc,
		const char *argv[], struct bt_config **cfg,
		const bt_interrupter *interrupter)
{
	return bt_config_cli_args_create(argc, argv, cfg, false, false,
		NULL, interrupter);
}
