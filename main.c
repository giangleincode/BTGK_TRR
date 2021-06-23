#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include"graph_jrb/graph_jrb.h"
#define Max_Char 255
#define Max 10005
#define true 1
#define false 0
#include<stdio.h>
#include<limits.h>
#define V 16


int graph_kruscal[V][V] = {0};

int out_arr[Max][Max] = {0};

int DFS_Cycle(Graph graph, int start){
    int visited[1000] = {};
    int n, output[100], i, u , v;
    int color[1000] = {0}; //khởi tạo tất cả đỉnh là màu trắng _ tức là ch dc thăm
    Dllist node, stack;
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));
    color[start] = 1; // dinh dc dua vao stack thi co màu xám
    while(! dll_empty(stack)){
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if(color[u] == 1 || color[u] == 2){
            //PrintVertex(u);
           // visited[u] =  1;
            color[u]++; // ghé thăm và đã ra khỏi stack r thì ++ màu
            n = outdegree(graph, u, output);
            for(i =0; i < n  ; i++){
                v = output[i];
                // if(v == start) return 0; //cycle deleted
                if(color[v] == 0|| color[v] == 1) {
                    dll_append(stack, new_jval_i(v));
                    color[v] ++; // đưa vào stack sẽ ++ màu
                }
            }
        }
    }
    for(int i = 0 ; i< 21; i++){
      //  printf("%d\n", color[i]);
       if(color[i] == color[start] + 1 && color[i]!= start) return 1; // tồn tại cycle
    }
    return 0; // ko tồn tại cycle
}

int Algorithm_for_Kruskal(Graph g, int verte_num, double min,  Graph out, int out_ed_num, int start){
   // test = createGraph();
   
  
    //printf("%d\n",DFS_Cycle(out, start));
    for(int i = 0; i < verte_num; i++){
        
        for(int j = i+1 ; j < verte_num; j++){
           if(getEdgeValue(g, i, j) == min )
               {
                  addVertex(out, i, "none");
                  addVertex(out, j, "none");
                  addEdge(out, i, j, min, 1);

                  // out_arr[i][j] = min;
               // addweightEdge(out, i, j, min);
               if(DFS_Cycle(out , start) == 1)
               {
                  delEdge(out, i, j, 1);
                  delVertex(out, i);
                  delVertex(out, j);

                  // out_arr[i][j] = 0;
                  // out_arr[j][i] = 0;

                  // out.matrix[i* out.n + j] = 0;
                  // out.matrix[j* out.n + i] = 0;
               }
               else {
                   if(getEdgeValue(out, i, j) != 0)
                   {
                   printf("Them thanh cong canh %d %d vao cay bao trum \n", i, j);
                   out_ed_num ++;
                   }
               }
           }
        }
    }  
     
    
   // dropGraph(test);
   // dropGraph(test);
    return out_ed_num;
}

int readfile_1(Graph graph, char filename[Max_Char])
{
   IS is = new_inputstruct(filename);

   if (is == NULL)
   {
      printf("ERROR!\n");
      exit(0);
   }

   get_line(is);

   int num_vertex = atoi(is->fields[0]);

   while (get_line(is) > 0)
   {
      int v1 = atoi(is->fields[0]);
      int v2 = atoi(is->fields[1]); 
      addVertex(graph, v1, is->fields[0]);
      addVertex(graph, v2, is->fields[1]);
      addEdge(graph, v1, v2, atof(is->fields[2]), 1);
   }
   
   return num_vertex;

   jettison_inputstruct(is);
}

int readfile_0(Graph graph, char filename[Max_Char])
{
   IS is = new_inputstruct(filename);

   if (is == NULL)
   {
      printf("ERROR!\n");
      exit(0);
   }

   get_line(is);

   int num_vertex = atoi(is->fields[0]);

   while (get_line(is) > 0)
   {
      int v1 = atoi(is->fields[0]);
      int v2 = atoi(is->fields[1]); 
      addVertex(graph, v1, is->fields[0]);
      addVertex(graph, v2, is->fields[1]);
      addEdge(graph, v1, v2, atof(is->fields[2]), 0);
   }
   
   return num_vertex;

   jettison_inputstruct(is);
}

void readfile_arr(char filename[Max_Char])
{
   IS is = new_inputstruct(filename);

   if (is == NULL)
   {
      printf("ERROR!\n");
      exit(0);
   }

   get_line(is);

   while (get_line(is) > 0)
   {
      int v1 = atoi(is->fields[0]);
      int v2 = atoi(is->fields[1]); 
      int v3 = atoi(is->fields[2]);
      graph_kruscal[v1][v2] = v3;
      graph_kruscal[v2][v1] = v3;
   }
   
   jettison_inputstruct(is);
}

