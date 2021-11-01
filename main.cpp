#include <iostream>
//#include <bits/stdc++.h>
#include <queue>
#include <vector>
#include <chrono>
#include <iterator>
#include<array>
#include <algorithm>
#include  <fstream>


using namespace std;
const int MAX_N = 301;


int t, n, m;
std::vector<std::pair<int, int>> adj[MAX_N];

long dis[MAX_N];
int pre[MAX_N];
bool in_queue[MAX_N];

bool visited[MAX_N], on_stack[MAX_N];
std::vector<int> vec1;


bool detect_cycle()
{
    
    std::fill(visited, visited+ n ,false);
    std::fill(on_stack, on_stack + n, false);
    for (int i = 0; i < 1 ; i++)
        if (!visited[i])
        {
            for (int j = i; j != -1; j = pre[j])
                if (!visited[j])
                {
                    visited[j] = true;
                    vec1.push_back(j);
                    on_stack[j] = true;
                }
                else
                {
                    if (on_stack[j])
                    
                       return true;
                    break;
                }
            for (int j : vec1)
                on_stack[j] = false;
            
            vec1.clear();
        }
    
    return false;
}

bool spfa_early_terminate()
{
    std::fill(pre, pre + n, -1);
    std::fill(in_queue, in_queue + n, true);
    std::queue<int> queue;
    for (int i = 0 ; i < n; ++i)
        queue.push(i);
    int iter = 0;
    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop();
        in_queue[u] = false;
        for (auto [v, w] : adj[u])
            
            if (dis[u] + w < dis[v])
            {
                pre[v] = u;
                dis[v] = dis[u] + w;
                
                if (++iter == n-1)
                {
                    iter = 0;
                    if (detect_cycle())
                        return true;
                }
                if (!in_queue[v])
                {
                    queue.push(v);
                    in_queue[v] = true;
                }
            }
    }
    if (detect_cycle())
        return true;
    return false;
}



int main(int argc, char* argv[])
{
    
    ifstream myfile ;
    ofstream output;
    output.open(argv[2]);
    myfile.open(argv[1]);
    
    int HowmanyTimes=0;
    myfile>> HowmanyTimes;
    for(int z=0 ; z < MAX_N;z++ ){
      adj[z].reserve(151);
        
    }
    vec1.reserve(300);
    
    for(int as=0 ; as< HowmanyTimes; as++){
        //vec1.clear();
        myfile >> m;
        n = 2*m ;
        
        
        std::fill(dis, dis + n, 0);
       
        for(int z=0 ; z < n;z++ ){
            adj[z].clear();
            
        }
    for (int i = 0; i < m; ++i)
    {
        
        
        int MaxValueOfArray=0;
        for(int y=0 ; y<m ;y++){
            int value=0;
            myfile >> value ;
            int destination = m+y;
            if(i+m == destination){
               
               
                adj[destination].emplace_back(i, value -MaxValueOfArray);
                
            }
            else{
                adj[i].emplace_back(destination, MaxValueOfArray-value);
                
            }
            }
        
        
    }
        
        
      while(spfa_early_terminate()){
       
          
        vec1.push_back(*vec1.begin());
       
        reverse(vec1.begin(), vec1.end());
          

      for(int i=0 ; i < vec1.size()-1 ; i++ ){
            int w =0;
            
          
            for(long a = (adj[vec1.at(i)].size()-1)  ; a >=0 ; a--){
                
                    if(adj[vec1.at(i)].at(a).first== vec1.at(i+1) ){
                      
                        
                        w = adj[vec1.at(i)].at(a).second;
                        
                        adj[vec1.at(i)].erase(adj[vec1.at(i)].begin()+a);
                      
                        adj[vec1.at(i+1)].emplace_back(vec1.at(i),-1*w);
                        
                       
                        break;
                    }
                }
          
             }
        
         vec1.clear();
        
    }
        
    int costtime = 0 ;
        
    for ( int i=m ; i<2*m ;i++){
     
        costtime+= adj[i].at(0).second;
         
      
    }
        
        
    output << costtime  <<endl;
        
}
    
    return 0;
 
}


