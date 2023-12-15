#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BYTE	unsigned char
#define WORD    unsigned short
#define SWORD   short
#define DWORD	unsigned long
#define SDWORD	long
#define BOOL	unsigned char
#define	QWORD   unsigned long long
#define SQWORD	long long

#define MAX_LINE_LENGTH 428
#define NUM_ROWS 20100
#define Len_Now 8

long int hexStringToDecimal(char* hexString)
{
    if (*hexString == '\0')
    {
        fprintf(stderr, "Empty string\n");
        exit(EXIT_FAILURE);
    }

    int isNegative = (*hexString == '-');
    if (isNegative)
    {
        hexString++; 
    }

    long int result = 0;

    while (*hexString != '\0')
    {
        char digit = *hexString;
        int value;
        if (digit >= '0' && digit <= '9')
        {
            value = digit - '0';
        }
        else if (digit >= 'A' && digit <= 'F')
        {
            value = digit - 'A' + 10;
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            value = digit - 'a' + 10;
        }
        else
        {
            fprintf(stderr, "Invalid character in the string: %c\n", digit);
            exit(EXIT_FAILURE);
        }

        result = result * 16 + value;

        hexString++;
    }

    if (isNegative)
    {
        result = -result;
    }

    return result;
}

//函数功能: 数组成员翻转函数
//
//参数:		Buf[in]	输入数据
//			Len[in]	数据长度
//返回值: 	无
//		   
//备注:   	
//-----------------------------------------------
void lib_InverseData( BYTE *Tem_Buf, WORD Len )
{
    WORD i = 0;
    WORD Temp08 = 0;
    WORD* Buf = 0;

    Buf = (WORD*)Tem_Buf;

    for (i = 0; i < Len / 4; i++)
	{
		Temp08 = Buf[i];
		Buf[i] = Buf[Len/2-1-i];
		Buf[Len/2-1-i] = Temp08;//交换数据
	}
}

void reverseAndConvert(BYTE* input, DWORD* output, WORD Len)
{
   
    lib_InverseData(input, Len);
    
    //*output = strtol(input, NULL, 16); // 将字符串转换为数值 
    *output = hexStringToDecimal(input);
}

int main()
{
    FILE* inputFile, * outputFile;
    BYTE line[MAX_LINE_LENGTH+1] = { 0 };
    DWORD reversedData = 0;
    BYTE i = 0;
    BYTE Bytes[Len_Now+1] = { 0 };
   
    if ((inputFile = fopen("input.csv", "r")) == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    if ((outputFile = fopen("output.csv", "w")) == NULL)
    {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    for (i = 0; i < NUM_ROWS; i++)
    {
        if (fgets(line, sizeof(line), inputFile) != NULL)
        {
            
            if (line[0] == '\n')
            {
                i--;
            }
            else
            {
                memcpy(Bytes, line + 396, Len_Now);//每次都要修改

                Bytes[Len_Now] = '\0';
                reverseAndConvert(Bytes, &reversedData, Len_Now);
                
                //fprintf(outputFile, "%u\n", reversedData);
                fprintf(outputFile, "%ld\n", reversedData);
                
            }

        }
        else
        {
            fprintf(stderr, "Error reading line %d from input file\n", i + 1);
            break;
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Results saved to output.csv\n");

    return 0;

}
