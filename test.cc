#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

#define  BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT
#define  BOOST_SPIRIT_USE_PHOENIX_V3
#define  BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT

#include <boost/config/warning_disable.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

using namespace boost::spirit;

namespace bs    = boost::spirit;
namespace phx   = boost::phoenix;
namespace ascii = boost::spirit::ascii;

using boost::spirit::ascii::space; // use the ASCII space parser
using boost::spirit::ascii::char_;
using boost::spirit::_val;

using boost::phoenix::val;

#ifdef QT
#include <QString>
#include <QVariant>
#include <QMessageBox>
#endif

// ------------------------------------------------------
// namespace to avoid conflicts with other frameworks ...
// ------------------------------------------------------
namespace client
{
    int line_no  = 1;
    double value = 0.00;    // math

    struct nil { };

    struct expression_ast
    {
        typedef
        boost::variant<
              nil
            , int
            , double
            , std::string
            , boost::recursive_wrapper<expression_ast>
        >
        type;
        type expr;

        template <typename Expr>
        expression_ast(Expr const & expr)
            : expr(expr) {  }

        expression_ast() {}
    };

    struct ast_print
    {
        typedef void result_type;
    };

    template <typename Lexer>
    struct dbase_tokens : lex::lexer<Lexer>
    {
        dbase_tokens()
        {
        }
    };

    template <typename Iterator, typename Lexer>
    struct dbase_grammar
    :   public qi::grammar<Iterator>
    {   template <typename TokenDef>

        dbase_grammar(TokenDef const& tok) :
        dbase_grammar::base_type(start, "start")
        {
            start = qi::int_;
            
            start.name("start");
        }
        
        typedef qi::unused_type skipper_type;
        typedef qi::rule<Iterator, skipper_type> simple_rule;
        
        simple_rule start;
    };


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

    // -----------------------------------
    // parser oode for an dBase parser ...
    // -----------------------------------
    class dBase {
    public:
        dBase() {
            std::cout << "handle dbase grammar..."
                      << std::endl;
        }
        bool InitParseText(std::string text) {
            std::string data(text);

            typedef std::string::iterator base_iterator_type;
            typedef lex::lexertl::token<  base_iterator_type, boost::mpl::vector<char, int, std::size_t, std::string> > tokentype;
            typedef lex::lexertl::actor_lexer<tokentype> lexer_type;

            typedef dbase_tokens<lexer_type> dbase_tokens;
            typedef dbase_tokens::iterator_type iterator_type;
            typedef dbase_grammar<iterator_type, dbase_tokens::lexer_def> dbase_grammar;

            dbase_tokens  tokens;
            dbase_grammar dbase(tokens);

            base_iterator_type it = data.begin();
            iterator_type iter    = tokens.begin(it, data.end());
            iterator_type end     = tokens.end();

            expression_ast ast;
            return qi::parse(iter, end, dbase, ast);
        }
        void start(std::string src) {
            if (InitParseText(src))
                std::cout << "SUCCESS" << std::endl; else
                std::cout << "ERROR"   << std::endl;
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


int main() {
    using namespace client;
    Parser<dBase> p;
    p.start("// xxxxx");
    return 0;
}
 
