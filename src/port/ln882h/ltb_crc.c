// Copyright (c) Kuba Szczodrzyński 2026-7-5.

#include "ln882h.h"

uint16_t ltb_crc16(const void *buf, size_t len) {
	return crc16_ccitt(buf, len);
}

uint32_t ltb_crc32(const void *buf, size_t len) {
	return ln_crc32_signle_cal(buf, len);
}
