#include "calculator.hpp"
#include "loader.hpp"
#include "rand.hpp"
#include "stack.hpp"
#include "utility.hpp"
#include <math.h>

using namespace Calculator;

double evaluate(bool);

namespace {
    volatile uint8_t input[STACK_SIZE * 2];
    volatile uint8_t output[STACK_SIZE * 2];
    volatile double numbers[STACK_SIZE];
    double args[8];
    double vars[8];
    double answer;
    uint8_t raw = 0;
    uint8_t idx = 0;
    uint8_t from = 0;
    uint8_t to = 0;
    uint8_t expr_from = 0;
    uint8_t expr_to = 0;
    const Tokens::Token* token = nullptr;
    Error error = Error::NONE;
}

namespace Calculator {
namespace Tokens {
    namespace {
        const char STR_COMMA[] PROGMEM = ",";
        const char STR_LPAR[]  PROGMEM = "(";
        const char STR_RPAR[]  PROGMEM = ")";
        const char STR_ZERO[]  PROGMEM = "0";
        const char STR_ONE[]   PROGMEM = "1";
        const char STR_TWO[]   PROGMEM = "2";
        const char STR_THREE[] PROGMEM = "3";
        const char STR_FOUR[]  PROGMEM = "4";
        const char STR_FIVE[]  PROGMEM = "5";
        const char STR_SIX[]   PROGMEM = "6";
        const char STR_SEVEN[] PROGMEM = "7";
        const char STR_EIGHT[] PROGMEM = "8";
        const char STR_NINE[]  PROGMEM = "9";
        const char STR_POINT[] PROGMEM = ".";
        const char STR_SCI[]   PROGMEM = "x10";
        const char STR_X[]     PROGMEM = "X";
        const char STR_Y[]     PROGMEM = "Y";
        const char STR_A[]     PROGMEM = "A";
        const char STR_B[]     PROGMEM = "B";
        const char STR_C[]     PROGMEM = "C";
        const char STR_D[]     PROGMEM = "D";
        const char STR_E[]     PROGMEM = "E";
        const char STR_F[]     PROGMEM = "F";
        const char STR_ANS[]   PROGMEM = "Ans";
        const char STR_RND[]   PROGMEM = "Rnd#";
        const char STR_EULER[] PROGMEM = "e";
        const char STR_PI[]    PROGMEM = { (char) 0xF7, '\0' };
        const char STR_OR[]    PROGMEM = "OR";
        const char STR_XOR[]   PROGMEM = "XOR";
        const char STR_AND[]   PROGMEM = "AND";
        const char STR_MINUS[] PROGMEM = "-";
        const char STR_PLUS[]  PROGMEM = "+";
        const char STR_MOD[]   PROGMEM = "%";
        const char STR_MUL[]   PROGMEM = "*";
        const char STR_DIV[]   PROGMEM = { (char) 0xFD, '\0' };
        const char STR_COMBI[] PROGMEM = "C";
        const char STR_PERMU[] PROGMEM = "P";
        const char STR_POW[]   PROGMEM = "^";
        const char STR_ROOT[]  PROGMEM = { (char) 0xE8, '\0' };
        const char STR_INV[]   PROGMEM = { (char) 0xE9, '\0' };
        const char STR_FACTO[] PROGMEM = "!";
        const char STR_SIN[]   PROGMEM = "sin";
        const char STR_COS[]   PROGMEM = "cos";
        const char STR_TAN[]   PROGMEM = "tan";
        const char STR_ASIN[]  PROGMEM = { 's', 'i', 'n', (char) 0xE9, '\0' };
        const char STR_ACOS[]  PROGMEM = { 'c', 'o', 's', (char) 0xE9, '\0' };
        const char STR_ATAN[]  PROGMEM = { 't', 'a', 'n', (char) 0xE9, '\0' };
        const char STR_SINH[]  PROGMEM = "sinh";
        const char STR_COSH[]  PROGMEM = "cosh";
        const char STR_TANH[]  PROGMEM = "tanh";
        const char STR_LOG[]   PROGMEM = "log";
        const char STR_LN[]    PROGMEM = "ln";
        const char STR_SQRT[]  PROGMEM = "sqrt";
        const char STR_EXP[]   PROGMEM = "exp";
        const char STR_ABS[]   PROGMEM = "Abs";
        const char STR_MIN[]   PROGMEM = "min";
        const char STR_MAX[]   PROGMEM = "max";
        const char STR_INT[]   PROGMEM = "int";
        const char STR_DX[]    PROGMEM = "dx";
        const char STR_SUM[]   PROGMEM = { (char) 0xF6, '\0' };

