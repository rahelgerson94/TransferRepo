//
//  Rahel Gerson
//  pa3
//  csc352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end);
int len(int arr[]);
int assign_line(char *out, char *in, int out_start, int in_start, int in_end);
void reset_char_arr(char arr[], int start, int end);
void reset_int_arr( int arr[], int start, int end, int val);

void scut_line(char *output, char *input, int *col_list, int *delim_locs);
int len_int(int arr[]);
int len_char(char *arr);
void parse_cmd_args(char *input, int *output);
void find_locs(char *input, int *delim_locs, char delim);
void print_int_arr(int *arr);
// void get_separation_locs(char input[], char delim,int startLoc, int endLoc,int Output[]);
void get_separation_locs(char input[], char delim, int start_loc, int end_loc, int output[]);
void get_separation_locs_ws(char input[], int startLoc, int endLoc, int output[]);
void scut_letters(char input[], int cols2keep[], char output[]);

int find_double_digit(char *input); // return the index of the first digit of the 2 digit number
void parse_cmd_args_double(char *input, int *output, int start_idx);
void parse_cmd_args_single(char *input, int *output, int end_idx);
// void get_separation_locs(char input[],char delim,int startLoc, int endLoc,int output[], char delim_type);
void de_escape(char *arr);
int count(char *str, char ch);
void parse_cmd_args2(char input[], int output[]);
int char2num(char Input);
int check_argc(int argc);
int check_sel(char sel[]);
int check_type(char delim_type);
// int combineElements(int arr[],int cc);
int combineElements(char arr[], int cc);
int expandList(char input[], int output[]);
void transform_input(char output[], char input[], char delim_type);
int checkCharLoc(char input[],char b);
void transform_input_ws(char out[], char in[]);
void intcpy_(int dst[], int src[], int out_start, int in_start, int in_end);

char output[102];
char curr_trans[102];
int flag = 0;
char delim_type;
//char input[102];
char curr_line[102]; // null charachter and newline

int main(int argc, const char *argv[])
{
    // declarations
    int cols2keep[100]; reset_int_arr(cols2keep, 0,100, -1);
    int delim_locs[100]; reset_int_arr(delim_locs, 0,100, -1);
    int new_line_locs[100] = {-1}; reset_int_arr(new_line_locs, 0,100, -1);
   
    // Check for valid arg count
    if (argc != 3)
    {
        fprintf(stderr, "expected 2 command line arguments.\n");
        return -1;
    }

    // Check flag to see which mode we're in and abort if invalid
    if (strcmp(argv[1], "-l") == 0)
    {
        delim_type = 'l';
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        delim_type = 'c';
    }
    else if (strcmp(argv[1], "-w") == 0)
    {
        delim_type = 'w';
    }
    else
    {
        fprintf(stderr, "Invalid delimiter type.\n");
        return -1;
    }
    //check the col list is valid
    char *col_list = (char *)argv[2];
    flag = check_sel(col_list);
    if (flag == -1)
        return -1;
    else
    {
        parse_cmd_args2(col_list, cols2keep);
    };

    
    while(fgets(curr_line, 100, stdin) != NULL ){
        
        reset_char_arr(output, 0, 100);
        reset_int_arr(delim_locs, 0, 100, -1);
        reset_char_arr(curr_trans, 0, 100);
        
        if (delim_type == 'l')
        {
            scut_letters(curr_line, cols2keep, output);
        }
        else if (delim_type == 'w'){
            transform_input_ws(curr_trans, curr_line);
            get_separation_locs_ws(curr_trans, 0, -1, delim_locs);
            scut_line(output, curr_trans, cols2keep, delim_locs);
        }
        else
        {
            transform_input(curr_trans, curr_line, 'c');
            get_separation_locs(curr_trans, 'c', 0, -1, delim_locs);
            scut_line(output, curr_trans, cols2keep, delim_locs);
        }
        
        
    }
    return 0;
}

void scut_line(char *output, char *input, int *col_list, int *delim_locs){
    int ii = 0;
    int start = ii;
    int col = 0;
    char word[100] = {'\0'};
    while (delim_locs[ii] > 0)
    {
        col++;
        //memcpy(word, &input[start], delim_locs[ii] - start);
        strcpy_(word, input, 0, start, delim_locs[ii]);
        //strcpy_(char dst[], char src[], int out_start, int in_start, int in_end)
        int cc = 0;
        while (col_list[cc] > 0)
        {
            if (col_list[cc] == col)
            {
                // printf("The Correct Word >> %s\n",word);
                printf("%s ", word);
                break;
            }
            cc++;
        }
        start = delim_locs[ii] + 1;
        ii++;
        //memset(word, '\0', 100);
        reset_char_arr(word, 0, 100);
        //memset(output, '\0', 100);
        reset_char_arr(output, 0, 100);
    }
    printf("\n");
}


