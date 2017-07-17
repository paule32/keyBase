#ifndef TYPESTRUCT_H
#define TYPESTRUCT_H

struct TypeDouble {
    TypeDouble operator = (double val) {
        value = val;
        return *this;
    }
    double value;
    expression expr;
};

struct TypeDoublePrint {
    operator TypeDoublePrint() {
        return *this;
    }
    TypeDoublePrint operator = (double val) {
        value = val;
        return *this;
    }
    double value;
};


#endif // TYPESTRUCT_H
