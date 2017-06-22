#include <stdio.h>

#include <iostream>
#include <string>

#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

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

    struct add { };
    struct sub { };
    struct mul { };
    struct div { };
    template <typename OpTag> struct binary_op;

    typedef boost::variant<
          double
        , boost::recursive_wrapper< binary_op<add> >
        , boost::recursive_wrapper< binary_op<sub> >
        , boost::recursive_wrapper< binary_op<mul> >
        , boost::recursive_wrapper< binary_op<div> >
        > expression;

    template <typename OpTag>
    struct binary_op
    {
        expression left;  // variant instantiated here...
        expression right;

        binary_op( const expression & lhs, const expression & rhs )
            : left(lhs), right(rhs)
        {
        }

        double get(binary_op<sub> *bo)
        {
            std::cout << "getter\n";

            ///left  = bo->left ;
            //right = bo->right;

            //double res = boost::get<double>(left)
            //           - boost::get<double>(right);
            return 2.0;
        }

        binary_op(binary_op<mul> *mul, double val)
        {
            std::cout << "mexter" << std::endl;
            left  = mul;
            right = val;
        }

        binary_op(binary_op<sub> *bo)   {
            std::cout << "-----------------\n";

            std::cout << bo->left  << std::endl;
            std::cout << bo->right << std::endl;

            if (typeid(bo) == typeid(binary_op<sub>)) {
                std::cout << " ok = left" << std::endl;

                double res2 = get(&bo);

                std::cout << "==>> " << res2 << std::endl;
            }
            else {
                std::cout << (boost::get<double>(bo->left )
                            - boost::get<double>(bo->right))
                          <<  std::endl;
            }
        }
        binary_op(const binary_op<add> &bo)   {
            //std::cout << bo.left  << std::endl;
            //std::cout << bo.right << std::endl;

            std::cout << (boost::get<double>(bo.left )
                        + boost::get<double>(bo.right))
                      <<  std::endl;
        }
        binary_op(const binary_op<mul> &bo)   {
            std::cout << "mopser" << std::endl;
            //std::cout << bo.left  << std::endl;
            //std::cout << bo.right << std::endl;

            left  = bo.left ;
            right = bo.right;

            std::cout << (boost::get<double>(bo.left )
                       *  boost::get<double>(bo.right))
                      <<  std::endl;
        }
        binary_op(const binary_op<div> &bo)   {
            //std::cout << bo.left  << std::endl;
            //std::cout << bo.right << std::endl;

            std::cout << (boost::get<double>(bo.left )
                        / boost::get<double>(bo.right))
                      <<  std::endl;
        }
    };

    class calculator: public boost::static_visitor<double> {
    public:
        double operator()(double value) const {
            std::cout << "getter value: " << value << std::endl;
            return value;
        }
        double operator()(const binary_op<add> & binary) const     {
            return boost::apply_visitor( calculator(), binary.left )
                 + boost::apply_visitor( calculator(), binary.right );
        }
        double operator()(const binary_op<sub> & binary) const     {
            std::cout << "double subserle" << std::endl;
            std::cout << binary.left  << std::endl;
            std::cout << binary.right << std::endl;

            return boost::apply_visitor( calculator(), binary.left )
                 - boost::apply_visitor( calculator(), binary.right );
        }
        double operator()(const binary_op<mul> & binary) const     {
            std::cout << "double:" << std::endl;
            std::cout << binary.left  << std::endl;
            std::cout << binary.right << std::endl;

            return boost::apply_visitor( calculator(), binary.left )
                 * boost::apply_visitor( calculator(), binary.right );
        }
        double operator()(const binary_op<div> & binary) const     {
            return boost::apply_visitor( calculator(), binary.left )
                 / boost::apply_visitor( calculator(), binary.right );
        }
    };

    expression& operator - (expression& exp, const binary_op<sub> &v) {
        exp = boost::get<double>(v.left)
            - boost::get<double>(v.right);
        return exp;
    }

    std::ostream& operator << (std::ostream& os, const binary_op<add> &val) {
        qDebug() << "adder";

        double res = boost::get<double>(val.left)
                   + boost::get<double>(val.right);

        os << val.left  << std::endl;
        os << val.right << std::endl;
        os << "A------" << std::endl;
        os << res       << std::endl;

        return os;
    }
    std::ostream& operator<< (std::ostream& os, const binary_op<sub> &val) {
        qDebug() << "subser";
        return os;
    }
    std::ostream& operator<< (std::ostream& os, const binary_op<mul> &val) {
        qDebug() << "muller";
        return os;
    }
    std::ostream& operator<< (std::ostream& os, const binary_op<div> &val) {
        qDebug() << "diver";
        return os;
    }


    void test()
    {
        expression res1 = binary_op<mul>(2.0 ,4.0);
        expression res2 = binary_op<sub>(res1,3.0);
        expression result = ( res2 );

        std::cout << boost::apply_visitor(calculator(),result) << std::endl;

    }

