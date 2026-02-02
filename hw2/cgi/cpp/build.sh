#!/usr/bin/env bash
cd "$(dirname "$0")"
set -e

g++ -O2 -std=c++17 hello-html-cpp.cpp -o hello-html-cpp.cgi
# g++ -O2 -std=c++17 hello-json-cpp.cpp -o hello-json-cpp.cgi
# g++ -O2 -std=c++17 environment-cpp.cpp -o environment-cpp.cgi
# g++ -O2 -std=c++17 echo-cpp.cpp -o echo-cpp.cgi
# g++ -O2 -std=c++17 state-cpp.cpp -o state-cpp.cgi
chmod 755 *.cgi