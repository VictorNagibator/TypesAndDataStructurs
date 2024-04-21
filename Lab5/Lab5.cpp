#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <windows.h>

using namespace std;

//��������� ��� ����������� ������������� (����� �� ����������)
const int INF = INT_MAX;

//������� ��� ������ ����� �� �����
vector<vector<int>> readGraph(const string& filename) {
    ifstream file(filename); 
    if (!file.is_open()) {
        cout << "������ �������� �����!" << endl; 
        exit(1);
    }

    int numVertices;
    file >> numVertices;
    //��������������� ������� ��������� ��� ����������� �����
    vector<vector<int>> graph(numVertices, vector<int>(numVertices));

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; ++j) {
            file >> graph[i][j];

            //���� ��� ����� ����� 0, ������� ��� ��� ����������� � �������� �� INF
            if (graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }
    }

    file.close(); 
    return graph; 
}

//������� ��� ���������� ����������� ���� � ����� ����� ��������� start � end
pair<int, vector<int>> findShortestPath(const vector<vector<int>>& graph, int start, int end) {
    int numVertices = graph.size();

    //�������������� ������ ����������
    vector<int> dist(numVertices, INF);
    //�������������� ������ ������� ��� ������
    vector<int> parent(numVertices, -1);
    //�������������� ������ ���������� ������
    vector<bool> visited(numVertices, false);

    //������� ������������ ������� ��� �������� ��� (����������, �������)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start }); //��������� ��������� ������� � �������
    dist[start] = 0; //���������� �� ��������� ������� ����� 0

    //�������� ���� ��������� ��������
    while (!pq.empty()) {
        int u = pq.top().second; //��������� ������� � ���������� ����������� �� �������
        pq.pop();

        if (u == end) break; //����� �������� ��������, ����� ���������� �������� �������

        if (visited[u]) continue; //���� ������� ��� ��������, ���������� ��

        visited[u] = true; //�������� ������� ��� ����������

        //��������� ���������� �� �������� ������
        for (int v = 0; v < numVertices; ++v) {
            if (graph[u][v] != INF && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v]; //��������� ����������
                parent[v] = u; //���������� ������ �������
                pq.push({ dist[v], v }); //��������� ������� � �������
            }
        }
    }

    //��������������� ���� �� end �� start
    vector<int> path;
    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end()); //�������������� ����, ����� �� ��� �� start � end

    return make_pair(dist[end], path); //���������� ����� ����������� ���� � ��� ����
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 

    vector<vector<int>> graph = readGraph("input.dat");
    int numVertices = graph.size();

    int start, end;
    cout << "������� ��������� � �������� �������: ";
    cin >> start >> end;
    if (start > numVertices || start <= 0 || end >= numVertices || end <= 0) {
        cout << "������������ �������!" << endl;
        return 1;
    }

    //������� ���������� ����
    pair<int, vector<int>> shortestPathData = findShortestPath(graph, start - 1, end - 1);
    int shortestPathLength = shortestPathData.first;
    vector<int> shortestPath = shortestPathData.second;

    //������� ���������� �� ����� � � ����
    ofstream outFile("output.dat");
    if (!outFile.is_open()) {
        cout << "������ �������� ����� ��� ������ �����������!" << endl;
        return 1;
    }

    cout << "���������� ���� ����� ��������� " << start << " � " << end << ": ";
    outFile << "���������� ���� ����� ��������� " << start << " � " << end << ": ";
    for (int v : shortestPath) {
        cout << v + 1;
        outFile << v + 1;
        if (v != shortestPath.back()) {
            cout << " -> ";
            outFile << " -> ";
        }
    }
    cout << endl;
    outFile << endl;

    cout << "����� ����������� ����: " << shortestPathLength << endl;
    outFile << "����� ����������� ����: " << shortestPathLength << endl;

    outFile.close();

    return 0; 
}