int assign_line(char *out, char *in, int out_start_curr, int in_start, int in_end)
{
    int out_start_next;
    int len = in_end - in_start;
    for (out_start_next = out_start_curr; out_start_next < out_start_curr + len; out_start_next++)
    {
        out[out_start_next] = in[in_start];
        in_start++;
    }
    return out_start_next + 1; // take into account the space after the word
}

void reset_char_arr(char arr[], int start, int end)
{
    for (int i = start; i < end; i++)
    {
        arr[i] = '\0';
    }
}

void reset_int_arr(int arr[], int start, int end, int val)
{
    for (int i = start; i < end; i++)
    {
        arr[i] = val;
    }
}

// void get_separation_locs(char Input[],char delim,int startLoc, int endLoc,int Output[]){
//     if(endLoc == -1){
//         endLoc = 100;
//     }
//     int ll=0;
//     for(int ii = startLoc;ii < endLoc;ii++){
//         if(Input[ii] == delim || Input[ii] == '\n'){
//             Output[ll++] = ii;
//         }else if(Input[ii] == '\0') {
//             Output[ll++] = ii;
//             break;
//         }
//     }
// }

void get_separation_locs(char input[], char delim_type, int startLoc, int endLoc, int output[]){
    char delim;
    if (delim_type == 'c'){
        delim = ',';
    }
    else if (delim_type == '\n'){
        delim = '\n';
    }
    if (endLoc == -1)
    {
        endLoc = 100;
    }
    int ll = 0;
    for (int ii = startLoc; ii < endLoc; ii++)
    {
        if (input[ii] == delim || input[ii] == '\n')
        {
            output[ll++] = ii;
        }
        else if (input[ii] == '\0')
        {
            output[ll++] = ii;
            break;
        }
    }
}
void get_separation_locs_ws(char input[], int startLoc, int endLoc, int output[]){
    if (endLoc == -1)
    {
        endLoc = 100;
    }
    int ll = 0;
    for (int ii = startLoc; ii < endLoc; ii++)
    {
        if (input[ii] == ' ' ||input[ii] == '\t' || input[ii] == '\n')
        {
            output[ll++] = ii;
        }
        else if (input[ii] == '\0')
        {
            output[ll++] = ii;
            break;
        }
        
    }
}
void scut_letters(char input[], int cols2keep[], char output[])
{
    int output_idx = 0;
    int num_cols = len_int(cols2keep);
    // printf("%d", num_cols);
    for (int i = 0; i < num_cols; i++)
    {
        int col = cols2keep[i] - 1; // make zero idx
        output[output_idx] = input[col];
        output[output_idx + 1] = ' ';
        output_idx = output_idx + 2;
    }
    printf("%s\n", output);
}

void find_locs(char *input, int *delim_locs, char delim)
{
    int in_idx = 0;
    int out_idx = 0;

    while (input[in_idx] != '\0')
    {
        if (input[in_idx] == delim)
        {
            delim_locs[out_idx] = in_idx;
            out_idx++;
        }
        in_idx++;
    }
    delim_locs[out_idx] = -1;
}

// find the length of an int array
int len_int(int arr[])
{
    int i = 0;
    int len = 0;
    while (arr[i] >= 0){ //!= -1){
        //printf("%d ",arr[i] ) ;
        len++;
        i++;
    }
    return len;
}

int len_char(char *arr)
{
    int i = 0;
    int len = 0;
    while (arr[i] != '\0')
    {
        if (arr[i] == '\n')
            continue;
        else
        {
            len++;
        }
        i++;
    }
    return len;
}

