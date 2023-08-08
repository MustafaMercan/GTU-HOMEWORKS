#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 8080

#include "dropbox.h"



int clientSocket;

void signal_handler(int sig)
{
    if(sig == SIGINT)
    {
        printf("sigint signal");
        char buffer[BUFFER_SIZE];

        strcpy(buffer,"quit");
        if (send(clientSocket, buffer, strlen(buffer), 0) < 0) {
            perror("Komut gönderilemedi");
            exit(1);
        }
        exit(1);
    }
    else if(sig == SIGUSR1)
    {
        printf("connected\n");
    }



}
int main(int arg, char **args) {

    signal(SIGINT,signal_handler);
    signal(SIGUSR1,signal_handler);
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    if(arg < 4)
    {
        printf("invalid usage %s <dirname> <port> <ip adress> \n",args[0]);
        return 1;
    }
    char *file_name = args[1];
    int port = atoi(args[2]);
    char *ip_adress = args[3];
    

    printf("client pid num -> %d\n",getpid());
    printf("dir path -> %s\n",file_name);

    // Soket oluşturma
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket oluşturulamadı");
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    // Sunucu adresini ayarlama
    if (inet_pton(AF_INET, ip_adress, &serverAddress.sin_addr) <= 0) {
        perror("Geçersiz sunucu adresi");
        return 1;
    }

    // Sunucuya bağlanma
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Sunucuya bağlanılamadı");
        return 1;
    }

    printf("Sunucuya bağlandı\n");

    ClientCommand clientCommand;

    snprintf(clientCommand.command,sizeof(clientCommand.command),"Client Connected.");
    snprintf(clientCommand.client,sizeof(clientCommand.client),"%s",file_name);
    //strcpy(clientCommand.command,"Client Connected.");
    clientCommand.pid = getpid();

    char clientInf[sizeof(ClientCommand)];

    memcpy(clientInf, &clientCommand, sizeof(ClientCommand));

    send(clientSocket,clientInf, sizeof(clientInf),0);
    memset(buffer,0,BUFFER_SIZE);

    sendDataInfoNode received_data;
    memset(&received_data,0,sizeof(received_data));
    int readBytes = recv(clientSocket, &received_data, sizeof(received_data), 0);

    printf("message: %s\n",received_data.buffer);
    printf("server path -> %s\n",received_data.path);
    char *server_path = received_data.path;

    printf("server path -> %s\n",server_path);
    
    
    if(strcmp(buffer,"Thread pool is full. Please wait.") == 0)
    {
        pause();
    }
    

    FileInfo fileInfo;
    
    time_t initial_timestamp = time(NULL);
    char **previous_files = NULL;
    int previous_file_count = 0;

    init_file_info(&fileInfo);//fileInfo olusuyor
    

    init_server_side(&fileInfo,clientSocket,file_name,server_path);//server'de güncel olarak bulunan verileri okur ilk olarak.

    client_path_init(&fileInfo,file_name);//fileInfo dolduruluyor
    sleep(2);

    int current_file_count = 0;
   
    
    while (1) 
    {

        //reset_node(&fileInfo);
        current_file_count = 0;
        // Başlangıç zaman damgası ve dosya listesi
        //printf("sa\n");
        //printf("\n\n\nlisten server side \n\n\n");

        listen_server_side(&fileInfo,clientSocket,file_name,server_path); // update other side
        
        listen_dir(&fileInfo,clientSocket,file_name,true);

        detect_delete_file(&fileInfo,file_name);

        update_other_side(&fileInfo,clientSocket);

        printf("All files updated\n");

        
        sleep(4);


    }
    

    

    // Soketi kapatma
    close(clientSocket);

    return 0;
}
