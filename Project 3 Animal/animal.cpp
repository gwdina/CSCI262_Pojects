/*
	animal.cpp

	author: L. Henke and C. Painter-Wakefield
	date: 04 November 2019

	Animal/20 questions program for CSCI 262, starter code.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

class node {
public:
    string data;
    node* left = nullptr;
    node* right = nullptr;
};

void play_game(node*, vector<string>& storage);
node* read_game_tree();
void write_game_tree(node*);
void delete_game_tree(node*);


// TODO: Add helper method templates here, such as read_preorder().
node* read_preorder(ifstream& tree);
void write_preorder(ofstream& build, node* point);
void new_tree();
/**
 * Handles showing the main menu/basic UI
 */
int main() {
	node* root = read_game_tree();
	if (root == NULL) return -1;

	while (true) {
        vector<string> storage;
		string tmp;
		int choice;

		cout << "Welcome to 20 questions!" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game file" << endl;
        cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";
		getline(cin, tmp);
		choice = atoi(tmp.c_str());

		switch (choice) {
    		case 1:
    			play_game(root, storage);
    			break;
    		case 2:
    			write_game_tree(root);
    			break;
    		case 3:
    			break;
    		default:
    			cout << "Sorry, I don't understand." << endl << endl;
		}
		if (choice == 3) break;
	}

	delete_game_tree(root);
	return 0;
}

/**
 * Sets up the recursive call to the read_preorder
 * @return root of the tree
 */
node* read_preorder(ifstream& tree){//makes binary tree
    node* start = new node;
    string temp;
    getline(tree, temp);
    string choice = temp.substr(0,2); //#Q or #A
    string other = temp.substr(3); // the rest of the question
    start->data = other;
    if(choice == "#Q"){//starts with left then goes right when it hits the leaves of the tree
        start->left = read_preorder(tree);
        start-> right = read_preorder(tree);
    }
    if(choice == "#A"){//adds the leaves of the tree
        start->left = nullptr;
        start->right = nullptr;
    }

    return start;

}

node* read_game_tree() {//reads in file and sends it over to read_preorder
    ifstream tree;
    tree.open("animal_game_tree.txt");
    if(tree.fail()){
        cout << "Fail to open file." << endl;
        return nullptr;
    }
    node* head = read_preorder(tree);
    tree.close();
    return head;
}

/**
 * Plays the game
 * @param root Root of the game tree
 */
void play_game(node* root, vector<string>& storage) {//runs through the tree
    string answer;
    cout << root->data << " (y/n): ";
    getline(cin, answer);
    storage.push_back(root->data);
    storage.push_back(answer);// will be used if the computer loses and the player wants to extend

    if(answer == "y"){
        if((root->left == nullptr) && (root->right == nullptr)){
            cout << "I guessed your animal, I win!" << endl << endl;
            return;
        }
        play_game(root->left, storage);
    }

    if(answer == "n"){
        if((root->left == nullptr) && (root->right == nullptr)){
            cout << "Darn, I don't know" << endl;
            string thing;
            cout << endl << "Do you want to expand the tree? (y/n) ";
            getline(cin, thing);
            cout << endl;
            if (thing == "n"){
                return;
            }
            cout << "I asked the following:" << endl;
            if (thing == "y"){
                for(int i=0; i < storage.size(); ++i){//just gives out the question that already been asked and their answers
                    if(storage.at(i) == "y"){
                        cout << " YES" << endl;
                        continue;
                    }
                    if(storage.at(i) == "n"){
                        cout << " NO" << endl;
                        continue;
                    }
                    cout << storage.at(i);
                }

                node* with = new node;
                root->right = with;
                root->right->data = root->data;


                string anim;//adds the animal answer
                node* another = new node;
                cout << endl << "Enter new animal in the form a question: ";
                getline(cin, anim);
                root->left = another;
                root->left->data= anim;

                string quest;// adds the new description question to the tree
                cout << endl << "Enter new description question: ";
                getline(cin, quest);
                root->data = quest;
                cout << endl;
                return;
            }

        }
        play_game(root->right, storage);
    }
}

/**
 * Writes the game tree, sets up a recursive call to write_preorder();
 * @param root The root of the tree
 */
void write_preorder(ofstream& build, node* point){
    if((point->left != nullptr) &&(point->right != nullptr)){
        build << "#Q " << point->data << endl;
        write_preorder(build, point->left);
        write_preorder(build, point->right);
    }
    else{
        build << "#A " << point->data << endl;
    }

}

void write_game_tree(node* root) {//saves the current game,
    ofstream build("animal_game_tree.txt");
    write_preorder(build, root);
    build.close();
    cout << "Game file saved in 'animal_game_tree.txt'" << endl << endl;
}

/**
 * Deletes the game tree
 * @param root Root of the game tree
 */
void delete_game_tree(node* root) {
    // Optional. Do a post-order deletion of the game tree.
    // This isn't strictly needed as the program exits after this is called,
    // which frees up all the memory anyway.
}
