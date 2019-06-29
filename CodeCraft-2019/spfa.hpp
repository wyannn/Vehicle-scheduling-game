#ifndef _SPFA_H_
#define _SPFA_H_

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

// �����ڽӱ�
struct Edge
{
	int to; // ����Ľڵ�id
	int weight; 
};

bool spfa(int begin, int target, map<int, vector<Edge>> &adj_list, map<int, int> &dist, map<int, int> &path);

#endif