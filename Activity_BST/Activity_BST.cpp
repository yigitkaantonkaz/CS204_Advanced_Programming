#include <iostream>
#include <string>
#include <sstream>

#include "activity_bst.h"

using namespace std;

string fill_with_zeros(int num_zeros, const string& input){
   int zeros_to_add = num_zeros - input.length();
   if (zeros_to_add < 0) zeros_to_add = 0;
   return string(zeros_to_add, '0') + input;
}

string number_to_time(int number){
   if (number >2359 || number < 0) return "ERROR";
   return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2,
to_string(number%100));
}

bool time_check(int time){
    string time_str;
    time_str = number_to_time(time);
    
    if (time_str != "ERROR"){
        string minutes = time_str.substr(3,2);
        int minutes_int = stoi(minutes);
        string hours = time_str.substr(0,2);
        int hours_int = stoi(hours);
        if ((minutes_int >= 0) && (minutes_int <= 59)){
            if ((hours_int >= 0) && (hours_int <= 23)){
                return true;
            }
        }
    }
    return false;
};

void add_activity(tree_node *&root, int time, const string &activity){
    
    string time_str;
    time_str = number_to_time(time);
    
    if (time_check(time)){
        tree_node *current_ptr;
        tree_node *new_node_ptr;
        int checker = 0; //to check if it is added or not
        current_ptr = root;
        
        if (root == NULL){// means empty tree
            root = new tree_node(time, activity);
            root->right = NULL;
            root->left = NULL;
            root->parent = NULL;
            root->time = time;
            root->activity = activity;
            cout << "Added activity '" << activity << "' at " << time_str << endl;
        }
        else{
            while (checker == 0){
                if (time < current_ptr->time){
                    if (current_ptr->left != NULL){
                        current_ptr = current_ptr->left;
                    }
                    else { // have an empty left
                        new_node_ptr = new tree_node(time, activity);
                        new_node_ptr->time = time;
                        new_node_ptr->activity = activity;
                        new_node_ptr->left = NULL;
                        new_node_ptr->right = NULL;
                        current_ptr->left = new_node_ptr;
                        new_node_ptr->parent = current_ptr;
                        checker ++;
                        cout << "Added activity '" << activity << "' at " << time_str << endl;
                    }
                }
                else if (time > current_ptr->time){
                    if (current_ptr->right != NULL){
                        current_ptr = current_ptr->right;
                    }
                    else{
                        new_node_ptr = new tree_node(time, activity);
                        new_node_ptr->time = time;
                        new_node_ptr->activity = activity;
                        new_node_ptr->left = NULL;
                        new_node_ptr->right = NULL;
                        current_ptr->right = new_node_ptr;
                        new_node_ptr->parent = current_ptr;
                        checker ++;
                        cout << "Added activity '" << activity << "' at " << time_str << endl;
                    }
                }
            }
        }
    }
    else {
        cout << "ERROR! Could not add activity '" << activity << "' due to illegal time value" << endl;
    }
};

void print_activity(tree_node *root, int time){
    bool flag = true;
    int counter_right = 0, counter_left = 0;
    
    string time_str;
    time_str = number_to_time(time);
    
    if (time_check(time)){
        tree_node *temp_ptr;
        tree_node *current_ptr;
        current_ptr = root;
        
        if (root == NULL){
            cout << "Time: " << time_str << ", Activity: free" << endl;
        }
        else{
            while (flag) { // to check if smth printed
                if (time < current_ptr->time){
                    counter_left ++;
                    if (current_ptr->left != NULL){
                        current_ptr = current_ptr->left;
                    }
                    else{
                        if (counter_right == 0){
                            cout << "Time: " << time_str << ", Activity: free" << endl;
                        }
                        else{
                            if (current_ptr->parent->time > time){
                                temp_ptr = current_ptr;
                                while(temp_ptr->parent->time > time){
                                    temp_ptr = temp_ptr->parent;
                                }
                                cout << "Time: " << time_str << ", Activity: " << temp_ptr->parent->activity << endl;
                            }
                            else if (current_ptr->parent->time < time){
                                cout << "Time: " << time_str << ", Activity: " << current_ptr->parent->activity << endl;
                            }
                        }
                        flag = false;
                    }
                }
                else if (time > current_ptr->time){
                    counter_right ++;
                    if (current_ptr->right != NULL){
                        current_ptr = current_ptr->right;
                    }
                    else{
                        if (counter_left == 0){
                            cout << "Time: " << time_str << ", Activity: " << current_ptr->activity << endl;
                        }
                        else{
                            if (current_ptr->parent->time < time){
                                temp_ptr = current_ptr;
                                while (temp_ptr->parent->time < time){
                                    temp_ptr = temp_ptr->parent;
                                }
                                cout << "Time: " << time_str << ", Activity: " << current_ptr->activity << endl;
                            }
                            else if (current_ptr->parent->time > time){
                                cout << "Time: " << time_str << ", Activity: " << current_ptr->activity << endl;
                            }
                        }
                        flag = false;
                    }
                }
                else{ // condition that times are equal
                    cout << "Time: " << time_str << ", Activity: " << current_ptr->activity << endl;
                    flag = false;
                }
            }
        }
        
    }
    else{
        cout << "ERROR! Could not print activity at specific time due to illegal time" << endl;
    }
};

