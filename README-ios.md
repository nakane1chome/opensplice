brew install gawk
brew install bison
export PATH="$(brew --prefix bison)/bin:$PATH"

./configure armv7.darwin14_clang_cross-dev

. envs-armv7.darwin14_clang_cross-dev.sh
make

cd src/abstraction/os
$ ln -s darwin10 darwin14
cd src/abstraction/os-net/
$ ln -s darwin10 darwin14

mkdir -p src/abstraction/os/darwin14-ios/include
curl https://opensource.apple.com/source/Libc/Libc-320/include/crt_externs.h > src/abstraction/os/darwin14-ios/include/crt_externs.h
