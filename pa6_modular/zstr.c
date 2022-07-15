
/*
zstring.c
csc 352
Rahel Gerson
   
The purpose of this library is to have a collection of functions
that can create a zstr string, delete a cstr string, and do various
operations with these strings such as concatenate, search, etc.
*/


//#define debug
#include "zstr.h"
zstr_code zstr_status;
zstr zstr_create(char* initial_data){
    /*
     hold the char array initial_data using the malloc function, store the string length
     and allocated size, and then return a zstr
     */

    int total_bytes = get_total_bytes(initial_data);
    if (total_bytes == -1 ){
        zstr_status = ZSTR_ERROR;
        return NULL;
    }
    int len_str = len_char(initial_data);
    zstr z = calloc(total_bytes, sizeof(char));

    set_status(z, initial_data, &zstr_status, true, false, false); //error check
    if (zstr_status != ZSTR_OK){
        free(z);
        return NULL;
    }
#ifdef debug
    printf("[create] head = %p\n", z);
#endif
    /*
     int* l = (int*)z does 2 things
     1) l and z now point to the same mem addr. modifying the contents of one modifies the contents of the other.
     2) typecasting z to an int* changes the stride amount when accessing z and l:
     accessing a single elem in an int* will access  4 bytes of data, whereas accessing a single elem
     in a char* accesses 1 byte of data
     */
    int* l = (int*)z;
    *l = len_str; // bytes 0-3 of l and z now store len_str
    *(l+1) = total_bytes; // bytes 4-7 of l and z now store  total_bytes.

    int in_i=0; //input iterator
    for (int i = 8; i < 8+len_str; i++){
        *(z+i) = *(initial_data + in_i);
        in_i++;
    }
    *(z+8+len_str) = '\0';
    return z+8; //return a pointer to the begining of data
}



void zstr_destroy(zstr to_destroy){
    //printf("[destroy]head = %p\n", to_destroy-8);
    if (to_destroy == NULL) {
        zstr_status = ZSTR_ERROR;
        return;
    }
    else free(to_destroy-8);
    
}

void zstr_append(zstr* base, zstr to_append){
    if (*base == NULL || to_append == NULL){
        zstr_status = ZSTR_ERROR;
        return;
    }
    int base_data_len,  to_append_data_len;
    int base_tot, to_append_tot;
    char* base_data; char* to_append_data;
    
    get_info(*base, &base_data_len, &base_tot, &base_data);
    get_info(to_append, &to_append_data_len, &to_append_tot, &to_append_data);
    
    /*combine the data fields*/
    char new_data[base_data_len+to_append_data_len+1];
    //char* new_data = NULL;
    strcpy_(new_data, base_data, 0, 0, base_data_len);
    strcpy_(new_data, to_append_data, base_data_len, 0, to_append_data_len);
    
    int new_tot = get_total_bytes(new_data);
    if (new_tot == -1) {
        zstr_status = ZSTR_ERROR;
        return;
    }
    else{
        if ( new_tot > base_tot){ //if we don't have enough room
        zstr new_ = zstr_create(new_data);
        //new_ = *base;
        zstr_destroy(*base); //we freed the data, but the pointer lives on
        *base = new_;
        }
        else{ //if we do have enough room
            base_data_len = len_char(new_data);
            set_info(&(*base), base_data_len, base_tot, new_data, 8);
            
            /*
             THIS WORKS AS AN ALT. TO set_info()
             int* l = (int*)*base;
             *(l-2) = base_data_len;
             int in_i = 0;
             for (int i = 0; i < base_data_len; i++){
                 *(*base + i) = *(new_data + in_i);
                 in_i++;
             }
             *(*(base)+8+to_append_data_len) = '\0';
             */
        }
    set_status(*base, new_data, &zstr_status, false, false, true);
    }//else where combined data len <= 2048
}


int zstr_count(zstr base, zstr to_search){
    /*
    count how many times to_search appears within base.
    return 0 if no match is found.
     */
    if (base == NULL || to_search == NULL){
        zstr_status = ZSTR_ERROR;
        return 0;
    }
    int count = 0;
    int bi = 0;
    while (base[bi] != '\0'){
        bi = find_substr(base, to_search, bi);
        if (bi != -1) {
            count++;
            bi++;
        }
    }
    return count;
}

int zstr_compare(zstr x, zstr y){
    if (x == NULL && y == NULL){
        zstr_status = ZSTR_ERROR;
        return ZSTR_EQUAL;
    }
    else if (x == NULL && !(y == NULL)){
        zstr_status = ZSTR_ERROR;
        return ZSTR_LESS;
    }
    else if (!(x == NULL) && y == NULL){
        zstr_status = ZSTR_ERROR;
        return ZSTR_GREATER;
    }
    else{ //neither is null
        /*
        return:
         ZSTR_GREATER if x > y, ie if first non matching char in x is g.t than that in y
         ZSTR_EQUAL if x == y, and
         ZSTR_LESS if x < y. i.e if first non matching char in x is l.t than that in y
         */
        int x_data_len,  y_data_len;
        int x_tot, y_tot;
        char* x_data; char* y_data;
        
        get_info(x, &x_data_len, &x_tot, &x_data);
        get_info(y, &y_data_len, &y_tot, &y_data);
        
        //iterate until one of the strings is null
        int i = 0;
        while (x[i] != '\0' || x[i] != '\0'){
            if ((int)x[i] > (int)(y[i]))  return ZSTR_GREATER;
            else if ((int)x[i] < (int)(y[i]))  return ZSTR_LESS;
            else i++;
        }
        return ZSTR_EQUAL;
    }
}


