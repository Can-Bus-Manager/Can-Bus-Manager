#standard 64-bit Ubuntu base
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clang-tidy \
    clang-format \
    ninja-build \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    doxygen \
    graphviz \
    lcov \
    && rm -rf /var/lib/apt/lists/*