void parse_cmd_args2(char input[], int output[])
{
    int Start = 0;
    // int End = 0;
    int ii = 0;
    int extra = 0;
    int commas[100] = {0};
    // int num;
    get_separation_locs(input, 'c', 0, -1, commas);
    while (commas[ii] > 0)
    {
        char dst[100] = {'\0'};
        reset_char_arr(dst, 0,100);
        strcpy_(dst, input, 0, Start, commas[ii]);
        if (checkCharLoc(dst, '-') >= 0){
            int expandedList[100] = {-1};
            reset_int_arr(expandedList, 0,100, -1);
            int len = expandList(dst, expandedList);
            intcpy_(output, expandedList, ii + extra, 0, len);
            extra += (len -1);
            Start = commas[ii] + 1;
            ii++;
        }else{
        int num = combineElements(dst, commas[ii] - Start);
        output[ii] = num;
        Start = commas[ii] + 1;
        ii++;
        }
    }
}
int char2num(char Input)
{
    int out = Input - '0';
    if (out > 9 || out < 0)
    {
        return -1;
    }
    return out;
}
// int combineElements(int arr[],int cc){
//     int out = 0;
//     int mult = 1;
//     for (int ii = cc - 1; ii >= 0; ii--){
//         out += arr[ii] * mult;
//         mult = mult*10;
//     }
// }
int checkCharLoc(char input[],char b){
    int ii = 0;
    while(input[ii] != '\0'){
        if (input[ii] == b) return ii;
        ii++;
    }
    return -1;
}
int combineElements(char arr[], int cc)
{
    int nums[100] = {-1};

    for (int ll = 0; ll < cc; ll++)
    {

        int temp = char2num(arr[ll]);
        // TODO : fix the zero problem
        if (temp >= 0)
            nums[ll] = temp;
        else
        {
            char dst[100] = {'\0'};
            int expandedList[100] = {-1};
            reset_int_arr(expandedList, 0,100, -1);
            int Size = len_char(arr);
            strcpy_(dst, arr, 0, ll + 1, Size);
            expandList(dst, expandedList);
//            int num2go2 = combineElements(dst, Size - ll - 1);
//            int Add = 1;
//            while (nums[jj - 1] != num2go2)
//            {
//                nums[jj++] = nums[ll - 1] + Add++;
//            }
//            ll = jj + 1;
        }
    }
    int out = 0;
    int mult = 1;
    for (int ii = cc - 1; ii >= 0; ii--)
    {
        out += nums[ii] * mult;
        mult = mult * 10;
    }
    return out;
}
int expandList(char input[], int output[]){
    int check = checkCharLoc(input,'-');
    if(check < 0) return -1;
    output[0] = combineElements(input, check);
    int ll = 1;
    while (input[ll] >=0){
        int jj = ll;
        char dst[100] = {'\0'};
        int Size = len_char(input);
        strcpy_(dst, input, 0, check + 1, Size);
        int num2go2 = combineElements(dst, Size - check - 1);
        int Add = 1;
        while (output[jj - 1] != num2go2)
        {
            output[jj++] = output[ll - 1] + Add++;
        }
        return jj;
        ll = jj + 1;
    }
    ll++;
    return ll;
}
void parse_cmd_args(char *input, int *output)
{
    int out_idx = 0;
    int dd_begin = find_double_digit(input);
    int num_iters = count(input, ',') + 1;

    // single digits only
    if (dd_begin < 0)
    {
        for (int i = 0; out_idx <= num_iters; i = i + 2)
        {
            output[out_idx] = atoi(&input[i]); // make 0 indexed
            out_idx++;
        }
        output[out_idx] = -1;
        return;
    } // endif

    // list contains only double digits
    else if (dd_begin == 200)
    {
        char val[2];
        int out_idx = 0;
        for (int i = 0; out_idx <= num_iters; i = i + 3)
        {
            val[0] = input[i];
            val[1] = input[i + 1];
            output[out_idx] = atoi(val);
            // printf("%d ", output[out_idx]);
            out_idx++;
            //memset(val, '0', 2);
            reset_char_arr(val, 0, 2);
            
        }
        output[out_idx] = -1;
    }

    // list contains double digits and single digits
    else
    {
        char val[2];
        for (int i = 0; i < dd_begin - 1; i = i + 2)
        {
            output[out_idx] = atoi(&input[i]); // make 0 indexed
            out_idx++;
        }
        for (int i = dd_begin; out_idx < num_iters + 1; i = i + 3)
        {
            val[0] = input[i];
            val[1] = input[i + 1];
            output[out_idx] = atoi(val);
            // printf("%d ", output[out_idx]);
            out_idx++;

            //memset(val, '0', 2);
            reset_char_arr(val, 0, 2);
        }
        output[out_idx] = -1;
    }
}

void parse_cmd_args_double(char *input, int *output, int start_idx)
{
    char val[2];
    int out_idx = 0;
    for (int i = start_idx; input[i] != '\0'; i++)
    {
        if (input[i] == ',')
            continue;

        else
        {
            val[0] = input[i];
            val[1] = input[i + 1];
            output[out_idx] = atoi(val);
            out_idx++;
        }
    }
    output[out_idx] = -1;
}

