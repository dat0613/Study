FROM ubuntu:latest

# 패키지 설치
RUN apt-get -y update && \
apt-get -y install g++ cmake git clang zlib1g-dev libssl-dev curl wget apt-utils libcurl4-openssl-dev ninja-build && \
mkdir /download 
RUN cd /download && git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
ENV PATH="$PATH:/download/depot_tools"

# google crashpad 빌드
RUN mkdir /download/crashpad && \
cd /download/crashpad && fetch crashpad && cd crashpad && \
cd /download/crashpad/crashpad && gn gen out/Default && ninja -C out/Default

# make 빌드를 위해 호스트 머신 파일 복사
RUN mkdir /build_files

COPY ./ /build_files
WORKDIR /build_files

# 빌드
RUN cmake -H./ -B./Generated/Linux \
-DCMAKE_BUILD_TYPE:STRING="Release" \
-DCRASHPAD_INCLUDE_DIR:FILEPATH="/download/crashpad/crashpad" \
-DCRASHPAD_MINI_CHROMIUM_INCLUDE_DIR:FILEPATH="/download/crashpad/crashpad/third_party/mini_chromium/mini_chromium" \
-DCRASHPAD_CHROMEOS_BUILDFLAGS_INCLUDE_DIR:FILEPATH="/download/crashpad/crashpad/out/Default/gen" \
-DCRASHPAD_LIBRARY_DIR:FILEPATH="/download/crashpad/crashpad/out/Default/obj" \
-GNinja
RUN cmake --build ./Generated/Linux

# 바이너리 실행
CMD ["./Generated/Linux/breakpad-test/breakpad-test"]
