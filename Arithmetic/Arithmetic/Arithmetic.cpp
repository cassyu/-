// Arithmetic.cpp : �������̨Ӧ�ó������ڵ㡣
//

/************************************************
*  ũ��������⣨P64 ���е�Ӧ�ã�
*  Լ��������λ���������ֱ�˳���ʾũ���ǡ��ײ˺����״̬
*     ����{dddd} <= > {Farmer, Wolf, Cabbage, Goat} ���У�d = {0, 1}
*˵����0��ʾ�ڶ��� 1��ʾ����������ʼ״̬Ϊ0000����ֹ״̬Ϊ1111
************************************************ /

-------------------- -
���ߣ��������
��Դ��CSDN
ԭ�ģ�https ://blog.csdn.net/u011889952/article/details/44805069 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
*/
#include "stdafx.h"
#include "Framer.h"


int main()
{
    // ��¼�Ѿ�̽��״̬��ת��·������ʼ��Ϊ-1
    vector<int> path( 16, -1 );

    FramerWorker fro;
    fro.findRoute( path );
    fro.displayRoute( path );
    system( "pause" );
    return 0;
}

