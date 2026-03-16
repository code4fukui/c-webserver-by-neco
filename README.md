# c-webserver-by-neco

> 日本語のREADMEはこちらです: [README.ja.md](README.ja.md)

A web server implementation in C language with [neco](https://github.com/tidwall/neco) library.

## Usage

```sh
cc -c server.c neco.c
./a.out 8080
```
Open `http://localhost:8080/` to access the server.

## Dependencies

- [neco.h](neco.h) / [neco.c](neco.c) from [neco](https://github.com/tidwall/neco)

## License

Source code is available under the MIT License.