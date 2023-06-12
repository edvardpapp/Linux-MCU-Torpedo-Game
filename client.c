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
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    //Parancssori argumentumok kezelése
    if (argc < 4) {
        write(STDERR_FILENO, "Please provide an IP address, a port number and a serial port number.\n", strlen("Please provide an IP address, a port number and a serial port number.\n"));
        return -1;
    }

    //Socket kezelés, TCP kapcsolat kiépítése
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        write(STDERR_FILENO, "Error creating socket.n", strlen("Error creating socket.n"));
        return -1;
    }
    struct sockaddr_in server_addr;
    memset((char *) &server_addr, 0x00, sizeof(server_addr));
    int portno = atoi(argv[2]);
    server_addr.sin_family = AF_INET;
    struct in_addr seraddr;
    inet_aton(argv[1], &seraddr);
    server_addr.sin_addr = seraddr;
    server_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        write(STDERR_FILENO, "Error connecting.\n", strlen("Error connecting.\n"));
        return -1;
    }
    else {
        write(STDOUT_FILENO, "Connected to server.\n", strlen("Connected to server.\n"));
    }

    //UART kezelés
    struct termios serial;
    serial.c_cflag = CS8 | CREAD | CLOCAL;
    serial.c_cc[VMIN] = 1;
    serial.c_cc[VTIME] = 5;
    cfsetospeed(&serial, B1152000);
    cfsetispeed(&serial, B1152000);
    int serial_fd = open (argv[3], O_RDWR);
    if (serial_fd == -1) {
        write(STDERR_FILENO, "Could not open serial port!\n", 28);
        return -1;
    }
    tcsetattr(serial_fd, TCSANOW, &serial);

    //Pálya betöltése
    char select_level[4];
    read(sockfd, select_level, 4);
    write(serial_fd, select_level, 4);
    write(STDIN_FILENO, "Game started. GO!\n", strlen("Game started. GO!\n"));

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
    bool exit = false;
    fd_set rfds;
    struct timeval tv;
    int retsel;
    while (!exit) {
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        FD_SET(serial_fd, &rfds);
        FD_SET(sockfd, &rfds);
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
                    write(sockfd, "q", 1);
                }
            }
            else if (FD_ISSET(sockfd, &rfds)) {
                read(sockfd, &c, 1);
                write(serial_fd, &c, 1);
                exit = true;
            }
            else if (FD_ISSET(serial_fd, &rfds)) {
                write(sockfd, "w ", 1);
                exit = true;
            }
        }
        else {
            write(STDERR_FILENO, "Timeout\n", 9);
        }
    }

    //Adatok kiírása
    char winner[9];
    read(sockfd, winner, 9);
    read(sockfd, &c, 1);
    if (c == 'w') {
        write(STDOUT_FILENO, "Game over! The winner is:\n", strlen("Game over! The winner is:\n"));
        write(STDOUT_FILENO, winner, strlen(winner));
        char buff[8], time[6], shots_s[3], shots_c[3];
        read(serial_fd, buff, 8);
        sscanf(buff, "%s %s", time, shots_c);
        write(sockfd, shots_c, 3);
        read(sockfd, shots_s, 3);
        read(sockfd, time, 6);
        char str[30];
        sprintf(str, "Player 1 shots: %s\n", shots_s);
        write(STDOUT_FILENO, str, strlen(str));
        sprintf(str, "Player 2 shots: %s\n", shots_c);
        write(STDOUT_FILENO, str, strlen(str));
        write(STDOUT_FILENO, "Duration: ", strlen("Duration: "));
        write(STDOUT_FILENO, time, strlen(time));
    }
    else {
        write(STDOUT_FILENO, "Game aborted.\n", strlen("Game aborted.\n"));
    }

    //STDIN visszáállítás, FD-k lezárása
    tcsetattr(STDIN_FILENO, TCSANOW, &input_old);
    close(sockfd);
    close(serial_fd);
    return 0;
}