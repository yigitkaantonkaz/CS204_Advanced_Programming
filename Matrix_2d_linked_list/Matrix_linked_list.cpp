#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "sparse_matrix_2d_linked_list.h"

using namespace std;

row_node* read_matrix(const string& filename, int& num_rows, int& num_columns){
    //Reading file
    ifstream ifstream_input;
    string text_line;
    int counter = 0, current_num, current_column = 0, current_row = -1, counter_node = -1;
    row_node* head;
    row_node* head_ptr;
    row_node* row_ptr;
    cell_node* current_ptr;
    cell_node* temp_ptr;
    
    ifstream_input.open(filename.c_str());
    ifstream read_file(filename);
    
    //getting every line of the file until it ends
    while (getline(read_file,text_line)){
        istringstream iss_values(text_line); //taking each values
        if (counter == 0){ //using counter as checking the first line of the file
            iss_values >> num_rows >> num_columns;
            counter ++;
        }
        else {
            current_row ++;
            head_ptr = new row_node();
            //checking if it is first row
            if (current_row > 0){
                row_ptr->down = head_ptr;
                row_ptr = row_ptr->down;
            }
            while (iss_values >> current_num){
                if (current_num != 0){
                    counter_node ++;
                        temp_ptr = new cell_node;
                        temp_ptr->value = current_num;
                        temp_ptr->column = current_column;
                    // first cell creating
                    if (counter_node == 0){
                        head_ptr->cell = temp_ptr;
                        current_ptr = head_ptr->cell;
                        current_ptr->left  = NULL;
                        current_ptr->right  = NULL;
                        counter_node ++;
                    }
                    else if (counter_node > 0){
                        temp_ptr->left = current_ptr;
                        current_ptr->right = temp_ptr;
                        current_ptr = current_ptr->right;
                        current_ptr-> right = NULL;
                    }
                }
                current_column ++;
            }
            // program get in if statement when all values of line are equal to zero
            if (counter_node == -1){
                head_ptr->cell = NULL;
            }
            // create a head pointer to indicate the head of row_node
            if (current_row == 0){
                row_ptr = head_ptr;
                head = row_ptr;
            }
        row_ptr->down = nullptr;
        counter_node = -1;
        current_column = 0;
        }
    }
    
    ifstream_input.close(); ifstream_input.clear();
    read_file.close(); read_file.clear();
    
    return head;
};

void print_matrix(row_node* head, int num_rows, int num_columns){
    cell_node* cnst_ptr;
    row_node* cnst_head;
    cnst_head = head;
    
    for (int i = 0; i < num_rows; i++){ // for each row
        cnst_ptr = head->cell;
        for (int k = 0; k < num_columns; k++){ // for each column
            if (head->cell == NULL){ // means that all the line values are equal to 0
                cout << 0 << " ";
            }
            else{
                if (head->cell->column == k){ //checking if it is matching
                    // getting into the if statement means that
                    // value is different than zero
                    // so that it can be printed
                    cout << head->cell->value << " ";
                    head->cell = head->cell->right;
                }
                else {
                    cout << 0 << " ";
                }
            }
        }
        head->cell = cnst_ptr;
        cout << endl;
        // initializing head again due to increasing row number
        head = head->down;
    }
    head = cnst_head;
};

void delete_matrix(row_node* head){
    row_node* temp_ptr;
    
    while (head->down != NULL){ //to check if it is finished
        temp_ptr = head;
        // making head last cell node of the row
        if (head->cell != NULL){
            while (head->cell->right != NULL){
                head->cell = head->cell->right;
            }
            // shifting the head to left to delete the cell on right
            while (head->cell->left != NULL){
                head->cell = head->cell->left;
                delete head->cell->right;
            }
            delete head->cell; // deleting last cell of the row
        }
        // moving to the next row, deleting the upper row_node
        temp_ptr = temp_ptr->down;
        delete head;
        head = temp_ptr;
    }
};

row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns){
    row_node* result_head; // pointer that should be return
    row_node* head_ptr;
    row_node* row_ptr;
    cell_node* current_ptr;
    cell_node* temp_ptr;
    
    cell_node* left_cnst_ptr;
    cell_node* right_cnst_ptr;
    // used as a constant ptr for the first cell node of the current row
    
    row_node* left_head_cnst;
    row_node* right_head_cnst;
    //used as a cnst ptr for head ptr to able to return the beginning
    int sum = 0, cntr = 0;
    
    left_head_cnst = left;
    right_head_cnst = right;
    
    left_cnst_ptr = left->cell;
    right_cnst_ptr = right->cell;
    
    //left means left head
    //right means right head
    for (int i = 0; i < num_rows; ++i){
        head_ptr  = new row_node;
        if (i == 0){// means first row node created
            result_head = head_ptr;
        }
        else{ // used when creating second or more row nodes
            row_ptr->down = head_ptr;
        }
        for (int j = 0; j < num_columns; ++j){
            if (left->cell != NULL){ //checking if the row is empty or not
                if (left->cell->column == j){ //checking whether the current value is zero or non zero value
                    sum += left->cell->value;
                }
            }
            
            if (right->cell != NULL){ //checking if the row is empty or not
                if (right->cell->column == j){ //checking if the current value is zero or non zero value
                    sum += right->cell->value;
                }
            }
            
            if (sum != 0){ // when sum != 0, it should be store in a cell node
                temp_ptr = new cell_node;
                if (cntr == 0){ //checking if it is the first cell or not
                    head_ptr->cell = temp_ptr;
                    current_ptr = head_ptr->cell;
                    cntr ++;
                }
                else{ // means another cell node created before
                    temp_ptr->left = current_ptr;
                    current_ptr->right = temp_ptr;
                    current_ptr = current_ptr->right;
                }
                temp_ptr->column = j; //initializing current column
                if (left->cell != NULL){
                    if (left->cell->column == j){
                        temp_ptr->value += left->cell->value;
                        if (left->cell->right != NULL){
                            left->cell = left->cell->right;
                        }
                    }
                }
                
                if (right->cell != NULL){
                    if (right->cell->column == j){
                        temp_ptr->value += right->cell->value;
                        if (right->cell->right != NULL){
                            right->cell = right->cell->right;
                        }
                    }
                }
            }
            //below are cases that have values making each other zero
            if (left->cell != NULL){
                if ((sum == 0) && (left->cell->column == j)){
                    if (left->cell->right != NULL){
                        left->cell = left->cell->right;
                    }
                }
            }
            if (right->cell != NULL){
                if ((sum == 0) && (right->cell->column == j)){
                    if (right->cell->right != NULL){
                        right->cell = right->cell->right;
                    }
                }
            }
            sum = 0;
        }
        // returning cell ptr to the first cell node
        left->cell = left_cnst_ptr;
        right->cell = right_cnst_ptr;
        cntr = 0;
        // shifting head ptr to down until it reaches last row node
        if (left->down != NULL){
            left = left->down;
        }
        if(right->down != NULL){
            right = right->down;
        }
        left_cnst_ptr = left->cell;
        right_cnst_ptr = right->cell;
        row_ptr = head_ptr;
    }
    //returning back the head ptr to the real head ptr
    left = left_head_cnst;
    right = right_head_cnst;
    
    return result_head;
};

