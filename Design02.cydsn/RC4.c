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
#include"Rc4.h"
#include <string.h>
#include "main.h"

uint8 Rc4Sbox[SBOX_LEN];
uint8 Rc4Kbox[SBOX_LEN];



void init_sbox(void)
{
    int i, j = 0;
    unsigned char tmp;

    for (i = 0; i < SBOX_LEN; i++)
        Rc4Sbox[i] = i;

    for (i = 0; i < SBOX_LEN; i++)
    {
        j = (j + Rc4Sbox[i] + Rc4Kbox[i]) % SBOX_LEN;
        tmp = Rc4Sbox[i];
        Rc4Sbox[i] = Rc4Sbox[j];
        Rc4Sbox[j] = tmp;
    }
}





/*
 *******************************************************************************     
 * 功能名: init_kbox    
 * 说明:  初始化 kbox        
 * 输入:  key 密钥    
 * 输出: 
 * 返回:  
 *******************************************************************************     
 */
void init_kbox(unsigned char *key,unsigned char keyleng)
{
    int i;
    for (i = 0; i < SBOX_LEN; i++)
    {
        Rc4Kbox[i] = key[i % keyleng];
    }
}

/*
 *******************************************************************************
 * 功能名:  rc4_encrypt
 * 说明:  rc4计算
 * 输入:  	key 密钥
 			buf 数据
 			len 长度
 * 输出:
 * 返回:
 *******************************************************************************
 */

void rc4_encrypt(unsigned char *key,unsigned char key_leng, unsigned char *buf, int len)
{
    int i = 0, j = 0, t, index = 0;
    unsigned char tmp;
    unsigned char *data;
    data=buf;

    if (buf == NULL || len <= 0)
        return;
    init_kbox(key,key_leng);
    init_sbox();


    while (index < len)
    {
        i = (i + 1) % SBOX_LEN;
        j = (j + Rc4Sbox[i]) % SBOX_LEN;
        tmp = Rc4Sbox[i];
        Rc4Sbox[i] = Rc4Sbox[j];
        Rc4Sbox[j] = tmp;
        t = (Rc4Sbox[i] + Rc4Sbox[j]) % SBOX_LEN;

        buf[index] = data[index] ^ Rc4Sbox[t]; 
        index++;
    }
}

/**************************************************
累计和取反校验
***************************************************/
unsigned char CRC_Sum(unsigned char *Buf, unsigned char Length)
{
    unsigned char sum = 0x00;
    while (Length--)
    {
        sum += *Buf++;
    }
    return ~(unsigned char)sum;
}

/**************************************************
16进制转ASCII
***************************************************/
unsigned char Hex_To_Ascii(unsigned char Data)
{
    if(Data < 10)
    {
        return (Data+0x30);
    }
    else
    {
        return (Data+0x37);
    }
}






/* [] END OF FILE */
