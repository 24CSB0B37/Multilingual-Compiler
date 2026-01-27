#!/bin/bash

gcc -Iinclude \
    src/input_handler.c \
    src/lang_config.c \
    src/keyword_map.c \
    src/lexer.c \
    src/token_output.c \
    src/nlp_assist.c \
    src/main.c \
    -o mlexer
