#!/usr/bin/bash

> $1

echo -n "#define GIT_SHA1 \"" > $1

git --version 2>&1 >/dev/null
GIT_IS_AVAILABLE=$?
if [ $GIT_IS_AVAILABLE -ne 0 ]; then
git rev-parse --short HEAD | tr -d '\n' >> $1
fi

echo "\"" >> $1
echo "const char* g_GIT_SHA1 = GIT_SHA1;" >> $1