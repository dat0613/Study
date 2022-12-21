FROM ubuntu:latest

RUN apt-get -y update && apt-get install -y
RUN apt-get -y install g++ cmake git

RUN mkdir ./build
RUN cmake -H. -B./Generated/Linux -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
RUN cmake --build ./Generated/Linux

CMD ["./Generated/Linux/executable-example/executable-example"]