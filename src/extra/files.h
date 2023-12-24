#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../core/common.h"
#include "../core/log.h"
#include "../core/sstring.h"
#include "../core/vector.h"

char *resolve_path(char *path);
void mkdirs(char *filepath);
