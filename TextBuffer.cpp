#include "TextBuffer.hpp"
using namespace std;

  TextBuffer::TextBuffer() 
   : data(), cursor(data.end()), row(1), column(0), index(0) {}

  bool TextBuffer::forward() {
    if (cursor == data.end()) {
        return false;
    }
    char c = *cursor;
    ++cursor;
    ++index;
    if (c == '\n') {
        column = 0;
        ++row;
    }
    else {
        ++column;
    }
    return true;
  }

  bool TextBuffer::backward() {
    if (cursor == data.begin()) {
        return false;
    }
    --cursor;
    --index;
    char c = *cursor;
    if (c == '\n') {
        column = compute_column();
        --row;
    }
    else {
        --column;
    }
    return true;
  }

  void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    ++cursor;
    ++index;
    if (c == '\n') {
        column = 0;
        ++row;
    }
    else {
        ++column;
    }
  }

  bool TextBuffer::remove() {
    if (cursor == data.end()) {
        return false;
    }
    char c = *cursor;
    cursor = data.erase(cursor);
    if (c == '\n') {
        column = compute_column();
        --row;
    }
    return true;
  }

  void TextBuffer::move_to_row_start() {
    while (column > 0) {
        backward();
    }
  }

  void TextBuffer::move_to_row_end() {
    while (cursor != data.end() && *cursor != '\n') {
        forward();
    }
  }

  void TextBuffer::move_to_column(int new_column) {
    assert (new_column >= 0);
    if (new_column > column) {
        while (column < new_column) {
            if (cursor == data.end()) break;
            if (*cursor == '\n') break;
            forward();
        }
    }
    if (new_column < column) {
        while (column > new_column) {
            backward();
        }
    }
  }

  bool TextBuffer::up() {
    if (row == 1) {
        return false;
    }
    int move_col = column;
    move_to_row_start();
    backward();
    move_to_row_start();
    move_to_column(move_col);
    return true;
  }

  bool TextBuffer::down() {
    int move_col = column;
    move_to_row_end();
    if (cursor == data.end()) {
        return false;
    }
    forward();
    move_to_column(move_col);
    return true;
  }

  bool TextBuffer::is_at_end() const {
    if (cursor == data.end()) {
        return true;
    }
    return false;
  }

  char TextBuffer::data_at_cursor() const {
    assert (cursor != data.end());
    return *cursor;
  }

  int TextBuffer::get_row() const {
    return row;
  }

  int TextBuffer::get_column() const {
    return column;
  }

  int TextBuffer::get_index() const {
    if (cursor == data.end()) {
        return size();
    }
    return index;
  }

  int TextBuffer::size() const {
    return data.size();
  }

  std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
  }

  int TextBuffer::compute_column() const {
    Iterator i = cursor;
    int col = 0;
    while (i != data.begin()) {
        Iterator previous = i;
        --previous;
        if (*previous == '\n') {
            return col;
        }
        i = previous;
        ++col;
    }
    return col;
  }