        enum Variable : uint8_t {
            X, Y, A, B, C, D, E, F
        };
    }

    const Token list[] PROGMEM = {
        {  0, Type::SPECIAL,  Assoc::LEFT,  0, 0, nullptr },
        {  0, Type::SPECIAL,  Assoc::LEFT,  0, sizeof(STR_COMMA), STR_COMMA },
        {  0, Type::SPECIAL,  Assoc::LEFT,  0, sizeof(STR_LPAR),  STR_LPAR  },
        {  0, Type::SPECIAL,  Assoc::LEFT,  0, sizeof(STR_RPAR),  STR_RPAR  },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_ZERO),  STR_ZERO  },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_ONE),   STR_ONE   },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_TWO),   STR_TWO   },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_THREE), STR_THREE },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_FOUR),  STR_FOUR  },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_FIVE),  STR_FIVE  },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_SIX),   STR_SIX   },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_SEVEN), STR_SEVEN },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_EIGHT), STR_EIGHT },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_NINE),  STR_NINE  },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_POINT), STR_POINT },
        {  0, Type::NUMERIC,  Assoc::LEFT,  0, sizeof(STR_SCI),   STR_SCI   },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_X),     STR_X     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_Y),     STR_Y     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_A),     STR_A     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_B),     STR_B     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_C),     STR_C     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_D),     STR_D     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_E),     STR_E     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_F),     STR_F     },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_ANS),   STR_ANS   },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_RND),   STR_RND   },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_EULER), STR_EULER },
        {  1, Type::SYMBOLIC, Assoc::RIGHT, 0, sizeof(STR_PI),    STR_PI    },
        {  2, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_OR),    STR_OR    },
        {  3, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_XOR),   STR_XOR   },
        {  4, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_AND),   STR_AND   },
        {  5, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_MINUS), STR_MINUS },
        {  5, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_PLUS),  STR_PLUS  },
        {  6, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_MOD),   STR_MOD   },
        {  6, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_MUL),   STR_MUL   },
        {  6, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_DIV),   STR_DIV   },
        {  7, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_COMBI), STR_COMBI },
        {  7, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_PERMU), STR_PERMU },
        {  8, Type::OPERATOR, Assoc::RIGHT, 2, sizeof(STR_POW),   STR_POW   },
        {  9, Type::OPERATOR, Assoc::RIGHT, 1, sizeof(STR_MINUS), STR_MINUS },
        {  9, Type::OPERATOR, Assoc::RIGHT, 1, sizeof(STR_PLUS),  STR_PLUS  },
        { 10, Type::OPERATOR, Assoc::LEFT,  2, sizeof(STR_ROOT),  STR_ROOT  },
        { 10, Type::OPERATOR, Assoc::RIGHT, 1, sizeof(STR_INV),   STR_INV   },
        { 10, Type::OPERATOR, Assoc::RIGHT, 1, sizeof(STR_FACTO), STR_FACTO },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_SIN),   STR_SIN   },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_COS),   STR_COS   },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_TAN),   STR_TAN   },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_ASIN),  STR_ASIN  },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_ACOS),  STR_ACOS  },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_ATAN),  STR_ATAN  },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_SINH),  STR_SINH  },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_COSH),  STR_COSH  },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_TANH),  STR_TANH  },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_LOG),   STR_LOG   },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_LN),    STR_LN    },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_SQRT),  STR_SQRT  },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_EXP),   STR_EXP   },
        { 12, Type::FUNCTION, Assoc::LEFT,  1, sizeof(STR_ABS),   STR_ABS   },
        { 12, Type::FUNCTION, Assoc::LEFT,  2, sizeof(STR_MIN),   STR_MIN   },
        { 12, Type::FUNCTION, Assoc::LEFT,  2, sizeof(STR_MAX),   STR_MAX   },
        { 12, Type::COMPOUND, Assoc::LEFT,  2, sizeof(STR_SUM),   STR_SUM   },
        { 12, Type::COMPOUND, Assoc::LEFT,  2, sizeof(STR_INT),   STR_INT   },
        { 12, Type::COMPOUND, Assoc::LEFT,  2, sizeof(STR_DX),    STR_DX    },
    };

    constexpr uint8_t NUMBER_FLAG = 0b10000000;
    constexpr uint8_t NUMBER_MASK = 0b01111111;

    double eval(uint8_t id) {
        switch (id) {
            case Name::VAR_X:
            case Name::VAR_Y:
            case Name::VAR_A:
            case Name::VAR_B:
            case Name::VAR_C:
            case Name::VAR_D:
            case Name::VAR_E:
            case Name::VAR_F:
                return vars[id - Name::VAR_X];
            case Name::ANS:
                return answer;
            case Name::RND:
                return fmod((double) Random::next() / Random::next(), 1);
            case Name::EULER:
                return M_E;
            case Name::PI:
                return M_PI;
            case Name::OR:
                return (uint8_t) args[0] | (uint8_t) args[1];
            case Name::XOR:
                return (uint8_t) args[0] ^ (uint8_t) args[1];
            case Name::AND:
                return (uint8_t) args[0] & (uint8_t) args[1];
            case Name::SUBTRACT:
                return args[0] - args[1];
            case Name::ADD:
                return args[0] + args[1];
            case Name::MODULO:
                return fmod(args[0], args[1]);
            case Name::MULTIPLY:
                return args[0] * args[1];
            case Name::DIVIDE:
                return args[0] / args[1];
            case Name::COMBINATION:
                // TODO
                return 0.0;
            case Name::PERMUTATION:
                // TODO
                return 0.0;
            case Name::POWER:
                return pow(args[0], args[1]);
            case Name::MINUS:
                return -args[0];
            case Name::PLUS:
                return +args[0];
            case Name::ROOT:
                return pow(args[1], 1.0 / args[0]);
            case Name::INVERT:
                return 1.0 / args[0];
            case Name::FACTORIAL:
                // TODO
                return 0.0;
            case Name::SINE:
                return sin(args[0]);
            case Name::COSINE:
                return cos(args[0]);
            case Name::TANGENT:
                return tan(args[0]);
            case Name::ARCSIN:
                return asin(args[0]);
            case Name::ARCCOS:
                return acos(args[0]);
            case Name::ARCTAN:
                return atan(args[0]);
            case Name::SINH:
                return sinh(args[0]);
            case Name::COSH:
                return cosh(args[0]);
            case Name::TANH:
                return tanh(args[0]);
            case Name::LOG10:
                return log10(args[0]);
            case Name::LN:
                return log(args[0]);
            case Name::SQRT:
                return sqrt(args[0]);
            case Name::EXPONENT:
                return exp(args[0]);
            case Name::ABS:
                return fabs(args[0]);
            case Name::MINIMUM:
                return args[0] < args[1] ? args[0] : args[1];
            case Name::MAXIMUM:
                return args[0] > args[1] ? args[0] : args[1];
            case Name::SUM: {
                args[5] = args[0];
                args[6] = args[1];
                double& from = args[5];
                double& to = args[6];
                double& result = args[7];
                double& x = vars[Variable::X];

                if (from > to) {
                    error = Error::INVALID_RANGE;
                    return INFINITY;
                }

                result = 0.0;
                x = round(from);

                do
                    result += ::evaluate(true);
                while (++x <= to);

                return result;
            }
            case Name::INTEGRAL:
                // TODO
                return 0.0;
            case Name::DERIVATIVE:
                // TODO
                return 0.0;
        }

        return INFINITY;
    }

    bool is_unary() {
        uint8_t last = idx == 0 ? (uint8_t) Name::STOP : input[idx - 1];
        return (raw == Name::ADD || raw == Name::SUBTRACT)
            && (last != Name::RIGHT_PARENT || last == Name::STOP)
            && !(last == Name::RIGHT_PARENT || list[last].type == Type::NUMERIC
                || list[last].type == Type::SYMBOLIC);
    }
    
    bool is_associative(uint8_t with) {
        return (list[raw].assoc == Assoc::LEFT  && list[raw].order <= list[with].order)
            || (list[raw].assoc == Assoc::RIGHT && list[raw].order <  list[with].order);
    }
}
}

