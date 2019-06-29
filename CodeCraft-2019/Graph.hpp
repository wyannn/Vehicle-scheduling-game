#ifndef _GRAPH_H_
#define _GRAPH_H_

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

// 邻接集合
typedef map<int, vector<int>> AdjSet;
typedef map<int, bool>        AdjSet_visit;

class Graph 
{
protected:
 
  AdjSet        m_vertices; // 点邻接表向量
  AdjSet        m_edge; // 边邻接表向量
  AdjSet        m_edge_weights;

  AdjSet        m_next;
  AdjSet        m_d;
  AdjSet_visit  m_visited;

  int           m_vcount;// 顶点数量
  int           m_ecount;// 边的数量

public:

  Graph(map<int, vector<int>> CROSS,map<int, vector<int>> ROADS,int point_num,int road_num);
  virtual ~Graph()
  {
    m_vertices.clear();
    m_vcount = 0;
    m_ecount = 0;
  }
  // 取值函数
  int            vcount() const { return m_vcount;           }
  int            ecount() const { return m_ecount;           }
  AdjSet         next()         { return m_next;             }
  AdjSet         d()            { return m_d;                }
  AdjSet_visit   visited()      { return m_visited;          }
  AdjSet         vertices()     { return m_vertices;         }
  AdjSet         edge_weights() { return m_edge_weights;     }
  AdjSet         edge()         { return m_edge;             }


  int AddEdge(const int Start_cross_id, const int End_cross_id,int road_id,int road_length,int isDuplex);// 添加边
  int AddVertex(int Corss_id);// 添加顶点



}; // class Graph


#endif