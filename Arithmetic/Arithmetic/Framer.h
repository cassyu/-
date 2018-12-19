#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <bitset>
#include <deque>

using namespace std;
// 本程序采用广度优先搜索算法求解农夫过河问题

// 过河者，共4种对象
enum Wader
{
    cabbage,
    goat,
    wolf,
    farmer,
};

// 过河状态类型，4bit分别对应4种过河对象
typedef bitset<4>  bitvec;

class FramerWorker
{
public:
    //判断状态是否安全
    bool is_safe(const bitvec& n);
    // 判断待过河的对象是否与农夫在河的同一侧
    bool withFarmer(int m,bitvec& v);

    void findRoute(vector<int>& paty);

    void displayRoute( const vector<int>& path );
};

