/* -*- Mode: C; tab-width:2 -*- */
/* ex: set ts=2 shiftwidth=2 softtabstop=2 cindent: */

/**
 * @brief    device related messages
 * @author   Naim Busek	(naim@gmail.com)
 * @version  0.1
 *
 */
#ifndef _PLAT_MSG_TYPES_H_
#define _PLAT_MSG_TYPES_H_
#include <message_types.h>

/**
 * @brief device msg_types list
 */
enum {
	/* radio msgs */
	MSG_CC1K_RADIO_PACKET_SENT = PLAT_MSG_START,
	MSG_CC1K_RADIO_PACKET_RECV,
	MSG_CC1K_RADIO_ADJUST_SQUELCH,
	MSG_RADIO_ENABLE_ACK,
	/* flash msgs */
	MSG_EXFLASH_DESELECT,
	MSG_EXFLASH_AVAIL,
	MSG_EXFLASH_READDONE,
	MSG_EXFLASH_CRCDONE,
	MSG_EXFLASH_WRITEDONE,
	MSG_EXFLASH_SYNCDONE,
	MSG_EXFLASH_FLUSHDONE,
	MSG_EXFLASH_ERASEDONE,
};

#endif /* _PLAT_MSG_TYPES_H_ */

