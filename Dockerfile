# Copyright (c) 2025 David Ibehej
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

# -- Build --
FROM ubuntu:24.04 AS build
WORKDIR /workspace
RUN apt-get update && apt-get install -y build-essential cmake
COPY . .
RUN bash ./build.sh release

# -- Development --
FROM ubuntu:24.04 AS dev
WORKDIR /workspace
RUN apt-get update && apt-get install -y build-essential cmake gdb clang-format git 
COPY --from=build /workspace/ /workspace/

# -- Deployment --
FROM ubuntu:24.04 AS deploy
WORKDIR /app
COPY --from=build /workspace/build/release/bin/DynamicProgramming .
CMD ["./DynamicProgramming"]
