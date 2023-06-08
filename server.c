#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    //Parancssori argumentumok kezelése
    if (argc < 3) {
        write(STDERR_FILENO, "Please provide a port number and a serial port number.\n", strlen("Please provide a port number and a serial port number.\n"));
        return -1;
    }

    //Socket kezelés, TCP kapcsolat felállítása
    int sockfd, newsockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        write(STDERR_FILENO, "Error creating socket\n", strlen("Error creating socket\n"));
        return -1;
    }
    struct sockaddr_in serv_addr, client_addr;
    memset(&serv_addr, 0x00, sizeof(serv_addr));
    int portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        write(STDERR_FILENO, "Error binding.\n", strlen("Error binding.\n"));
        return -1;
    }
    listen(sockfd, 1);
    int client_len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);
    if (newsockfd < 0) {
        write(STDERR_FILENO, "Error on accpet.\n", strlen("Error on accpet.\n"));
        return -1;
    }
    else {
        write(STDOUT_FILENO, "Client connected.\n", strlen("Client connected.\n"));
    }

    //UART kezelés
    struct termios serial;
    serial.c_cflag = CS8 | CREAD | CLOCAL;
    serial.c_cc[VMIN] = 1;
    serial.c_cc[VTIME] = 5;
    cfsetospeed(&serial, B1152000);
    cfsetispeed(&serial, B1152000);
    int serial_fd = open (argv[2], O_RDWR);
    if (serial_fd == -1) {
        write(STDERR_FILENO, "Could not open serial port!\n", 28);
        return -1;
    }
    tcsetattr(serial_fd, TCSANOW, &serial);

    //Pályaválasztás
    char level[2];
    char dummy[100];
    write(STDOUT_FILENO, "Type in level number: 00-15\n", strlen("Type in level number: 00-15\n"));
    read(STDIN_FILENO, level, 2);
    read(STDIN_FILENO, dummy, 100);
    bool valid_level = false;
    while (!valid_level) {
        if (atoi(level) > 15 || (level[0] != '0' && level[0] != '0')) {
            write(STDOUT_FILENO, "Type in a VALID level number: 00-15\n", strlen("Type in a VALID level number: 00-15\n"));
            read(STDIN_FILENO, level, 2);
            read(STDIN_FILENO, dummy, 100);
        }
        else{
            write(STDIN_FILENO, "Game started. GO!\n", strlen("Game started. GO!\n"));
            valid_level = true;
        }
    }
    char select_level[4] = {'x', 'x', level[0], level[1]};
    write(newsockfd, select_level, 4);
    write(serial_fd, select_level, 4);

    //STDIN linebuffer és echo kikapcsolás
    struct termios input, input_old;
    if (tcgetattr(STDIN_FILENO, &input_old) == -1) {
        write(STDERR_FILENO, "Error getting input attributes\n", strlen("Error getting input attributes\n"));
        return -1;;
    }
    input = input_old;
    input.c_lflag &= (~ICANON);
    input.c_lflag &= (~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &input);
    
    //MCU program futás irányítás
    char c;
    bool exit = false, win = false;
    fd_set rfds;
    int retsel;
    struct timeval tv;
    char winner[10] = "Player 1\n";
    while (!exit) {
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        FD_SET(serial_fd, &rfds);
        FD_SET(newsockfd, &rfds);
        tv.tv_sec = 60;
        tv.tv_usec = 0;

        retsel = select(serial_fd + 1, &rfds, NULL, NULL, &tv);
        if (retsel == -1) {
            write(STDERR_FILENO, "Error!\n", 7);
            exit = true;
        }
        else if (retsel > 0) {
            if (FD_ISSET(STDIN_FILENO, &rfds)) {
                read(STDIN_FILENO, &c, 1);
                write(serial_fd, &c, 1);
                if (c == 'q') {
                    exit = true;
                    write(newsockfd, "q", 1);
                }
            }
            else if (FD_ISSET(newsockfd, &rfds)) {
                read(newsockfd, &c, 1);
                write(serial_fd, "q", 1);
                exit = true;
                if (c == 'w') {
                    win = true;
                    sprintf(winner, "Player 2\n");
                }
            }
            else if (FD_ISSET(serial_fd, &rfds)) {
                write(newsockfd, "q", 1);
                exit = true;
                win = true;
            }
        }
        else {
            write(STDERR_FILENO, "Timeout\n", 9);
        }
    }

    //Adatok kiírása
    write(newsockfd, winner, strlen(winner));
    if (win) {
        write(newsockfd, "w", 1);
        write(STDOUT_FILENO, "Game over! The winner is:\n", strlen("Game over! The winner is:\n"));
        write(STDOUT_FILENO, winner, strlen(winner));
        char buff[8], time[6], shots_s[3], shots_c[3];
        read(serial_fd, buff, 8);
        sscanf(buff, "%s %s", time, shots_s);
        time[strlen(time)] = '\n';
        read(newsockfd, shots_c, 3);
        write(newsockfd, shots_s, 3);
        write(newsockfd, time, 6);
        char str[30];
        sprintf(str, "Player 1 shots: %s\n", shots_s);
        write(STDOUT_FILENO, str, strlen(str));
        sprintf(str, "Player 2 shots: %s\n", shots_c);
        write(STDOUT_FILENO, str, strlen(str));
        write(STDOUT_FILENO, "Duration: ", strlen("Duration: "));
        write(STDOUT_FILENO, time, strlen(time));
    }
    else {
        write(newsockfd, "l", 1);
        write(STDOUT_FILENO, "Game aborted.\n", strlen("Game aborted.\n"));
    }

    //STDIN visszáállítás, FD-k lezárása
    tcsetattr(STDIN_FILENO, TCSANOW, &input_old);
    close(sockfd);
    close(newsockfd);
    close(serial_fd);
    return 0;
}