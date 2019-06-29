#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <fstream>
#include <limits>
#include <queue>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <map>
#include <cmath>

#include "include.hpp"

using namespace std;

void bulid_adj_list(map<int, vector<int>> &ROADS, map<int, vector<Edge>> &adj_list, AdjSet &all_vertices, AdjSet &all_edge, AdjSet &all_edge_weights, map<int, int> &dist, map<int, int> &path, vector<int> &answer, vector<int> &consume_time, int &car_id, int &car_plantime, int &car_to, int &car_speed, int &car_from)
{
	const int &INF = 0x7FFFFFFF;
	// 邻接表: 连接顶点、 权重分配：路长
	answer.clear();
	consume_time.clear();
	answer.push_back(car_plantime);
	answer.push_back(car_to);
	consume_time.push_back(car_plantime);
	for (AdjSet::iterator it_ver = all_vertices.begin(), it_wei = all_edge_weights.begin(), it_edg = all_edge.begin(); it_ver != all_vertices.end() && it_wei != all_edge_weights.end() && it_edg != all_edge.end(); it_ver++, it_wei++, it_edg++)
	{
		int from = it_ver->first;
		dist[from] = INF;
		path[from] = -1; 
		vector<int> to = it_ver->second;
		vector<int> weights = it_wei->second;
		vector<int> edges = it_edg->second;
		vector<Edge> ends;
		for (unsigned int i = 0; i < to.size(); i++)
		{
			Edge end = {to[i], (int)min(ceil(double(weights[i]) / car_speed), ceil(double(weights[i]) / ROADS[edges[i]][1]))};
			ends.push_back(end);
		}
		adj_list[from]= ends;
	}
}

void judge(map<int, vector<int>> &answers, map<int, vector<int>> &consume_times, map<int, vector<vector<int>>> &optimize_cars, const double &limit_rate)
{
	map<int, map<vector<int>, vector<int>>> optimize_roads; // <时间, <<from, to节点id>, <车id>>
	optimize_cars.clear();
	set<int> car_num_in_road;

	for (map<int, vector<int>>::iterator it_time = consume_times.begin(), it_ans = answers.begin(); it_time != consume_times.end() && it_ans != answers.end(); it_time++, it_ans++)
	{
		for (unsigned i = 1; i < it_time->second.size(); i++)
		{
			vector<int> from_to(2, 0);
			from_to[0] = it_ans->second[i];
			from_to[1] = it_ans->second[i + 1];
			optimize_roads[it_time->second[i]][from_to].push_back(it_ans->first);
		}
	}

	// 求 limit_car_num
	for (auto it1 = optimize_roads.begin(); it1 != optimize_roads.end(); it1++)
	{
		for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
		{
			car_num_in_road.insert(int(it2->second.size()));
		}
	}

	auto it = car_num_in_road.begin();
	for (unsigned int i = 0; i < car_num_in_road.size() * limit_rate; i++)
		it++;
	int limit_car_num = *(it);

	// 选择优化的道路（一条路上车的数目超过limit_car_num就优化）
	for (auto it1 = optimize_roads.begin(); it1 != optimize_roads.end();)
	{
		for (auto it2 = it1->second.begin(); it2 != it1->second.end();)
		{
			if (int(it2->second.size()) < limit_car_num)
				it1->second.erase(it2++);
			else
				it2++;
		}
		if (int(it1->second.size()) == 0)
			optimize_roads.erase(it1++);
		else
			it1++;
	}

	// 转换成优化的车辆id
	for (auto it1 = optimize_roads.begin(); it1 != optimize_roads.end(); it1++)
	{
		for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
		{
			vector<int> from_to = it2->first;
			vector<int> car_ids = it2->second;
			for (unsigned int i = 0; i < car_ids.size(); i++)
			{
				optimize_cars[car_ids[i]].push_back(from_to);
			}
		}
	}
}


