FROM gcc:latest

ADD ./src /app/src

WORKDIR /app/src

RUN gcc -o DockerMain main.c

CMD ["./DockerMain", "main.c", "temp.txt"]
