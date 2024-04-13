// Copyright 2014-2024 the Code for FUKUI authors. All rights reserved. MIT license.

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include "neco.h"

const char* CONTENT_TYPE[] = {
  "html", "text/html; charset=utf8",
  "js", "application/javascript",
  "mjs", "application/javascript",
  "jpg", "image/jpeg",
  "png", "image/png",
  "svg", "image/svg+xml",
  "gif", "image/gif",
  "bmp", "image/bmp",
  "txt", "text/plain; charset=utf8",
  "css", "text/css",
  "csv", "text/csv",
  "json", "application/json",
  "xml", "text/xml",
  "pdf", "application/pdf",
  "zip", "application/zip",
  "mp3", "audio/mpeg",
  "wav", "audio/wav",
  "mp4", "video/mp4",
  "m4v", "video/mp4",
  "wasm", "application/wasm",
  "", "text/plain",
};

void request(int argc, void *argv[]) {
    int fd = *(int*)argv[0];
    char req[256];
    int n = neco_read(fd, req, sizeof(req));
    if (n <= 0) { // リクエストが取得できない時
        close(fd);
        return;
    }
    char* path = req + 5;
    char* p;
    for (p = path; *p != ' '; p++);
    *p = '\0';
    if (*path == '\0') {
        path = "index.html";
        p = path + 10;
    }
    printf("path: %s\n", path); // リクエストのpath

    char* ext;
    for (ext = p - 1; *ext != '.' && ext >= path; ext--);
    ext++;
    printf("ext: %s\n", ext); // リクエストの拡張子

    if (*path == '/' || strstr(path, "..") || strchr(path, '\\')) { // 不正なリクエスト
        close(fd);
        return;
    }

    struct stat statbuf;
    if (stat(path, &statbuf)) { // ファイルが無い時
        char res[] = "HTTP/1.0 404 NotFound\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: 10\r\n"
                    "\r\n"
                    "not found\n";
        neco_write(fd, res, sizeof(res));
        close(fd);
        return;
    }
    long size = statbuf.st_size;

    const char* ctype = "text/plain";
    for (int i = 0;; i += 2) {
        if (!strcmp(CONTENT_TYPE[i], ext) || *CONTENT_TYPE[i] == '\0') {
            ctype = CONTENT_TYPE[i + 1];
            break;
        }
    }
    printf("ctype %s %s\n", ext, ctype); // リクエストに対応するCONTENT_TYPE

    char buf[1024 * 100];
    sprintf(buf, "HTTP/1.0 200 OK\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %d\r\n"
                "\r\n", ctype, (int)size);
    neco_write(fd, buf, strlen(buf));
    int fdf = open(path, O_RDONLY);
    for (;;) {
        int n = neco_read(fdf, buf, sizeof(buf));
        if (n < 0) break;
        neco_write(fd, buf, n);
    }
    close(fdf);
    close(fd);
    return;
}

int neco_main(int argc, char *argv[]) {
    int port = argc > 1 ? atoi(argv[1]) : 8080;
    char address[128];
    sprintf(address, "%s:%d", "[::]", port);
    int servfd = neco_serve("tcp", address);
    if (servfd < 0) {
        printf("neco_serve: %s\n", neco_strerror(servfd));
        return 0;
    }
    printf("Serving at http://%s\n", address);
    for (;;) {
        int fd = neco_accept(servfd, 0, 0);
        if (servfd < 0) {
            printf("neco_accept: %s\n", neco_strerror(fd));
            continue;
        }
        neco_start(request, 1, &fd);
    }
    return 0;
}
