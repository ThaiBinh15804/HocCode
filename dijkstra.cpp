#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 3 // Số đỉnh ban đầu (0, 1, 2, 16)

// Hàm tìm đỉnh có khoảng cách nhỏ nhất chưa được thăm
int timDinhNhoNhat(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Hàm in kết quả sau khi tìm đường đi ngắn nhất
void inKetQua(int dist[], int parent[]) {
    printf("Dinh \t Khoang cach tu nguon \t Truy vet duong di\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d \t\t\t ", i, dist[i]);
        int j = i;
        while (j != -1) {
            printf("%d ", j);
            j = parent[j];
        }
        printf("\n");
    }
}

// Hàm tìm đường đi ngắn nhất từ đỉnh nguồn đến tất cả các đỉnh khác trong đồ thị
void dijkstra(int graph[V][V], int nguon) {
    int dist[V];     // Mảng lưu khoảng cách ngắn nhất từ nguồn đến đỉnh i
    bool sptSet[V];  // SptSet[i] sẽ true nếu đỉnh i đã được xem xét trong đường đi ngắn nhất
    int parent[V];   // Mảng lưu đỉnh cha của mỗi đỉnh trên đường đi ngắn nhất
    
    // Khởi tạo tất cả các khoảng cách là vô cùng và sptSet[i] là false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1; // Không có đỉnh cha ban đầu
    }
    
    // Khoảng cách từ đỉnh nguồn đến chính nó luôn là 0
    dist[nguon] = 0;
    
    // Tìm đường đi ngắn nhất cho tất cả các đỉnh
    for (int count = 0; count < V - 1; count++) {
        int u = timDinhNhoNhat(dist, sptSet);
        sptSet[u] = true; // Đánh dấu đỉnh u đã được thăm
        
        // Cập nhật khoảng cách của tất cả các đỉnh kề với đỉnh đã chọn
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v]&&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Cập nhật đỉnh cha của v
            }
        }
    }
    
    // In kết quả
    inKetQua(dist, parent);
}

int main() {
    int graph[V][V] = {{0, 2, 4},
                       {0, 0, 1}, 
                       {0, 0, 0}};

    int nguon = 0; // Đỉnh nguồn
    
    dijkstra(graph, nguon);
    
    return 0;
}
