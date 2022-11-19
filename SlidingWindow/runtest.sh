#build project
cmake -S . -B build
cmake --build build

#run tests
./build/SlidingWindow_test
./build/Receiver_test
./build/Sender_test

#cleanup build folder
rm -r ./build