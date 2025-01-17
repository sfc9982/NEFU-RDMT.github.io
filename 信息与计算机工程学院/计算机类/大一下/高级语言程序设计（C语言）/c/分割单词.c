#include <stdio.h>
#include <stdlib.h>
/*程序思路：
S1:循环获取一行字符存入数组a，如果获取成功，执行S2~S5.
     用while(gets(a)!=NULL)即可实现。
S2：查找英文句子最后的结束字符(. ? !)
     用char * 变量p访问数组a，即(p=a)开始,p++ 直到*p=='.' 或者 *p=='?' *p=='！'; 程序以下两种方法都可以实现
     (1)  p=a;
          while(*p!='.' && *p!='?' && *p!='!') p++;
          c=*p;
     (2)p=a;
        while(*p!='\0')
         {
          if(*p=='.' || *p=='?' || *p=='!') break;
          p++;
         }
         c=*p;
S3：分割单词，存入入words二维数组。
     这部分功能比较复杂，可继续进行设计。基本思路是，用指针p访问数组a中元素，从a开始，到指向\0。
     如果是字母，则说明是单词的一部分，就存入words数组。
     存入的方法为，用row（int）来表示正在处理的是第几个单词，第0个单词存入words第0行，第1个单词存入第1行。
     因此，当p指向字符为字母时，放入word[row]行，列表用j表示，即存入words[row][j].j从0开始。每存入一个字母，j++。
     当p指向字符不是字母时，需要判断是否为单词的结束（就是p指向的不是字母字符，p指向的不是第一个字符且p-1指向的是字母字符）。
     如果是，需要结束当前第row个字符的输入，也就是需要封边（\0），row++，j=0。
     由于本题目中字符串用. ! ?结束，因此不需要考虑\0前没有非字母字符时最后一个单词的处理问题。

       因为经常要判断一个字符是否为单词组成字符，而如果每次都用*p>='A' && *p<='Z' || *p>='a' && *p<='z' 来判断，太麻烦了。因此，可以写
       一个函数isalpha来完成判断一个字符是否为字母的功能。

       如果理解上面的判断单词结束的方法太困难，可以增加一个变量is_word表示当前是否正在处理单词的输入。初始值为0，遇到字母时，改为1
     ，遇到非字母字符时，设置为0.这样当出现两个连续空格时，由于第一个空格时已经把is_word改为0，在判断是否单词结束时就只需要判断
     is_word是否为1就可以了。

S4：逆序输出words二维数组中的各行单词。可用j来作为循环变量。
     （1）j从row-1到1，循环输出单词word[j]后，输出空格。
     （2）输出最后一个单词
     for(j=row-1;j>=1;j--) printf("%s ",word[j]);
     printf("%s",word[0]);
S5：输出结尾的字符和回车。
     printf("%c\n",c);
*/

int isalpha(char a)
{
    //判断字符a是否为单词中的字符，注意本题目中'也是单词的一部分，如it's是一个单词。因此，把它也作为字母处理了。正常情况下用下面语句来实现：
        //return a>='a' && a<='z' || a>='A' && a<='Z' || a=='\'' || a=='‘';

    //但是本题目中测试例子中存在一个中文状态下的单引号，这个单引号是用两个字符来表示的，因此直接用上面这样处理不可以。
    //可以转换为用如下方法： 不是分割字符，不是结束字符就是单词组成
    return (a!=' ' && a!='\t' && a!='\0' && a!='\r' && a!='.' && a!='?' && a!='!');
}
int main(int argc,char * argv[])
{
    char a[1000],words[500][50],*p,c;
    int j,row,is_word;
    printf("Enter a sentence: ");
    while(gets(a)!=NULL)
    {
        p=a;
        j=0;
        row=0;
        is_word=0;
        //查找英文句子的结束字符  . ? !
        while(*p!='.' && *p!='?' && *p!='!') p++;
        c=*p;
        //分割单词
        p=a;
        while( *p!='\0'  && *p!='\r')
        {
            if(isalpha(*p))  //字母
            {
                words[row][j]=*p;
                j++;
                is_word=1;  //表示正在处理一个单词
            }
            else
            {
                //is_word为1表示正在处理单词，因此，当前位置是一个单词的结束

                if(is_word==1)//也可以用if( p!=a &&  isalpha(*(p-1))==0 )
                {
                    words[row][j]='\0';
                    j=0;
                    row++;
                    is_word=0;  //表示当前单词处理完毕，这样如果后面再遇到连续的空格时，is_word==0表示当前没有处理单词，也就不是单词结束
                }
            }
            p++;

        }
        //输出处理的单词。
        printf("Reversal of sentence: ");
        for(j=row-1; j>=1; j--) printf("%s ",words[j]);
        printf("%s",words[0]);
        //输出结尾字符，并换行，这样一组数据的输出占一行。
        printf("%c\n",c);
    }
    return 0;
}
