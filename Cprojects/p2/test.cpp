#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;
static bool odd(int a)
{	if ((a/2)!=a*1.0/2){return true;}
		}
static bool even(int a)
{	if ((a/2)==a*1.0/2){return true;}
		}
static bool list_equal(list_t l1, list_t l2)
    // EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }    
}    

int main()
{
    int i;
    list_t listA, listA_answer;
    list_t listB, listB_answer;

    listA = list_make();
    listB = list_make();
    listA_answer = list_make();
    listB_answer = list_make();

    for(i = 5; i>0; i--)
    {
        listA = list_make(i, listA);
        listA_answer = list_make(6-i, listA_answer);
        listB = list_make(i+10, listB);
        listB_answer = list_make(i+10, listB_answer);
    }

    for(i = 5; i>0; i--)
    {
        listB_answer = list_make(i, listB_answer);
    }	
	tree_t test_tree;
	tree_t subtree1=tree_make(6,tree_make(),tree_make(7,tree_make(),tree_make()));
	tree_t subtree2=tree_make(3,tree_make(2,tree_make(),tree_make()),tree_make());
	test_tree=tree_make(5,subtree2,subtree1);
	list_t B=append(listA,list_make(100,list_make()));
	list_print(B);
	list_print(reverse(B));
	list_print(chop(B,0));
	//cout<<isArithmeticSequence()<<endl;

/*
	test_tree=tree_make(5,tree_make(),tree_make());
	test_tree=tree_make(6,test_tree,tree_make());
	test_tree=tree_make(3,test_tree,test_tree);
	tree_t tree2=test_tree;
	test_tree=tree_make(1000,test_tree,test_tree);

	tree_print(test_tree);

	cout<<tree_sum(test_tree)<<endl;
	cout<<tree_search(test_tree,6)<<endl;
	cout<<depth(test_tree)<<endl;
	cout<<tree_max(test_tree)<<endl;
	
	cout<<tree_hasMonotonicPath(test_tree)<<endl;
	cout<<tree_allPathSumGreater(test_tree,1000)<<endl;
	//cout<<covered_by(tree2,test_tree)<<endl;
	//cout<<contained_by(tree2,test_tree)<<endl;
	list_print(append(listA,list_make()));
	list_print(traversal(test_tree));
	tree_print(insert_tree(1,test_tree));
	list_print(listA);
	cout<<endl;
	list_print(filter_odd(listA));
	//list_print(filter(listA,even));

	list_print(filter(listA,odd));
	cout<<endl;
	cout<<even(99)<<endl;
	cout<<endl;
	cout<<99/2;
*/	
}