int find_double_digit(char *input)
{ // return the index of the first digit of the 2 digit number

    if (input[0] != ',' && input[1] != ',')
        return 200; // 200 means only double digits

    else
    {
        for (int i = 0; input[i] != '\0'; i++)
        {
            // 2 digit
            if (input[i] == ',' && input[i + 1] != ',' && input[i + 2] != ',')
                return i + 1;
        }
    }

    return -1; //
}

void strcpy_(char dst[], char src[], int out_start, int in_start, int in_end)
{
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        dst[out_i] = src[in_i];
        in_i++;
    }
}
void intcpy_(int dst[], int src[], int out_start, int in_start, int in_end)
{
    int len = in_end - in_start;
    int in_i = in_start;
    for (int out_i = out_start; out_i < out_start + len; out_i++)
    {
        dst[out_i] = src[in_i];
        in_i++;
    }
}

void print_int_arr(int *arr)
{
    printf("{ ");
    int length = len_int(arr);

    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            printf("%d }\n", arr[i]);
            return;
        }
        else
        {
            printf("%d, ", arr[i]);
        }
    }
}

void de_escape(char *arr)
{
    int curr = 0;
    int next = 1;
    while (arr[next] != '\0')
    {
        if (arr[curr] == '\\' && arr[next] == 'n')
        {
            arr[curr] = '\n';
            int temp = next;
            while (arr[temp] != '\0')
            {
                arr[temp] = arr[temp + 1];
                temp++;
            }
        }
        curr++;
        next++;
    }
}

int count(char *str, char ch)
{
    int i = 0;
    int count = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ch)
            count++;
        i++;
    }
    return count;
}

int check_argc(int argc)
{
    if (argc - 1 != 2)
    {
        // TODO : make this print to standard error
        printf("expected 2 command line arguments.\n");
        return -1;
    }
    else
        return 0;
}

int check_type(char delim_type)
{
    // TODO : make this print to standard error
    if (delim_type == 'c' || delim_type == 'l' || delim_type == 'w')
        return 0;

    else
    {
        printf("Invalid delimiter type.\n");
        return -1;
    }
}

int check_sel(char sel[])
{
    if (atoi(&sel[0]) == 0)
    {
        printf("Invalid selection.\n");
        return -1;
    }
    int i;
    // check only dashes and commas and digits
    for (i = 0; sel[i] != '\0'; i++)
    {
        if (!(sel[i] == ',' || sel[i] == '-' || char2num(sel[i]) >= 0))
        {
            printf("Invalid selection.\n");
            return -1;
        }
    }
    // check last char is a digit
    if (char2num(sel[i - 1]) < 0)
    {
        printf("Invalid selection.\n");
        return -1;
    }
    else
        return 0;
}


void transform_input(char out[], char in[], char delim_type){
    int in_start = 0, in_end = in_start+1;
    int out_start=0;
    int end_delim_loc;
    char delim;
    if (delim_type == 'c'){
         delim = ',';
    }
        while (in[in_start] != '\0'){
            if (in[in_start] == delim){
                if (in[in_start+1] == delim){
                    end_delim_loc = in_start +1;
                    while (in[end_delim_loc] == delim)
                        end_delim_loc++;
                    
                    strcpy_(out, in, out_start, in_start , in_start+1);
                    in_start = end_delim_loc;
                }
                else{
                    in_end = in_start+1;
                    strcpy_(out, in, out_start, in_start , in_end);
                    in_start++;
                }
                
            }
            else{
                in_end = in_start+1;
                strcpy_(out, in, out_start, in_start , in_end);
                in_start++;
            }
            
            out_start++;
            //printf("%s\n", out);
        }
    
                
      
}

void transform_input_ws(char out[], char in[]){
    int in_start = 0, in_end = in_start+1;
    int out_start=0;
    int end_delim_loc;
    
        while (in[in_start] != '\0'){
            if (in[in_start] == ' ' || in[in_start] == '\t'){
                if (in[in_start+1] == ' ' || in[in_start+1] == '\t'){
                    end_delim_loc = in_start +1;
                    while (in[end_delim_loc] == ' ' || in[end_delim_loc] == '\t')
                        end_delim_loc++;
                    
                    strcpy_(out, in, out_start, in_start , in_start+1);
                    in_start = end_delim_loc;
                }
                else{
                    in_end = in_start+1;
                    strcpy_(out, in, out_start, in_start , in_end);
                    in_start++;
                }
                
            }
            else{
                in_end = in_start+1;
                strcpy_(out, in, out_start, in_start , in_end);
                in_start++;
            }
            
            out_start++;
            //printf("%s\n", out);
        }
    
                
      
}

