//银行家算法
#include <iostream>
#include <fstream>
#define n 5 //进程个数
#define m 3 //资源种类
using namespace std;
void input();        //输入参数
void infile();       //文件输入
int t_input(int *r); //当前请求
bool check();        //检测安全状态
int Available[m], Alloc[n][m], Need[n][m];
//Available:当前可用资源,Alloc:已使用资源,Need：资源需求
int re[n]; //记录结果
int main()
{
    int request[m]; //请求资源
    int ch;
    cout << "【1】手动输入数据；" << endl;
    cout << "【2】从文件中读取数据。" << endl;
    cout << "请选择：";
    cin >> ch;
    if (ch == 1)
        input();
    else if (ch == 2)
        infile();
    else
    {
        cout << "选择错误，自动选择从文件中读取。" << endl;
        infile();
    }
label:
    int p = t_input(request);
    while (1)
    {
        int q = 0;
        //检测非法请求
        for (q = 0; q < m; q++)
            if (!(request[q] <= Need[p][q])) //非法请求
            {
                cout << "非法请求! 请选择：" << endl
                     << "[1]重新输入" << endl
                     << "[2]退出程序" << endl;
                int p;
                cin >> p;
                if (p == 1)
                    goto label;
                else if (p == 2)
                    return 0;
                else
                {
                    cout << "非法选择！强制退出！";
                }
            }
        //检测阻塞
        for (q = 0; q < m; q++)
            if (!(request[q] <= Available[q]))
            {
                cout << "不能满足当前分配!" << endl;
                system("pause");
                goto label;
            }
        for (q = 0; q < m; q++)
        {
            Available[q] -= request[q];
            Alloc[p][q] += request[q];
            Need[p][q] -= request[q];
        }
        bool r = check();
        if (r)
        {
            cout << "可满足当前分配." << endl;
            cout << "安全序列为：";
            for (int i = 0; i < n; i++)
                cout << re[i] + 1 << '\t';
            cout << endl;
            system("pause");
            goto label;
        }
        else
        {
            cout << "不能满足当前分配!" << endl;
            system("pause");
            goto label;
        }
    }
    system("pause");
    return 0;
}
void infile()
{
    ifstream infile;
    infile.open("banktext.txt");
    if (!infile.is_open())
    {
        cout << "文件读取错误!";
        exit(1);
    }
    int k = 0;
    while (k < 12)
    {
        k++;
        for (int i = 0; i < n && (k < 6); i++, k++)
        {
            for (int j = 0; j < m; j++)
                infile >> Alloc[i][j];
        }
        for (int i = 0; i < n && (k > 5 && k < 11); i++, k++)
        {
            for (int j = 0; j < m; j++)
                infile >> Need[i][j];
        }
        for (int i = 0; i < m && k == 11; i++)
            infile >> Available[i];
    }
}
bool check()
{
    bool Finish[n];
    for (int i = 0; i < n; i++)
        Finish[i] = 0;
    int *work = Available;
    int t = 0;
    int i = 0, j = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            if (Finish[i] == 0 && Need[i][j] <= work[j])
            {
                continue;
                //     Finish[i] = 1;
                //     work[j] += Alloc[i][j];
                //     re[t] = i;
                //     t++;
                //     i = 0;
            }
            else
                break;
        if (j == m)
        {
            Finish[i] = 1;
            for (j = 0; j < m; j++)
                work[j] += Alloc[i][j];
            re[t] = i;
            t++;
            i = -1;
        }
    }
    for (int i = 0; i < n; i++)
        if (Finish[i] == 0)
            return 0;
    return 1;
}
int t_input(int *r)
{
    int p;
    cout << "请输入请求资源的进程的编号（如进程P2则输入2）：" << endl;
    cin >> p;
    char t = 'A';
    cout << "请分别输入对各资源的请求数量：" << endl;
    for (int i = 0; i < m; i++, t++)
    {
        cout << t << '\t';
        cin >> r[i];
    }
    return p - 1;
}
void input()
{
    char t = 'A';
    cout << "请输入当前可利用资源数量:" << endl;
    for (int i = 0; i < m; i++)
    {
        cout << t << '\t';
        cin >> Available[i];
        t++;
    }
    cout << "请输入当前已分配资源的数量：" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << 'P' << i + 1 << ':' << endl;
        t = 'A';
        for (int j = 0; j < m; j++, t++)
        {
            cout << t << '\t';
            cin >> Alloc[i][j];
        }
    }
    cout << "请输入当前的资源需求量：" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << 'P' << i + 1 << ':' << endl;
        t = 'A';
        for (int j = 0; j < m; j++, t++)
        {
            cout << t << '\t';
            cin >> Need[i][j];
        }
    }
}