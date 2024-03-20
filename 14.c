#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAGIC_SIZE 4

typedef struct {
    const char *magic_number;
    const char *file_type;
} MagicNumber;


MagicNumber magic_numbers[] = {
    {"\x89\x50\x4E\x47",   "PNG"},      // PNG
    {"\xFF\xD8\xFF",       "JPEG"},     // JPEG
    {"\x47\x49\x46\x38\x37\x61", "GIF"},// GIF87a
    {"\x47\x49\x46\x38\x39\x61", "GIF"},// GIF89a
    {"\x25\x50\x44\x46",   "PDF"},      // PDF
    {"\x52\x49\x46\x46",   "WAV"},      // WAV
    {"\x4D\x5A",           "EXE"},      // DOS/Windows executable
    {"\x7F\x45\x4C\x46",   "ELF"},      // ELF executable
    {"\x4F\x67\x67\x53\x00\x02\x00\x00", "OGG"}, // OGG
    {"\x1F\x8B\x08",       "GZIP"},     // GZIP
    {"\x25\x21",           "PS"},       // PostScript
    {"\x50\x4B\x03\x04",   "ZIP"},      // ZIP
    {"\x50\x4B\x05\x06",   "ZIP"},      // Empty ZIP
    {"\x50\x4B\x07\x08",   "ZIP"},      // Spanned ZIP
    {NULL,                  "Unknown"}   // Unknown file type
};


char* identifyFileType(FILE *file) {
    unsigned char magic[MAX_MAGIC_SIZE];
    size_t bytes_read = fread(magic, 1, MAX_MAGIC_SIZE, file);
    if (bytes_read < MAX_MAGIC_SIZE)  return "Unknown"; 

    for (int i = 0; magic_numbers[i].magic_number != NULL; i++) 
        if (memcmp(magic, magic_numbers[i].magic_number, MAX_MAGIC_SIZE) == 0) 
            return (char *)magic_numbers[i].file_type;

    return "Unknown";
}


int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <filename>\n", argv[0]); return 1; }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) { perror("Error opening file"); return 1; }

    char *file_type = identifyFileType(file);
    printf("File type: %s\n", file_type);
    fclose(file);

    return 0;
}