row_node* transpose(row_node* head, int num_rows, int num_columns){
    row_node* transpose_head;
    row_node* row_ptr;
    row_node* head_ptr;
    cell_node* current_ptr;
    cell_node* temp_ptr;
    row_node* head_cnst;
    int cntr = 0;
    
    head_cnst = head;
    
    for(int i = 0; i < num_columns; i++){
        head_ptr = new row_node;
        if (i == 0){ // checking first row node
            transpose_head = head_ptr;
        }
        else{
            row_ptr->down = head_ptr;
        }
        for(int k = 0;k < num_rows; k++){
            if (head->cell != NULL){ // checking is row is empty or not
                if (head->cell->column == i){ // checking value is different than zero
                    temp_ptr = new cell_node;
                    if (cntr == 0){ // first cell creating
                        head_ptr->cell = temp_ptr;
                        current_ptr = head_ptr->cell;
                    }
                    else{
                        temp_ptr->left = current_ptr;
                        current_ptr->right = temp_ptr;
                        current_ptr = current_ptr->right;
                    }
                    if (head->cell->column == i){ //means that it has a value different than zero
                        temp_ptr->value = head->cell->value;
                        if (head->cell->right != NULL){
                            head->cell = head->cell->right;
                        }
                        temp_ptr->column = k;
                    }
                    cntr ++;
                }
            }
            if (head->down != NULL){
                head = head->down;
            }
        }
        cntr = 0;
        row_ptr = head_ptr;
        head = head_cnst;
    }
    // getting back head ptr and head->cell ptr
    for (int j = 0; j < num_rows ; j++){
        if (head->cell != NULL){
            while (head->cell->left != NULL){
                head->cell = head->cell->left;
            }
            if (head->down != NULL){
                head = head->down;
            }
        }
    }
    head = head_cnst;
    
    return transpose_head;
};

bool is_symmetric(row_node* head, int num_rows, int num_columns){
    
        if (num_rows == num_columns){ // checking row == col
            
        //called func to get tranposed head ptr
        row_node* transpose_head = transpose(head, num_rows, num_columns);
        
        row_node* head_cnst;
        row_node* transpose_cnst;
        cell_node* head_cnst_ptr;
        cell_node* transpose_cnst_ptr;
        int current_head_value, current_transpose_value;
        
        head_cnst = head;
        head_cnst_ptr = head->cell;
        
        transpose_cnst = transpose_head;
        transpose_cnst_ptr = transpose_head->cell;
        
        /*  calling the transpose version of matrix
            to test it is symmetric or not
            because if the transpose version is the same with the matrix itself
            then it should be symmetric */
        
        for (int i = 0; i < num_rows; ++i){
            for(int j = 0; j < num_columns; j++){
                if (head->cell != NULL){
                    if(head->cell->column == j){
                        current_head_value = head->cell->value;
                        if (head->cell->right != NULL){
                            head->cell = head->cell->right;
                        }
                    }
                    else{
                        current_head_value = 0;
                    }
                }
                else {
                    current_head_value = 0;
                }
                if (transpose_head->cell != NULL){
                    if(transpose_head->cell->column == j){
                        current_transpose_value = transpose_head->cell->value;
                        if (transpose_head->cell->right != NULL){
                            transpose_head->cell = transpose_head->cell->right;
                        }
                    }
                    else {
                        current_transpose_value = 0;
                    }
                }
                else{
                    current_transpose_value = 0;
                }
                // checking current value is same or not in both matrices
                // if not return false
                if (current_head_value != current_transpose_value){
                    head->cell = head_cnst_ptr;
                    transpose_head->cell = transpose_cnst_ptr;
                    return false;
                }
            }
            // getting back the head pointers
            head->cell = head_cnst_ptr;
            transpose_head->cell = transpose_cnst_ptr;
            if (head->down != NULL){
                head = head->down;
            }
            if (transpose_head->down != NULL){
                transpose_head = transpose_head->down;
            }
            head_cnst_ptr = head->cell;
            transpose_cnst_ptr = transpose_head->cell;
        }
        head = head_cnst;
        transpose_head = transpose_cnst;
            
        return true; // it is symmetric
    }
    return false; // means row != col
};
