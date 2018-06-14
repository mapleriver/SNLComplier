#include "OStreamToTextEdit.h"

OStreamToTextEdit::OStreamToTextEdit(std::ostream &out, QTextEdit *textEditor):
    outStream(out),
    textEditor(textEditor)
{
    this->oldBuffer = out.rdbuf();
    outStream.rdbuf(this);
}

OStreamToTextEdit::~OStreamToTextEdit()
{
    if (!text.empty())
       textEditor->append(text.c_str());

     outStream.rdbuf(oldBuffer);
}

int OStreamToTextEdit::overflow(std::basic_streambuf<char>::int_type v)
{
    if (v == '\n')
    {
        textEditor->append(text.c_str());
        text.erase(text.begin(), text.end());
    }
    else
        text += v;
    return v;
}

std::streamsize OStreamToTextEdit::xsputn(const char *p, std::streamsize n)
{
    text.append(p, p + n);

     int pos = 0;
     while (pos != std::string::npos)
     {
      pos = text.find('\n');
      if (pos != std::string::npos)
      {
       std::string tmp(text.begin(), text.begin() + pos);
       textEditor->append(tmp.c_str());
       text.erase(text.begin(), text.begin() + pos + 1);
      }
     }

     return n;
}
