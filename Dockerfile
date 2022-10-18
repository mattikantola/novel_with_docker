FROM arm64v8/gcc
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN g++ -o analyysi novel_analysis.cpp
CMD ["./analyysi"]