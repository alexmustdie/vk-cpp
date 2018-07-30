# vk-cpp

## Install

sudo mkdir vk
sudo cp include/*.hpp /usr/include/vk/
g++ -shared -o build/libvk.so -std=c++14 src/*.cpp -fPIC -lhttp_client
sudo cp build/libvk.so /usr/lib/