#if 0
    class expression_ast
    {
    public:
        typedef
        boost::variant<
              nil
            , int
            , double
            , boost::recursive_wrapper<expression_ast>
            , boost::recursive_wrapper<binary_op>
        >
        type_expr;
        type_expr expr;

        expression_ast()  {}

        expression_ast & operator += (int rhs);
        //expression_ast & operator -= (expression_ast * rhs);
        //expression_ast & operator *= (expression_ast * rhs);
        //expression_ast & operator /= (expression_ast * rhs);
    };

    expression_ast expr_ast;

    std::ostream& operator<< (std::ostream& os, const expression_ast &ast)
    {
        qDebug() << "blaxter: ";
        os << ast.expr;
        return os;
    }

    std::ostream& operator<< (std::ostream& os, const nil &sn)
    {
        qDebug() << "nullscher";
        return os;
    }

    struct binary_op
    {
        binary_op(
              char op
            , expression_ast & left
            , expression_ast & right)
            : op(op)
            , left(left)
            , right(right)
        {
            std::cout << "Math2: " << std::endl;
        }

        //binary_op(char op, expression_ast::type_expr &left, expression_ast *right)
        binary_op(char op, expression_ast::type_expr &left, int right)
        {
            qDebug() << "lefter";
            expr_ast.expr = right;
        }

        binary_op & operator << (binary_op bop) {
            left  = bop.left;
            right = bop.right;
            return *this;
        }

        char op;
        expression_ast left;
        expression_ast right;
    };

    expression_ast& expression_ast::operator += (int rhs) {
        qDebug() << "inter: " << rhs;
        expr = binary_op('+', expr, rhs);
        return *this;
    }

    /*
    expression_ast& expression_ast::operator -= (expression_ast * rhs) {
        expr = binary_op('-', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator *= (expression_ast * rhs) {
        expr = binary_op('*', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator /= (expression_ast * rhs) {
        expr = binary_op('/', expr, rhs);
        return *this;
    }*/

    QDebug & operator << (QDebug dbg, const expression_ast ast) {
        dbg << "hallo";
        return dbg;
    }

    std::ostream& operator<< (std::ostream& os, const binary_op &bipo)
    {
        qDebug() << "bipo";
        //qDebug() << boost::get<double>(bipo);

        os << bipo.left;
        os << bipo.right;

        return os;
    }


    // -------------------------------
    // print/handle our AST - exec ...
    // -------------------------------
    struct ast_print {
        typedef void result_type;

        void operator()(nil const & dv) const
        {
            qDebug() << "NILer";
        }
        void operator()(int const & dv) const
        {
            std::cout << "int: " << dv << std::endl;
        }
        void operator()(double const & dv) const
        {
            std::cout << "dbl: " << dv << std::endl;
        }

        void operator()(expression_ast const& ast) const
        {
            qDebug() << "aster";

            qDebug() << typeid(ast.expr).name();

            if (expr_ast.expr.type() == typeid(binary_op)) {
                std::cout << boost::get<binary_op>(ast.expr) << std::endl;
            }

            qDebug() << "-------";

            //binary_op *bop = boost::get<binary_op>;

            //if (!(ast.expr.type().name() == std::string("N11dBaseParser3nilE")))
            boost::apply_visitor(*this, ast.expr);
        }

        void operator()(binary_op const& expr) const
        {
            std::cout << "op:" << expr.op << "(";
            boost::apply_visitor(*this, expr.left.expr);
            std::cout << ", ";
            boost::apply_visitor(*this, expr.right.expr);
            std::cout << ')';
        }
    };

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

    void test() {
        expression_ast ast; // = new expression_ast;
        ast += int(4);
        expr_ast = ast;
        qDebug() << "ok";

        ast_print printer;
        printer(expr_ast);
    }
#endif
}

bool parseText(QString src)
{
    kallup::test();
    return true;
/*
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
    }*/
    return false;
}
