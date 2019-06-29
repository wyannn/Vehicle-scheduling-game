#include "Graph.hpp"

Graph::Graph(map<int, vector<int>> CROSS,map<int, vector<int>> ROADS,int point_num,int road_num)
{
	m_vcount = point_num;
	m_ecount = road_num;
	for (auto it = CROSS.begin(); it != CROSS.end(); it++)
	{
		AddVertex(it->first);
	}
	for (auto it = ROADS.begin(); it != ROADS.end(); it++)
	{
		//           from            to         id        length       isDuplex
		AddEdge(it->second[3],it->second[4],it->first,it->second[0],it->second[5]);
	}
}

// ��Ӷ���
int Graph::AddVertex(int Corss_id)
{
  m_vertices[Corss_id].push_back(0);
  ++m_vcount;
  return 0;
}

int Graph::AddEdge(const int Start_cross_id, const int End_cross_id,int road_id,int road_length,int isDuplex)
{
  std::vector<int>::iterator it;
  if(*(m_vertices[Start_cross_id].begin()) == 0)
  {
	  m_vertices[Start_cross_id].erase(m_vertices[Start_cross_id].begin());
	  m_vertices[Start_cross_id].push_back(End_cross_id);
  }
  else
  {
	  m_vertices[Start_cross_id].push_back(End_cross_id);
  }
  m_edge[Start_cross_id].push_back(road_id);
  m_edge_weights[Start_cross_id].push_back(road_length);
  if(isDuplex == 1)
  {
	  if(*(m_vertices[End_cross_id].begin()) == 0)
	  {
		  m_vertices[End_cross_id].erase(m_vertices[End_cross_id].begin());
		  m_vertices[End_cross_id].push_back(Start_cross_id);
	  }
	  else
	  {
		  m_vertices[End_cross_id].push_back(Start_cross_id);
	  }
	  m_edge[End_cross_id].push_back(road_id);
	  m_edge_weights[End_cross_id].push_back(road_length);
  }
  ++m_ecount;
  return 0;
}


/*// ɾ������
int Graph::RemoveVertex(int delPoint_id)
{
  if (delPoint_id > (int)(m_vertices.size())) {
    return -1;
  }
  // ����ͼ��Ѱ���붥�����صı�
  // ����ͼ���йصı�һ���ڸö�����ڽӹ�ϵ��
  if (!m_directed)
  {
    int e = m_vertices[delPoint_id].size();
    m_vertices.erase(m_vertices.begin() + delPoint_id);
    m_ecount -= e;
    --m_vcount;
    return 0;
  }
  else
  {
    // ����ͼ
    for (unsigned int i = 0; i < m_vertices.size(); ++i)
	{
      RemoveEdge(i, u);
    }
    m_vertices.erase(m_vertices.begin() + u);
    --m_vcount;
    return 0;
  }
  return -1;
}*/

/*
// ɾ����
int Graph::RemoveEdge(const int &u, const int &v)
{
  auto it_find = m_vertices[u].find(v);
  if (it_find != m_vertices[u].end()) {
    m_vertices[u].erase(v);
    --m_ecount;
  } else {
    return -1;
  }
  if (m_directed) { return 0; }
  // ����ͼɾ�������
  it_find = m_vertices[v].find(u);
  if (it_find != m_vertices[u].end()) {
    m_vertices[v].erase(u);
  } else {
    // �˺���֮��������أ�
    return -1;
  }
  return 0;
}

// �����������֮���Ƿ����ڽӹ�ϵ
bool Graph::IsAdjacent(const int &u, const int &v) {
  if (m_vertices[u].count(v) == 1) {
    return true;
  }
  return false;
}*/

