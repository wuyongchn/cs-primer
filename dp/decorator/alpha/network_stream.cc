#include "network_stream.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

namespace alpha {
char NetworkStream::Read(int number) {
  cout << "NetworkStream Read" << endl;
  int idx = rand() % 26;
  return 'a' + idx;
}
void NetworkStream::Seek(int position) {
  cout << "NetworkStream Seek to " << position << endl;
  return;
}
void NetworkStream::Write(char data) {
  cout << "NetworkStream Write " << data << endl;
  return;
}
}  // namespace alpha
