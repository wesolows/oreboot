/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010 Marc Bertens <mbertens@xs4all.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <device/pci_def.h>
#include <device/pnp_def.h>
#include <console/console.h>
#include <southbridge/intel/i82371eb/i82371eb.h>
#include <northbridge/intel/i440bx/raminit.h>
#include <cpu/x86/bist.h>
#include <cpu/intel/romstage.h>
#include <superio/smsc/smscsuperio/smscsuperio.h>
#include <lib.h>

#define SERIAL_DEV PNP_DEV(0x3f0, SMSCSUPERIO_SP1)

int spd_read_byte(unsigned int device, unsigned int address)
{
	return smbus_read_byte(device, address);
}

void mainboard_romstage_entry(unsigned long bist)
{
	smscsuperio_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	console_init();
	report_bist_failure(bist);

	enable_smbus();
	sdram_initialize();
}
