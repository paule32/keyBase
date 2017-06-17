#include <stdio.h>
#include <iostream>

#include <QString>
#include <QVariant>
#include <QMessageBox>
#include <QDebug>

int line_no  = 1;
int file_eof = 0;
int last_op  = 0;

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

// -------------------
// our AST struct ...
// -------------------
typedef struct _MyNode {
public:
    SymbolType_      command;
    std::string   id;
    QChar            op;
    double         value;

    _MyNode * parent;
    _MyNode * lhs;
    _MyNode * rhs;

    _MyNode() {
        parent = nullptr;
        lhs = nullptr;
        rhs = nullptr;
    }

    ~_MyNode() {
        delete lhs;
        delete rhs;
    }
}
MyNode;
MyNode *eval_ast = nullptr;

void print_ast()
{
    MyNode * tmp = new MyNode;
    tmp = eval_ast;
    while (tmp != nullptr) {
        printf("res: %f\n",tmp->value);
        tmp = tmp->rhs;
    }
}

void add_astnode(char op, double val1, double val2)
{
    MyNode * tmp = new MyNode;
    MyNode * new_node;

    tmp = eval_ast;
    new_node = new MyNode;

    if (op == '+')
    new_node->op = '+';

    if (val1 < val2) {
        new_node->lhs = new MyNode;
        new_node->lhs->value = val2;
        tmp = new_node->lhs;
    }
    else {
        std::cout << "A: " << val1;
        std::cout << "B: " << val2;

        new_node->rhs = new MyNode;
        new_node->rhs->value = val1;
        tmp = new_node->rhs;
    }

    tmp->parent     = new MyNode;
    tmp->parent->id = std::string("assign");

    eval_ast = tmp;

    std::cout << "C:> " << tmp->value << std::endl;
}

// ------------------------------------------------------
// namespace to avoid conflicts with other frameworks ...
// ------------------------------------------------------
namespace kallup {
    QString number, ident;

    int    m_pos = 0; // buffer position
    char * m_TextBuffer;    // the source code buffer

    // ------------------------------------
    // cut spaces, and return next char ...
    // ------------------------------------
    int SkipWhiteSpaces()
    {
        int c = 0;
        while (1) {
            c = m_TextBuffer[m_pos++];
            if (isspace(c))
            continue;
            break;
        }
        return c;
    }

    QString GetIdent()
    {
        int c = 0;
        while (1) {
            c = m_TextBuffer[m_pos++];
            if (isalpha(c)) {
                ident += c;
                continue;
            }   break;
        }
        return ident;
    }

#if 0
    int Match(char *buffer, char expected)
    {
        if (SkipWhitespaces() == expected)
        return expected;
        throw QString("Expected token '%1' at position: %2")
            .arg(expected)
            .arg(pos);
    }
#endif
    QString GetNumber(void)
    {
        int c = SkipWhiteSpaces();

        if ((c >= '0') && (c <= '9'))
        number += c; else
        throw QString("number expected, but found other chars.\n"
                      "or Syntax Error.");

        while (1) {
            c = m_TextBuffer[m_pos];
            if (isdigit(c)) {
                number += c;
                ++m_pos;
                continue;
            }
            else if (c == '.') {
                number += '.';
                ++m_pos;
                continue;
            }
            else if (c == EOF || c == 0) {
                if (number.size() > 0)
                return number; else
                throw QString("wrong token as excpected.");
            }
            else if (isspace(c)) {
                if (number.size() > 0)
                return number;
                continue;
            }
            else {
                throw QString("number expected, wrong type: >>%1<<").arg(c);
                break;
            }
        }
        return number;
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

    struct bool_ { };
    struct int_  { };
    struct char_ { };

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
            qDebug() << GetNumber();
            return true;
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
            qDebug() << GetIdent();
            return true;
        }

        QVariant value;
        QString  name;
    };

    Token<bool> bool_;
    Token<int>  int_;
    Token<char> char_;

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
        grammar & operator << (Token<int> t) {
            qDebug() << "a token: " << t.name;
            t.parse();
            return *this;
        }
        grammar & operator + (Token<char> t) {
            qDebug() << "a token: " << t.name;
            t.parse();
            return *this;
        }
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

            // grammar:
            go  +char_ << int_ << int_ << int_;

            // ---------------------------------
            // sanity check, if all token read ?
            // ---------------------------------
            if (m_pos < strlen(m_TextBuffer))
            throw QString("not all input are proceed.");
        }
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

            eval_ast = new MyNode;
            eval_ast->parent = new MyNode;
            eval_ast->parent->id = "root";
            eval_ast->op  = '+';
        }
    };
}

bool parseText(QString src)
{
    try {
        using namespace kallup;
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
