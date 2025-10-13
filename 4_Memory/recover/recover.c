#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    uint8_t buffer[512];
    uint8_t jpeg_signatures[] = {0xff, 0xd8, 0xff};
    FILE *card;
    FILE *destination = NULL;
    char *raw_file = argv[1];
    // char *img_file_name = "recovered";
    int file_count = 000;
    char file_count_string[10];
    char final_destination_string[20];

    // accept exactly one command-line argument, or return 1
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // return 1 if can't open memory card
    card = fopen(raw_file, "r");
    if (card == NULL)
    {
        printf("Can't open memory card for reading");
        return 1;
    }

    // While there's still data left to read from the memory card
    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        // if first jpeg, write first file
        if (buffer[0] == jpeg_signatures[0] && buffer[1] == jpeg_signatures[1] &&
            buffer[2] == jpeg_signatures[2] && (buffer[3] & 0xf0) == 0xe0)
        {
            // close previous file
            if (destination != NULL)
            {
                fclose(destination);
            }

            // create string from file_count
            sprintf(file_count_string, "%d", file_count);

            // concatenate destination string ("prefix"+file_count+"sufix")
            if (file_count < 10)
            {
                strcpy(final_destination_string, "00");
                strcat(final_destination_string, file_count_string);
                strcat(final_destination_string, ".jpg");
                printf("%s\n", final_destination_string);
            }
            if (file_count > 9 && file_count < 100)
            {
                strcpy(final_destination_string, "0");
                strcat(final_destination_string, file_count_string);
                strcat(final_destination_string, ".jpg");
                printf("%s\n", final_destination_string);
            }

            file_count = file_count + 1;

            // open destination file
            destination = fopen(final_destination_string, "w");

            // write image to file
            fwrite(buffer, sizeof(uint8_t), 512, destination);
        }
        else
        {
            if (destination != NULL)
            {
                // write image to file
                fwrite(buffer, sizeof(uint8_t), 512, destination);
            }
        }
    }
    // close last file
    if (destination != NULL)
    {
        fclose(destination);
    }

    // Clear memory (close remaining files)
    fclose(card);
}
