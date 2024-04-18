#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


// creating the file pointer

FILE *file;
// creating the mutext variable to apply the lock
pthread_mutex_t mutex;


// function which calcualte the letter frequency
void findAlphabetsfrequency (char s[], int count[])
{
  int c = 0;

    
  while (s[c] != '\0')
    {
      if(s[c]>='A' && s[c] <= 'Z')
      {
        s[c]=s[c]+32;
      }
      if (s[c] >= 'a' && s[c] <= 'z')
        {
          count[s[c] - 'a']++;
        }
      c++;
    }
}

// global array vaible where count can be stored
int count[26] = { 0 };


// function which can be executed by the threads
void *readLinesFromFile ()
{

  char data[100000];
  
  // read a line from a file
  while(fgets (data, sizeof data, file) != NULL)
    {
      //fprintf (stdout, "\n text - %s", data);
      pthread_mutex_unlock(&mutex);
      //find alphabets frequency foe each line in the text file
      findAlphabetsfrequency (data, count);
      
      // unclock 
      pthread_mutex_lock(&mutex);
                // sleep the current thread so that other thread gets into action for reading another line of the file
    }


   // sleep(1);
  return NULL;
}


int main (int argc, char* argv[])
{

   
  int numOfThreads, status = 0;
 
  if(argc ==  2){

    numOfThreads = atoi(argv[1]);

    if (numOfThreads !=3)
      {

      printf("\nYou've entered: %d, but the threads count should be between 2 and 4",numOfThreads);
      
      return 0;

    }

  char fileName[100] = "test";

  // Open the file
  file = fopen (fileName, "r");

  // Check if file exists
  if (file == NULL)
    {
      printf ("Failed to open file %s", fileName);
      return 0;
    }

  //max 4 threads as mentioned in assignmrnt
  int threads[3];
  for (int i = 0; i < numOfThreads; i++)
    {
      threads[i] = i;
    }
  pthread_t thread_ids[3];

  // Create multiple threads based on user entered value
  for (int i = 0; i < numOfThreads; i++)
    {
            sleep(1);
      if (pthread_create(&thread_ids[i], NULL, &readLinesFromFile,NULL) != 0)
        {
          puts ("Error in thread creation");
          return 1;
        }
    }

  // Join all the created threads
  for (int i = 0; i < numOfThreads; i++)
    {
      if (pthread_join (thread_ids[i], NULL) != 0)
        {
          puts ("Error in joining threads");
          return 1;
        }
    }

      printf ("{ ");

      for (int c = 0; c < 26; c++)
        {
          if (c != 25)
            {
              printf ("'%c': %d,", c + 'a', count[c]);
            }
          else
            {
              printf ("'%c': %d", c + 'a', count[c]);
            }
        }

      printf (" }");
      printf ("\n");


  // Close the file resource
  fclose (file);
  }
  else{
          printf("Enter only one argument");
          exit(0);
  }

  return 0;
}
