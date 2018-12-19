#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <bitset>
#include <deque>

using namespace std;
// ��������ù�����������㷨���ũ���������

// �����ߣ���4�ֶ���
enum Wader
{
    cabbage,
    goat,
    wolf,
    farmer,
};

// ����״̬���ͣ�4bit�ֱ��Ӧ4�ֹ��Ӷ���
typedef bitset<4>  bitvec;

class FramerWorker
{
public:
    //�ж�״̬�Ƿ�ȫ
    bool is_safe(const bitvec& n);
    // �жϴ����ӵĶ����Ƿ���ũ���ںӵ�ͬһ��
    bool withFarmer(int m,bitvec& v);

    void findRoute(vector<int>& paty);

    void displayRoute( const vector<int>& path );
};

