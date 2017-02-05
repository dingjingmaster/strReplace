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

    printf("原来字符串：%s\n", src);
    printf("要替换的字符串：%s\n", sub);
    printf("替换的字符串：%s\n", newSub);
    printf("替换结果：%s\n", dst);
    return 0;
}

int replaceSubstr(/*in*/char *src, /*out*/char** dst, /*in*/char *sub,  /*in*/char *newSub)
{

    if( NULL == src || NULL == sub || NULL == newSub ){

        return -1;
    }

    char* srcBuf       = src;                               //头节点
    char* subBuf       = sub;                               //子字符串

    int subLen         = strlen( sub );                     //要替换字符串的长度
    int newSubLen      = strlen( newSub );                  //替换字符串的长度

    char buf[BUFSIZ]   = {0};
    strcpy(buf, src);
    char* pBuf         = buf;


    //查找字符串所在位置
    while( 1 )
    {
        //如果子串为空则退出
        if( *srcBuf == '\0' )
        {
            //新串替换了旧串, 将结果传出
            *dst = ( char* )malloc( strlen(buf) + 1 );
            memset(*dst, 0, strlen(buf) + 1);
            strncpy(*dst, buf, strlen(buf));
            break;
        }
        //开始查找子串
        if( !strncmp( srcBuf, subBuf, subLen ))                 //找到子串
        {
            //找到子串
            int subSt = subLen - newSubLen;
            if ( subSt > 0 )                                    //子串比新的子串长, 左移差位
            {
                //printf("子串比新的子串长\n");                    //新串短 左移 差值
                //替换
                strncpy(pBuf, newSub, newSubLen);

                //跳过
                srcBuf += subLen;
                pBuf += newSubLen;

                //左移
                char* pTmp = pBuf;
                while(*pTmp != '\0')
                {
                    *pTmp = *(pTmp + subSt);
                    pTmp ++;
                }
                *(pTmp + 1) = '\0';
            }
            else if( subSt < 0 )                                //子串比新的子串短  右移差位
            {
                //printf("子串比新的子串短\n");
                //右移
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

                //替换
                strncpy(pBuf, newSub, newSubLen);

                //跳过
                srcBuf += subLen;
                pBuf += newSubLen;
            }
            else if(subSt == 0)
            {
                //printf("新旧子串一样长\n");
                //替换
                strncpy(pBuf, newSub, newSubLen);

                //跳过
                srcBuf += newSubLen;
                pBuf += newSubLen;
            }
        }
        else
        {
            //没有找到子串
            srcBuf += 1;
            pBuf += 1;
        }


    }
}
