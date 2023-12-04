#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "md5.h"
 
unsigned char PADDING[]={0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// 初始化结构体 MD5_CTX                       
void MD5Init(MD5_CTX *context)
{
     context->count[0] = 0;
     context->count[1] = 0;
     // 初始化四种状态 
     context->state[0] = 0x67452301;
     context->state[1] = 0xEFCDAB89;
     context->state[2] = 0x98BADCFE;
     context->state[3] = 0x10325476;
}
// 将输入数据添加到MD5算法的计算上下文中，并在需要时触发哈希计算以生成最终的哈希值 
void MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputlen)  
{							/*input是指向输入数据的指针 ， inputlen是输入数据的长度*/ 
    unsigned int i = 0,index = 0,partlen = 0;
    // 将位数计数器context->count[0]转换为字节单位;按位与操作保证索引在0-63之间	 
    index = (context->count[0] >> 3) & 0x3F;
    // 计算缓冲区剩余空间大小 
    partlen = 64 - index;
    // 添加input数据，所以需要更新结构体中位数数组count，使用<<是为了将其转化为位数 
    context->count[0] += inputlen << 3;
    // 检查低32位的位数计数器context->count[0]是否小于输入数据的位数
    if(context->count[0] < (inputlen << 3)) // 左移三位，等价于inputlen*8 ，可以将字节转化为位数
		// 将高32位的位数计数器递增1。这样可以确保位数计数器能够正确地记录输入数据的总位数。 
       context->count[1]++;
    // 右移29位，将输入数据的字节数转换为32位整数表示的倍数,将这个值加到高32位的位数计数器
	// context->count[1]上，确保位数计数器能够正确地记录输入数据的总位数。
    context->count[1] += inputlen >> 29;
    // 如果输入数据超过剩余内存空间，就分组处理(一个分组64)
    if(inputlen >= partlen)
    {
       memcpy(&context->buffer[index],input,partlen); // 将输入的数据拷贝到缓冲区 
       MD5Transform(context->state,context->buffer); // 对位数计数器context->buffer中的数据进行处理
       // 处理输入数据中剩余的完整分组。每次增加64,直到剩余的数据长度不足一个完整分组。
       for(i = partlen;i+64 <= inputlen;i+=64)
       		// &input[i]表示从输入数据的第i个位置开始的64字节数据。
           MD5Transform(context->state,&input[i]);
        // 以保证在输入数据长度不足一个分组时，剩余数据能够正确地拷贝到缓冲区的开头进行处理。
       index = 0;        
    }
//    else { i = 0; }
	// 将输入的数据拷贝到缓冲区 
    memcpy(&context->buffer[index],&input[i],inputlen-i);
}
// 使用一系列的位运算、逻辑运算和常数操作，对状态数组进行更新，以生成新的哈希值。
// MD5是一种常用的哈希函数，用于将任意长度的数据映射为固定长度的哈希值（通常是128位）,

