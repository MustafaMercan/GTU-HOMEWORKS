
#include "dropbox.h"

int main(int argc, char* argv[]) {

    RequestQueue requestQueue;
    FileInfo fileInfo;
    int current_file_count;

    int server_fd, new_socket, port;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    


    if (argc != 4) {
        printf("valid usage : %s <directory> <threadPoolSize> <Port number>\n", argv[0]);
        return 1;
    }

    char *server_file = argv[1];
    int thread_pool_size = atoi(argv[2]);
    port = atoi(argv[3]);


    pthread_t threadPool[thread_pool_size];
    printf("server path -> %s\n",server_file);



    // Socket oluşturma
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket oluşturulamadı");
        return 1;
    }

    // SO_REUSEADDR seçeneğini ayarlama
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt hata");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Socket'i localhost ve belirtilen port üzerinde dinlemek için bağlama
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bağlama hatası");
        return 1;
    }

    // İstemcilerin bağlantıları dinleme
    if (listen(server_fd, thread_pool_size) < 0) {
        perror("Dinleme hatası");
        return 1;
    }

    printf("Sunucu başlatıldı. Bağlantıları dinliyor...\n");
    
    //char path[] = "./server_file";
    init_file_info(&fileInfo);//create file info default

    server_path_init(&fileInfo,server_file);//reads server file
    //FileInfo fileInfo;

    
    
    
    // İstek tamponunu başlatma
    initializeRequestBuffer(&requestQueue,&fileInfo,server_file);

    // İş parçacığı havuzunu başlatma
    for (int i = 0; i < thread_pool_size; i++) {
        if (pthread_create(&threadPool[i], NULL, handleRequest, &requestQueue) != 0) {
            perror("thread error");
            return 1;
        }
    }
    //print_file_info(&fileInfo);

    

    while (1) 
    {
        // Yeni bir istemci bağlantısı kabul etme
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("connect reject");
            return 1;
        }

        printf("New client socket -> %d\n",new_socket);
        
        // İstemci bağlantı bilgilerini iş parçacığına aktarma
        
        //threadData->sockfd = new_socket;
        //threadData->client_address = address;
        // İstekleri tampona ekleme

        char buffer[sizeof(ClientCommand)];
        ssize_t readBytes = recv(new_socket, buffer, sizeof(buffer),0);
        
        ClientCommand clientCommand;

        memcpy(&clientCommand, buffer, sizeof(ClientCommand));

        printf("client pid num -> %d client command -> %s client path -> %s\n",clientCommand.pid,clientCommand.command,clientCommand.client);


        enqueueRequest(&requestQueue,clientCommand,new_socket,address,server_file,thread_pool_size);
        pthread_cond_signal(&requestQueue.empty);
        sleep(2);
    }

    close(new_socket);

    for (int i = 0; i < thread_pool_size; i++) {
        pthread_join(threadPool[i], NULL);
    }
    
    return 0;
}
