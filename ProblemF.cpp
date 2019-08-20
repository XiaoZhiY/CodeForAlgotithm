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
    /*
    2
    3
    5 0 1 2 1 4
    3 2 0 2
    2 2 0
    2
    1 0
    1 0
    */
    int kase;
    cin >> kase;
    while(kase--)
    {
        int treeNum;
        cin >> treeNum;
        vector<int> treeDepth;
        vector<int> treeLength;

        //计算深度 为了方便 以后 最后计算的时候可以 直接 拿 totalDepth - treeDepth[i] + treeLength[i] 作为结果
        int totalDepth = 0;
        for(int i = 0; i < treeNum;i++)
        {
            vector<int> dataInTree;
            int treeNodeNum;
            cin >> treeNodeNum;
            for(int j = 0 ; j < treeNodeNum;j++)
            {
                int t; cin >> t; dataInTree.push_back(t);
            }
            Tree tree(dataInTree);


            // 因为最后要两倍 所以 干脆这里做了 就不为了 可读性了
            int depth = tree.getDepth() * 2;
            totalDepth += depth;
            treeDepth.push_back(depth);
            treeLength.push_back(tree.getLength());
        }

        int maxRes = -1;
        int minRes = 0x7fffffff;

        for(int i = 0; i < treeNum;i++)
        {
            maxRes = max(maxRes, totalDepth - treeDepth[i] + treeLength[i]);
            minRes = min(maxRes, totalDepth - treeDepth[i] + treeLength[i]);
        }
        cout << maxRes << " " << minRes << endl;
    }
}