int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;
	
	if(argc < 5){
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}
	
	std::string carPath(argv[1]);
	std::string roadPath(argv[2]);
	std::string crossPath(argv[3]);
	std::string answerPath(argv[4]);
	
	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;
	
	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	
	
	map<int, vector<int>> CROSS, ROADS, CARS;
	ifstream infile;

	//cross
	string s;
    infile.open(crossPath.data());
    assert(infile.is_open());
    while(getline(infile,s))
    {
        if ((int)s.find('#') != -1)
			continue;
		istringstream ins(s.substr(1, s.size() - 2));	
		string num;
		vector<string> data;
		while (getline(ins, num, ','))
			data.push_back(num);

		CROSS[stoi(data[0])].push_back(stoi(data[1]));
		CROSS[stoi(data[0])].push_back(stoi(data[2]));
		CROSS[stoi(data[0])].push_back(stoi(data[3]));
		CROSS[stoi(data[0])].push_back(stoi(data[4]));
    }
    infile.close();

	//road
    infile.open(roadPath.data());
    assert(infile.is_open());
    while(getline(infile,s))
    {
        if ((int)s.find('#') != -1)
			continue;
		istringstream ins(s.substr(1, s.size() - 2));	
		string num;
		vector<string> data;
		while (getline(ins, num, ','))
			data.push_back(num);

		ROADS[stoi(data[0])].push_back(stoi(data[1]));
		ROADS[stoi(data[0])].push_back(stoi(data[2]));
		ROADS[stoi(data[0])].push_back(stoi(data[3]));
		ROADS[stoi(data[0])].push_back(stoi(data[4]));
		ROADS[stoi(data[0])].push_back(stoi(data[5]));
		ROADS[stoi(data[0])].push_back(stoi(data[6]));
    }
    infile.close();

	//car
    infile.open(carPath.data());
    assert(infile.is_open());
    while(getline(infile,s))
    {
        if ((int)s.find('#') != -1)
			continue;
		istringstream ins(s.substr(1, s.size() - 2));	
		string num;
		vector<string> data;
		while (getline(ins, num, ','))
			data.push_back(num);

		CARS[stoi(data[0])].push_back(stoi(data[1]));
		CARS[stoi(data[0])].push_back(stoi(data[2]));
		CARS[stoi(data[0])].push_back(stoi(data[3]));
		CARS[stoi(data[0])].push_back(stoi(data[4]));
    }
    infile.close();

	Graph    G_init(CROSS,ROADS, 0, 0);

	// 全局初始化，adj_list， dist， path每个车都有一个
	map<int, vector<Edge>> adj_list;
	map<int, int> dist, path;
	map<int, vector<int>> answers;
	map<int, vector<int>> consume_times;

	vector<int> answer;
	vector<int> consume_time;

	AdjSet all_vertices = G_init.vertices();
	AdjSet all_edge = G_init.edge();
	AdjSet all_edge_weights = G_init.edge_weights();

	//求出理想情况下最优路径（每个车单独跑）
	for (map<int, vector<int>>::iterator it_car = CARS.begin(); it_car != CARS.end(); it_car++)
	{
		int car_id = it_car->first, car_from = it_car->second[0], car_to = it_car->second[1], car_speed = it_car->second[2], car_plantime = it_car->second[3];
		bulid_adj_list(ROADS, adj_list, all_vertices, all_edge, all_edge_weights, dist, path, answer, consume_time, car_id, car_plantime, car_to, car_speed, car_from);
		// spfa算法
		bool sign = spfa(car_from, car_to, adj_list, dist, path);
		if (!sign)
		{
			while (answer[answer.size() - 1] != car_from)
			{
				answer.push_back(path[answer[answer.size() - 1]]);
			}
		}
		reverse(answer.begin() + 1, answer.end());
		for (unsigned int i = 1; i < answer.size() - 1; i++)
		{
			for (unsigned int k = 0; k < adj_list[answer[i]].size(); k ++)
			{
				if (adj_list[answer[i]][k].to == answer[i + 1])
				{
					consume_time.push_back(adj_list[answer[i]][k].weight);
				}
			}
		}
		answers[car_id] = answer;
		for (unsigned i = 1; i < consume_time.size(); i++)
			consume_time[i] += consume_time[i - 1];
		consume_times[car_id] = consume_time;
	}


	// 优化2
	//同一时刻 同一条路上有多少车
	map<int, vector<vector<int>>> optimize_cars; //<car_id, road_ids(from_to)>
	map<int, map<vector<int>, vector<int>>> optimize_roads;
	const double &limit_rate = 0.6, &optimize_rate = 0.000001;
	int count = 50;
	while (count--)
	{
		judge(answers, consume_times, optimize_cars, limit_rate);
		if (optimize_cars.size() < answers.size() * optimize_rate)
			break;
		//优化 1重新构建链路表 2使用spfa
		for (auto it = optimize_cars.begin(); it != optimize_cars.end(); it++)
		{
			int car_id = it->first, car_from = CARS[car_id][0], car_to = CARS[car_id][1], car_speed = CARS[car_id][2], car_plantime = CARS[car_id][3];
			vector<vector<int>> from_tos = it->second;
			bulid_adj_list(ROADS, adj_list, all_vertices, all_edge, all_edge_weights, dist, path, answer, consume_time, car_id, car_plantime, car_to, car_speed, car_from);
			for (unsigned int i = 0; i < from_tos.size(); i++)
			{
				for (unsigned j = 0; j < adj_list[from_tos[i][0]].size(); j++)
				{
					if (adj_list[from_tos[i][0]][j].to == from_tos[i][1])
					{
						adj_list[from_tos[i][0]][j].weight *= 2;
						break;
					}
				}
			}
			//spfa
			bool sign = spfa(car_from, car_to, adj_list, dist, path);
			if (!sign)
			{
				while (answer[answer.size() - 1] != car_from)
				{
					answer.push_back(path[answer[answer.size() - 1]]);
				}
			}
			reverse(answer.begin() + 1, answer.end());
			for (unsigned int i = 1; i < answer.size() - 1; i++)
			{
				for (unsigned int k = 0; k < adj_list[answer[i]].size(); k ++)
				{
					if (adj_list[answer[i]][k].to == answer[i + 1])
					{
						consume_time.push_back(adj_list[answer[i]][k].weight);
					}
				}
			}
			answer[0] += 1;
			consume_time[0] += 1;
			answers[car_id] = answer;
			for (unsigned i = 1; i < consume_time.size(); i++)
				consume_time[i] += consume_time[i - 1];
			consume_times[car_id] = consume_time;
		}
	}
	
	// test 1
	/*vector<int> total_order;
	for (auto it = answers.begin(); it != answers.end(); it++)
	{
		total_order.push_back(it->first);
	}*/
	

	// test2
	map<int, vector<int>> time_bach_cars;
	vector<int> total_order;
	for (map<int, vector<int>>::iterator it = consume_times.begin(); it != consume_times.end(); it++)
	{
		time_bach_cars[it->second[0]].push_back(it->first);
	}

	for (map<int, vector<int>>::iterator it = time_bach_cars.begin(); it != time_bach_cars.end(); it++)
	{
		for (unsigned i = 0; i < it->second.size(); i++)
		{
			total_order.push_back(it->second[i]);
		}
	}

	//一次走一批车  test1 + 这个 目前最好
	//int road_num = ROADS.size();
	int add_time = 0, time_step = 80, car_step = 1000;
	for (unsigned i = 0; i < total_order.size() - car_step - 1; i += car_step + 1)
	{
		for (int j = 0; j <= car_step; j++)
		{
			answers[total_order[i + j]][0] += add_time;
		}
		add_time += time_step;
	}

	//将节点转化为路
	for (map<int, vector<int>>::iterator it = answers.begin(); it != answers.end(); it++)
	{
		for (unsigned i = 1; i < it->second.size() - 1; i++)
		{
			for (unsigned j = 0; j < all_vertices[it->second[i]].size(); j++)
			{
				if (all_vertices[it->second[i]][j] == it->second[i + 1])
				{
					it->second[i] = all_edge[it->second[i]][j];
					break;
				}
			}
		}
	}

	//输出
	ofstream outfile;
	outfile.open(answerPath); 
	string comma = ", ";
	for (map<int, vector<int>>::iterator it = answers.begin(); it != answers.end(); it++)
	{
		outfile << '(' << it->first << comma;
		for (unsigned int i = 0; i < it->second.size() - 1; i++)
		{
			if (i == it->second.size() - 2)
				outfile << it->second[i] << ')' << endl;
			else
				outfile << it->second[i] << comma;
		}
	}

	return 0;
}