int check_degree(Graph graph)
{
   JRB node;
   int bool = true;

   jrb_traverse(node, graph.vertices)
   {
      int output[Max] = {};
      int check = outdegree(graph, jval_i(node->key), output);

      if (check % 2 == 1)
      {
         bool = false;
      }
      break;
   }

   return bool;
}

int Dag_check(Graph graph_1)
{
   int check = DAG(graph_1);

   if (check  == 1)
   {
      printf("Đồ thị không có chu trình\n");
   } else printf("Đồ thị có chu trình\n");

   printf("-------------------------------------\n");
   return check;
}

void DFS_check(Graph graph_1)
{
   int start, finish;

   printf("Nhập điểm vào: ");
   scanf("%d", &start);
   printf("Nhập điểm đến: ");
   scanf("%d", &finish);
   printf("Tìm đường theo DFS: \n");
   int output[Max] = {};
   int num_ver = DFS(graph_1, start, finish, output);

   printf("Số đỉnh là: %d\n", num_ver);
   printf("Gồm các đỉnh là:\n");
   for (int i = 0; i < num_ver; i++)
   {
      printf("%d ", output[i]);
   }  

   printf("\n----------------------------------------\n");
}

void BFS_check(Graph graph_1)
{
   int start, finish;

   printf("Nhập điểm vào: ");
   scanf("%d", &start);
   printf("Nhập điểm đến: ");
   scanf("%d", &finish);
   printf("Tìm đường theo BFS: \n");
   int output[Max] = {};
   int num_ver = shortest_noWeight_path(graph_1, start, finish, output);

   printf("Số đỉnh là: %d\n", num_ver);
   printf("Gồm các đỉnh là:\n");
   for (int i = 0; i < num_ver; i++)
   {
      printf("%d ", output[i]);
   }  

   printf("\n----------------------------------------\n");
}

void Father_code_check(Graph graph_1)
{
   printf("Father code\n");
   int father_code[Max][2], output_temp[Max] = {}, count = 0, check = -1;
   JRB node;
   jrb_traverse(node, graph_1.vertices)
   {
      check++;
      if (check != 0)
      {
         father_code[count][1] = jval_i(node->key);
         int temp = shortest_noWeight_path(graph_1, jval_i(node->key), 0, output_temp);
         father_code[count][2] = output_temp[1];
         // output_temp = '\n';
         count++;
      }
   }

   printf("Dãy số father code là\n");
   for (int i = 1; i <= 2; i++)
   {
      for (int j = 0; j < count; j++)
      {
         printf("%d    ", father_code[j][i]);
      }
      printf("\n");
   }

   printf("-----------------------------------------\n");
}

void check_indeg(Graph graph_0)
{
   printf("Indeg:\n");
   int out_indeg[Max] = {}, ver_indeg;
   printf("Nhập điểm muốn lấy indeg: ");
   scanf("%d", &ver_indeg);
   int num_indeg =   indegree(graph_0, ver_indeg, out_indeg);
   printf("Số các đỉnh là: %d\n", num_indeg);
   printf("Gồm các đỉnh là:\n");
   for (int i = 0; i < num_indeg; i++)
   {
      printf("%d ", out_indeg[i]);
   }
   printf("\n");

   printf("-----------------------------------------\n");
}

void check_outdeg(Graph graph_0)
{
   printf("Outdeg:\n");
   int out_outdeg[Max] = {}, ver_outdeg;
   printf("Nhập điểm muốn lấy outdeg: ");
   scanf("%d", &ver_outdeg);
   int num_outdeg =   outdegree(graph_0, ver_outdeg, out_outdeg);
   printf("Số các đỉnh là: %d\n", num_outdeg);
   printf("Gồm các đỉnh là:\n");
   for (int i = 0; i < num_outdeg; i++)
   {
      printf("%d ", out_outdeg[i]);
   }
   printf("\n");
   
   printf("-----------------------------------------\n");
}

void check_topo(Graph graph_0)
{
   printf("Topo\n");
   printf("Dãy topo: \n");
   int out_topo[Max] = {}, num_topo = topologicalSort(graph_0, out_topo);

   printf("Số các đỉnh là: %d\n", num_topo);
   printf("Gồm các đỉnh: \n");
   for (int i = 0; i < num_topo; i++)
   {
      printf("%d ", out_topo[i]);
   }

   printf("\n");

   printf("-----------------------------------------\n");

}

