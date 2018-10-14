#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    memset(express,0,200*sizeof(char));
    len=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Num1_clicked()
{
    express[len++]='1';
    ui->express->setText(this->express);
}

void MainWindow::on_Num2_clicked()
{
    express[len++]='2';
    ui->express->setText(this->express);
}

void MainWindow::on_Num3_clicked()
{
    express[len++]='3';
    ui->express->setText(this->express);
}

void MainWindow::on_Num4_clicked()
{
    express[len++]='4';
    ui->express->setText(this->express);
}

void MainWindow::on_Num5_clicked()
{
    express[len++]='5';
    ui->express->setText(this->express);
}

void MainWindow::on_Num6_clicked()
{
    express[len++]='6';
    ui->express->setText(this->express);
}

void MainWindow::on_Num7_clicked()
{
    express[len++]='7';
    ui->express->setText(this->express);
}

void MainWindow::on_Num8_clicked()
{
    express[len++]='8';
    ui->express->setText(this->express);
}

void MainWindow::on_Num9_clicked()
{
    express[len++]='9';
    ui->express->setText(this->express);
}

void MainWindow::on_sum_clicked()
{
    express[len++]='+';
    ui->express->setText(this->express);
}

void MainWindow::on_minus_clicked()
{
    express[len++]='-';
    ui->express->setText(this->express);
}

void MainWindow::on_product_clicked()
{
    express[len++]='*';
    ui->express->setText(this->express);
}

void MainWindow::on_devide_clicked()
{
    express[len++]='/';
    ui->express->setText(this->express);
}

void MainWindow::on_equal_clicked()
{
    char express_copy[200];
    strcpy(express_copy,this->express);
    this->driver();
    if(this->error)
    {
        ui->answer->setText("Wrong express");
    }
    else
    {
        char ans[200]={0};
        sprintf(ans,"%lf",this->result);
        int Len=strlen(ans);
        for(int i=Len-1;i>0;i--)
        {
            if(ans[i]=='0')
            {
                ans[i]='\0';
            }
            else if(ans[i]=='.')
            {
                ans[i]='\0';
                break;
            }
            else
                break;
        }
        ui->answer->setText(ans);
    }
    ui->express->setText(express_copy);
    memset(this->express,0,sizeof(char)*200);
    this->len=0;
}

void MainWindow::on_right_clicked()
{
    express[len++]=')';
    ui->express->setText(this->express);
}

void MainWindow::on_left_clicked()
{
    express[len++]='(';
    ui->express->setText(this->express);
}

void MainWindow::on_Num0_clicked()
{
    express[len++]='0';
    ui->express->setText(this->express);
}



void MainWindow::on_exp_clicked()
{
    express[len++]='^';
    ui->express->setText(this->express);
}

void MainWindow::on_delete_2_clicked()
{
    express[--len]='\0';
    ui->express->setText(this->express);
}

void MainWindow::on_clear_clicked()
{
    memset(this->express,0,sizeof(char)*200);
    this->len=0;
    ui->express->setText("express");
}

void MainWindow::driver()
{
    stack<char> Operator;//操作符栈
    stack<double> Operand;//操作数栈
    char infix[maxn][25];//分割后的中缀表达式
    char postfix[maxn][25];//后缀表达式
    int InfixNum = split(infix);
    int PostfixNum=infix2postfix(infix, Operator, postfix, InfixNum);
    calculate(postfix, PostfixNum, Operand);
}

int MainWindow::split(char infix[][25])
{
    int count = 0;
    int j=0;//infix数组的下标
    for(int i=0;i<len;i++)
        if(express[i]=='+'&&express[i+1]=='+')
        {
            express[i]='#';
            express[i+1]=' ';
        }
        else if(express[i]=='-'&&express[i+1]=='-')
        {
            express[i]='@';
            express[i+1]=' ';
        }
    for (int i = 0; i < len; i++)
    {
        if (express[i] >= '0'&&express[i] <= '9')
        {
            count++;
        }
        else
        {
            if (count)
            {
                strncpy(infix[j], express + i - count, count);
                infix[j++][count] = '\0';
                count = 0;
            }
            strncpy(infix[j], express + i, 1);
            infix[j++][1] = '\0';
        }
    }
    if (count)
    {
        strncpy(infix[j], express + len - count, count);
        infix[j++][count] = '\0';
    }
    return j;//返回分割的项数
}

int MainWindow::infix2postfix(char infix[][25], stack<char>& Operator, char postfix[][25], int InfixNum)
{
    int j = 0;//后缀表达式下标
    for (int i = 0; i < InfixNum; i++)
    {
        if (infix[i][0] >= '0'&&infix[i][0] <= '9')//操作数
        {
            strcpy(postfix[j++], infix[i]);
        }
        else if(infix[i][0]==')')//右括号
        {
            while (Operator.top() != '(')//弹出元素直到遇到对应的左括号
            {
                postfix[j][0] = Operator.top();
                postfix[j++][1] = '\0';
                Operator.pop();
            }
            Operator.pop();//弹出左括号
        }
        else//其他
        {
            char temp = infix[i][0];
            //从栈中弹出元素直到遇到优先级更低的元素或者左括号
            while (!Operator.IsEmpty() && Operator.top()!='('&& priority[Operator.top()] >= priority[temp])
            {
                postfix[j][0] = Operator.top();
                postfix[j++][1] = '\0';
                Operator.pop();
            }
            Operator.push(temp);//将当期操作符进栈
        }
    }
    while (!Operator.IsEmpty())//弹出剩余元素
    {
        postfix[j][0] = Operator.top();
        postfix[j++][1] = '\0';
        Operator.pop();
    }
    return j;//返回后缀表达式项数
}

void MainWindow::calculate(char postfix[][25], int PostfixNum, stack<double>& Operand)
{
    for (int i = 0; i < PostfixNum; i++)
    {
        if(postfix[i][0]==' ')
        {
            continue;
        }
        else if (postfix[i][0] >= '0'&&postfix[i][0] <= '9')//遇到数字直接入栈
        {
            Operand.push(atoi(postfix[i]));
        }
        else//遇到运算符弹出两个操作数，计算后将结果入栈
        {
            double operand1,operand2;
            if(!Operand.IsEmpty())
            {
                operand1 = Operand.top();
                Operand.pop();
            }
            else
            {
                this->error=1;
                return;
            }
            if(postfix[i][0]=='#')
            {
                Operand.push(operand1+1);
                continue;
            }
            else if(postfix[i][0]=='@')
            {
                Operand.push(operand1-1);
                continue;
            }
            if(!Operand.IsEmpty())
            {
                operand2 = Operand.top();
                Operand.pop();
            }
            else
            {
                this->error=1;
                return;
            }
            if (postfix[i][0] == '+')
            {
                Operand.push(operand1 + operand2);
            }
            else if (postfix[i][0] == '*')
            {
                Operand.push(operand1*operand2);
            }
            else if (postfix[i][0] == '-')
            {
                Operand.push(operand2-operand1);
            }
            else if (postfix[i][0] == '/')
            {
                if (fabs(operand1) < 0.00001)
                {
                    qDebug() << "Wrong express!" << endl;
                    this->error= 1;//返回表达式错误
                    return;
                }
                else
                Operand.push(operand2/operand1);
            }
            else if (postfix[i][0] == '^')
            {
                Operand.push(pow(operand2,operand1));
            }
        }
    }
    result = Operand.top();//运算结果为栈顶元素
    Operand.pop();
    if(Operand.IsEmpty())
    {
        this->error= 0;
    }
    else
    {
        this->error=1;
        return;
    }
}