zstr zstr_substring(zstr base, int begin, int end){
    /*
     create a new zstr with the contents that are contained within the substring of base
     between begin (inclusive) and end (exclusive). The function should ensure that the new zstr
     created uses the smallest zstr size in order to fit the substring.
     */
    if (!(begin < end)) {
        zstr_status = ZSTR_ERROR;
        return NULL;
    }
    if (base == NULL){
        zstr_status = ZSTR_ERROR;
        return NULL;
    }
   
    int data_len = end-begin;
    char data[data_len];
    strcpy_(data, base, 0, begin, end);
    zstr z = zstr_create(data);
    set_status(z, data, &zstr_status, false, true, false);
    
    
    return z;
}


void zstr_print_detailed(zstr z){
    /*
    STRLENGTH: 20
    DATASIZE: 32
    STRING: >data<*/
    if (z == NULL){
        zstr_status = ZSTR_ERROR;
        return ;
    }
    int* l = (int*)(z-8);
    printf("STRLENGTH: %d\n", *(l));
    printf(" DATASIZE: %d\n", *(l+1));
    printf("   STRING: >");
    for (int i = 0; i < *(l) ; i++){
        printf("%c",*(z+i));
    }
    printf("<\n");
}

// 16, 32, 256, 1024, or 2048
int get_total_bytes(char* data){
    /*determine the total mallocated size based off strlen*/
    int len = len_char(data);
    int min = len+9; //bytes
    if (min <= 16 ) return 16;
    else if (min <= 32) return 32; // 17 < min < 32
    else if (min <= 256) return 256; // 33 < min < 256
    else if (min <= 1024) return 1024; // 257 < min < 1024
    else if (min <= 2048) return 2048;
    else return -1; //data is too big
}


void set_status(zstr z, char* data, zstr_code* zstr_status, bool init, bool substring, bool append){
    //zstr_status is an out_param
    *zstr_status = ZSTR_OK;
    if (init || append){
        if (z == NULL) *zstr_status = ZSTR_ERROR;
        if (len_char(data) + 9 > 2048) *zstr_status = ZSTR_ERROR;
    }
    else if (substring){
        int curr_data_len, tot_bytes;
        get_info(z, &curr_data_len, &tot_bytes, &data);
        
        if ((get_total_bytes(data) > tot_bytes) || //if the old data size cannot hold the new data size (get_total_bytes(data))
            (z == NULL) ||
            (len_char(data) + 9 > 2048))
            *zstr_status = ZSTR_ERROR;
    }
}

void get_info(zstr z, int* data_len, int* total_bytes, char** data){
    if (z==NULL) {
        *data_len = 0;
        *total_bytes = 0;
        *data=NULL;
        return;
    }
    int* l = (int*)(z-8);
    *data_len = *l;
    *total_bytes = *(l+1);
    //printf("%s\n", z);
    
    *data = z;
    //printf("%s\n", *data);
    
//    for (int i = 0; i <= *data_len; i++){
//        *(*data+i) = *(z + i);
//    }
    //strcpy_(*data, (char*)z, 0, 0, *data_len);
}

void set_info(zstr* z, int data_len, int total_bytes, char* data, int start){
    if (z==NULL){
        zstr_status = ZSTR_ERROR;
        return;
    }
    /*
     z is an out param
     start should be:
        0 if we want to start at tthe very head of z, ie passing the raw output of calloc()
        8 if we're starting at the data field of z, ie if you're passing a normal zstr
     */

    
    /*
     1. *(z-8) dereference double ptr; the -8 gets us to the head of z, not the data
     2. typecast as an int ptr to store length info
    
     int* l = (int*)z does 2 things
     1) l and z now point to the same mem addr. modifying the contents of one modifies the contents of the other.
     2) typecasting z to an int* changes the stride amount when accessing z and l:
     accessing a single elem in an int* will access  4 bytes of data, whereas accessing a single elem
     in a char* accesses 1 byte of data
     */
    
    //int* l = (int*)*z-start; //THIS DID NOT MODIFY Z!!
    int* l = (int*)*z; //THIS MODIFIES Z!
    *(l-2) = data_len; // bytes 0-3 of z store data_len
    *(l-1) = total_bytes; //bytes 4-7 of z store total_bytes.
    
    /* set the data field of z*/
    int data_i=0; //data iterator
    int z_start =  8-start; //zstr iterator
    for (int i = z_start; i < z_start  + data_len; i++){
        *(*z+i) = *(data + data_i); //note! *(*(z+i)) gave an error!
#ifdef debug
        printf("%c\n", *(*z+i));
#endif
        data_i++;
    }
    *(*z+data_len) = '\0';
#ifdef debug
    if (*(*z+data_len) == '\0') printf("NULL\n");
#endif
}

//int         (char input[], char search[], int ind){
int zstr_index(zstr base, zstr to_search){
    /* return the index in base where search appears
     ex: if base = blafishes, to_search = fis,
     out should be 3
     */
    if (base == NULL || to_search == NULL){
        zstr_status = ZSTR_ERROR;
        return -1;
    }
    int ind = 0;
    int ll = 0; //iterator for the search term
    int out = ind;
    bool first_match = true;
    
    while(base[ind] != '\0'){
        if(base[ind] == to_search[ll]){
            if (first_match) {
                out = ind;
                first_match = false;
            }
            ll++;
            if (to_search[ll] == '\0')
                return  out;
        }
        else{
            first_match = true;
            ll=0;
        }
        ind++;
    }
    return -1;
}

