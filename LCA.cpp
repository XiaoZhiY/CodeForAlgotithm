#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Tree
{
public:
    Tree() {}

    /// 从父节点表示法初始化一个树
    Tree(vector<int> &node)
    {
        // 0 1 2 1 4
        tree.resize(node.size() + 1);
        nodeCnt = node.size();
        for(int i = 0;i < node.size();i++)
        {
            if(node[i] == 0)
            {
                rootNode = i + 1;
            }
            else
            {
                tree[node[i]].push_back(i+1);
            }

        }

    }
    ~Tree()
    {

    }

    void BFS()
    {
        queue<int> q;
        q.push(rootNode);
        while(!q.empty())
        {
            int curNode = q.front(); q.pop();
            cout << curNode << endl;
            for(int i = 0; i < tree[curNode].size();i++)
            {
                q.push(tree[curNode][i]);
            }
        }
    }
    // 获取树中的最长路
    int getLength()
    {
        int first = -1, second = -1;
        for(int i = 0 ;i < tree[rootNode].size(); i++)
        {
            int len = getDepth(tree[rootNode][i]);
            if(len >= first)
                { second = first; first = len; }
            else if(len > second)
                second = len;
        }
        return first + second + 2;
    }

    // 获取树中的深度
    int getDepth()
    {
        return getDepth(rootNode);
    }

protected:
    int getDepth(int root)
    {
        if(tree[root].size() == 0)
            return 0;

        int maxDepth = -1;
        for(int i = 0; i < tree[root].size(); i++)
        {
            maxDepth = max(maxDepth, getDepth(tree[root][i]));
        }
        return maxDepth + 1;
    }
private:
    // 使用邻接表来构建树
    int rootNode;
    int nodeCnt;
    vector<vector<int>> tree;
};

int main()
{
    vector<int> vec{2,0};
    Tree tree(vec);
    tree.BFS();
    cout << endl;
    cout << tree.getDepth() << endl;
    cout << tree.getLength() << endl;
    return 0;
}