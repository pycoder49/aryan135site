#!/usr/bin/env bash
cd "$(dirname "$0")"
set -e

rustc hello-html-rust.rs -O -o hello-html-rust.cgi
rustc hello-json-rust.rs -O -o hello-json-rust.cgi
rustc environment-rust.rs -O -o environment-rust.cgi
# rustc echo-rust.rs -O -o echo-rust.cgi
# rustc state-rust.rs -O -o state-rust.cgi

chmod 755 *.cgi
