#ifndef OSTREAMTOTEXTEDIT_H
#define OSTREAMTOTEXTEDIT_H

#include <iostream>
#include <streambuf>
#include <string>

#include <QTextEdit>

class OStreamToTextEdit : public std::basic_streambuf<char>
{
public:
    OStreamToTextEdit (std::ostream& out, QTextEdit* textEditor);
   ~OStreamToTextEdit ();

protected:
   virtual int_type overflow (std::basic_streambuf<char>::int_type v);

   virtual std::streamsize xsputn (const char* p, std::streamsize n);

private:
   std::ostream& outStream;
   std::streambuf* oldBuffer;
   QTextEdit* textEditor;
   std::string text;
};



#endif // OSTREAMTOTEXTEDIT_H