double parse() {
    double& result = args[0] = 0.0;
    double& exp = args[1] = 0.0;
    double& power = args[2];
    uint8_t len = to - from;
    uint8_t i = from;

    for (; i < to && input[i] != Tokens::STOP && input[i] != Tokens::POINT && input[i] != Tokens::SCI; i++);
    uint8_t point_pos = i;

    for (; i < to && input[i] != Tokens::STOP && input[i] != Tokens::SCI; i++);
    uint8_t exp_pos = i;

    power = pow(10.0, point_pos - from);
    for (i = from; i < exp_pos; i++) {
        raw = input[i];
        if (raw == Tokens::POINT) {
            if (i == point_pos) {
                continue;
            } else {
                error = Error::SYNTAX;
                return INFINITY;
            }
        }

        power /= 10.0;
        result += power * (raw - Tokens::ZERO);
    }

    power = pow(10.0, len - exp_pos - 1 - from);
    for (i++; i < len; i++) {
        raw = input[i];
        if (raw == Tokens::POINT || raw == Tokens::SCI) {
            error = Error::SYNTAX;
            return INFINITY;
        }

        power /= 10.0;
        exp += power * (raw - Tokens::ZERO);
    }
    
    return result * pow(10.0, exp);
}

void to_reverse_polish_notation() {
    using Tokens::Type;
    const Tokens::Token* last = nullptr;

    uint8_t out = 0;
    uint8_t num = 0;
    bool nested = false;

    Stack::clear();
    for (idx = 0; (raw = input[idx]) != Tokens::STOP; idx++) {
        token = &Tokens::list[raw];

        if (token->type == Type::NUMERIC) {
            if (last != nullptr && last->type == Type::SYMBOLIC)
                Stack::push<uint8_t>(Tokens::MULTIPLY);

            from = idx;
            while ((raw = input[++idx]) != Tokens::STOP && 
                (token = &Tokens::list[raw])->type == Type::NUMERIC);
            to = idx--;
            token = &Tokens::list[input[idx]];

            output[out++] = Tokens::NUMBER_FLAG | num;
            numbers[num++] = parse();

            if (error != Error::NONE)
                return;
        } else if (token->type == Type::SYMBOLIC) {
            if (last != nullptr && (last->type == Type::SYMBOLIC || last->type == Type::NUMERIC))
                Stack::push<uint8_t>(Tokens::MULTIPLY);

            output[out++] = raw;
        } else if (token->type != Type::SPECIAL) {
            if (token->type == Type::COMPOUND) {
                if (nested) {
                    error = Error::NESTING_NOT_ALLOWED;
                    return;
                }

                nested = true;
                expr_from = out;
            }

            if (token->type != Type::FUNCTION && token->type != Type::COMPOUND) {
                if (!Tokens::is_unary()) {
                    while (Stack::size() != 0 && Stack::peek<uint8_t>() != Tokens::LEFT_PARENT 
                            && Tokens::is_associative(Stack::peek<uint8_t>()))
                        output[out++] = Stack::pop<uint8_t>();
                } else if (raw == Tokens::ADD) {
                    raw = Tokens::PLUS;
                } else if (raw == Tokens::SUBTRACT) {
                    raw = Tokens::MINUS;
                }
            } else if (input[idx + 1] != Tokens::LEFT_PARENT) {
                error = Error::MISMATCHED_PARENTHESES;
                return;
            } else if (last != nullptr && (last->type == Type::SYMBOLIC 
                    || last->type == Type::NUMERIC)) {
                Stack::push<uint8_t>(Tokens::MULTIPLY);
            }

            Stack::push<uint8_t>(raw);
        } else if (raw == Tokens::COMMA) {
            while (Stack::size() != 0 && Stack::peek<uint8_t>() != Tokens::LEFT_PARENT)
                output[out++] = Stack::pop<uint8_t>();

            if (Stack::size() == 0) {
                error = Error::MISMATCHED_PARENTHESES;
                return;
            }

            if (nested) {
                nested = false;
                expr_to = out;
            }
        } else if (raw == Tokens::LEFT_PARENT) {
            if (last != nullptr && (last->type == Type::NUMERIC || last->type == Type::SYMBOLIC))
                Stack::push<uint8_t>(Tokens::MULTIPLY);

            Stack::push<uint8_t>(raw);
        } else if (raw == Tokens::RIGHT_PARENT) {
            while (Stack::size() != 0 && Stack::peek<uint8_t>() != Tokens::LEFT_PARENT)
                output[out++] = Stack::pop<uint8_t>();

            if (Stack::size() != 0 && Stack::peek<uint8_t>() == Tokens::LEFT_PARENT) {
                Stack::pop<uint8_t>();
            } else {
                error = Error::MISMATCHED_PARENTHESES;
                return;
            }
        } else {
            error = Error::UNKNOWN;
            return;
        }

        if (out >= ARRAY_SIZE(output) || num >= ARRAY_SIZE(numbers)) {
            error = Error::OUT_OF_MEMORY;
            return;
        }

        last = token;
    }

    while (Stack::size() != 0) {
        if (Stack::peek<uint8_t>() == Tokens::LEFT_PARENT) {
            Stack::pop<uint8_t>();
            continue;
        }

        output[out++] = Stack::pop<uint8_t>();
    }

    output[out] = Tokens::STOP;
}

