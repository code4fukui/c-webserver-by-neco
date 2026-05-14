# c-webserver-by-neco

> 日本語のREADMEはこちらです: [README.ja.md](README.ja.md)

A simple, concurrent web server implemented in C using the [neco](https://github.com/tidwall/neco) coroutine library. The `neco` source files are included in this repository for convenience.

## Features

-   **Concurrent by Design:** Handles each incoming connection in a separate coroutine.
-   **Non-blocking I/O:** Built on `neco`'s efficient, non-blocking network functions.
-   **Static File Server:** Serves HTML, CSS, images, and other file types.
-   **MIME Type Detection:** Automatically sets the correct `Content-Type` header for common file extensions.

## Requirements

-   A C compiler (e.g., GCC or Clang)

## Usage

Compile and run the server:

```sh
# Compile the source files
cc server.c neco.c

# Run the server, listening on port 8080
./a.out 8080
```

Open `http://localhost:8080/` in your browser to view the default `index.html` page.

## License

Source code is available under the MIT License.