void check_dijik(Graph graph_0)
{
   int start, finish;

   printf("Nhập điểm vào: ");
   scanf("%d", &start);
   printf("Nhập điểm đến: ");
   scanf("%d", &finish);
   printf("Tìm đường theo Dijsktra: \n");
   int path[Max], i;

   double w = shortestPath(graph_0, start, finish, path, &i);
   if (w == INFINITIVE_VALUE)
   {
      printf("ROUTE NOT FOUND\n");
   } else{
      printf("Độ dài đường đi là: %g\n", w);
      printf("Gồm các đỉnh là: "); 
      for (int  j = 0; j < i; j++)
      {
         printf("%d ", path[j]);
      }
      printf("\n");
  }

   printf("-----------------------------------------\n");

}

void check_prufel_code(Graph graph_1)
{
   int count = 0;
   int check[Max] = {};
   JRB node;
    // printf("adsa");
   jrb_traverse(node, graph_1.vertices)
   {
    //    printf("adsa ");

      int output[Max] = {};
      int num_out = outdegree(graph_1, jval_i(node->key), output);

    //   printf("%d ", num_out);
      
      if (num_out == 1)
      {
         check[count] = output[0];
         count++;
         delVertex(graph_1, jval_i(node->key));
         node = jrb_first(graph_1.vertices);
      }
   }

   printf("Dãy prufel code là: \n");
   for (int i = 0; i < count - 1; i++)
   {
      printf("%d ", check[i]);
   }

   printf("\n");
   printf("-----------------------------------------\n");

}

int check_lienthongmach(Graph graph)
{
   JRB node;
   int bool = true;
   int check = 0;


   jrb_traverse(node, graph.vertices)
   {
      JRB node_temp;

      // printf("%d ",jval_i(node->key));

      jrb_traverse(node_temp, graph.vertices)
      {
         if (jval_i(node->key) != jval_i(node_temp->key))
         {
            int out[Max] = {};
            int  v1 = jval_i(node->key);
            int v2 = jval_i(node_temp->key);
            // printf("%d %d\n",v1, v2);

            int check = DFS(graph, v1, v2, out);
            
            if (check < 2)
            {
               bool = false;
               break;
            }
         }
      }

      if (bool == false)
      {
         break;
      }
   }
   return bool;
}

int TO_Mau(Graph g, int n, int* m){ //Xu ly de cho ra ket qua vao mang m[]  
    int kt;
    int so_mau = 0;
    for(int i =1;i <=n ;i++)
        if(!m[i]) {
            so_mau++; //Dem so mau
            m[i] =so_mau;
            for(int j = i+1; j<=n ; j++) //Kiem tra xem nhung dinh nao co the gan bang mau sm nua khong
                if((getEdgeValue(g, i, j) == INFINITIVE_VALUE)&&(m[j] == 0)){
                    kt=1;
                    for(int k = i+1; k < j; k++)
                        if(getEdgeValue(g, i, j) != INFINITIVE_VALUE&&(m[i]==m[k])){
                            kt=0;
                            break;
                        }
                    if(kt==1) m[j] = so_mau;
                }                   
        }
    return so_mau;
}

void In_ra_man_hinh(int n, int so_mau, int *m){ //In ket qua ra man hinh
    for(int i = 1;i <= so_mau; i++){
        printf("\nMau %d : _", i );
        for(int j=1;j<=n;j++) if(m[j]==i) printf("%d\t",j);
       
    }
    
}

int Kruskal(Graph g, int verte_num, Graph out, int start){

    int min = 0;
    int out_ed_num = 0;
    int distance = 0;
    while(out_ed_num != verte_num - 1){
        out_ed_num = Algorithm_for_Kruskal(g, verte_num, min,  out, out_ed_num, start);
     
        min ++;  
    }

    return out_ed_num;
}

int parent[V];

void printMST(int a[V], int b[V], int weight[V])
{
    int minWeight = 0;
    for (int i = 0; i < V-1; i++)
    {
        printf("Edge: %d - %d   Weight: %d\n", a[i], b[i], weight[i]);
        minWeight = minWeight + weight[i] ;
    }
    
    printf("MinWeight = %d\n", minWeight);
}

int findParent(int node)
{
    while (parent[node] >= 0)
    {
        node = parent[node];
    }
    return node;
}

int findParentPathCompression(int node)
{
    if (node == parent[node])
    {
        return node;
    }

    return parent[node] = findParentPathCompression(parent[node]);
}

