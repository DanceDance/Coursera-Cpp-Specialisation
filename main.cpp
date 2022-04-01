#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

template <typename It>
It safe_next(It it, It end, size_t n) {
  while(it != end && n--)
      it++;
  return it;
}

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() : cursor_(text_.begin()) {}
  void Left() {
    if (cursor_ != text_.begin())
      cursor_--;
  }
  void Right() {
    if (cursor_ != text_.end())
      cursor_++;
  }
  void Insert(char token) {
    text_.insert(cursor_, token);
  }
  void Cut(size_t tokens = 1) {
    auto copy_end = CopyInternal(tokens);
    text_.erase(cursor_, copy_end);
    cursor_ = copy_end;
    
  }
  void Copy(size_t tokens = 1) {
    CopyInternal(tokens);
  }
  void Paste() {
    for (const char &c: clipboard_)
      Insert(c);
  }
  string GetText() const {
    return string(begin(text_), end(text_));
  }
  char CursorPos() const {
    if (cursor_ == text_.end())
      return 'X';
    return *cursor_;
  }
private:
  string clipboard_;
  list<char> text_;
  list<char>::iterator cursor_;

  list<char>::iterator CopyInternal(size_t tokens) {
    auto copy_end = safe_next(cursor_, end(text_), tokens);
    clipboard_ = string(cursor_, copy_end);
    return copy_end;
  }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);

  return 0;
}