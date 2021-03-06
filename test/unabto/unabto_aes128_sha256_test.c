#define NABTO_LOG_MODULE_CURRENT NABTO_LOG_MODULE_TEST

#include <unabto/unabto_env_base.h>

#if NABTO_ENABLE_TEST_CODE

#include <unabto/unabto_external_environment.h>
#include <../test/unabto/unabto_aes128_sha256_test.h>
#include <unabto/unabto_aes128_sha256.h>

/**
 * Test integrity verification works as expected.
 * 
 * Reference integrity check: 
 * 120221-23:33:17.819 {b76b0b50} [___DEFAULT,user1] unabto_crypto.c(356):                unabto verify integrity key is
 * 0000:  8c c7 0b 0e 8f 4f 18 e9  0f 5b 54 47 76 79 d6 7e  .....O.. .[TGvy.~
 * 0010:  c8 f9 1e be 9d ce 41 f3  2f 41 c1 24 bc 2d a7 46  ......A. /A.$.-.F
 * 120221-23:33:17.819 {b76b0b50} [___DEFAULT,user1] unabto_crypto.c(357):                buffer
 * 0000:  00 00 00 00 00 00 00 71  81 02 00 00 00 03 00 b4  .......q ........
 * 0010:  39 80 00 0a c0 a8 01 8c  a3 cf 32 00 00 24 57 33  9....... ..2..$W3
 * 0020:  9b 16 c9 fa 9a 16 54 1a  90 57 f6 8b 93 3a 91 65  ......T. .W...:.e
 * 0030:  d3 c6 5a f7 c4 be a3 1e  09 c1 fc 16 fc 8f 36 00  ..Z..... ......6.
 * 0040:  00 76 23 0a 55 d0 5e 62  21 81 ca e0 de 37 ac 36  .v#.U.^b !....7.6
 * 0050:  81 06 64 2a 83 59 e7 66  56 df f9 ef 94 30 55 e9  ..d*.Y.f V....0U.
 * 0060:  50 d6 e1 63 8d 84 15 fe  6c 96 35 48 6e 70 dc 8d  P..c.... l.5Hnp..
 * 0070:  e8 be 53 f9 56 45 b2 be  cc 2f ca 2c eb 04 41 58  ..S.VE.. ./.,..AX
 * 0080:  e7 a1 2e 04 cf 45 f7 b1  18 96 c0 da 88 0b d6 6f  .....E.. .......o
 * 0090:  69 b5 d9 98 52 fe e2 56  86 a5 d4 2f 1a cb 12 d2  i...R..V .../....
 * 00a0:  fd 4a 69 03 f9 4f e0 1f  72 3b 14 b8 b4 81 ea 89  .Ji..O.. r;......
 * 00b0:  a3 ae 1b 5d
 */

static const uint8_t key[32] = {0x8c, 0xc7, 0x0b, 0x0e, 0x8f, 0x4f, 0x18, 0xe9, 0x0f, 0x5b, 0x54, 0x47, 0x76, 0x79, 0xd6, 0x7e,
                                0xc8, 0xf9, 0x1e, 0xbe, 0x9d, 0xce, 0x41, 0xf3, 0x2f, 0x41, 0xc1, 0x24, 0xbc, 0x2d, 0xa7, 0x46};

static const uint8_t integrity[16] = {0xf9, 0x4f, 0xe0, 0x1f, 0x72, 0x3b, 0x14, 0xb8, 0xb4, 0x81, 0xea, 0x89, 0xa3, 0xae, 0x1b, 0x5d};

static const uint8_t buffer[164] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x81, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0xb4,
                                    0x39, 0x80, 0x00, 0x0a,
                                    0xc0, 0xa8, 0x01, 0x8c, 0xa3, 0xcf, 0x32, 0x00, 0x00, 0x24, 0x57, 0x33,
                                    0x9b, 0x16, 0xc9, 0xfa, 0x9a, 0x16, 0x54, 0x1a, 0x90, 0x57, 0xf6, 0x8b, 0x93, 0x3a, 0x91, 0x65,
                                    0xd3, 0xc6, 0x5a, 0xf7, 0xc4, 0xbe, 0xa3, 0x1e, 0x09, 0xc1, 0xfc, 0x16, 0xfc, 0x8f, 0x36, 0x00,
                                    0x00, 0x76, 0x23, 0x0a, 0x55, 0xd0, 0x5e, 0x62, 0x21, 0x81, 0xca, 0xe0, 0xde, 0x37, 0xac, 0x36,
                                    0x81, 0x06, 0x64, 0x2a, 0x83, 0x59, 0xe7, 0x66, 0x56, 0xdf, 0xf9, 0xef, 0x94, 0x30, 0x55, 0xe9,
                                    0x50, 0xd6, 0xe1, 0x63, 0x8d, 0x84, 0x15, 0xfe, 0x6c, 0x96, 0x35, 0x48, 0x6e, 0x70, 0xdc, 0x8d,
                                    0xe8, 0xbe, 0x53, 0xf9, 0x56, 0x45, 0xb2, 0xbe, 0xcc, 0x2f, 0xca, 0x2c, 0xeb, 0x04, 0x41, 0x58,
                                    0xe7, 0xa1, 0x2e, 0x04, 0xcf, 0x45, 0xf7, 0xb1, 0x18, 0x96, 0xc0, 0xda, 0x88, 0x0b, 0xd6, 0x6f,
                                    0x69, 0xb5, 0xd9, 0x98, 0x52, 0xfe, 0xe2, 0x56, 0x86, 0xa5, 0xd4, 0x2f, 0x1a, 0xcb, 0x12, 0xd2,
                                    0xfd, 0x4a, 0x69, 0x03};

void truncated_hmac_sha256_verify_integrity_test(bool *a)
{
  *a = unabto_truncated_hmac_sha256_verify_integrity(key, 32, buffer, 164, integrity);
}

int integrity_verify_timing(void)
{
  nabto_stamp_t future;
  bool a;
  int i = 0;

  nabtoSetFutureStamp(&future, 1000);

  while(!nabtoIsStampPassed(&future))
  {
    truncated_hmac_sha256_verify_integrity_test(&a);
    i++;
  }

  return i;
}

#endif
