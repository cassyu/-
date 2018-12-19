#include "stdafx.h"
#include "Framer.h"


bool FramerWorker::is_safe( const bitvec& state )
{
    //羊吃白菜
    if( state[cabbage] == state[goat] && state[farmer] != state[goat] )
        return false;

    // 狼吃羊
    if( ( state[goat] == state[wolf] ) && ( state[farmer] != state[wolf] ) )
        return false;

    return true;
}

// 判断待过河的对象是否与农夫在河的同一侧
// state为当前状态
bool FramerWorker::withFarmer( int wader, bitvec& state )
{
    return ( state[farmer] == state[wader] );
}

void FramerWorker::findRoute( vector<int>& paty )
{
    // 待发现的各个状态
    queue<int>  discovering;
    // 过河的初始状态为 0000
    discovering.push(0x00);
    // 初始状态路径初始化
    paty[0] = 0;

    while( !discovering.empty() && ( paty[15] == -1 ) )
    {
        // 获取当前待发现状态
        // 隐式类型转换：int -> bitset<4>
        bitvec curstate = discovering.front();
        // 队首元素弹出
        discovering.pop();
        // 农夫到河对岸，伴随农夫的对象
        // 依次尝试狼、白菜、羊
        for( int companion = 0; companion <= 3; ++companion )
        {
            // 随农夫过河的只能是与农夫在同一河边的
            if( withFarmer( companion, curstate ) )
            {
                // 农夫过河后的新状态
                bitvec nextstate = curstate;
                // 农夫必定过河
                nextstate.flip(farmer);
                
                // 如果不是农夫单独过河的情形
                if( companion != farmer )
                {
                    nextstate.flip( companion );
                }

                int nextindex = nextstate.to_ulong();
                if( is_safe( nextstate ) && ( paty[nextindex] == -1 ) )
                {
                    paty[nextindex] = curstate.to_ulong();
                    discovering.push( nextindex );
                }
            }
        }
    }

}

void FramerWorker::displayRoute( const vector<int>& path )
{
    // 如果“1111”状态没有前驱
    // 则没能够成功到达目的状态
    if( path[15] == -1 )
    {
        cout << "该过河状态无解" << endl;
        return;
    }

    // 将整数表示的路径转换为布尔矢量表示的状态路径
    // 存储状态路径的容器
    deque<bitvec>  statePath;
    for( int i = 15; i > 0; i = path[i] )
    {
        statePath.push_front(i);
    }

    // 反向插入，完成路径从初始状态到目的状态的转换
    // 隐式类型转换：int -> bitset<4>
    // 将初始状态插入

    statePath.push_front( 0 );

    // 当前状态变量、下一状态变量与转换变量
    bitvec current, next, trans;
    bool crossed = true;
    int step = 1;

    for( unsigned int i = 1; i < statePath.size(); ++i )
    {
        current = statePath[i - 1];
        next = statePath[i];
        // 状态变量中的变化位
        trans = current^next;

        // 获取状态发生变化的对象 
        int wader = -1;
        for( int i = 0; i <= 2; ++i )
        {
            if( trans.test( i ) )
            {
                wader = i;
                break;
            }
        }

        cout << "步骤" << step++ << ": ";
        switch( wader )
        {
            case goat:
                cout << "农夫把羊带" << ( crossed ? "到河彼岸" : "回河此岸" ) << endl;
                break;
            case cabbage:
                cout << "农夫把白菜带" << ( crossed ? "到河彼岸" : "回河此岸" ) << endl;
                break;
            case wolf:
                cout << "农夫把狼带" << ( crossed ? "到河彼岸" : "回河此岸" ) << endl;
                break;
            case -1:
                cout << "农夫独自" << ( crossed ? "到河彼岸" : "回河此岸" ) << endl;
                break;
            default:
                break;
        }
        crossed = !crossed;
    }
    cout << "Congratulations！过河问题求解成功！" << endl;
}

