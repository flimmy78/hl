/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#define SBOX_LEN 32
#define KEY_LEN 8
#define MKEY_LEN 16
#define DATA_LEN 16


void init_key(void);
void init_kbox(unsigned char *key,unsigned char keyleng);
void init_sbox(void);
void rc4_encrypt(unsigned char *key,unsigned char key_leng, unsigned char *buf, int len);
unsigned char CRC_Sum(unsigned char *Buf, unsigned char Length);
unsigned char Hex_To_Ascii(unsigned char Data);
/* [] END OF FILE */
