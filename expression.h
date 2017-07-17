#ifndef EXPRESSION_H
#define EXPRESSION_H

struct add_ { };
struct sub_ { };
struct mul_ { };
struct div_ { };

struct expr   { };
struct sconst { };
struct mconst { };

template <typename OpTag1> struct binary_op;
template <typename OpTag2> struct cmd_print;
template <typename OpTag3> struct cmd_varset;

typedef boost::variant<
  double
, std::string

, boost::recursive_wrapper< binary_op<add_> >
, boost::recursive_wrapper< binary_op<sub_> >
, boost::recursive_wrapper< binary_op<mul_> >
, boost::recursive_wrapper< binary_op<div_> >

, boost::recursive_wrapper< cmd_varset<TypeDouble> >
, boost::recursive_wrapper< cmd_print <TypeDoublePrint> >
> expression;

#endif // EXPRESSION_H