double evaluate(bool expr = false) {
    if (!expr)
        Stack::clear();

    for (idx = expr ? expr_from : 0; raw = output[idx], 
            expr ? idx < expr_to : raw != Tokens::STOP; idx++) {
        if (raw & Tokens::NUMBER_FLAG) {
            Stack::push(numbers[raw & Tokens::NUMBER_MASK]);
        } else {
            token = &Tokens::list[raw];

            if (!expr && idx == expr_from && expr_from != expr_to) {
                idx = expr_to - 1;
                continue;
            }

            for (int8_t i = token->args - 1; i >= 0; i--) {
                if (Stack::size() == 0) {
                    error = Error::MISMATCHED_OPERATOR;
                    return INFINITY;
                }

                args[i] = Stack::pop<double>();
            }
            
            if (!expr)
                from = idx;

            Stack::push(Tokens::eval(raw));
            if (error != Error::NONE)
                return INFINITY;

            if (!expr)
                idx = from;
        }
    }

    if (!expr) {
        if (Stack::size() > 1) {
            error = Error::MISMATCHED_OPERATOR;
            return INFINITY;
        }

        answer = Stack::peek<double>();
    }

    return Stack::pop<double>();
}

Tokens::Token Calculator::get(uint8_t id) {
    return Loader::get(&Tokens::list[id]);
}

const char* Calculator::test() {
    return Tokens::STR_SIN;
}

void Calculator::set(uint8_t id, uint8_t pos) {
    input[pos] = id;
}

double Calculator::evaluate() {
    return ::evaluate(false);
}

