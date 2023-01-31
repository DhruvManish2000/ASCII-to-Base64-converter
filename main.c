//
// Credits: Created by chaari on 2021-02-04.
// Questions asked: How to do the if statement for padding

// How to write in a neat manner in the file or is this not required?

#include<stdio.h>
#include <locale.h>
#include <string.h>

#define ERR -1

#define KEYS 64
#define FROM_SIZE 3
#define TO_SIZE 5

int main() {
    FILE* fkey;
    FILE* fin;
    FILE* fout;
    setlocale(LC_ALL, "en_US.UTF-8");

    // Change the path to the files

    char fkey_path[] = "/Users/dhruvmanish/desktop/lab_2/Key.dat"; //(mac OS or Linux)
    char fin_path[] = "/Users/dhruvmanish/desktop/lab_2/Raw.dat";
    char fout_path[] = "/Users/dhruvmanish/desktop/lab_2/Encoded.dat";

    // declaration of variables
    unsigned char buf_in[FROM_SIZE];
    unsigned char buf_out[TO_SIZE];
    char keys[64];
    int count = 0;
    int total_char = 0;
    size_t read_fin;
    unsigned char copy[3];

// First file for key
    fkey=fopen(fkey_path,"r");
    //load Key.dat
if (fkey == NULL){
    printf("File cannot be found, please enter the correct path in code");
    return ERR;
}
fread(keys, 1, 64, fkey);

// second file
    fin=fopen(fin_path,"r");
    //open  Raw.dat in reading mode
if (fin == NULL){
    printf("File cannot be found, please enter the correct path in code");
    return ERR;
}

    fout=fopen(fout_path,"w");
    //open  Encoded.dat in writing mode
    // no file detected then display user an error
    if (fout == NULL){
        printf("File cannot be found, please enter the correct path in code");
        return ERR;
    }

    //Conversion from ASCII to Base64, 3, 2 or 1 bytes read from raw.dat

while (read_fin!=0) {

    // reading the file raw.dat 3 char at a time
    read_fin = fread(buf_in, 1, 3, fin);

    if(read_fin == 3) {

        // to check when to enter a new line
        if (count == 12) {
            buf_out[0] = '\n';
            fwrite(buf_out, 1, 1, fout);
            count = 0;
        }
        // total char counter, when to go to a new line
        total_char++;

        // first base 64 value calculation
        copy[0] = buf_in[0];
        copy[0] = copy[0] >> 2;

        // finding the corresponding value in keys array to convert to base 64, similar with all other tempvars with different numbers
        int tempvar_1 = 0;
        tempvar_1 = copy[0];
        buf_out[0] = keys[tempvar_1];

        // second base 64 value calculation
        copy[1] = buf_in[1];
        copy[1] = copy[1] >> 2;
        buf_in[0] = buf_in[0] << 6;
        copy[1] = buf_in[0] | copy[1];
        copy[1] = copy[1] >> 2;

        int tempvar_2 = 0;
        tempvar_2 = copy[1];
        buf_out[1] = keys[tempvar_2];

        // third base 64 value calculation
        copy[2] = buf_in[2];
        copy[2] = copy[2] >> 6;
        buf_in[1] = buf_in[1] << 4;
        buf_in[1] = buf_in[1] >> 2;
        copy[2] = buf_in[1] | copy[2];

        int tempvar_3 = 0;
        tempvar_3 = copy[2];
        buf_out[2] = keys[tempvar_3];

        // fourth base 64 value
        buf_in[2] = buf_in[2] << 2;
        buf_in[2] = buf_in[2] >> 2;

        int temp_var4 = 0;
        temp_var4 = buf_in[2];
        buf_out[3] = keys[temp_var4];

            // writing the character with spacing after every 8 set of char in a row and saving Base64 text into a file
            if (total_char == 2) {
                buf_out[4] = ' ';
                total_char = 0;
                fwrite(buf_out, 5, 1, fout);
            }
            else {
                fwrite(buf_out, 4, 1, fout);
            }
        // counter increment
        count++;
    }
    // 2 bytes read from raw.dat
    else if(read_fin == 2)
    {
        // first base 64 value
        copy[0] = buf_in[0];
        copy[0] = copy[0] >> 2;

        int tempvar_7 = 0;
        buf_out[0] = keys[tempvar_7];

        // Second base 64 value
        copy[1] = buf_in[1];
        copy[1] = copy[1] >> 2;
        buf_in[0] << 6;
        copy[1] = buf_in[0] | copy[1];
        copy[1] = copy[1] >> 2;

        int tempvar_8 = 0;
        tempvar_8 = copy[1];
        buf_out[1] = keys[tempvar_8];

        // Third base 64 value
        unsigned char allones = ~0;
        allones = allones >> 4;
        buf_in[1] = buf_in[1] & allones;

        int tempvar_9 = 0;
        tempvar_9 = buf_in[1];
        buf_out[2] = keys[tempvar_9];

        // Fourth base 64 value
        unsigned char tempvar_10[0];
        tempvar_10[0] = '=';
        buf_out[3] = tempvar_10[0];

        //Saving Base64 text into a file
       fwrite(buf_out, 4, 1, fout);
    }

    // 1 bytes read
    else if(read_fin == 1){
        // base 64 first value
        copy[0] = buf_in[0];
        copy[0] = copy[0] >> 2;

        int tempvar_4 = 0;
        tempvar_4 = copy[0];
        buf_out[0] = keys[tempvar_4];

        // base 64 second value
        copy[1] = buf_in[1];
        buf_in[0] = buf_in[0] << 6;
        buf_in[0] = buf_in[0] >> 2;

        int tempvar_5 = 0;
        tempvar_5 = buf_in[0];
        buf_out[1] = keys[tempvar_5];

        // base 64 third and fourth value
        unsigned char tempvar_6[0];
        tempvar_6[0] = '=';
        buf_out[2] = tempvar_6[0];
        buf_out[3] = tempvar_6[0];

        //Saving Base64 text into a file
       fwrite(buf_out, 4, 1, fout);
    }
}

// close the files raw.dat and encoded.dat
    fclose(fin);
    fclose(fout);

    return 0;
}
