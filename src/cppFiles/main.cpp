#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <utility>
#include <algorithm>
#include <functional>

// 0 1 0 0 0 0 0 0 
// 0 1 0 0 0 0 1 0 
// 0 1 1 0 0 1 0 0 
// 0 0 1 0 0 0 1 0 
// 0 0 0 0 1 1 0 0 
// 0 0 1 1 0 0 0 0 
// 0 0 0 0 1 1 1 0 

void inspectNeighbour( const int rowPos, 
                       const int collPos, 
                       const int countRows, 
                       const int countCollumns, 
                       std::deque<std::pair<const int, const int>>& visitedPlace, 
                       std::stack<std::pair<const int, const int>>& placeToVisit,
                       const std::vector<std::vector<int>>& oceanMap){
    if(rowPos >= 0 && rowPos < countRows && collPos >=0 && collPos < countCollumns && oceanMap[rowPos][collPos] == 1)
    {
        if(std::find(visitedPlace.begin(), visitedPlace.end(), std::make_pair(rowPos, collPos)) == visitedPlace.end())
        {
            visitedPlace.push_back(std::make_pair(rowPos, collPos));
            placeToVisit.push(std::make_pair(rowPos, collPos));
        }
    }
    return;
}

std::size_t FindMaxIsland(const std::vector<std::vector<int>>& matrix)
{
    int maxSize = 0;
    std::deque<std::pair<const int, const int>> visitedPlaces;
    for(int rows = 0; rows < matrix.size(); ++rows)
    {
        for(int collumns = 0; collumns < matrix[rows].size(); ++collumns){
            if(matrix[rows][collumns] == 1){
                
                // when write a stack to process recursively without a recursion
                std::stack<std::pair<const int, const int>> placesToVisit;
                int tempMaxSize = 0;
                
                // check if we already meet this ground
                if(std::find(visitedPlaces.begin(), visitedPlaces.end(), std::make_pair(rows, collumns)) == visitedPlaces.end())
                {
                    visitedPlaces.push_back(std::make_pair(rows, collumns));
                    placesToVisit.push(std::make_pair(rows, collumns));
                    while(!placesToVisit.empty())
                    {
                        tempMaxSize += 1;
                        std::pair<int, int> groudTOInspect = placesToVisit.top();
                        int rw = groudTOInspect.first;
                        int cl = groudTOInspect.second;
                        placesToVisit.pop();
                        //left neighobour
                        inspectNeighbour(rw, cl- 1, matrix.size() ,matrix[rows].size(), visitedPlaces, placesToVisit, matrix);
                        // right neighobour
                        inspectNeighbour(rw, cl+ 1, matrix.size() ,matrix[rows].size(), visitedPlaces, placesToVisit, matrix);
                        // up neighobour
                        inspectNeighbour(rw- 1, cl, matrix.size() ,matrix[rows].size(), visitedPlaces, placesToVisit, matrix);
                        // down neighobour
                        inspectNeighbour(rw+ 1, cl, matrix.size() ,matrix[rows].size(), visitedPlaces, placesToVisit, matrix);
                    }
                    if(tempMaxSize > maxSize)
                        maxSize = tempMaxSize;
                }
            }
        }
    }
    return maxSize;
}

int main()
{
    std::vector<std::vector<int>> ocean = 
    {
        { 0, 1, 0, 0, 0, 0, 0, 0},
        { 0, 1, 0, 0, 0, 0, 1, 0},
        { 0, 1, 1, 1, 0, 1, 0, 0},
        { 0, 0, 1, 1, 0, 0, 1, 0},
        { 0, 0, 0, 1, 1, 1, 0, 0},
        { 0, 0, 1, 1, 0, 0, 0, 0},
        { 0, 0, 0, 0, 1, 1, 1, 0}
    };
    std::cout << "The max islands: " << FindMaxIsland(ocean) << "\n";
}