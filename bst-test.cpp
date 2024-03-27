#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"
// #include "hw4_tests/bst_tests/check_bst.h"
// #include "print_bst.h"

using namespace std;


int main(int argc, char *argv[])
{

    AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(3, 0x5a));
	testTree.insert(std::make_pair(4, 0xb));
	testTree.insert(std::make_pair(1, 4));
	testTree.insert(std::make_pair(3, 159));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<uint16_t,uint16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }



    // AVLTree<int, double> bst;
	// bst.insert(std::make_pair(2, 1.0));
	// bst.insert(std::make_pair(3, 1.0));
	// bst.insert(std::make_pair(1, 1.0));
	// bst.insert(std::make_pair(4, 1.0));
	// bst.remove(1);

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<int,double>::iterator it = bst.begin(); it != bst.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // bst.print();



    // AVLTree<int16_t, int16_t> testTree;

	// testTree.insert(std::make_pair(95, 95));
	// testTree.insert(std::make_pair(-27, -27));
	// testTree.insert(std::make_pair(-52, -52));
    // testTree.insert(std::make_pair(-18, -18));
	// testTree.insert(std::make_pair(-24, -24));
    // testTree.insert(std::make_pair(109, 109));
	// testTree.insert(std::make_pair(-58, -58));

	// testTree.insert(std::make_pair(-49, -49));
	// testTree.insert(std::make_pair(127, 127));

	// testTree.insert(std::make_pair(9, 9));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<int16_t,int16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // testTree.print();

    // testTree.insert(std::make_pair(-84, -84));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<int16_t,int16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // testTree.print();

	// testTree.insert(std::make_pair(141, 141));
	// testTree.insert(std::make_pair(-38, -38));
	// testTree.insert(std::make_pair(-12, -12));
    // testTree.insert(std::make_pair(48, 48));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<int16_t,int16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // testTree.print();

    // testTree.insert(std::make_pair(-89, -89));
    // testTree.insert(std::make_pair(61, 61));
    // testTree.insert(std::make_pair(87, 87));
    // testTree.insert(std::make_pair(11, 11));
    // testTree.insert(std::make_pair(-35, -35));
    // testTree.insert(std::make_pair(-87, -87));
    // testTree.insert(std::make_pair(130, 130));
    // testTree.insert(std::make_pair(72, 72));
    // testTree.insert(std::make_pair(76, 76));
    // testTree.insert(std::make_pair(-113, -113));
    // testTree.insert(std::make_pair(110, 110));
    // testTree.insert(std::make_pair(-54, -54));
    // testTree.insert(std::make_pair(63, 63));
    // testTree.insert(std::make_pair(-126, -126));
    // testTree.insert(std::make_pair(-125, -125));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<int16_t,int16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // testTree.print();







    // Binary Search Tree tests

    //MY TESTS
    // BinarySearchTree<int, double> bt;
	// bt.insert(std::make_pair(2, 1.0));
	// bt.insert(std::make_pair(1, 1.0));
	// bt.insert(std::make_pair(3, 1.0));
	

    // cout << "Binary Search Tree initial contents:" << endl;
    // for(BinarySearchTree<int,double>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // bt.remove(2);
    // cout << "Binary Search Tree after removed :" << endl;
    // for(BinarySearchTree<int,double>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    //GIVEN TESTS

    // BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));
    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');

    // AVL Tree Tests
    // AVLTree<char,int> at;
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    return 0;
}
