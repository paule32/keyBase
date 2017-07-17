#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define  BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT

#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

#include <QString>
#include <QVariant>
#include <QMessageBox>
#include <QDebug>

const int cmd_invalid     = 0;
const int cmd_assign      = 1;  // var = 12
const int cmd_assign_plus = 2;  // var = 12 + 44
const int cmd_assign_new  = 3;  // var = new ...

enum SymbolType_ {
    NoError,
    Undefined,
    NumberError,
    EndOfText
};
SymbolType_ SymbolType;

// ------------------------------------------------------
// namespace to avoid conflicts with other frameworks ...
// ------------------------------------------------------
namespace kallup
{
    int line_no  = 1;
    int file_eof = 0;
    int last_op  = 0;

    QString number, ident;

    int    m_pos = 0; // buffer position
    char * m_TextBuffer;    // the source code buffer
    double value = 0.00;    // math

    class mystream {
    public:
        mystream() {
            m_filePtr = nullptr;
        }
        mystream(char* fileName, int mode) {
            try {
                m_filePtr = nullptr;
                open(fileName,mode);
            } catch (...) {
                std::cout << "can not open mem file.\n";
            }
        }
        ~mystream() {
            close();
        }
        void open(char* fileName, int mode) {
            if (m_filePtr != nullptr)
            fclose(m_filePtr);

            switch (mode)
            {
            case 0:
                m_filePtr = fopen(fileName, "wb");
                break;
            case 1:
                m_filePtr = fopen(fileName, "rb");
                break;
            }
        }

        void close() {
            if (!m_filePtr)
            fclose(m_filePtr);
        }

        void read(void *data, unsigned long size) {
            if (m_filePtr) {
                fread(data,1,size,m_filePtr);
            }
        }

        void write(const void *data, unsigned long size) {
            if (m_filePtr) {
                fwrite(data,1,size,m_filePtr);
            }
        }

    private:
        FILE *m_filePtr;
    };

    template <class T>
    inline mystream & operator << (mystream & s, T val) {
        s.write(&val,sizeof(T));
        return s;
    }

    template <class T>
    inline mystream & operator >> (mystream & s, T val) {
        s.read(&val,sizeof(T));
        return s;
    }

    template<class T>
    inline mystream & operator<<(mystream & s, const vector<T>& _arr)
    {
        s << (long)_arr.size();
        if (_arr.size() > 0) s.write(&_arr.front(), (unsigned long)sizeof(T)*_arr.size());
        return s;
    }

    template<class T>
    inline mystream & operator>>(mystream & s, vector<T>& _arr)
    {
        long size;
        s >> size;
        if (size > 0) {
            _arr.resize(size);
            s.read(&_arr.front(), (unsigned long)sizeof(T)*_arr.size());
        }
        return s;
    }

    class expression { public:
          expression() { }

        typedef boost::variant<
          double
        , std::string
        >
        expression_type;
        expression_type expr;

    };


    class ast_struct: public boost::static_visitor<double> {
    public:
        double operator()(std::string txt) const {
            std::cout << txt << std::endl;
            return 123.42;
        }
        double operator()(double val) const {
            std::cout << "getter value01: " << val << std::endl;
            value = val;
            //return boost::apply_visitor( ast_struct(), tdp.expr );
            return  value;
        }
    };

    // ----------------------------------
    // inline's, to reduce code size, and
    // make code better in reading ...
    // ----------------------------------
    inline int get_ch() {
        return m_TextBuffer[m_pos++];
    }
    inline void get_endl() {
        int c;
        while (1) {
            c = get_ch();
            if (c == '\n') {
                line_no++;
                break;
            }
        }
    }

    bool TokenSkipper = false;  // ws each token?
    // ------------------------------------
    // cut spaces, and return next char ...
    // ------------------------------------
    bool SkipWhiteSpaces()
    {
        int c = 0;
        while (1) {
            c = get_ch();
            if (c == '&') {
                c = get_ch();
                if (c == '&') {
                    get_endl();
                    continue;
                }   else break;
            }
            else if (c == '*') {
                c = get_ch();
                if (c == '*') {
                    get_endl();
                    continue;
                }   else break;
            }
            else if (c == '/') {
                c = get_ch();
                if (c == '/') {
                    get_endl();
                    continue;
                }
                else if (c == '*') {
                    while (1) {
                        c = get_ch();
                        if (c == '\n')
                        line_no++;
                        else if (c == '*') {
                            c = get_ch();
                            if (c == '/')
                            break;
                        }
                    }
                    continue;
                }
                else {
                    --m_pos;
                    break;
                }
            }
            else if (isspace(c)) {
                if (c == '\n')
                line_no++;
                continue;
            }
            break;
        }
        --m_pos;
        return true;
    }

    bool GetIdent()
    {
        SkipWhiteSpaces();
        ident.clear();

        int c = 0;
        while (1) {
            c = get_ch();
            if (isalnum(c)) {
                ident += c;
            }
            else if (c == '/') {
                c = get_ch();
                if (c == '/') {
                    get_endl();
                    continue;
                }
                else if (c == '*') {
                    while (1) {
                        c = get_ch();
                        if (c == '\n')
                        line_no++;
                        else if (c == '*') {
                            c = get_ch();
                            if (c == '/')
                            break;
                        }
                    }
                }
                break;
            }   else {
                --m_pos;
                break;
            }
        }

        if (ident.length() < 1)
        throw QString("Syntax Error - No data?");

        return SkipWhiteSpaces();
      //return ident;
    }

    bool Match(char expected)
    {
        SkipWhiteSpaces();
        if (m_TextBuffer[m_pos++] == expected) {
            qDebug() << expected;
            return true;
        }
        throw QString("Expected token '%1' at position: %2")
            .arg(expected)
            .arg(m_pos);
        return false;
    }

