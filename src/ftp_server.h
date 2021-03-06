#pragma once

#include "epoll.h"
#include "socket.h"
#include "ftp_client_t.h"

#include "../threadpool/threadpool.h"
#include "../threadpool/task.h"

#include <unistd.h>
#include <sys/time.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <cstdlib>
#include <cerrno>

#include <pthread.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>

const int PORT = 9999;
const int DATA_PORT = 8888;
const std::string IP = "192.168.221.128";
const int MAX_LISTEN_NUMBER = 10;
const int FTP_PTHREAD_NUMBER = 6;

const std::string WELCOME_CLIENT = "Welcome to use FTP server!";

class CFTPServer
{
public:
    CFTPServer();
    ~CFTPServer();

    void run();

private:
    bool create_control_listen_socket();
    bool create_data_listen_socket();
    bool create_epoll();

    bool close_epoll();

    void init_current_workdir();

    std::string parse_ip_address(struct sockaddr_in& addr);
    std::string recv_client_command(int fd);

    static void handle(int);

private:
    void process_quit_command(int fd);
    void process_pasv_command(int fd);
    void process_list_command(int fd);
    void process_pwd_command(int fd);
    void process_user_command(int fd);
    void process_pass_command(int fd);
    void process_size_command(int fd);
    void process_cwd_command(int fd);
    void process_port_command(int fd);
    void process_stor_command(int fd);
    void process_rest_command(int fd);
    void process_other_command(int fd);
    void process_retr_command(int fd);

    static void process_command(std::vector<void*> args);

private:
    int m_control_listen_fd;
    int m_data_listen_fd;

    CEpoll m_epoll;

    pthread_mutex_t m_pthread_mutex;

    std::string m_current_workdir;
    
    std::map<int, ftp_client_t> m_client_map;
    std::map<std::string, int> m_address_map;

    CThreadPool m_pthread_pool;
};