void print_activity_and_duration(tree_node *root, int time){
    bool flag = true;
    int counter_right = 0, counter_left = 0; // to check the direction
    string time_str;
    time_str = number_to_time(time);
    
    if (time_check(time)){
        tree_node *temp_ptr;
        tree_node *current_ptr;
        current_ptr = root;
        if (root == NULL){ // nothing added
            cout << "Time period: [00:00 - 00:00]: free" << endl;
        }
        else{
            while(flag){ // while not anything cout
                if (time < current_ptr->time){
                    counter_left ++; // at least 1 time go left
                    if (current_ptr->left != NULL){
                        current_ptr = current_ptr->left;
                    }
                    else{
                        if (counter_right == 0){
                            cout << "Time period: [00:00 - " << number_to_time(current_ptr->time)<< "]: free" << endl;
                        }
                        else{
                            if (current_ptr->parent->time > time){
                                temp_ptr = current_ptr;
                                while(temp_ptr->parent->time > time){
                                    temp_ptr = temp_ptr->parent;
                                }
                                cout << "Time period: [" << number_to_time(temp_ptr->parent->time) << " - " << number_to_time(current_ptr->time) << "]: "<< temp_ptr->parent->activity << endl;
                            }
                            else if (current_ptr->parent->time < time){
                                cout << "Time period: [" << number_to_time(current_ptr->parent->time)<< " - " << number_to_time(current_ptr->time)<< "]: " << current_ptr->parent->activity << endl;
                            }
                        }
                        flag = false;
                    }
                }
                else if (time > current_ptr->time){
                    counter_right ++; // at least 1 time go right
                    if (current_ptr->right != NULL){
                        current_ptr = current_ptr->right;
                    }
                    else{
                        if (counter_left == 0){
                            cout << "Time period: [" << number_to_time(current_ptr->time) << " - 00:00]: " << current_ptr->activity << endl;
                        }
                        else{
                            if (current_ptr->parent->time < time){
                                temp_ptr = current_ptr;
                                while (temp_ptr->parent->time < time){
                                    temp_ptr = temp_ptr->parent;
                                }
                                cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(temp_ptr->parent->time) << "]: "<< current_ptr->activity << endl;
                            }
                            else if (current_ptr->parent->time > time){
                            cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(current_ptr->parent->time) << "]: "<< current_ptr->activity << endl;
                            }
                        }
                        flag = false;
                    }
                }
                else{ // condition that times are equal
                    if ((counter_left == 0) || (counter_right == 0)){
                        if (current_ptr->parent == NULL){
                            if(current_ptr->right != NULL){
                                cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(current_ptr->right->time) << "]: " << current_ptr->activity << endl;
                            }
                            else{
                                cout << "Time period: [" << number_to_time(current_ptr->time) << " - 00:00]: " << current_ptr->activity << endl;
                            }
                        }
                        else if (counter_left == 0){
                            if(current_ptr->right != NULL){
                                cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(current_ptr->right->time) << "]: " << current_ptr->activity << endl;
                            }
                            else{
                                cout << "Time period: [" << number_to_time(current_ptr->time) << " - 00:00]: " << current_ptr->activity << endl;
                            }
                        }
                        else if (counter_right == 0){
                            if (current_ptr->right == NULL){
                                cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(current_ptr->parent->time) << "]: " << current_ptr->activity << endl;
                            }
                            else{
                                temp_ptr = current_ptr->right;
                                while ((temp_ptr->left != NULL) && (temp_ptr->left->time < temp_ptr->time)){
                                    temp_ptr = temp_ptr->left;
                                }
                                cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(temp_ptr->time)<< "]: " << current_ptr->activity << endl;
                            }
                        }
                    }
                    else{
                        if (current_ptr->parent->time < time){
                            temp_ptr = current_ptr;
                            while (temp_ptr->parent->time < time){
                                temp_ptr = temp_ptr->parent;
                            }
                            cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(temp_ptr->parent->time) << "]: "<< current_ptr->activity << endl;
                        }
                        else if (current_ptr->parent->time > time){
                        cout << "Time period: [" << number_to_time(current_ptr->time) << " - " << number_to_time(current_ptr->parent->time) << "]: "<< current_ptr->activity << endl;
                        }
                    }
                    flag = false;
                }
            }
        }
    }
    else{
        cout << "ERROR! Could not print activity at specific time due to illegal time" << endl;
    }
};