    bool GetNumber(void)
    {
        SkipWhiteSpaces();
        number.clear();

        while (1) {
            int c = get_ch();
            if (isdigit(c)) {
                number += c;
                continue;
            }
            else if (c == '.') {
                number += '.';
                continue;
            }
            else if (c == '/') {
                c = get_ch();
                if (c == '/') {
                    get_endl();
                    continue;
                }
                else if (c == '*') {
                    while (1) {
                        c = get_ch();
                        if (c == '\n')
                        line_no++;
                        else if (c == '*') {
                            c = get_ch();
                            if (c == '/')
                            break;
                        }
                    }
                }
            }
            else if (c == EOF || c == 0) {
                if (number.size() > 0)
                break ; else
                throw QString("wrong token as excpected.");
            }
            else if (isspace(c)) {
                if (number.size() > 0)
                break;
                continue;
            }
            else {
                throw QString("number expected, wrong type: >>%1<<").arg(c);
                break;
            }
        }
        SkipWhiteSpaces();
        return true;
    }

    template <typename T>
    struct Token {
        Token() {
            qDebug() << "new token";
        }
    };

    template < typename T >
    struct Token<T*> {
        Token(){ std::cout << "A< T* >" << std::endl; }
    };

    struct TokenTypeAssign { };
    struct TokenTypeSpace  { };

    struct bool_   { };
    struct int_    { };
    struct char_   { };
    struct space_  { };
    struct assign_ { };

    template <> struct Token<TokenTypeAssign> {
    public:
        Token() {
            name = QString("TokenTypeAssign");
            value = 0;
        }
        bool parse() {
            if (!Match('='))
            throw QString("ASSIGN SIGN '=' expected.");
            return true;
        }
        QVariant value;
        QString  name;
    };
    template <> struct Token<TokenTypeSpace> {
    public:
        Token() {
            name  = QString("TokenSpace");
            value = 0;
        }
        bool parse() {
            qDebug() << "parse space";
            return SkipWhiteSpaces();
          //return true;
        }
        QVariant value;
        QString  name;
    };

    template <> struct Token<bool> {
    public:
        Token() {
            name  = QString("bool");
            value = static_cast<bool>(false);
        }
        QVariant value;
        QString  name;
    };

    template <> struct Token<int> {
    public:
        Token() {
            name  = QString("int");
            value = static_cast<int>(0);
        }
        bool parse() {
            qDebug() << "parse int";
            return GetNumber();
          //return true;
        }

        QVariant value;
        QString  name;
    };

    template <> struct Token<char> {
    public:
        Token() {
            name  = QString("char");
            value = QString("");
        }
        bool parse() {
            qDebug() << "parse char";
            return GetIdent();
          //return true;
        }

        QVariant value;
        QString  name;
    };

    Token<bool> bool_;
    Token<int>  int_;
    Token<char> char_;

    Token<TokenTypeSpace> space_;
    Token<TokenTypeAssign> assign_;

    class ParserCommon {
    public:
        ParserCommon(QString src) {
            m_TextBuffer = new char[src.size()+1];
            strcpy(m_TextBuffer,src.toLatin1().data());
        }
        ~ParserCommon() {
            delete m_TextBuffer;
        }
    };

    // ------------------------------------
    // wrapper class for token scanning ...
    // ------------------------------------
    class grammar {
    public:
        grammar() { }
        template <typename T> grammar & operator << (T &t) { is_eof = t.parse();return *this; }
        template <typename T> grammar & operator +  (T &t) { is_eof = t.parse();return *this; }

        bool is_eof;
    };

    // -----------------------------------
    // parser oode for an dBase parser ...
    // -----------------------------------
    class dBase {
    public:
        dBase() {
            qDebug() << "handle dbase grammar...";
        }
        void start(QString src)  {
            ParserCommon pc(src);
            grammar go;

            // our grammar:
            while (1) {
                if (go.is_eof) break;
                go +char_ << assign_ << int_;
            }

            // ---------------------------------
            // sanity check, if all token read ?
            // ---------------------------------
            if (m_pos < strlen(m_TextBuffer))
            throw QString("not all input are proceed.");
        }
    private:
        expression::expression_type expr;
    };

    template   <typename T>
    class Parser: public T {
    public:
        Parser() {
            qDebug() << "parser init.";
            line_no = 1;
            m_pos   = 0;

            ident .clear();
            number.clear();
        }
    };

    void test(QString src)
    {
#if 0
        expression::expression_type res1 = 2.0 + 5.0;
        expression::expression_type res2 = 21.42;

        std::cout << std::endl
                  << "start visitor..."
                  << std::endl;
        std::cout << boost::apply_visitor(ast_struct(),res1) << std::endl; std::cout << "next...\n";
        std::cout << boost::apply_visitor(ast_struct(),res2) << std::endl;
#endif
    }


}

// int main() {
bool parseText(QString src)
{
    using namespace kallup;

#if 0
    // ------------------------------
    // stream test - unser Brain ...
    // ------------------------------
    kallup::mystream s("test.dat",0);
    vector<int> somevector(100,123);
    somevector.at(20) = 35;
    s << somevector;
    s.close();

    kallup::test(src);
    return true;
#endif
    try {
        Parser<dBase> p;
        p.start(src);

        QMessageBox::information(0,"Info","SUCCESS");
        return true;
    }
    catch (QString &e) {
        QMessageBox::critical(0,"Error",
        QString("Error in line: %1\n%2")
        .arg(line_no)
        .arg(e));
    }
    return false;
}
