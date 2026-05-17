#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    const char *writefile;
    const char *writestr;
    int fd;
    size_t total_written;
    size_t write_len;

    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid argument count: expected 2 arguments, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return 1;
    }

    writefile = argv[1];
    writestr = argv[2];

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Failed to open %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }

    write_len = strlen(writestr);
    total_written = 0;
    while (total_written < write_len) {
        ssize_t bytes_written = write(fd, writestr + total_written, write_len - total_written);

        if (bytes_written == -1) {
            syslog(LOG_ERR, "Failed to write to %s: %s", writefile, strerror(errno));
            close(fd);
            closelog();
            return 1;
        }

        total_written += (size_t)bytes_written;
    }

    if (close(fd) == -1) {
        syslog(LOG_ERR, "Failed to close %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }

    closelog();
    return 0;
}
