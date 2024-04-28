#include <iostream>
#include <stdlib.h>
#include <queue>
#include <omp.h>

using namespace std;

class node
{
public:
    node *left, *right;
    int data;
};

class Breadthfs
{
public:
    node *insert(node *, int);
    void bfs(node *);
};

node *Breadthfs::insert(node *root, int data)
{
    if (!root)
    {
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }
    queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        if (temp->left == NULL)
        {
            temp->left = new node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root;
        }
        else
        {
            q.push(temp->left);
        }
        if (temp->right == NULL)
        {
            temp->right = new node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root;
        }
        else
        {
            q.push(temp->right);
        }
    }
    return root; // Return root in case none of the conditions above are met
}

void Breadthfs::bfs(node *head)
{
    queue<node *> q;
    q.push(head);
    int qSize;
    while (!q.empty())
    {
        qSize = q.size();
#pragma omp parallel for
        // creates parallel threads
        for (int i = 0; i < qSize; i++)
        {
            node *currNode;
#pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            } // prints parent node
#pragma omp critical
            {
                if (currNode->left) // push parent's left node in queue
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            } // push parent's right node in queue
        }
    }
}

int main()
{
    Breadthfs bfs;
    node *root = NULL;
    int numElements;
    cout << "Enter the number of elements you want to add: ";
    cin >> numElements;
    for (int i = 0; i < numElements; ++i)
    {
        int data;
        cout << "Enter data " << i + 1 << ": ";
        cin >> data;
        root = bfs.insert(root, data);
    }
    cout << "Breadth First Search Traversal:\n";
    bfs.bfs(root);
    return 0;
}
