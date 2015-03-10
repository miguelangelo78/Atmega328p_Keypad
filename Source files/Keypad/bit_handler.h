#ifndef BIT_HANDLER_H_
#define BIT_HANDLER_H_

#define TOP_NIBBLE_MASK 0xF0
#define BOT_NIBBLE_MASK 0x0F
#define BYTE_MASK TOP_NIBBLE_MASK | BOT_NIBBLE_MASK

#define port_set(port, data, mask) (port = data & mask)
#define bit_get(p,m) ((p) & (1<<m))
#define bit_set(p,m) ((p) |= (1<<m))
#define bit_clear(p,m) ((p) &= ~(1<<m))
#define bit_flip(p,m) ((p) ^= (1<<m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))

#endif /* BIT_HANDLER_H_ */