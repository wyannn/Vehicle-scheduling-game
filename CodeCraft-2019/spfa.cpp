#include "spfa.hpp"

bool spfa(int begin, int target, map<int, vector<Edge>> &adj_list, map<int, int> &dist, map<int, int> &path)
{
	const int &INF = 0x7FFFFFFF, &NODE_NUM = adj_list.size();//用邻接表的大小传递顶点个数，减少参数传递
	deque<int> que(1, begin);//处理队列
	map<int, bool> flag;//标志数组，判断是否在队列中
	map<int, int> count;//记录各点入队次数，用于判断负权回路
	dist[begin] = 0;//出发点到自身路径长度为0
	++count[begin];//开始计数
	flag[begin] = 1;//入队
	while(!que.empty())
	{
		const int now = que.front();//当前处理的点，由于后面被删除，不可定义成常量引用
		que.pop_front();
		if (now == target)
			break;
		else
		{
			flag[now] = 0;//将该点拿出队列
			for(unsigned int i = 0; i < adj_list[now].size(); i++)//遍历所有与当前点有路径的点
			{
				const int &next = adj_list[now][i].to;//目标点，不妨定义成常量引用，稍稍快些
				if(dist[now] < INF && dist[next] > dist[now] + adj_list[now][i].weight)//优于当前值
				{
					dist[next] = dist[now] + adj_list[now][i].weight;//更新
					path[next] = now;//记录路径
					if(!flag[next])//若未在处理队列中
					{
						if(++count[next] == NODE_NUM) return 1;//计数后出现负权回路
						if(que.empty() || dist[next] < dist[que.front()])
							que.push_front(next);//放在队首
						else
							que.push_back(next);//否则放在队尾
						flag[next] = 1;//入队
					}
				}
			}
		}
	}
	return 0;
}