#include<iostream>
#include <cassert>
using namespace std;
template<class T>
class Node {
private:
    Node *left;
    Node *right;
    Node *parent;
    int hight;
    int freq;
    int cpyfreq;
    int Sum_RightSubtree;
    int Sum_LeftSubtree;
    int Sum_Subtree;
    bool isMain;
    Node(T val) {
        left = nullptr;
        right = nullptr;
        parent= nullptr;
        Value = val;
        hight = 1;
        freq=1;
        Sum_Subtree=Sum_RightSubtree=Sum_LeftSubtree=0;
        isMain= true;
    }
    Node<T>* findRoot(Node<T>*A)
    {
        Node<T> *ROOt=A;
        while (ROOt->parent!= nullptr)
            ROOt=ROOt->parent;
        return ROOt;
    }
    Node<T>* Prev(T Value, Node<T> *root)
    {
        if (root == nullptr)
            return nullptr;
        if (root->Value >= Value)
            return  Prev(Value, root->left);
        Node<T> *p = Prev(Value, root->right);
        if(p== nullptr)
            return root;
        return p;
    }
    Node<T> * GO(T Value, Node<T> *root) {
        if(root== nullptr)
            return nullptr;
        if(root->Value<=Value)
            return GO(Value,root->right);
        Node<T>*ans=root;
        Node<T>*tmp=GO(Value,root->left);
        if(tmp!= nullptr)
            ans=tmp;
        return ans;
    }
public:
    T Value;
    template<class X,int MAX>
    friend class AliTree ;
    Node<T> *  next(bool prev=0)
    {
        Node<T> *ROOt= this;
        if(isMain&&freq>1)
        {
            cpyfreq=freq;
            Node * X=new Node(this->Value);
            X->right= this->right;
            X->left= this->left;
            X->freq= this->freq;
            X->cpyfreq=freq-1;
            X->parent= this;
            X->isMain=false;
            return X;
        }
        else if(isMain||cpyfreq==1)
            return prev? jumpprev(this):jumpnext(this);
        else
        {
            this->cpyfreq--;
            return this;
        }
    }
    Node<T> *  prev()
    {
        return next(1);
    }
    Node<T> *  jumpnext(Node<T>*A)
    {

        return GO(A->Value, findRoot(A));
    }
    Node<T> *  jumpprev(Node<T>*A)
    {
        return Prev(A->Value, findRoot(A));
    }
};
template<class  T,int MAX=2000000001>
class AliTree {
private:
    Node<T> * RooT = nullptr;
    Node<T> * End = nullptr;
    int Hight_Node(const Node<T> * ) const;
    Node<T> *Update_Hight(Node<T> *) ;
    Node<T> * Update_Sum(Node<T> *);
    int Blanced_factor(Node<T> *) const ;
    Node<T> *Right_Rotation(Node<T> *);
    Node<T> *Left_Rotation(Node<T> *) ;
    Node<T> *insert(Node<T> * ,T) ;
    Node<T> *remove(T , Node<T> *) ;
    Node<T>* find(T , Node<T> *) ;
    Node<T> * find_MIN(Node<T> *) ;
    Node<T> * find_MAX(Node<T> *) ;
    Node<T> * Maximum_NumberlessThanValue(T , Node<T> *) ;
    Node<T> * upper_bound(T , Node<T> *) ;
    Node<T> *find_by_index(int ,Node<T>*);
    int number_integers_greaterThan_Value(T Value,Node<T> *);
public:
    template<class X>
    friend class Node;
    int size()const ;
    bool empty() const;
    void insert(T value) ;
    void remove(T value) ;
    void removeall(T  ) ;
    Node<T> *begin()  ;
    Node<T> * end() ;
    Node<T> *rbegin()  ;
    Node<T> * rend() ;
    bool find(T value) ;
    T find_min() ;
    T find_max() ;
    Node<T> * Maximum_NumberlessThanValue(T value);
    Node<T> * Maximum_NumberlessThan_OR_Equal_Value(T ) ;
    Node<T> * upper_bound(T ) ;
    Node<T> * lower_bound(T   );
    Node<T> *find_by_index(int );
    int index_of_key(T );
    int number_integers_greaterThan_Value(T );
    int number_integers_greaterThan_OR_Equal_Value(T );
    int number_integers_lessThan_Value(T );
    int number_integers_lessThan_OR_Equal_Value(T );
    int count_integer_between_L_and_R(T  ,T );
    int count(T);

};
template<class T,int MAX>
int AliTree<T,MAX>::size()const {
    if(RooT== nullptr)
        return 0;
    return (RooT->Sum_Subtree+RooT->freq);
}
template<class T,int MAX>
bool AliTree<T,MAX>::empty()const {
    return this->size()==0;
}
template<class T,int MAX>
Node<T>* AliTree<T,MAX> ::begin() {
    if(this->empty())
        return end();
    return this->find_MIN(RooT);
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> ::end()  {
    return End;
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> ::rbegin()  {
    return find_MAX(RooT);
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> ::rend()  {
    return nullptr;
}

template<class T,int MAX>
Node<T> * AliTree<T,MAX>:: Update_Hight(Node<T> *root) {
    root->hight = 1 + max(Hight_Node(root->left), Hight_Node(root->right));
    return root;
}
template<class T,int MAX>
int AliTree<T,MAX>:: Hight_Node(const Node<T> *N) const {
    if (N == nullptr)
        return 0;
    return N->hight;
}
template<class T,int MAX>
int AliTree<T,MAX> ::Blanced_factor(Node<T> *root) const {
    if (root == nullptr)
        return 0;
    return Hight_Node(root->left) - Hight_Node(root->right);
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX>:: Right_Rotation(Node<T> *root) {
    Node<T> *child = root->left;
    root->left = child->right;
    if(child->right!= nullptr)
        child->right->parent=root;
    child->right = root;
    root->parent=child;
    root= Update_Sum(root);
    root = Update_Hight(root);
    child = Update_Hight(child);
    child= Update_Sum(child);
    return child;
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> ::Left_Rotation(Node<T> *root) {
    Node<T> *child = root->right;
    root->right = child->left;
    if(child->left!= nullptr)
        child->left->parent=root;
    child->left = root;
    root->parent=child;
    root= Update_Sum(root);
    root = Update_Hight(root);
    child= Update_Sum(child);
    child = Update_Hight(child);
    return child;
}
template<class  T,int MAX>
Node<T> *AliTree<T,MAX>::Update_Sum(Node< T>*N)
{
    N->Sum_Subtree=N->Sum_LeftSubtree=N->Sum_RightSubtree=0;
    if(N->left!= nullptr)
        N->Sum_LeftSubtree=N->left->Sum_Subtree+N->left->freq;
    if(N->right!= nullptr)
        N->Sum_RightSubtree=N->right->Sum_Subtree+N->right->freq;
    N->Sum_Subtree=N->Sum_RightSubtree+N->Sum_LeftSubtree;
    return N;
}

template<class T,int MAX>
Node<T> * AliTree<T,MAX>::insert(Node<T> *root, T N) {
    if ( root== nullptr)
        return root = new Node<T>(N);
    if (N > root->Value) {
        Node<T>*TMP= insert(root->right,N);
        root->right =TMP ;
        if(TMP!= nullptr)
            TMP->parent=root;
    }
    else if(N < root->Value) {
        Node<T>*TMP=insert(root->left, N);
        root->left =TMP;
        if(TMP!= nullptr)
            TMP->parent=root;
    }
    else
    {
        root->freq=min(root->freq+1,MAX);
        return root;
    }
    int blanced = Blanced_factor(root);
    if (blanced == 2) {
        if (Blanced_factor(root->left) == -1)
            root->left = Left_Rotation(root->left);
        root = Right_Rotation(root);

    } else if (blanced == -2) {
        if (Blanced_factor(root->right) == 1)
            root->right = Right_Rotation(root->right);
        root = Left_Rotation(root);
    }
    root=Update_Sum(root);
    root= Update_Hight(root);
    return root;
}
template<class T,int MAX>
void AliTree<T,MAX> ::insert(T value) {
    Node<T>*TMP=insert(RooT, value);
    RooT = TMP;
    RooT->parent= nullptr;
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> ::remove(T value, Node<T> *root) {
    if (root == nullptr)
        return root;
    if (root->Value == value&&(root->left== nullptr||root->left->Value!=root->Value)) {
        if(root->freq>1)
        {
            root->freq--;
            return root;
        }
        if (root->right == nullptr)
            return root->left;
        if (root->left == nullptr)
            return root->right;
        Node<T> *P = find_MIN(root->right);
        root->Value = P->Value;
        root->freq=P->freq;
        P->freq=1;
        Node<T>*TMP =remove(root->Value, root->right);;
        root->right =TMP;
        if(TMP!= nullptr)
            TMP->parent=root;
    } else if (value > root->Value) {
        Node<T>*TMP= remove(value, root->right);
        root->right =TMP ;
        if(TMP!= nullptr)
            TMP->parent=root;
    }
    else {
        Node<T>*TMP= remove(value, root->left);
        root->left =TMP ;
        if(TMP!= nullptr)
            TMP->parent=root;
    }
    int blanced = Blanced_factor(root);
    if (blanced == 2) {
        if (Blanced_factor(root->left) == -1)
            root->left = Left_Rotation(root->left);
        root = Right_Rotation(root);

    } else if (blanced == -2) {
        if (Blanced_factor(root->right) == 1)
            root->right = Right_Rotation(root->right);
        root = Left_Rotation(root);
    }
    root= Update_Sum(root);
    return root;
}
template<class T,int MAX>
void AliTree<T,MAX> ::remove(T value) {
    assert(this->size()>0);
    Node<T>*TMP=remove(value, RooT);;
    RooT=TMP ;
    if(RooT!= nullptr)
        RooT->parent= nullptr;
}
template<class T,int MAX>
void  AliTree<T,MAX> :: removeall(T Value) {
    Node<T> * TMP= find(Value,RooT);
    assert(TMP!= nullptr);
    TMP->freq=1;
    remove(Value);
}
template<class T,int MAX>
Node<T>* AliTree<T,MAX>:: find(T Value, Node<T> *root) {
    if (root == nullptr)
        return end();
    if (root->Value == Value)
        return root;
    if (root->Value < Value)
        return find(Value, root->right);
    return find(Value, root->left);
}

template<class T,int MAX>
bool AliTree<T,MAX>::find(T value) {
    return find(value, RooT)!=end();
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX>:: find_MIN(Node<T> *root) {

    if (root->left == nullptr)
        return root;
    return find_MIN(root->left);
}
template<class T,int MAX>
T AliTree<T,MAX>::find_min() {

    assert(this->size()>0);
    return find_MIN(RooT)->Value;
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> :: find_MAX(Node<T> *root)  {
    if (root->right == nullptr)
        return root;
    return find_MAX(root->right);
}
template<class T,int MAX>
T AliTree<T,MAX> :: find_max() {
    assert(this->size()>0);
    return find_MAX(RooT)->Value;
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> :: Maximum_NumberlessThanValue(T V, Node<T> *root) {
    if (root == nullptr)
        return end();
    if (root->Value >= V)
        return  Maximum_NumberlessThanValue(V, root->left);
    Node<T> *p =  Maximum_NumberlessThanValue(V, root->right);
    if(p== nullptr)
        return root;
    return p;
}template<class T,int MAX>
Node<T> * AliTree<T,MAX>::Maximum_NumberlessThanValue(T value) {
    return Maximum_NumberlessThanValue(value, RooT);
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX>::Maximum_NumberlessThan_OR_Equal_Value(T Value)
{
    return Maximum_NumberlessThanValue(Value+1);
}
template<class T,int MAX>
Node<T> *  AliTree<T,MAX> ::upper_bound(T Value, Node<T> *root) {
    if(root== nullptr)
        return end();
    if(root->Value<=Value)
        return upper_bound(Value,root->right);
    Node<T>*ans=root;
    Node<T>*tmp=upper_bound(Value,root->left);
    if(tmp!= nullptr)
        ans=tmp;
    return ans;
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> :: upper_bound(T Value)
{
    return this->upper_bound(Value,RooT);
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> :: lower_bound(T Value)
{
    return this->upper_bound(Value-1);
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> ::find_by_index (int index,Node<T>* root){
    if(root->Sum_LeftSubtree<=index&&index<=root->Sum_LeftSubtree+root->freq-1)
        return root;
    if(index<root->Sum_LeftSubtree)
        return find_by_index(index,root->left);
    return find_by_index(index-root->Sum_LeftSubtree-root->freq,root->right);
}
template<class T,int MAX>
Node<T> * AliTree<T,MAX> ::find_by_index (int index){
    assert(index< this->size());
    return find_by_index(index,RooT);
}
template<class T,int MAX>
int AliTree<T,MAX> :: number_integers_greaterThan_Value(T Value,Node<T> *root){
    if(root== nullptr)
        return 0;
    if(root->Value==Value)
        return root->Sum_RightSubtree;
    if(root->Value>Value)
        return root->freq+root->Sum_RightSubtree+ number_integers_greaterThan_Value(Value,root->left);
    return number_integers_greaterThan_Value(Value,root->right);
}
template<class T,int MAX>
int AliTree<T,MAX> ::number_integers_greaterThan_Value(T Value){
    return number_integers_greaterThan_Value(Value,RooT);
}
template<class T,int MAX>
int AliTree<T,MAX> ::number_integers_greaterThan_OR_Equal_Value(T Value){
    Node<T >*VA=this->Maximum_NumberlessThanValue(Value);
    if(VA== nullptr)
        return this->size();
    return number_integers_greaterThan_Value(VA->Value);
}
template<class T,int MAX>
int AliTree<T,MAX> :: number_integers_lessThan_Value(T Value){
    return this->size()- number_integers_greaterThan_OR_Equal_Value(Value);
}
template<class T,int MAX>
int AliTree<T,MAX> ::number_integers_lessThan_OR_Equal_Value(T Value){
    Node<T >*VA=this->upper_bound(Value);
    if(VA== nullptr)
        return this->size();
    return number_integers_lessThan_Value(VA->Value);
}
template<class T,int MAX>
int AliTree<T,MAX> ::count_integer_between_L_and_R(T L ,T R ){
    return number_integers_lessThan_OR_Equal_Value(R)- number_integers_lessThan_Value(L);
}
template<class T,int MAX>
int AliTree<T,MAX> ::count(T Value){
    return count_integer_between_L_and_R(Value,Value);
}
template<class T,int MAX>
int AliTree<T,MAX> ::index_of_key(T Value)
{
    return number_integers_lessThan_Value(Value);
}


void test()
{

    AliTree<int>A;// multie ordered set  //
    AliTree<int,1>B; // ordered set // don't allow duplicate value
    AliTree<pair<int,int>>C;
    AliTree<string>D;
    A.insert(5); // insert Value
    A.insert(10);
    A.insert(8);
    A.insert(0);
    A.insert(9);
    A.insert(313);
    A.insert(313);
    A.insert(313);
    // itreate on set (forward)
    for(auto it=A.begin(); it!=A.end(); it=it->next())
        cout<<it->Value<<" ";
    cout<<endl;
    // itreate on set (backward)
    for(auto it=A.rbegin(); it!=A.rend(); it=it->prev())
        cout<<it->Value<<" ";
    // some method           time complexity for all method is log(N) while N number of distinct elements (log base 2)
    A.index_of_key(9); // first index for value #return integer
    A.number_integers_lessThan_Value(11); // number of values less than the parameter value .the data structure focus on real number but for fun it fixed to work in an object #return integer
    A.Maximum_NumberlessThanValue(11) ; // grater value less than parameter value #return Node pointer
    A.find_by_index(3); // retrun value in index  (sorted in ascending order) #return Node pointer
    A.remove(313); // remove one value #return integer
    A.removeall(313); // remove all frequency of value #return void
    A.count_integer_between_L_and_R(3,5); // count number of value between L and R   (sorted in ascending order) #return integer
    A.lower_bound(313);  // the smallest value greater than or equal   parameter value return Node pointer
    A.upper_bound(10);  // the smallest value greater than    parameter value  return Node pointer
    A.find_min() ; // minimum value in set
    A.find_max(); //maximum value in set
    // all method work for string and pair  if you need use your struct as object implement functor or opreater overloading.
    // prev and next work for all pointer except end pointer and rend pointer not work prev of end pointer != maximum number in set
    // so use begin and rbegin
}
int main() {
    test();

    return 0;
}