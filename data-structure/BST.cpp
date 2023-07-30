// Implementacion de un BST con recorridos pre, in y post orden
class BST{
    int data;
    BST *left,*right;
    
    public:
        BST();
        BST(int);
        BST* insert(BST*,int);
        BST* deleteNode(BST*,int);
        void preorder(BST*);
        void inorder(BST*);
        void postorder(BST*);
        void printLeafNodes(BST*);
};

BST::BST(){
    data=0;
    left=right=NULL;
}

BST::BST(int value){
    data=value;
    left=right=NULL;
}

BST* BST::insert(BST* root, int value){
    if(!root){
        return new BST(value);
    }
    if(value>=root->data){
        root->right=insert(root->right,value);
    }
    else if(value<root->data){
        root->left=insert(root->left,value);
    }
    return root;
}

BST* BST::deleteNode(BST* root, int k)
{
    if (root == NULL)
        return root;
 
    if (root->data > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->data < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }
 
    if (root->left == NULL) {
        BST* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        BST* temp = root->left;
        delete root;
        return temp;
    }
 
    else {
 
        BST* succParent = root;
 
        BST* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
 
        root->data = succ->data;
 
        delete succ;
        return root;
    }
}

void BST::preorder(BST* root){
    if(!root){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void BST::inorder(BST* root){
    if(!root){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void BST::postorder(BST* root){
    if(!root){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

void BST::printLeafNodes(BST* root){
    if (!root)
        return;
    if (!root->left && !root->right){
        cout << root->data << " ";
        return;
    }
    if (root->left)
       printLeafNodes(root->left);
    if (root->right)
       printLeafNodes(root->right);
}

int main(){
    int n,num;
    cin>>n;
    BST b,*root=NULL;
    for(int i=0;i<n;i++){
        cin>>num;
        if(i==0){
            root=b.insert(root,num);
            continue;
        }
        b.insert(root,num);
    }
    b.preorder(root);
    cout<<endl;
    b.inorder(root);
    cout<<endl;
    b.postorder(root);
    cout<<endl;
    return 0;
}