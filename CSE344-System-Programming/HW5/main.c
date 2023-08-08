#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/time.h>


struct timeval start_time, end_time;
int BUFFER_SIZE;


typedef struct {
    int fd_source;
    int fd_destination;
    char source_path[256];
    char destination_path[256];
} FileData;

FileData *buffer;
int buffer_count = 0;
int buffer_index = 0;
int buffer_out = 0;

int buffer_flag = 1;



pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_empty_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_full_cond = PTHREAD_COND_INITIALIZER;

void signal_handler(int sig)
{
    gettimeofday(&end_time, NULL);

    // Calculate total time
    long long start_usec = start_time.tv_sec * 1000000LL + start_time.tv_usec;
    long long end_usec = end_time.tv_sec * 1000000LL + end_time.tv_usec;
    double total_time = (double)(end_usec - start_usec) / 1000000.0;
    printf("Total time: %.6f seconds\n", total_time);

    free(buffer);
    
    exit(1);
}

void process_directory(const char* path, char* dest) {

    DIR* dir = opendir(path);
    if (dir == NULL) {
        printf("File cannot open: %s\n", path);
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;  // Geçerli dizin ve üst dizin girişlerini atla
        }

        char entry_path[300];
        sprintf(entry_path, "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) {   
            char next_path[300];
            sprintf(next_path,"%s/%s",dest,entry->d_name);
            mkdir(next_path,0777);
            

            pthread_mutex_lock(&buffer_mutex);
            
            while (buffer_count == BUFFER_SIZE) {
                pthread_cond_wait(&buffer_full_cond, &buffer_mutex);
            }

            buffer[buffer_index].fd_source = -1;
            buffer[buffer_index].fd_destination = -1;

            strcpy(buffer[buffer_index].source_path, entry_path);
            strcpy(buffer[buffer_index].destination_path, next_path);


            pthread_cond_signal(&buffer_empty_cond);
            pthread_mutex_unlock(&buffer_mutex);

            process_directory(entry_path,next_path);

        } else if (entry->d_type == DT_REG || entry->d_type == DT_FIFO) {

            char next_path[300];
            sprintf(next_path,"%s/%s",dest,entry->d_name);

            int fd_source = open(entry_path, O_RDONLY);
            
            if (fd_source == -1) {
                printf("src cannot open: %s\n", entry_path);
                continue;
            }

            if(entry->d_type == DT_FIFO)
            {
                mkfifo(next_path,0666);
            }
            int fd_destination = open(next_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

            if (fd_destination == -1) {
                printf("dest cannot open: %s\n", next_path);
                close(fd_source);
                continue;
            }

            buffer[buffer_index].fd_source = fd_source;
            buffer[buffer_index].fd_destination = fd_destination;

            strcpy(buffer[buffer_index].source_path, entry_path);
            strcpy(buffer[buffer_index].destination_path, next_path);

        }

        buffer_count++;
        buffer_index = (buffer_index + 1) % BUFFER_SIZE;
    }

    closedir(dir);
}

void* producer(void* arg) {


    char* directories[2];
    directories[0] = ((char**)arg)[0];
    directories[1] = ((char**)arg)[1];


    process_directory(directories[0], directories[1]);

    pthread_mutex_lock(&buffer_mutex);

    // Inform the program that the producer is done

    buffer_flag = -1;
    pthread_mutex_unlock(&buffer_mutex);

    pthread_cond_broadcast(&buffer_empty_cond);  
    pthread_exit(NULL);
}

void* consumer(void* arg) {

    while (1) {
        pthread_mutex_lock(&buffer_mutex);
        // Wait while buffer is empty

        
        while (buffer_count == 0 && buffer_flag != -1)
        {
            pthread_cond_wait(&buffer_empty_cond, &buffer_mutex);
        }

        if (buffer_flag == -1 && buffer_count == 0) {
            pthread_mutex_unlock(&buffer_mutex);
            pthread_cond_broadcast(&buffer_empty_cond);
            pthread_exit(NULL);

        }
        int fd_source = buffer[buffer_out].fd_source;
        int fd_destination = buffer[buffer_out].fd_destination;
        
        char source_file[512];
        char destination_file[512];

        strcpy(source_file, buffer[buffer_out].source_path);
        strcpy(destination_file, buffer[buffer_out].destination_path);

        
        buffer_count--;
        buffer_out = (buffer_out + 1) % BUFFER_SIZE;
        pthread_cond_broadcast(&buffer_empty_cond);  


        
        pthread_mutex_unlock(&buffer_mutex);


        char str[1024];
        ssize_t bytes_read;
        ssize_t bytes_written;


        
        if(fd_source != -1 && fd_destination != -1)
        {
            while ((bytes_read = read(fd_source, str, sizeof(str))) > 0) 
            {
                bytes_written = write(fd_destination, str, bytes_read);
                if (bytes_written == -1) {
                    break;
                }
            }
            close(fd_source);
            close(fd_destination);
        }
        printf("%s copied to",source_file);
        printf("%s\n",destination_file);
    }
}


int main(int argc, char* argv[]) {


    if (argc < 5) {
        printf("Usage: ./pCp <buffer_size> <consumer_num> <source_dir> <destination_dir>\n");
        return 1;
    }

    signal(SIGINT,signal_handler);


    BUFFER_SIZE = atoi(argv[1]);
    int NUM_CONSUMERS = atoi(argv[2]);

    char* source_dir = argv[3];
    char* destination_dir = argv[4];

    buffer = (FileData*)malloc(BUFFER_SIZE * sizeof(FileData));



    if (pthread_mutex_init(&buffer_mutex, NULL) != 0) {
        printf("Mutex error\n");
        return 1;
    }

    // Create producer thread
    pthread_t producer_thread;

    char* directories[2];
    directories[0] = source_dir;
    directories[1] = destination_dir;


    pthread_create(&producer_thread, NULL, producer, (void*)directories);
    // Create consumer threads
    pthread_t consumer_threads[NUM_CONSUMERS];

    for (int i = 0; i < NUM_CONSUMERS ;i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }


    // Start time
    
    gettimeofday(&start_time, NULL);

    // Wait for producer thread to complete
    pthread_join(producer_thread, NULL);


    // Wait for consumer threads to complete
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);

    // Calculate total time
    long long start_usec = start_time.tv_sec * 1000000LL + start_time.tv_usec;
    long long end_usec = end_time.tv_sec * 1000000LL + end_time.tv_usec;
    double total_time = (double)(end_usec - start_usec) / 1000000.0;

    // Display total time
    printf("Total time: %.6f seconds\n", total_time);

    free(buffer);
    
}