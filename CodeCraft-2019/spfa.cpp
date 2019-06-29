#include "spfa.hpp"

bool spfa(int begin, int target, map<int, vector<Edge>> &adj_list, map<int, int> &dist, map<int, int> &path)
{
	const int &INF = 0x7FFFFFFF, &NODE_NUM = adj_list.size();//���ڽӱ�Ĵ�С���ݶ�����������ٲ�������
	deque<int> que(1, begin);//�������
	map<int, bool> flag;//��־���飬�ж��Ƿ��ڶ�����
	map<int, int> count;//��¼������Ӵ����������жϸ�Ȩ��·
	dist[begin] = 0;//�����㵽����·������Ϊ0
	++count[begin];//��ʼ����
	flag[begin] = 1;//���
	while(!que.empty())
	{
		const int now = que.front();//��ǰ����ĵ㣬���ں��汻ɾ�������ɶ���ɳ�������
		que.pop_front();
		if (now == target)
			break;
		else
		{
			flag[now] = 0;//���õ��ó�����
			for(unsigned int i = 0; i < adj_list[now].size(); i++)//���������뵱ǰ����·���ĵ�
			{
				const int &next = adj_list[now][i].to;//Ŀ��㣬��������ɳ������ã����Կ�Щ
				if(dist[now] < INF && dist[next] > dist[now] + adj_list[now][i].weight)//���ڵ�ǰֵ
				{
					dist[next] = dist[now] + adj_list[now][i].weight;//����
					path[next] = now;//��¼·��
					if(!flag[next])//��δ�ڴ��������
					{
						if(++count[next] == NODE_NUM) return 1;//��������ָ�Ȩ��·
						if(que.empty() || dist[next] < dist[que.front()])
							que.push_front(next);//���ڶ���
						else
							que.push_back(next);//������ڶ�β
						flag[next] = 1;//���
					}
				}
			}
		}
	}
	return 0;
}