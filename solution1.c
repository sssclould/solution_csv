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
#define Len_Now 4


//��������: �����Ա��ת����
//
//����:		Buf[in]	��������
//			Len[in]	���ݳ���
//����ֵ: 	��
//		   
//��ע:   	
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
		Buf[Len/2-1-i] = Temp08;//��������
	}
}

void reverseAndConvert(BYTE* input, DWORD* output, WORD Len)
{
   
    lib_InverseData(input, Len);
    
    *output = strtol(input, NULL, 16); // ���ַ���ת��Ϊ��ֵ 
   
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
                
                memcpy(Bytes, line+416, Len_Now);//ÿ�ζ�Ҫ�޸�
                Bytes[Len_Now] = '\0';

                reverseAndConvert(Bytes, &reversedData, Len_Now);
                
                fprintf(outputFile, "%u", reversedData);
                //////////////////////////////////////////////////////////������ʵ���˶��д洢
                memcpy(Bytes, line + 404, Len_Now);//ÿ�ζ�Ҫ�޸�
                Bytes[Len_Now] = '\0';

                reverseAndConvert(Bytes, &reversedData, Len_Now);
                fprintf(outputFile, ",%u", reversedData);

                fprintf(outputFile, "\n");

                
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
