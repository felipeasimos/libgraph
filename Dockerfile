FROM alpine:latest

COPY . /app

WORKDIR /app

RUN apk add valgrind make llvm clang libc-dev libc6-compat build-base compiler-rt