void end_time(tree_node *root, const string &activity, int &counter){
    tree_node *temp_ptr;
    temp_ptr = root;
    if (temp_ptr != NULL){
        end_time(temp_ptr->left, activity, counter);
        if (counter == 0){
            cout << number_to_time(temp_ptr->time) << "]: " << activity << endl;
            counter ++;
        }
        end_time(temp_ptr->right, activity, counter);
    }
};

void print_single_activity(tree_node *root, const string &activity){
    tree_node *current_ptr;
    tree_node *temp;
    current_ptr = root;
    int cntr = 0;
    
    if (activity == "free"){
        if (root != NULL){
            while(root->left){
                root = root->left;
            }
            if (root->time != 0){
                cout << "Time period: [00:00 - " << number_to_time(root->time) << "] - free" << endl;
            }
            return;
        }
        else{
            cout << "Time period: [00:00 - 00:00] - free" <<  endl;
            return;
        }
    }
    
    if (current_ptr != NULL){
        print_single_activity(current_ptr->left, activity);
        if (current_ptr->activity == activity){
            cout << "Time period: [" << number_to_time(current_ptr->time) << " - ";
            if (current_ptr->right != NULL){
                end_time(current_ptr->right, activity, cntr);
            }
            else{
                if(current_ptr->parent != NULL){
                    if (current_ptr->parent->time < current_ptr->time){ // node in right side
                        temp = current_ptr;
                        while((temp->parent != NULL) && (temp->parent->time < temp->time)){
                            temp = temp->parent;
                        }
                        if (temp->parent == NULL){
                            cout << "00:00]: " << activity << endl;
                        }
                        else{
                            cout << number_to_time(temp->parent->time) << "]: " << activity << endl;
                        }
                    }
                    else{ // node in left side
                        cout << number_to_time(current_ptr->parent->time) << "]: " << activity << endl;
                    }
                }
                else{
                    cout << "00:00]: " << activity << endl;
                    return;
                }
            }
        }
        print_single_activity(current_ptr->right, activity);
    }
};

void print_all_activities(tree_node *root){
    // used recursion that prints all nodes
    tree_node *current_ptr;
    current_ptr = root;
    if(current_ptr != NULL){
        print_all_activities(current_ptr->left);
        cout << "[" << number_to_time(current_ptr->time) << "] - " << current_ptr->activity << endl;
        print_all_activities(current_ptr->right);
    }
};

void delete_tree(tree_node *root){
    tree_node *delete_ptr;
    
    if (root == NULL){
        return;
    }
    if ((root->left != NULL) || (root->right != NULL)){
        if((root->left == NULL) && (root->right == NULL)){ // at the bottom
            if(root->time < root->parent->time){ // in the left position
                root->parent->left = NULL;
            }
            else{ // in the right pos
                root->parent->right = NULL;
            }
            delete root;
            return;
        }
    }
    
    while(root->left){
        delete_tree(root->left);
    }
    
    if(root->right){
        delete_tree(root->right);
    }
    
    if(root->parent == NULL){
        delete_ptr = new tree_node(root->time, root->activity);
        delete delete_ptr;
        root = delete_ptr;
        return;
    }
    
    if(root->time < root->parent->time){
        root->parent->left = NULL;
    }
    else{
        root->parent->right = NULL;
    }
    delete root;
};

