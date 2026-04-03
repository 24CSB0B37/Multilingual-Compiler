#!/bin/bash
set -e
cd "$(dirname "$0")"/..

./build.sh

echo "Testing Japanese vocabulary..."
./mlexer jp samples/demo_jp_extended.c > /tmp/out_jp.txt

for keyword in struct typedef void for break continue switch case default enum const static return; do
    if ! grep -q "\b$keyword\b" /tmp/out_jp.txt; then
        echo "JP missing keyword: $keyword"
        exit 1
    fi
done

echo "Testing Arabic vocabulary..."
./mlexer arabic samples/demo_arabic_extended.c > /tmp/out_arabic.txt

for keyword in struct typedef void for break continue switch case default enum const static return; do
    if ! grep -q "\b$keyword\b" /tmp/out_arabic.txt; then
        echo "ARABIC missing keyword: $keyword"
        exit 1
    fi
done


echo "Language vocabulary test passed"
