/*
 * tinf - tiny inflate library (inflate, gzip)
 * Copyright (c) 2003-2019 Joergen Ibsen
 * zlib license — see tinf.c for full text
 */
#ifndef TINF_H_INCLUDED
#define TINF_H_INCLUDED

typedef enum {
	TINF_OK         = 0,
	TINF_DATA_ERROR = -3,
	TINF_BUF_ERROR  = -5
} tinf_error_code;

int tinf_uncompress(void *dest, unsigned int *destLen,
                    const void *source, unsigned int sourceLen);

int tinf_gzip_uncompress(void *dest, unsigned int *destLen,
                         const void *source, unsigned int sourceLen);

unsigned int tinf_crc32(const void *data, unsigned int length);

#endif
