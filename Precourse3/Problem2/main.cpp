#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fstream>

#define MAX_BOOK_TITLE 30
#define MAX_AUTHOR_NAME 16
#define MAX_BOOKS 2

// You CAN NOT REMOVE or CHANGE exist declaration
// But, CAN ADD whatever you want


#pragma pack(push, 1)
// Total 54 bytes data
typedef struct book_{
    char title[MAX_BOOK_TITLE]; // 30 bytes
    char author[MAX_AUTHOR_NAME]; // 16 bytes
    uint32_t volume_number; // 4 bytes
    uint32_t ISBN; // 4 bytes
} book;
#pragma pack(pop)

typedef struct library_{
  book *books;
} library;

// Function to save the books data of the library
void serialize(char* path, library* lib, int number_of_books){
  std::ofstream file(path, std::ios::binary);
  for (int i=0 ; i < number_of_books ; ++i)
  {
    file.write(reinterpret_cast<char*>(&(lib->books[i])), sizeof(book));
  }
  file.close();
}

// Function to load the books data of the library
void deserialize(char* path, library *lib, int number_of_books){
  std::ifstream file(path, std::ios::binary);
  for (int i=0; i < number_of_books ; ++i)
  {
    file.read(reinterpret_cast<char*>(&(lib->books[i])), sizeof(book));
  }
  file.close();
}

// Function to fill defaults data
// Do Not Edit This Functions
void insert_books(library *lib){

  strcpy(lib->books[0].title,"The Songs of Stardust:Harmony");
  strcpy(lib->books[0].author,"John Bolton");
  lib->books[0].ISBN = 15952557;
  lib->books[0].volume_number = 1;

  strcpy(lib->books[1].title,"Whispers Secrets are Unveiled");
  strcpy(lib->books[1].author,"donald trump");
  lib->books[1].ISBN = 67652241;
  lib->books[1].volume_number = 99;
}

// Function to print data
// Do Not Edit This Functions
void print_contents(library *lib){
  printf("\nPrint All Contents of The Library\n");
  for (int idx = 0 ; idx < MAX_BOOKS ; ++idx){
    printf("------------------------------------------------------\n");
    printf("Title : %s\n",lib->books[idx].title);
    printf("Author : %s\n",lib->books[idx].author);
    printf("ISBN : %d\n",lib->books[idx].ISBN);
    printf("volume_number : %d\n",lib->books[idx].volume_number);
    printf("------------------------------------------------------\n");
  }
}

// Do Not Edit This Functions
int main(int argc, char* argv[]){

  // Declare 2 library instance
  library lib, backup;
  void* memory_pool = malloc(54 * MAX_BOOKS * 2);

  lib.books = (book*)memory_pool;
  backup.books = (book*)((char*)(memory_pool + 54 * MAX_BOOKS));

  insert_books(&lib);
  print_contents(&lib);

  // save the data of lib instance
  serialize("data.bin", &lib, MAX_BOOKS);
  
  // load the data to backup instance
  deserialize("data.bin", &backup, MAX_BOOKS);

  // Check the loaded value
  print_contents(&lib);

  // The original value might be changed ?
  print_contents(&backup);

  return 0;
}
