// -----------------------------------------------
// KI - Testumgebung (c) 2017 de.sci.informatik.ki
// All Rights Reserved.
//
// touched by: Jens Kallup - 18.07.2017
// -----------------------------------------------
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <set>
#include <utility>

using namespace std;

#define  BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT
#define  BOOST_SPIRIT_USE_PHOENIX_V3
#define  BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT

#include <boost/config/warning_disable.hpp>

#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/object/construct.hpp>

#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/phoenix.hpp>

using namespace boost::spirit;

namespace bs    = boost::spirit;
namespace phx   = boost::phoenix;
namespace ascii = boost::spirit::ascii;

using boost::spirit::ascii::space; // use the ASCII space parser
using boost::spirit::ascii::char_;
using boost::spirit::_val;

using boost::phoenix::val;

#include <QString>
#include <QVariant>
#include <QMessageBox>

// ----------------------------------------
// exception classes for error handling ...
// ----------------------------------------
class QStringError {
public:
    QStringError(QString str) { what = str; }
    QStringError()            { what = QString("common mistake"); }
    QString what;
};

namespace boost { namespace spirit { namespace traits
{
    template <> struct is_container<QString> : mpl::true_ {};
    template <> struct container_value<QString> : mpl::identity<QChar> {};
    template <>
    struct push_back_container<QString, QChar>
    {
        static bool call(QString& c, QChar const& val)
        {
            c.append(val);
            return true;
        }
    };
}}}

// ------------------------------------------------------
// namespace to avoid conflicts with other frameworks ...
// ------------------------------------------------------
namespace kallup
{
    int line_no  = 1;

    struct class_op;
    struct binary_op;
    struct unary_op;

    struct expression_ast
    {
        typedef
        boost::variant<
              int
            , double
            , std::string
            , boost::recursive_wrapper<expression_ast>
            , boost::recursive_wrapper<binary_op>
            , boost::recursive_wrapper<unary_op>
            , boost::recursive_wrapper<class_op>
        >
        type;
        type expr;

        template <typename Expr>
        expression_ast(Expr const & expr)
            : expr(expr) {  }

        expression_ast() {}
        expression_ast(
                  std::string const& name
                , std::string const& str1
                , std::string const& str2
                , expression_ast const& rhs);

        expression_ast(expression_ast const & rhs, std::string const & name);

        expression_ast& operator += (expression_ast const & rhs);
        expression_ast& operator -= (expression_ast const & rhs);
        expression_ast& operator *= (expression_ast const & rhs);
        expression_ast& operator /= (expression_ast const & rhs);
    };

    expression_ast dast;
    expression_ast end_result;

    struct binary_op
    {
        binary_op(
              char op
            , expression_ast const & left
            , expression_ast const & right)
            : op(op)
            , left(left)
            , right(right)
        {
            std::cout << "Math2: " << std::endl;
        }

        char op;
        expression_ast left;
        expression_ast right;
    };

    struct unary_op
    {
        unary_op(
            char op
          , expression_ast const& subject)
        : op(op), subject(subject) {}

        char op;
        expression_ast subject;
    };

    struct class_op
    {
        class_op(
              std::string const& op
            , std::string const& cname
            , std::string const& oname
            , expression_ast const& left
            , expression_ast const& right)
            : op(op)
            , class_cname(cname)
            , class_oname(oname)
            , left(left)
            , right(right) { }

        std::string op;
        std::string class_cname;
        std::string class_oname;

        expression_ast left;
        expression_ast right;
    };

    expression_ast::expression_ast(expression_ast const & rhs, std::string const & name) {
        cout << "dinit" << endl;
        cout << name << endl;
        cout << rhs.expr.type().name() << endl;

        expr = rhs;
    }

    expression_ast::expression_ast  (
              std::string const& name
            , std::string const& str1
            , std::string const& str2, expression_ast const& rhs) {
        expr = class_op(name, str1, str2, *this, rhs);
    }

