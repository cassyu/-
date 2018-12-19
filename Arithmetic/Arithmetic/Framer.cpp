#include "stdafx.h"
#include "Framer.h"


bool FramerWorker::is_safe( const bitvec& state )
{
    //��԰ײ�
    if( state[cabbage] == state[goat] && state[farmer] != state[goat] )
        return false;

    // �ǳ���
    if( ( state[goat] == state[wolf] ) && ( state[farmer] != state[wolf] ) )
        return false;

    return true;
}

// �жϴ����ӵĶ����Ƿ���ũ���ںӵ�ͬһ��
// stateΪ��ǰ״̬
bool FramerWorker::withFarmer( int wader, bitvec& state )
{
    return ( state[farmer] == state[wader] );
}

void FramerWorker::findRoute( vector<int>& paty )
{
    // �����ֵĸ���״̬
    queue<int>  discovering;
    // ���ӵĳ�ʼ״̬Ϊ 0000
    discovering.push(0x00);
    // ��ʼ״̬·����ʼ��
    paty[0] = 0;

    while( !discovering.empty() && ( paty[15] == -1 ) )
    {
        // ��ȡ��ǰ������״̬
        // ��ʽ����ת����int -> bitset<4>
        bitvec curstate = discovering.front();
        // ����Ԫ�ص���
        discovering.pop();
        // ũ�򵽺Ӷ԰�������ũ��Ķ���
        // ���γ����ǡ��ײˡ���
        for( int companion = 0; companion <= 3; ++companion )
        {
            // ��ũ����ӵ�ֻ������ũ����ͬһ�ӱߵ�
            if( withFarmer( companion, curstate ) )
            {
                // ũ����Ӻ����״̬
                bitvec nextstate = curstate;
                // ũ��ض�����
                nextstate.flip(farmer);
                
                // �������ũ�򵥶����ӵ�����
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
    // �����1111��״̬û��ǰ��
    // ��û�ܹ��ɹ�����Ŀ��״̬
    if( path[15] == -1 )
    {
        cout << "�ù���״̬�޽�" << endl;
        return;
    }

    // ��������ʾ��·��ת��Ϊ����ʸ����ʾ��״̬·��
    // �洢״̬·��������
    deque<bitvec>  statePath;
    for( int i = 15; i > 0; i = path[i] )
    {
        statePath.push_front(i);
    }

    // ������룬���·���ӳ�ʼ״̬��Ŀ��״̬��ת��
    // ��ʽ����ת����int -> bitset<4>
    // ����ʼ״̬����

    statePath.push_front( 0 );

    // ��ǰ״̬��������һ״̬������ת������
    bitvec current, next, trans;
    bool crossed = true;
    int step = 1;

    for( unsigned int i = 1; i < statePath.size(); ++i )
    {
        current = statePath[i - 1];
        next = statePath[i];
        // ״̬�����еı仯λ
        trans = current^next;

        // ��ȡ״̬�����仯�Ķ��� 
        int wader = -1;
        for( int i = 0; i <= 2; ++i )
        {
            if( trans.test( i ) )
            {
                wader = i;
                break;
            }
        }

        cout << "����" << step++ << ": ";
        switch( wader )
        {
            case goat:
                cout << "ũ������" << ( crossed ? "���ӱ˰�" : "�غӴ˰�" ) << endl;
                break;
            case cabbage:
                cout << "ũ��Ѱײ˴�" << ( crossed ? "���ӱ˰�" : "�غӴ˰�" ) << endl;
                break;
            case wolf:
                cout << "ũ����Ǵ�" << ( crossed ? "���ӱ˰�" : "�غӴ˰�" ) << endl;
                break;
            case -1:
                cout << "ũ�����" << ( crossed ? "���ӱ˰�" : "�غӴ˰�" ) << endl;
                break;
            default:
                break;
        }
        crossed = !crossed;
    }
    cout << "Congratulations�������������ɹ���" << endl;
}

