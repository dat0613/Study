FROM ubuntu:latest

# 패키지 설치
RUN sudo apt-get -y update
RUN sudo apt-get -y install g++ cmake git clang zlib1g-dev

# google crashpad 빌드
RUN cd / && mkdir download && cd download
RUN git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
RUN export PATH=/download/depot_tools:$PATH
RUN cd /download && mkdir crashpad && cd crashpad
RUN fetch crashpad && cd crashpad && git pull -r && gclient sync
RUN gn gen out/Default && ninja -C out/Default

# make 빌드를 위해 호스트 머신 파일 복사
RUN mkdir /build_files

COPY ./ /build_files
WORKDIR /build_files

# 빌드
RUN cmake -H./ -B./Generated/Linux -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
RUN cmake --build ./Generated/Linux

# 바이너리 실행
CMD ["./Generated/Linux/executable-example/executable-example"]