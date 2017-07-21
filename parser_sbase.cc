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
#include <iterator>
using namespace std;

#include "mainwindow.h"

#define  BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT
#define  BOOST_SPIRIT_USE_PHOENIX_V3
#define  BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT

#include <boost/config/warning_disable.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
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
#include <boost/phoenix/object/construct.hpp>

#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/range.hpp>
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
    int line_col = 1;

    // -----------------------------
    // minmal info of some flags ...
    // -----------------------------
    char cmd_load = 0;
    char cmd_dara = 0;  // load data ""

    std::vector<std::string> stempList;

    std::string stemp1;
    std::string stemp2;
    std::string stemp3;

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
        typedef std::string result_type;
        template <typename T>
        void operator()(T const &t) const {
            char c = t;
            if (c == '\n' || c == '\r') {
                ++line_no;
                  line_col = 1;
            }
            else if (c == ' ') {
                ++line_col;
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
            QMessageBox::information(0,"Info","ein falser");
        }
    };
    phx::function<handle_true_struct > const handle_true  = handle_true_struct ();
    phx::function<handle_false_struct> const handle_false = handle_false_struct();

    struct any_string_value_ {
        typedef std::string result_type;
        template <typename T>
        std::string operator()(T const t) const {
            auto s1 = std::string(t);
            std::cout << s1 << std::endl;
            return s1;
        }
    };
    phx::function<any_string_value_> any_string_value;

    struct handle_line_col_add_struct {
        typedef void result_type;
        template <typename T>
        void operator()(T const &t) const {
            line_col += (int)(t);
        }
    };
    phx::function<handle_line_col_add_struct> line_col_add;

    // ---------------------------
    // load local sqlite3 data ...
    // ---------------------------
    struct handle_load_struct {
        template <typename>
        struct result { typedef void type; };

        template <typename T>
        void operator()(T const &t) const {
            auto s1 = std::string(t);
            QMessageBox::information(0,"Info",
            QString("eine datenbank: %1")
            .arg(s1.c_str()));
        }
    };
    phx::function<handle_load_struct> handle_load_data;

    // ------------------------------------------------------
    // define objects, or load them from database - facts ...
    // ------------------------------------------------------
    struct handle_define_struct {
        typedef std::string result_type;
        template <typename T>
        std::string operator()(T const &t) const {
            auto s1 = std::string(t);
            QMessageBox::information(0,"Info",
            QString("define: %1, noch keine Daten?")
            .arg(s1.c_str()));
            return s1;
        }
        template <typename T1, typename T2>
        std::string operator()(T1 const &t1, T2 const &t2) const {
            auto s1 = std::string(t1);
            auto s2 = std::string(t2);
            QMessageBox::information(0,"Info",
            QString("define: %1, Daten in File: %2?")
            .arg(s1.c_str())
            .arg(s2.c_str()));
            return s1;
        }
    };
    phx::function<handle_define_struct> handle_object;

    // --------------------------
    // SET handler (language, ...
    // --------------------------
    struct handle_set_struct {
        typedef std::string result_type;
        template <typename T1,
                  typename T2,
                  typename T3>
        std::string operator()(
            T1 const &t1,
            T2 const &t2,
            T3 const &t3) const {
            auto s1 = std::string(t1);
            auto s2 = std::string(t2);
            auto s3 = std::string(t3);

            std::cout << s1 << std::endl;
            std::cout << s2 << std::endl;
            std::cout << s3 << std::endl;


#if 0
            if (qstr1.toUpper() == QString("lang")    .toUpper()
            ||  qstr1.toUpper() == QString("language").toUpper());
            else
            throw QStringError("token nicht erkannt");

            // source lang
            if (qstr2.toUpper() == QString("de").toUpper()) { } else
            if (qstr2.toUpper() == QString("en").toUpper()) { } else
            throw QStringError("token nicht erkannt");

            // target lang
            if (qstr3.toUpper() == QString("de").toUpper()) { } else
            if (qstr3.toUpper() == QString("en").toUpper()) { } else
            throw QStringError("token nicht erkannt");

            if (qstr2.toUpper() == qstr3.toUpper())
            throw QStringError("source == target\nnot allowed.");

            // ----------------------
            // set tmp. variables ...
            // ----------------------
            setSource(qstr2.toUpper());
            setTarget(qstr3.toUpper());
#endif
            return s1;
        }

        void setSource(QString &l) const { source = l; }
        void setSource(QString  l) const { source = l; }

        void setTarget(QString  l) const { target = l; }
        void setTarget(QString &l) const { target = l; }

        mutable QString source;
        mutable QString target;
    };
    phx::function<handle_set_struct> handle_set;

    // ------------------------------------
    // translate, speak words or text's ...
    // ------------------------------------
    struct handle_trans_say_struct {
        typedef void result_type;
        template <typename T1, typename T2>
        void operator()(
            T1 const &t1,
            T2 const &t2) const {
            auto s1 = std::string(t1);
            auto i1 = int(t2);
            //auto *trans = MyTranslator(t);

            if (i1 == 1) stemp1 = s1; else
            if (i1 == 2) stemp2 = s1; else
            if (i1 == 3) stemp3 = s1;

            if (s1 == std::string("set@ok")) {
                std::cout << "=> " << stemp1
                          << ", "  << stemp2
                          << ", "  << stemp3 << " <---"
                          << std::endl;
            }

            if (i1 == 0) {
                std::cout << "SAY: " << s1 << std::endl;
            }

            QString dataText = QString::fromStdString(s1);
            mainWin->formWindow
                    ->dataEdit
                    ->document()
                    ->setPlainText(dataText);
        }
    };
    phx::function<handle_trans_say_struct> handle_trans_say;

    struct error_handler_
    {
        template <typename>
        struct result { typedef void type; };

        template <typename T>
        void operator()(T const &t) const {
            auto s1 = std::string(t);
            QString err_str = s1.c_str();
            QStringList sl = err_str.split(':');

            QString pos = QString("\n"
                        "LineNo : %1\n"
                        "ColumNo: %2").
                    arg(line_no).
                    arg(line_col);

            if (sl.at(0) == QString("cmd")) {
                if (sl.at(1) == QString("load")) err_str = QString("LOAD DATA \"datafile\""); else
                if (sl.at(1) == QString("say" )) err_str = QString("SAY word"); else
                if (sl.at(1) == QString("set" )) err_str = QString("SET LANG de en");

            }

            else {
                std::cout << s1 << std::endl;
            }

            std::stringstream ss;
            ss  << "Error! Expecting: "      << std::endl
                << err_str.toLatin1().data() << std::endl
                << pos    .toLatin1().data()
                << std::endl
            ;
            QMessageBox::information(0,"Parser-Error", ss.str().c_str());
        }
    };
    phx::function<error_handler_> const error_handler = error_handler_();

    // ------------------------------------------------
    // custom skipper ...
    // for comments
    // ------------------------------------------------
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
                (lexeme[char_("\t\n\r")] [ line_func(qi::_1) ] )
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
            using boost::spirit::standard_wide::no_case;
            using boost::spirit::standard_wide::char_;
            using boost::spirit::standard_wide::string;

            using boost::spirit::qi::lexeme;
            using boost::spirit::qi::lit;
            using boost::spirit::qi::_val;

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
                  n_expr                        [ _val = qi::_1 ]
                |  '('   >> expression          [ _val = qi::_1 ] >> ')'
                |   ('-' >> factor              [ _val = neg(qi::_1)])
                |   ('+' >> factor              [ _val = qi::_1 ] )
                ;

            n_expr =
                  int_   [ _val = qi::_1 ]
                | float_ [ _val = qi::_1 ]
                ;

            my_string %=
                (
                lexeme["'"  >> +(char_ - "'" ) >> "'" ][ _val = qi::_1, any_string_value(qi::_1) ] |
                lexeme["\"" >> +(char_ - "\"") >> "\""][ _val = qi::_1, any_string_value(qi::_1) ] |
                lexeme["["  >> +(char_ - "]" ) >> "]" ][ _val = qi::_1, any_string_value(qi::_1) ] )
                ;

            my_symbol
                = qi::as_string [
                    +qi::alnum |
                    *lexeme[char_("\u00f6\u00d6"
                                  "\u00dc\u00fc"
                                  "\u00c4\u00e4"
                                  "\u00df")]]
                [ _val = qi::_1 ]
                ;

            symsbols
                = symbol_true
                | symbol_false
                | n_expr
                | cmd_load
                | cmd_set
                | cmd_say
                ;

            cmd_load
                = symbol_load > +(qi::ascii::space)
                > symbol_data > +(qi::ascii::space)
                > my_string
                [ handle_load_data(qi::_1) ]
                ;

            cmd_set
                = (symbol_set > +(qi::ascii::space)
                > (my_symbol [ handle_trans_say(qi::_1,1) ] ) >  +(qi::ascii::space)
                > (my_symbol [ handle_trans_say(qi::_1,2) ] ) >  +(qi::ascii::space)
                > (my_symbol [ handle_trans_say(qi::_1,3) ] ) >> *(qi::ascii::space)
                [ handle_trans_say(std::string("set@ok"),4) ]
                )
                ;

            cmd_say
                = (symbol_say >  +(qi::ascii::space)
                > (my_symbol [ handle_trans_say(qi::_1,0) ] )  >> *(qi::ascii::space))
                ;

            symbol_true   = ((lexeme[no_case["true" ]])  )
                            |(lexeme[no_case[".t."  ]])  ;
            symbol_false  = ((lexeme[no_case["false"]])  )
                            |(lexeme[no_case[".f."  ]])  ;

            symbol_load   = (lexeme[no_case["load" ]]   );
            symbol_data   = (lexeme[no_case["data" ]]   );

            symbol_define = (lexeme[no_case["define"]]  );
            symbol_set    = (lexeme[no_case["set"]]     );
            symbol_say    = (lexeme[no_case["say"]]     );

            // error's ...
            qi::on_error<fail>(cmd_load, error_handler(std::string("cmd:load")));
            qi::on_error<fail>(cmd_say , error_handler(std::string("cmd:say" )));
            qi::on_error<fail>(cmd_set , error_handler(std::string("cmd:set" )));
        }


        qi::rule<Iterator, Skipper>
            symsbols, symbol_false, symbol_true,
            symbol_define,
            symbol_source, symbol_target,
            symbol_load,
            symbol_data;

        qi::rule<Iterator, void(), Skipper>
            cmd_say,
            cmd_load,
            cmd_set;

        qi::rule<Iterator, std::string(), Skipper>

            symbol_set,
            symbol_say,
            my_symbol,
            my_string;

        qi::rule<Iterator, expression_ast()>
            expression, term, factor,
            n_expr;
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
            using namespace boost;
            using namespace spirit::qi;
            using namespace std;

            std::string data = text.toStdString();
            if (data.size() < 1)
            throw new QStringError("No data for parser.");

            auto str_std = std::string(data);
            typedef std::string::const_iterator iterator_t;

            iterator_t iter = str_std.begin();
            iterator_t end  = str_std.end();

            typedef dbase_skipper <iterator_t> skipper;
            typedef dbase_grammar <iterator_t, skipper> grammar;

            // ----------------
            // remove trash ...
            // ----------------
            stempList.clear();
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
    catch (...) {
        QMessageBox::information(0,"Error",
        "unknow error occur.");
    }

    return false;
}
