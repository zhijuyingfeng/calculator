#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstring>
#include <QDebug>
#include "stack.h"
#include <QMap>
#include <cmath>
#include <cstdio>
#include <cstdlib>


const int maxn = 200;
const QMap<char, int> priority = { {'(',4}, {'#',3},{'@',3},{'^',2},{'*',1},{'/',1},{'+',0},{'-',0} };//存储运算符优先级

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Num1_clicked();

    void on_Num2_clicked();

    void on_Num3_clicked();

    void on_Num4_clicked();

    void on_Num5_clicked();

    void on_Num6_clicked();

    void on_Num7_clicked();

    void on_Num8_clicked();

    void on_Num9_clicked();

    void on_sum_clicked();

    void on_minus_clicked();

    void on_product_clicked();

    void on_devide_clicked();

    void on_equal_clicked();

    void on_right_clicked();

    void on_left_clicked();

    void on_Num0_clicked();

    void on_exp_clicked();

    void on_delete_2_clicked();

    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
    char express[200];
    int len;
    double result;
    bool error;

    int split(char infix[][25]);//对表达式进行分割，分离出操作数与操作符
    int infix2postfix(char infix[][25], stack<char>& Operator, char postfix[][25], int InfixNum);//中缀表达式转后缀表达式
    void calculate(char postfix[][25], int PostfixNum, stack<double>& Operand);//对后缀表达式求值
    void driver();//驱动程序
};

#endif // MAINWINDOW_H
