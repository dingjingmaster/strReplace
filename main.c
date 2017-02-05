#include <stdio.h>
#include <string.h>
#include <math.h>

int replaceSubstr(/*in*/char *src, /*out*/char** dst, /*in*/char *sub,  /*in*/char *new_sub);

int main(int argc, char *argv[])
{
    char* src = "2hhh111hhh222";
    char* dst = NULL;
    char* sub = "hhh";
    char* newSub = "jjjj";

    replaceSubstr(/* in char *src */ src,           \
                  /*out char** dst */ &dst,         \
                  /*in char *sub */sub,             \
                  /*in char *newSub */newSub);

    printf("ԭ���ַ�����%s\n", src);
    printf("Ҫ�滻���ַ�����%s\n", sub);
    printf("�滻���ַ�����%s\n", newSub);
    printf("�滻�����%s\n", dst);
    return 0;
}

int replaceSubstr(/*in*/char *src, /*out*/char** dst, /*in*/char *sub,  /*in*/char *newSub)
{

    if( NULL == src || NULL == sub || NULL == newSub ){

        return -1;
    }

    char* srcBuf       = src;                               //ͷ�ڵ�
    char* subBuf       = sub;                               //���ַ���

    int subLen         = strlen( sub );                     //Ҫ�滻�ַ����ĳ���
    int newSubLen      = strlen( newSub );                  //�滻�ַ����ĳ���

    char buf[BUFSIZ]   = {0};
    strcpy(buf, src);
    char* pBuf         = buf;


    //�����ַ�������λ��
    while( 1 )
    {
        //����Ӵ�Ϊ�����˳�
        if( *srcBuf == '\0' )
        {
            //�´��滻�˾ɴ�, ���������
            *dst = ( char* )malloc( strlen(buf) + 1 );
            memset(*dst, 0, strlen(buf) + 1);
            strncpy(*dst, buf, strlen(buf));
            break;
        }
        //��ʼ�����Ӵ�
        if( !strncmp( srcBuf, subBuf, subLen ))                 //�ҵ��Ӵ�
        {
            //�ҵ��Ӵ�
            int subSt = subLen - newSubLen;
            if ( subSt > 0 )                                    //�Ӵ����µ��Ӵ���, ���Ʋ�λ
            {
                //printf("�Ӵ����µ��Ӵ���\n");                    //�´��� ���� ��ֵ
                //�滻
                strncpy(pBuf, newSub, newSubLen);

                //����
                srcBuf += subLen;
                pBuf += newSubLen;

                //����
                char* pTmp = pBuf;
                while(*pTmp != '\0')
                {
                    *pTmp = *(pTmp + subSt);
                    pTmp ++;
                }
                *(pTmp + 1) = '\0';
            }
            else if( subSt < 0 )                                //�Ӵ����µ��Ӵ���  ���Ʋ�λ
            {
                //printf("�Ӵ����µ��Ӵ���\n");
                //����
                subSt = abs(subSt);
                char* pTmp = pBuf;
                while(*pTmp != '\0')
                {
                    pTmp ++;
                }

                while(pTmp != pBuf)
                {
                    *(pTmp + subSt) = *pTmp;
                    pTmp --;
                }

                //�滻
                strncpy(pBuf, newSub, newSubLen);

                //����
                srcBuf += subLen;
                pBuf += newSubLen;
            }
            else if(subSt == 0)
            {
                //printf("�¾��Ӵ�һ����\n");
                //�滻
                strncpy(pBuf, newSub, newSubLen);

                //����
                srcBuf += newSubLen;
                pBuf += newSubLen;
            }
        }
        else
        {
            //û���ҵ��Ӵ�
            srcBuf += 1;
            pBuf += 1;
        }


    }
}