    expression_ast& expression_ast::operator += (expression_ast const& rhs) {
        expr = binary_op('+', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator -= (expression_ast const& rhs) {
        expr = binary_op('-', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator *= (expression_ast const& rhs) {
        expr = binary_op('*', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator /= (expression_ast const& rhs) {
        expr = binary_op('/', expr, rhs);
        return *this;
    }

    // We should be using expression_ast::operator-. There's a bug
    // in phoenix type deduction mechanism that prevents us from
    // doing so. Phoenix will be switching to BOOST_TYPEOF. In the
    // meantime, we will use a phoenix::function below:
    struct negate_expr {
        template <typename T>
        struct result { typedef T type; };

        expression_ast operator()(expression_ast & expr) const {
            cout << "lllllllllllllllll\n";
            return expression_ast(unary_op('-', expr));
        }
    };

    phx::function<negate_expr> neg;

    // -----------------------
    // walk throug the AST ...
    // -----------------------
    struct ast_print
    {
        typedef void result_type;

        void operator()(int const value)
        {
            cout << "const int = " << value << endl;
            dast = value;
            cout << dast.expr.type().name() << endl;
        }

        void operator()(expression_ast const& ast) const
        {
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

        void operator()(unary_op const& expr) const
        {
            std::cout << "op:" << expr.op << "(";
            boost::apply_visitor(*this, expr.subject.expr);
            std::cout << ')';
        }

        void operator()(class_op const& expr) const
        {
            std::cout << "class:"
                      << expr.class_cname << ":"
                      << expr.class_oname
                      << "(null)"
                      << std::endl;
            boost::apply_visitor(*this, expr.left.expr);
        }
    };

    struct line_no_struct {
        template <typename T>
        void operator()(T const &t) const  {
            char c = t;
            if (c == '\n' || c == '\r') {
                ++line_no;
            }
        }
    };

    struct handle_true_struct {
        template <typename, typename, typename>
        struct result { typedef void type; };
        void operator()() const {
            QMessageBox::information(0,"Info","ein truer");
        }
    };
    struct handle_false_struct {
        template <typename, typename, typename>
        struct result { typedef void type; };
        void operator()() const {
            QMessageBox::information(0,"Info","ein false");
        }
    };
    phx::function<handle_true_struct > const handle_true  = handle_true_struct ();
    phx::function<handle_false_struct> const handle_false = handle_false_struct();

    struct error_handler_
    {
         template <typename, typename, typename>
         struct result { typedef void type; };

         template <typename Iterator>
         void operator()(
              info const& what
            , Iterator err_pos, Iterator last) const
            {
            std::stringstream ss;
            ss  << "Error! Expecting "
                 << what                         // what failed?
                 << " here: \""
                 << std::string(err_pos, last)   // iterators to error-pos, end
                 << "\""
                 << std::endl
            ;
            std::cout << ss.str();
            QMessageBox::information(0,"Parser", ss.str().c_str());
        }
    };
    phx::function<error_handler_> const error_handler = error_handler_();

    // ------------------------------------------------
    // custom skipper ...
    // for comments
    // ------------------------------------------------
    struct error_handler_skip_
    {
         template <typename, typename, typename>
         struct result { typedef void type; };

         template <typename Iterator>
         void operator()(
             info const& what,
             Iterator err_pos, Iterator last) const {
             std::stringstream ss;
             ss  << "Error! Expectingkkklkl "
                 << what                         // what failed?
                 << " here: \""
                 << std::string(err_pos, last)   // iterators to error-pos, end
                 << "\""
                 << std::endl
             ;
             std::cout << ss.str();
             QMessageBox::information(0,"Parser", ss.str().c_str());
        }
    };
    boost::phoenix::function<  error_handler_skip_ >
    const error_handler_skip = error_handler_skip_ ();

    template <typename Iterator>
    struct dbase_skipper : qi::grammar<Iterator>
    {
        dbase_skipper() : dbase_skipper::base_type(my_skip, "dBase")
        {
            using boost::spirit::qi::lexeme;
            using qi::ascii::char_;
            using qi::ascii::space;
            using qi::lit;
            using qi::eol;
            using qi::eoi;

            using qi::on_error;
            using qi::fail;

            my_skip =
                (space [ line_func(qi::_1) ] )
                |
                (lexeme["**"]) >> *((char_) - eol) >> (eol | eoi ) |
                (lexeme["&&"]) >> *((char_) - eol) >> (eol | eoi ) |
                (lexeme["//"]) >> *((char_) - eol) >> (eol | eoi )
                |
                (lexeme["/*"]) >> *((char_) - lexeme["*/"]) >> (lexeme["*/"])
            ;

            on_error<fail> (
                  my_skip
                , std::cout
                << boost::phoenix::val("Error! Expecting comment")
                << std::endl
            );
        }

        dbase_skipper operator()(Iterator) { }

        phx::function<line_no_struct> line_func;
        qi::rule<Iterator> my_skip;
    };

    template <typename Iterator, typename Skipper = dbase_skipper<Iterator>>
    struct dbase_grammar : public qi::grammar<Iterator,Skipper>
    {
        qi::rule<Iterator, Skipper> start;
        dbase_grammar() :
        dbase_grammar::base_type(start)
        {
            using boost::spirit::qi::no_case;
            using boost::spirit::qi::_val;

            using qi::lit;
            using qi::char_;
            using qi::lexeme;

            using qi::on_error;
            using qi::fail;

            start
                = +symsbols
                ;

            expression =
                term                            [ _val  = qi::_1 ]
                >> *(   ('+' >> term            [ _val += qi::_1 ])
                    |   ('-' >> term            [ _val -= qi::_1 ])
                    )
                ;

            term =
                factor                          [ _val  = qi::_1]
                >> *(   ('*' >> factor          [ _val *= qi::_1])
                    |   ('/' >> factor          [ _val /= qi::_1])
                    )
                ;

            factor =
                qi::int_                [ _val = qi::_1 ]
                |  '('   >> expression          [ _val = qi::_1 ] >> ')'
                |   ('-' >> factor              [ _val = neg(qi::_1)])
                |   ('+' >> factor              [ _val = qi::_1 ] )
                ;

            qi::on_error<fail>(symsbols, error_handler(qi::_4, qi::_3, qi::_2));
            symsbols
                = symbol_true | symbol_false
                ;

            symbol_true  = ((lexeme[no_case["true" ]] | lexeme[no_case[".t."]]) [ handle_true () ] );
            symbol_false = ((lexeme[no_case["false"]] | lexeme[no_case[".f."]]) [ handle_false() ] );
        }

        qi::rule<Iterator, Skipper> symsbols, symbol_false, symbol_true;
        qi::rule<Iterator, expression_ast()>
            expression, term, factor;
    };

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

    // -----------------------------------
    // parser oode for an dBase parser ...
    // -----------------------------------
    class dBase {
    public:
        dBase() {
            std::cout << "handle dbase grammar..."
                      << std::endl;
        }
        template <typename Iterator, typename Skipper>
        bool pparse(Iterator &iter,
                    Iterator &end,
                    const dbase_grammar<Iterator, Skipper> &g) {
            typedef dbase_skipper<Iterator> skipper;
            skipper skips;

            return
            boost::spirit::qi::phrase_parse(
            iter, end, g, skips, end_result);
        }
        bool InitParseText(QString text)
        {
            std::string data(text.toLatin1().data());
            if (data.size() < 1)
            throw new QStringError("No data for parser.");

            typedef std::string::const_iterator iterator_t;

            iterator_t iter = data.begin();
            iterator_t end  = data.end();

            typedef dbase_skipper <iterator_t> skipper;
            typedef dbase_grammar <iterator_t, skipper> grammar;

            grammar pg;
            return pparse(iter, end, pg);
        }
        bool start(QString src)  {
            if (InitParseText(src)) {
                QMessageBox::information(0,"Info","SUCCESS");
                return true;
            } else {
                throw new QStringError;
                return false;
            }
        }
    };

    template   <typename T>
    class Parser: public T {
    public:
        Parser() {
            std::cout << "parser init." << std::endl;
            line_no = 1;
        }
    };
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
        return p.start(src);
    }
    catch (QStringError *e) {
        QMessageBox::critical(0,"Error",
        QString("Error in line: %1\n%2")
        .arg(line_no)
        .arg(e->what));
    }
    return false;
}