// 将用户输入的密码进行哈希计算得到哈希值，并将哈希值存储在文件中。
// 当用户登录时，系统会对用户输入的密码进行相同的哈希计算，
// 并将计算得到的哈希值与存储的哈希值进行比较。如果两个哈希值匹配，则验证成功。
void MD5Transform(unsigned int state[4],unsigned char block[64])
{	// MD5哈希计算，来达到加密 效果 
     unsigned int a = state[0];
     unsigned int b = state[1];
     unsigned int c = state[2];
     unsigned int d = state[3];
     unsigned int x[64];
     MD5Decode(x,block,64);
     FF(a, b, c, d, x[ 0], 7, 0xd76aa478); /* 1 */
	 FF(d, a, b, c, x[ 1], 12, 0xe8c7b756); /* 2 */
	 FF(c, d, a, b, x[ 2], 17, 0x242070db); /* 3 */
	 FF(b, c, d, a, x[ 3], 22, 0xc1bdceee); /* 4 */
	 FF(a, b, c, d, x[ 4], 7, 0xf57c0faf); /* 5 */
	 FF(d, a, b, c, x[ 5], 12, 0x4787c62a); /* 6 */
	 FF(c, d, a, b, x[ 6], 17, 0xa8304613); /* 7 */
	 FF(b, c, d, a, x[ 7], 22, 0xfd469501); /* 8 */
	 FF(a, b, c, d, x[ 8], 7, 0x698098d8); /* 9 */
	 FF(d, a, b, c, x[ 9], 12, 0x8b44f7af); /* 10 */
	 FF(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
	 FF(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
	 FF(a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
	 FF(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
	 FF(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
	 FF(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */
 
	 /* Round 2 */
	 GG(a, b, c, d, x[ 1], 5, 0xf61e2562); /* 17 */
	 GG(d, a, b, c, x[ 6], 9, 0xc040b340); /* 18 */
	 GG(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
	 GG(b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /* 20 */
	 GG(a, b, c, d, x[ 5], 5, 0xd62f105d); /* 21 */
	 GG(d, a, b, c, x[10], 9,  0x2441453); /* 22 */
	 GG(c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
	 GG(b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /* 24 */
	 GG(a, b, c, d, x[ 9], 5, 0x21e1cde6); /* 25 */
	 GG(d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
	 GG(c, d, a, b, x[ 3], 14, 0xf4d50d87); /* 27 */
	 GG(b, c, d, a, x[ 8], 20, 0x455a14ed); /* 28 */
	 GG(a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
	 GG(d, a, b, c, x[ 2], 9, 0xfcefa3f8); /* 30 */
	 GG(c, d, a, b, x[ 7], 14, 0x676f02d9); /* 31 */
	 GG(b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */
 
	 /* Round 3 */
	 HH(a, b, c, d, x[ 5], 4, 0xfffa3942); /* 33 */
	 HH(d, a, b, c, x[ 8], 11, 0x8771f681); /* 34 */
	 HH(c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
	 HH(b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
	 HH(a, b, c, d, x[ 1], 4, 0xa4beea44); /* 37 */
	 HH(d, a, b, c, x[ 4], 11, 0x4bdecfa9); /* 38 */
	 HH(c, d, a, b, x[ 7], 16, 0xf6bb4b60); /* 39 */
	 HH(b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
	 HH(a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
	 HH(d, a, b, c, x[ 0], 11, 0xeaa127fa); /* 42 */
	 HH(c, d, a, b, x[ 3], 16, 0xd4ef3085); /* 43 */
	 HH(b, c, d, a, x[ 6], 23,  0x4881d05); /* 44 */
	 HH(a, b, c, d, x[ 9], 4, 0xd9d4d039); /* 45 */
	 HH(d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
	 HH(c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
	 HH(b, c, d, a, x[ 2], 23, 0xc4ac5665); /* 48 */
 
	 /* Round 4 */
	 II(a, b, c, d, x[ 0], 6, 0xf4292244); /* 49 */
	 II(d, a, b, c, x[ 7], 10, 0x432aff97); /* 50 */
	 II(c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
	 II(b, c, d, a, x[ 5], 21, 0xfc93a039); /* 52 */
	 II(a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
	 II(d, a, b, c, x[ 3], 10, 0x8f0ccc92); /* 54 */
	 II(c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
	 II(b, c, d, a, x[ 1], 21, 0x85845dd1); /* 56 */
	 II(a, b, c, d, x[ 8], 6, 0x6fa87e4f); /* 57 */
	 II(d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
	 II(c, d, a, b, x[ 6], 15, 0xa3014314); /* 59 */
	 II(b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
	 II(a, b, c, d, x[ 4], 6, 0xf7537e82); /* 61 */
	 II(d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
	 II(c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /* 63 */
	 II(b, c, d, a, x[ 9], 21, 0xeb86d391); /* 64 */
	 
     state[0] += a;
     state[1] += b;
     state[2] += c;
     state[3] += d;
}
// 在当前系统中可以理解为解码 
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len)
{/*input是表示输入的MD5哈希值；len表示输入的哈希值的长度；output用于存储解码后的数据。*/
     unsigned int i = 0,j = 0;
     while(j < len)
     {
           output[i] = (input[j]) |
                       (input[j+1] << 8) |
                       (input[j+2] << 16) |
                       (input[j+3] << 24);
           i++;
           j+=4; 
     }
}
// 在MD5算法的数据处理过程中,将输入数据的字节表示转换为小端字节序 
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len)
{	/*output用于存储计算得到的哈希值,input是指向输入数据的指针 ，len是输入数据的长度*/ 
    unsigned int i = 0,j = 0;
    while(j < len)
    {
         output[j] = input[i] & 0xFF;  
         output[j+1] = (input[i] >> 8) & 0xFF;
         output[j+2] = (input[i] >> 16) & 0xFF;
         output[j+3] = (input[i] >> 24) & 0xFF;
         i++;
         j+=4;
    }
}
// 通过多个函数的组合实现加密 
void MD5Final(MD5_CTX *context,unsigned char digest[16])
{
    unsigned int index = 0,padlen = 0;
    unsigned char bits[8];
    index = (context->count[0] >> 3) & 0x3F;
    padlen = (index < 56)?(56-index):(120-index);
    MD5Encode(bits,context->count,8); // 将数据的位数转换为字节数，并存储在bits中 
    MD5Update(context,PADDING,padlen); // 向MD5算法的上下文中添加填充字节到PADDING数组，长度为padlen字节 
    MD5Update(context,bits,8); // 转换后的位数字节数组bits添加到上下文中。
    MD5Encode(digest,context->state,16); // 将MD5算法上下文中的最终状态转换为最终的哈希值，并存储在digest中
}
// 将输入的原始数据进行MD5哈希计算，并将计算得到的哈希值以字符串形式存储在cipher数组中
void MD5(unsigned char *original, unsigned char cipher[33]){
	int i;
	unsigned char tempStr[16] = {0};
    MD5_CTX md5;
    MD5Init(&md5); // 初始化上下文 
    MD5Update(&md5, original, strlen((char*)original)); // 将原始数据添加到MD5算法的上下文中进行处理 
    MD5Final(&md5, tempStr); // 将MD5算法的最终状态转换为最终的哈希值
    // 循环是用来将哈希值的每个字节转换为两位十六进制数并存储在cipher数组中 
    for(i=0;i<16;i++){  
        sprintf(&cipher[i*2], "%02x", tempStr[i]);
    }
}

