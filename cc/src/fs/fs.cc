#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>

static int myfs_getattr(const char *path, struct stat *stbuf) {
  // Implement the getattr() function to get attributes of a file
  return 0;
}

static int myfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                        off_t offset, struct fuse_file_info *fi) {
  // Implement the readdir() function to read a directory
  return 0;
}

static int myfs_read(const char *path, char *buf, size_t size, off_t offset,
                     struct fuse_file_info *fi) {
  // Implement the read() function to read a file
  return 0;
}

static struct fuse_operations myfs_operations = {
    .getattr = myfs_getattr,
    .readdir = myfs_readdir,
    .read = myfs_read,
};

int main(int argc, char *argv[]) {
  return fuse_main(argc, argv, &myfs_operations, NULL);
}
