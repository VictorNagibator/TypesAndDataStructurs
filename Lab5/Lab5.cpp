#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <windows.h>

using namespace std;

//Константа для обозначения бесконечности (ребра не существует)
const int INF = INT_MAX;

//Функция для чтения графа из файла
vector<vector<int>> readGraph(const string& filename) {
    ifstream file(filename); 
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl; 
        exit(1);
    }

    int numVertices;
    file >> numVertices;
    //Непосредственно матрица смежности для взвешенного графа
    vector<vector<int>> graph(numVertices, vector<int>(numVertices));

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; ++j) {
            file >> graph[i][j];

            //Если вес ребра равен 0, считаем это его отсутствием и заменяем на INF
            if (graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }
    }

    file.close(); 
    return graph; 
}

//Функция для нахождения кратчайшего пути в графе между вершинами start и end
pair<int, vector<int>> findShortestPath(const vector<vector<int>>& graph, int start, int end) {
    int numVertices = graph.size();

    //Инициализируем вектор расстояний
    vector<int> dist(numVertices, INF);
    //Инициализируем вектор предков для вершин
    vector<int> parent(numVertices, -1);
    //Инициализируем вектор посещенных вершин
    vector<bool> visited(numVertices, false);

    //Создаем приоритетную очередь для хранения пар (расстояние, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start }); //Добавляем начальную вершину в очередь
    dist[start] = 0; //Расстояние до начальной вершины равно 0

    //Основной цикл алгоритма Дейкстры
    while (!pq.empty()) {
        int u = pq.top().second; //Извлекаем вершину с наименьшим расстоянием из очереди
        pq.pop();

        if (u == end) break; //Можно прервать алгоритм, когда достигнута конечная вершина

        if (visited[u]) continue; //Если вершина уже посещена, пропускаем ее

        visited[u] = true; //Помечаем вершину как посещенную

        //Обновляем расстояния до соседних вершин
        for (int v = 0; v < numVertices; ++v) {
            if (graph[u][v] != INF && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v]; //Обновляем расстояние
                parent[v] = u; //Запоминаем предка вершины
                pq.push({ dist[v], v }); //Добавляем вершину в очередь
            }
        }
    }

    //Восстанавливаем путь от end до start
    vector<int> path;
    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end()); //Переворачиваем путь, чтобы он шел от start к end

    return make_pair(dist[end], path); //Возвращаем длину кратчайшего пути и сам путь
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 

    vector<vector<int>> graph = readGraph("input.dat");
    int numVertices = graph.size();

    int start, end;
    cout << "Введите начальную и конечную вершины: ";
    cin >> start >> end;
    if (start > numVertices || start <= 0 || end >= numVertices || end <= 0) {
        cout << "Некорректные вершины!" << endl;
        return 1;
    }

    //Находим кратчайший путь
    pair<int, vector<int>> shortestPathData = findShortestPath(graph, start - 1, end - 1);
    int shortestPathLength = shortestPathData.first;
    vector<int> shortestPath = shortestPathData.second;

    //Выводим результаты на экран и в файл
    ofstream outFile("output.dat");
    if (!outFile.is_open()) {
        cout << "Ошибка открытия файла для записи результатов!" << endl;
        return 1;
    }

    cout << "Кратчайший путь между вершинами " << start << " и " << end << ": ";
    outFile << "Кратчайший путь между вершинами " << start << " и " << end << ": ";
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

    cout << "Длина кратчайшего пути: " << shortestPathLength << endl;
    outFile << "Длина кратчайшего пути: " << shortestPathLength << endl;

    outFile.close();

    return 0; 
}