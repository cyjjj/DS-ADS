#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

/* Your function will be put here */
ElementType num[Max_Expr+1];//������ջ
int Top = -1;

void Push(double Opn)
{
    num[++Top] = Opn;
}

double Pop(void)
{
    if (Top < 0) return Infinity;
    return num[Top--];
}

ElementType EvalPostfix(char *expr)
{
    char b[Max_Expr+1];//�ӱ��ʽ��ȡ�ַ�
    int i = 0, p = 0;
    double m, n;

    while(expr[i] != '\0'){
        int j = 0;
        if(expr[i] == ' ') i++;//�����ո�
        while((expr[i]=='.') || (expr[i]<='9'&&expr[i]>='0') 
        || (expr[i]=='-'&&(expr[i+1]!=' '&&expr[i+1]!='\0'))){
            b[j] = expr[i];
            j++;
            i++;
        }//��ȡ�ַ���������b��
        if(expr[i]==' ' || (Top<0&&expr[i+1]=='\0')) {
            Push(atof(b));
            while(b[p]){
                b[p] = '\0';
                p++;
            }
            p = 0;
            i++;
        }//��������ת����charת��Ϊdouble
        else if(expr[i]!=' '&&(expr[i]>'9'||expr[i]<'0')
        &&(expr[i+1]==' '||expr[i+1]=='\0')){
            m = Pop();
            n = Pop();
            if(m == Infinity || n == Infinity)
                return Infinity;
            switch(expr[i]){
                case '+':
                    Push(m + n);
                    break;
                case '-':
                    Push(n - m);
                    break;
                case '*':
                    Push(m * n);
                    break;
                case '/':
                    if (m == 0)
                        return Infinity;
                    Push(n / m);
                    break;
                default:
                    break;
            }
            i++;
        }//����
    }
    if(Top < 0) return Infinity;//Ϊ��

    return Pop();
}