void kruskal(int graph[V][V])
{
    int u, v, m = 0, count = 0;
    int firstNode, secondNode;
    int a[V];
    int b[V];
    int weight[V];
    int min;
    for (int i = 0; i < V; i++)
    {
            parent[i] = -1;
    }
        
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (graph[i][j] == 0)
            {
                graph[i][j] = INT_MAX;
            }   
        }
    }
    while (count < V-1)
    {
        min = INT_MAX;

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (graph[i][j] < min)
                {
                    min = graph[i][j];
                    firstNode = i;
                    secondNode = j;
                }
            }
        }
        
        u = findParent(firstNode);
        v = findParent(secondNode);

        if (u != v)
        {
            parent[v] = u;
            a[m] = firstNode;
            b[m] = secondNode;
            weight[m] = graph[firstNode][secondNode];
            count++;
            m++;
        }
        
        graph[firstNode][secondNode] = graph[secondNode][firstNode] = INT_MAX;
    }

    printMST(a, b, weight);
    
}

//Từ printMST đến kruskal là chỉ xử lý krusklal

int *makequeue(int n){
    int *H=malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        H[i]=i; //luu id cost
    } 
    return H;  
}

int deletemin(double *cost,int *H,int *count){
    if (*count<=0)return 0;
    double min_value=INFINITIVE_VALUE;
    int min;
    for (int i = 0; i < *count; i++)
    {
        if (cost[H[i]]<min_value)
        {
            min=H[i];
            min_value=cost[H[i]];
        }   
    }
    // xoa id min trong H -> Dich chuyen mang H
    for(int i = 0; i < *count; i++){
        if (H[i]==min)
        {
            for (int j = i; j < (*count)-1; j++)
            {
                H[j] = H[j+1];
            }   
            break;
        }
    }
    // Giam so luong phan tu sau khi xoa.
    --*count;
    return min;
}

void prim(Graph g, int soDinh){
    int *H=makequeue(soDinh);
    int z,v,count;
    count=soDinh;
    int *prev=malloc(soDinh*sizeof(int));
    double *cost=malloc(soDinh*sizeof(double));
    for (int i = 0; i < soDinh; i++)
    {
        cost[i]=INFINITIVE_VALUE; //khoi tao mang cost
        prev[i]=0;
    }
    cost[0]=0;
    while (count>0)
    {
        v=deletemin(cost,H,&count);
        for (int i = 0; i < count; i++)
        {
            z=H[i];
            if (cost[z]>getEdgeValue(g,v,z))
            {
                cost[z]=getEdgeValue(g,v,z);
                prev[z]=v;
            }    
        }
    }
    for (int i = 1; i < soDinh; i++)//in ra mst
    {
        printf("%d %d\n",i,prev[i]);
    }
    return;
}

//Sử lý Prim của nanh

int main()
{
   Graph graph_1 = createGraph(), graph_0 = createGraph();
   int num_vertex = readfile_1(graph_1,"../input.txt");
   num_vertex = readfile_0(graph_0, "../input.txt");

   int output[Max] = {};


//    int check = Dag_check(graph_0);

   BFS_check(graph_1);

   DFS_check(graph_1);


//    Father_code_check(graph_1);

//    check_indeg(graph_0);

//    check_outdeg(graph_0);

//    check_topo(graph_0);

//    check_dijik(graph_0);

    // check_prufel_code(graph_1);
//    int bool = check_lienthongmach(graph_1);

//    if (bool == true)
//    {
//       printf("Thành phần liên thông mạch!!\n");
//    } else printf("Thành phần không liên thông mạch!!\n");

//    printf("-----------------------------------------\n");

//    check_kruskal("../input.txt");


//    readfile_arr("../input.txt");


//     printf("Kruskal\n");
//     kruskal(graph_kruscal);



    // Graph graph=createGraph();
    // int soDinh, soCanh,v1,v2;
    // char s1[5],s2[5];
    // double weight;
    // FILE *f;
    // if ((f=fopen("../dothicotrongso.txt","r"))==NULL)
    // {
    //     printf("Cannot open file dothicotrongso.txt\n");
    //     return 0;
    // }else
    // {
    //     fscanf(f,"%d",&soDinh);
    //     while (fscanf(f,"%s %s %lf",s1,s2,&weight)!=EOF)
    //     {
    //         // printf("%s %s %lf\n",s1,s2,weight);
    //         v1=atoi(s1);
    //         v2=atoi(s2);
    //         addVertex(graph,v1,s1);
    //         addVertex(graph,v2,s2);
    //         addEdge(graph,v1,v2,weight,1);
    //     }
    //     prim(graph,soDinh);
    // }



//    int so_mau = TO_Mau(graph_1, num_vertex, output);

//    In_ra_man_hinh(num_vertex, so_mau, output);

//    printf("\n");

   dropGraph(graph_1);
   dropGraph(graph_0);

   return 0;
}
