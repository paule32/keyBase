#include <stdio.h>

#include <iostream>
#include <string>

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

    struct add_ { };
    struct sub_ { };
    struct mul_ { };
    struct div_ { };

    struct expr   { };
    struct sconst { };
    struct mconst { };

    template <typename OpTag1> struct binary_op;

    class expression_wrapper { public:
          expression_wrapper() { }

        typedef boost::variant<
          double
        , std::string

        , boost::recursive_wrapper< binary_op<add_> >
        , boost::recursive_wrapper< binary_op<sub_> >
        , boost::recursive_wrapper< binary_op<mul_> >
        , boost::recursive_wrapper< binary_op<div_> >

        > expression;


        expression_wrapper::expression operator = (TypeDouble<int> const &val) {
            std::cout << "assiggnn" << std::endl;
        }
    };

    template <typename OpTag1>
    struct binary_op
    {
        expression_wrapper::expression * left ;
        expression_wrapper::expression * right;

        binary_op() { }
        binary_op(double val1, double val2) {
            double res = val1 * val2;
            value = res;
        }

        binary_op(expression_wrapper::expression &exp, double val) {
            auto *left  = new expression_wrapper::expression;
            auto *right = new expression_wrapper::expression;

            left  = value;
            right = val;

            std::cout << "L:   " << left  << std::endl;
            std::cout << "R:   " << right << std::endl;
            std::cout << "val: " << val << std::endl;
            exp = val;
        }
        binary_op(double val, expression_wrapper::expression &exp) {
            auto *left  = new expression_wrapper::expression;
            auto *right = new expression_wrapper::expression;

            //left  = val;
            //right = value;

            std::cout << "L2:   " << left  << std::endl;
            std::cout << "R2:   " << right << std::endl;
            std::cout << "val2: " << val << std::endl;
            //value = boost::get<double>(left);
            exp   = value;
        }

        void get(binary_op<mul_> &obj) {
            auto *left  = new expression_wrapper::expression;
            auto *right = new expression_wrapper::expression;

            std::cout << "pp: " << std::endl;
            left  = obj.left;
            right = obj.right;
        }

        binary_op(expression_wrapper::expression &lhs) {
            auto *left  = new expression_wrapper::expression;
            auto *right = new expression_wrapper::expression;

            left = lhs;
            std::cout << "popser: " << /*boost::get<double>(left) <<*/ std::endl;
        }

        binary_op(expression_wrapper::expression *&obj) {

        }

        binary_op(
              expression_wrapper::expression & lhs,
              expression_wrapper::expression & rhs)
            : left(lhs), right(rhs)
        {
        }

        binary_op(binary_op<mul_> *mul, double val)
        {
            auto *left  = new expression_wrapper::expression;
            auto *right = new expression_wrapper::expression;

            std::cout << "mexter" << std::endl;
            left  = mul;
            right = val;
        }

        binary_op(const binary_op<sub_> &bo)   {
            std::cout << "subser: " << bo.left ->type().name() << std::endl;
            std::cout << "subser: " << bo.right->type().name() << std::endl;

            double res2 = 1.2; //boost::get<double>(bo.right);
            {
                //auto *left  = new expression_wrapper::expression;
                //auto *right = new expression_wrapper::expression;

                value = value - res2;
                //left  = value ;
                std::cout << "ein lefter: " << value << std::endl;
            }
        }
        binary_op(const binary_op<add_> &bo)   {

        }
        binary_op(const binary_op<mul_> &bo)   {
            std::cout << "mopser" << std::endl;
            //auto *left  = new expression_wrapper::expression;
            //auto *right = new expression_wrapper::expression;

            double l = 1; //boost::get<double>(bo.left );
            double r = 2; //boost::get<double>(bo.right);
            double s = r * l;

            //left = value = s;

            std::cout <<  "multerL " << l << std::endl;
            std::cout <<  "multerR " << r << std::endl;
            std::cout <<  "multerS " << s << std::endl;
        }
        binary_op(const binary_op<div_> &bo)   {
        }
    };

    expression_wrapper::expression operator + (
        expression_wrapper::expression &exp1,
        expression_wrapper::expression &exp2)
    {
        std::cout << "plus" << std::endl;

        return exp1;
    }
    expression_wrapper::expression& operator += (expression_wrapper::expression &exp, double val) {
        expression_wrapper::expression tmp = val;
        exp = exp + tmp;
        return exp;
    }

    expression_wrapper::expression& operator - (expression_wrapper::expression& exp,
                            const binary_op<sub_> &v) {
        std::cout << "minus" << std::endl;
        exp = boost::get<boost::recursive_wrapper<double>>(v.left)
            - boost::get<boost::recursive_wrapper<double>>(v.right);
        return exp;
    }
    expression_wrapper::expression& operator +=
       (expression_wrapper::expression &exp1,
        expression_wrapper::expression &exp2) {
        exp1 = exp2;
        return exp1;
    }
    expression_wrapper::expression& operator += (
        expression_wrapper::expression &exp,
        cmd_varset<TypeDouble<int> > &v) {
        std::cout << "molobster1" << std::endl;
        cmd_varset<TypeDouble<int> > tdp = v;
        TypeDouble<int> td = tdp.value; //.value.value = v.value.value;
        td.value = tdp.value.value;
        double r = td.value;
        std::cout << "molobster2" << std::endl;
        std::cout << r  << std::endl;
        value = r;
        exp  += r;
        return  exp;
    }

    expression_wrapper::expression& operator += (
    expression_wrapper::expression& exp, const cmd_print<TypeDoublePrint<int> > &v) {
        exp += v.getVal().value;
        return exp;
    }


    class ast_struct: public boost::static_visitor<double> {
    public:
        double operator()(std::string txt) const {
            std::cout << txt << std::endl;
            return 123.42;
        }
        double operator()(const binary_op<add_> &obj) {

        }
        double operator()(double val) const {
            std::cout << "getter value01: " << val << std::endl;
            value = val;
            //return boost::apply_visitor( ast_struct(), tdp.expr );
            return  value;
        }

        double operator()(binary_op<add_> & binary) {
            //return boost::apply_visitor( ast_struct(), binary.left )
            //     + boost::apply_visitor( ast_struct(), binary.right);
        }
        double operator()(const binary_op<sub_> & binary) const     {
            std::cout << "double subserle" << std::endl;
            std::cout << boost::get<boost::recursive_wrapper<double>>(binary.left)  << std::endl;
            std::cout << boost::get<boost::recursive_wrapper<double>>(binary.right) << std::endl;

            return 2.2; //boost::apply_visitor( ast_struct(), binary.left );
               //- boost::apply_visitor( ast_struct(), binary.right );
        }
        /*
        double operator()(binary_op<mul_> &d0) {
            std::cout << "double:" << std::endl;

            expression_wrapper::expression d1; d1 = binary_op<mul_>(d0.left );
            expression_wrapper::expression d2; d2 = binary_op<mul_>(d0.right);

            expression_wrapper::expression d4; d4 = d1;

            return boost::apply_visitor( ast_struct(), d1)
                 * boost::apply_visitor( ast_struct(), d2);
        }*/
        /*
        double operator()(binary_op<div_> & binary) {
            //boost::recursive_wrapper<binary_op<div_>> tmp1; tmp1 = binary;
            //auto d2 = binary_op<div_>(tmp1);

            expression_wrapper::expression d1; d1 = binary_op<div_>(binary.left);
            expression_wrapper::expression d2; d2 = binary_op<div_>(binary.right);

            return boost::apply_visitor( ast_struct(), d1)
                 / boost::apply_visitor( ast_struct(), d2);
        }*/
    };


    std::ostream& operator << (std::ostream& os, const binary_op<add_> &val) {
        os << "adder" << std::endl;
        return os;
    }
    std::ostream& operator<< (std::ostream& os, const binary_op<sub_> &val) {
        std::cout << "subser" << std::endl;
        return os;
    }
    std::ostream& operator<< (std::ostream& os, binary_op<mul_> val_) {
        os << "muller" << std::endl;
        return os;
    }
    std::ostream& operator<< (std::ostream& os, const binary_op<div_> &val) {
        os << "diver" << std::endl;
        return os;
    }

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
    void SkipWhiteSpaces()
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
        return;
    }

    QString GetIdent()
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

        SkipWhiteSpaces();
        return ident;
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

    QString GetNumber(void)
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
            SkipWhiteSpaces();
            return true;
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
        template <typename T> grammar & operator << (T &t) { t.parse();return *this; }
        template <typename T> grammar & operator +  (T &t) { t.parse();return *this; }
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
            go +char_ << assign_ << int_;

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
        }
    };

    void test()
    {
        expression_wrapper::expression res1 = binary_op<mul_>(2.0 ,5.0);
        //expression_wrapper::expression res2 = binary_op<sub_>(3.0,res1);
        expression_wrapper::expression result = ( res1 );

        expression_wrapper::expression res3 = binary_op<add_>(21.13,0.00);

        std::cout << std::endl
                  << "start visitor..."
                  << std::endl;
        std::cout << boost::apply_visitor(ast_struct(),res3  ) << std::endl; std::cout << "next...\n";
        std::cout << boost::apply_visitor(ast_struct(),result) << std::endl;

    }
}

// int main() {
bool parseText(QString src)
{
    using namespace kallup;
    kallup::test();
    return true;
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
