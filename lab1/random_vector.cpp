#include "random_vector.h"
#include <cstdlib>
#include <random>

RandomVector::RandomVector(int size, double max_val) {
  std::random_device rd;
  std:: mt19937 gen(rd());
  std::uniform_real_distribution<> distr(0.0, max_val);
  for (auto i = 1; i<=size; ++i){
    vect.push_back(distr(gen));
  }
}
void RandomVector::print(){
  for (double value : vect){
    std::cout << value << ' ';
  }
  std::cout << std::endl;
}

double RandomVector::mean(){
  double sum = 0.0;
  for (double value : vect){
    sum += value;
  }
  return sum / vect.size();
}

double RandomVector::max(){
  double max_value = 0.0;
  for (double value : vect) {
    if (value > max_value) max_value = value;
  }
  return max_value;
}

double RandomVector::min(){
  double min_val = this->max();
  for (double value : vect) {
    if (value < min_val) min_val = value;
  }
  return min_val;
}

void RandomVector::printHistogram(int bins){
  double min = this->min();
  double max = this->max();
  double bin_width = (max - min)/bins;
  std::vector<int> freq(bins, 0);
  for (int i = 0; i < bins; i++) {
    freq[i] = 0;
    for (double value : vect) {
      if (value > (min + i*bin_width) && value <= (min + (i+1)*bin_width)){
        freq[i] += 1;
      }
    }
    if (i == 0) freq[i] += 1;
  }
  int max_freq = 0;
  for (int value : freq){
    if (value > max_freq) max_freq = value;
  }
  for (int i = max_freq; i >= 1;i--) {
    for (int value : freq) {
      if (value >= i){
        std::cout << "*** ";
      } else{
        std::cout << "    ";
      }
    }
    std::cout << std::endl;
  }
}