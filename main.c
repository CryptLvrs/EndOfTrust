#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define DEV_DIR "/dev/input"

enum Level { SUSPICIOUS, ALERT };

static enum Level classify(const char *device) {
    if (strncmp(device, "event", 5) != 0)
        return ALERT;
    return SUSPICIOUS;
}

static void act(enum Level level, const char *device) {
    switch (level) {
    case SUSPICIOUS:
        printf("[suspicious] %s\n", device);
        break;
    case ALERT:
        printf("[alert] %s\n", device);
        break;
    }
}

int main(void) {
    DIR *dir = opendir(DEV_DIR);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;
        act(classify(entry->d_name), entry->d_name);
    }
    closedir(dir);
    return 0;
}