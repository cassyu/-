// Arithmetic.cpp : 定义控制台应用程序的入口点。
//

/************************************************
*  农夫过河问题（P64 队列的应用）
*  约定：用四位二进制数分别顺序表示农夫、狼、白菜和羊的状态
*     即：{dddd} <= > {Farmer, Wolf, Cabbage, Goat} 其中：d = {0, 1}
*说明：0表示在东岸 1表示在西岸，初始状态为0000，终止状态为1111
************************************************ /

-------------------- -
作者：尼奥普兰
来源：CSDN
原文：https ://blog.csdn.net/u011889952/article/details/44805069 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
#include "stdafx.h"
#include "Framer.h"


int main()
{
    // 记录已经探测状态及转移路径，初始化为-1
    vector<int> path( 16, -1 );

    FramerWorker fro;
    fro.findRoute( path );
    fro.displayRoute( path );
    system( "pause" );
    return 0;
}

