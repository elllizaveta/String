#include "cppstring.h"
#include <iostream>
#include <cstring>

void String::Reallocate(size_t new_size) {
  if (new_size == capacity_) {
    return;
  }
  auto new_memory = new char[new_size];
  for (size_t i = 0; i < size_; ++i) {
    *(new_memory + i) = *(data_ + i);
  }
  capacity_ = new_size;
  delete[] data_;
  data_ = new_memory;
}

String::String(size_t size, char symbol) : size_(size), capacity_(size) {
  if (size == 0) {
    data_ = nullptr;
    return;
  }
  data_ = new char[capacity_];
  for (size_t i = 0; i < size; ++i) {
    *(data_ + i) = symbol;
  }
}

String::String(const char* a) {
  if (a == nullptr) {
    return;
  }
  for (size_t i = 0; *(a + i) != '\0'; ++i) {
    ++size_;
  }
  capacity_ = size_;
  data_ = new char[capacity_];
  data_ = strncpy(data_, a, size_);
}

String::String(const char* a, size_t size) {
  if (a == nullptr) {
    return;
  }
  capacity_ = size_ = size;
  data_ = new char[capacity_];
  data_ = strncpy(data_, a, size);
}

String::String(const String& a) {
  if (a.data_ == nullptr) {
    return;
  }
  capacity_ = size_ = a.Size();
  data_ = new char[capacity_];
  data_ = strncpy(data_, a.Data(), size_);
}

String::~String() {
  delete[] data_;
}

String::String(String&& a) noexcept : size_(a.size_), capacity_(a.capacity_), data_(a.data_) {
  a.data_ = nullptr;
}

String& String::operator=(String&& other) {
  String tmp = std::move(other);
  Swap(tmp);
  return *this;
}

String& String::operator=(const String& other) {
  String tmp = other;
  Swap(tmp);
  return *this;
}

char& String::operator[](size_t id) {
  return *(data_ + id);
}

const char& String::operator[](size_t id) const {
  return *(data_ + id);
}

char& String::At(size_t id) {
  if (id >= size_) {
    throw StringOutOfRange();
  }
  return *(data_ + id);
}

const char& String::At(size_t id) const {
  if (id >= size_) {
    throw StringOutOfRange();
  }
  return *(data_ + id);
}

char& String::Front() {
  return *data_;
}

const char& String::Front() const {
  return *data_;
}

char& String::Back() {
  return *(data_ + size_ - 1);
}

const char& String::Back() const {
  return *(data_ + size_ - 1);
}

const char* String::CStr() const {
  return data_;
}

char* String::CStr() {
  return data_;
}

const char* String::Data() const {
  return data_;
}

bool String::Empty() const {
  return size_ == 0;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  --size_;
}

void String::PushBack(char symbol) {
  if (size_ == capacity_) {
    Reallocate(std::max<size_t>(2 * capacity_, 1));
  }
  *(data_ + size_) = symbol;
  ++size_;
}

String& String::operator+=(const String& other) {
  if (size_ + other.size_ >= capacity_) {
    Reallocate(std::max(size_ + other.size_, 2 * capacity_));
  }
  for (size_t i = 0; i < other.size_; ++i) {
    *(data_ + size_) = *(other.data_ + i);
    ++size_;
  }
  return *this;
}

void String::Resize(size_t new_size, char symbol) {
  if (new_size > capacity_) {
    Reallocate(new_size);
  } else {
    size_ = new_size;
  }
  for (size_t i = size_; i < new_size; ++i) {
    data_[size_] = symbol;
    ++size_;
  }
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity > capacity_) {
    Reallocate(new_capacity);
  }
}

void String::ShrinkToFit() {
  Reallocate(size_);
}

String operator+(const String& first, const String& second) {
  String tmp = first;
  return tmp += second;
}

bool String::operator<(const String& other) const {
  size_t i = 0;
  while (i < size_ && i < other.size_) {
    if (*(data_ + i) != *(other.data_ + i)) {
      return *(data_ + i) < *(other.data_ + i);
    }
    ++i;
  }
  return i != other.size_;
}

bool operator>(const String& first, const String& second) {
  return second < first;
}

bool operator>=(const String& first, const String& second) {
  return !(first < second);
}

bool operator<=(const String& first, const String& second) {
  return !(second < first);
}

bool operator==(const String& first, const String& second) {
  return !(first < second) && !(second < first);
}

bool operator!=(const String& first, const String& second) {
  return (first < second) || (second < first);
}

std::ostream& operator<<(std::ostream& out, const String& a) {
  size_t size = a.Size();
  for (size_t i = 0; i < size; ++i) {
    out << a[i];
  }
  return out;
}
