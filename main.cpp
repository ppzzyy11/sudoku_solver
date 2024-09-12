#include <iostream>
#include <vector>

using namespace std;

const int X = 9, Y = 9;

static const bool only_one_solution = false;

void output_mat(const vector<vector<int>>& mat)
{
    static long long cnt = 1;
    //output the mat
    cout<<"mat: "<<cnt++<<'\n';
    for(int i = 0;i<X;i++)
    {
	cout<<"{";
	for(int j =0;j<Y;j++)
	{
	    cout<<mat[i][j]<<(j==Y-1?"":", ");
	    if(j%3==2)
		cout<<'\t';
	}
	
	cout<<"}"<<((i==X-1)?"":",");
	cout<<"\n";
	if (i%3==2)
	    cout<<'\n';
    }
}

pair<int, int> next_grid(pair<int, int> xy)
{
    int x = xy.first, y = xy.second;
    y++;
    x += y/Y;
    y %= Y;
    return make_pair(x, y);
}
bool is_out_of_scope(pair<int, int>xy)
{
    int x = xy.first, y = xy.second;
    return !(x>=0&&x<X&&y>=0&&y<Y);
}

bool is_valid_col(const vector<vector<int>>& mat, pair<int ,int> xy)
{
    if (is_out_of_scope(xy)) return false;
    int y = xy.second;
    vector<bool> visited(10, 0);
    visited[0]=true;
    for(int x=0;x<X;x++)
    {
	int num = mat[x][y];
	if (num == 0) continue;
	if (visited[num]==true)
	    return false;
	visited[num]=true;
    }
    return true;
}

bool is_valid_row(const vector<vector<int>>& mat, pair<int ,int> xy)
{
    if (is_out_of_scope(xy)) return false;
    int x = xy.first;
    vector<bool> visited(10, 0);
    visited[0]=true;
    for(int y=0;y<Y;y++)
    {
	int num = mat[x][y];
	if (num == 0) continue;
	if (visited[num]==true)
	    return false;
	visited[num]=true;
    }
    return true;
}

bool is_valid_squire(const vector<vector<int>>& mat, pair<int ,int> xy)
{
    if (is_out_of_scope(xy)) return false;
    int x = xy.first, y = xy.second;
    vector<bool> visited(10, 0);
    visited[0]=true;
    int top_x = x/3, top_y = y/3;
    for(int i=0;i<Y;i++)
    {
	int x = top_x*3 + i/3;
	int y = top_y*3 + i%3;
	int num = mat[x][y];
	if (num == 0) continue;
	
	if (visited[num]==true)
	    return false;
	visited[num]=true;
    }
    return true;
}

bool is_valid(const vector<vector<int>>& mat, pair<int ,int> xy)
{
    
    bool valid =  is_valid_col(mat, xy) && is_valid_row(mat, xy) && is_valid_squire(mat, xy);
    return valid;
}



bool recur(vector<vector<int>>& mat, pair<int, int> xy)
{
   
    if (is_out_of_scope(xy))
    {
	output_mat(mat);
	return true;
    }
    int x = xy.first, y= xy.second;
    auto next_xy = next_grid(xy);
    if(mat[x][y]!=0)
    {
	return is_valid(mat, xy)&&recur(mat, next_xy);
    }
	
    //mat[x][y]==0
    bool valid = false;
    for(int i =1;i<10;i++)
    {
	mat[x][y]=i;
	if (is_valid(mat, xy))
	{
	    valid |= recur(mat, next_xy);
	}
	if (valid && only_one_solution)
	    break;
	
    }
    mat[x][y]=0;
    return valid;
}

vector<vector<int>> problem = {
	/*
	{0,0,0,	0,0,0,	0,0,0}
	 */
	{1,0,0,	0,0,0,	0,0,0},//0
	{0,0,0,	0,0,7,	0,0,5},
	{0,8,0,	9,0,3,	4,2,0},
	
	{0,0,2,	0,4,0,	8,0,0},//3
	{8,1,0,	0,2,0,	0,0,0},
	{0,0,7,	0,0,0,	0,5,6},
	
	{6,5,0,	0,0,0,	0,0,0},//6
	{0,0,3,	0,0,0,	0,9,0},
	{0,0,0,	0,0,0,	7,0,4},
};
int main()
{
    bool valid = recur(problem, {0, 0});
    cout<<valid;
    return 0;
}
