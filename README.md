# vk-cpp

## Dependencies

<a href="https://github.com/alexmustdie/http-client-cpp">http-client</a> (my own)

## Install

sudo mkdir vk<br>
sudo cp include/\*.hpp /usr/include/vk/<br>
g++ -shared -o build/libvk.so -std=c++14 src/\*.cpp -fPIC -lhttp_client<br>
sudo cp build/libvk.so /usr/lib/
