/************************************************
 *           T O N Y ' S  S T U D I O           *
 * -------------------------------------------- *
 * Project Name: Discrete Math Calculator       *
 *     Filename: logic.js                       *
 *   Programmer: Tony Skywalker                 *
 *   Start Date: April 3, 2022                  *
 *  Last Update:                                *
 * -------------------------------------------- *
 * Overview:                                    *
 *   Hmm... Just simplify the torturing process *
 *   of logic calculation.                      *
 ************************************************/

// Symbol constants.
var OP_NOT = 0;
var OP_AND = 1;
var OP_OR = 2;
var OP_XOR = 3;
var OP_IMP = 4;
var OP_EQU = 5;
var OP_RIM = 6;
var OP_LBR = 7;
var OP_RBR = 8;
var OP_NUM = 9;

var VAR_P = 0;
var VAR_Q = 1;
var VAR_R = 2;
var VAR_S = 3;
var VAR_NUM = 4;

var CON_0 = 0;
var CON_1 = 1;
var CON_NUM = 2;

var TYPE_OP = 0;
var TYPE_VAR = 1;
var TYPE_CON = 2;

// The smaller the number is, the higher the priority is.
var PRIORITY = { '¬': 0, '∧': 1, '∨': 2, '⊕': 3, '→': 4, '↔': 5, '←': 4, '(': -1, ')': -1 };
var OPERATOR = ['¬', '∧', '∨', '⊕', '→', '↔', '←', '(', ')'];
var VARIABLE = ['p', 'q', 'r', 's'];
var CON_LIST = ['0', '1'];

var ERR_EMPTY_STACK = "Empty Stack!"
var ERR_BRACKET = "Bracket Mismatch!";
var ERR_INVALID = "Invalid Input!";
var ERR_NOTHING = "There appears to be nothing."

// The user's input.
var input = document.getElementById("input").getElementsByTagName("p")[0];

// The result sections.
var BOX_EMPTY = 0;
var BOX_ERROR = 1;
var BOX_RESULT = 2;
var boxList = [];

// The specific results.
var polishResult = document.getElementById("polish").getElementsByTagName("p")[0];
var disjResult = document.getElementById("disj").getElementsByTagName("p")[0];
var conjResult = document.getElementById("conj").getElementsByTagName("p")[0];
var truthResult = document.getElementById("truth").getElementsByTagName("table")[0];


/////////////////////////////////////////////////////////////////////
// Initialize properties.
/////////////////////////////////////////////////////////////////////

// Initialize the buttons.
function initButton() {
    var button;

    // Initialize operators.
    for (var i = 0; i < 9; i++) {
        (function(_i) {
            var id = "op-" + _i;
            button = document.getElementById(id);
            button.onclick = function() {
                appendSymbol(OPERATOR[_i]);
            };
        })(i);
    }

    // Initialize variables.
    for (var i = 0; i < VAR_NUM; i++) {
        (function(_i) {
            var id = "var-" + _i;
            button = document.getElementById(id);
            button.onclick = function() {
                appendSymbol(VARIABLE[_i]);
            };
        })(i);
    }

    // Initialize constants.
    for (var i = 0; i < 2; i++) {
        (function(_i) {
            var id = "con-" + _i;
            button = document.getElementById(id);
            button.onclick = function() {
                appendSymbol(CON_LIST[_i]);
            }
        })(i);
    }

    // Initialize commands.
    button = document.getElementById("cmd-reset");
    button.onclick = function() {
        resetInput();
    };

    button = document.getElementById("cmd-delete");
    button.onclick = function() {
        deleteSymbol();
    }

    button = document.getElementById("cmd-confirm");
    button.onclick = function() {
        process();
    }
}

// Initialize the result boxes.
function initBox() {
    box = document.getElementById("empty");
    box.style.display = "block";
    boxList.push(box);
    box = document.getElementById("error");
    box.style.display = "none";
    boxList.push(box);
    box = document.getElementById("result");
    box.style.display = "none";
    boxList.push(box);
}

/////////////////////////////////////////////////////////////////////
// Input related functions.
/////////////////////////////////////////////////////////////////////

// Append one symbol to the end of the input.
function appendSymbol(symbol) {
    // console.log(symbol + " appended");
    input.innerText += symbol;
}

// Delete the last symbol in the input.
function deleteSymbol() {
    if (input.innerText == "") {
        // console.log("Input is empty.")
    } else {
        var str = input.innerText;
        input.innerText = str.substring(0, str.length - 1);
        if (input.length == 0) {
            changeBox(BOX_EMPTY);
        }
        // console.log(str[str.length - 1] + " deleted");
    }
}

// Clear the input.
function resetInput() {
    input.innerText = "";
    changeBox(BOX_EMPTY);
    // console.log("Input cleared.");
}

/////////////////////////////////////////////////////////////////////
// Miscellaneous functions.
/////////////////////////////////////////////////////////////////////

// Set the error info.
function setError(err) {
    boxList[BOX_ERROR].innerHTML = '<h3>' + err + '</h3>';
}

// Change the result box.
function changeBox(id) {
    for (var i = 0; i < 3; i++) {
        if (i == id) {
            boxList[i].style.display = "block";
        } else {
            boxList[i].style.display = "none";
        }
    }
}


/////////////////////////////////////////////////////////////////////
// Core functions.
/////////////////////////////////////////////////////////////////////

// A custom stack.
class Stack {
    constructor() {
        this.value = [];
        this.size = 0;
    }

    push(val) {
        this.value.push(val);
        this.size++;
    }

    top() {
        if (this.size == 0) {
            throw ERR_EMPTY_STACK;
        } else {
            return this.value[this.size - 1];
        }
    }

    pop() {
        if (this.size == 0) {
            throw ERR_EMPTY_STACK;
        } else {
            this.value.pop();
            this.size--;
        }
    }

    empty() {
        return (this.size == 0);
    }

    getSize() {
        return this.size;
    }

    getString() {
        var str = "";

        while (!this.empty()) {
            str += this.top();
            this.pop();
        }

        return str;
    }
}

// Truth table
class TruthTable {
    // pqrv
    // 0000
    // 0010
    // 0101
    // ....
    constructor() {
        // how many varibles
        this.size = 0;
        // how many rows
        this.length = 0;
        // the variable list
        this.varList = "";
        // the value list
        this.valueList = [];
    }

    init(variables) {
        this.varList = variables;
        this.size = this.varList.length;
    }

    append(value) {
        this.valueList.push(value);
        this.length++;
    }
}

// Get the type of the symbol.
function getType(symbol) {
    for (var i = 0; i < CON_NUM; i++) {
        if (symbol == CON_LIST[i]) {
            return TYPE_CON;
        }
    }

    for (var i = 0; i < VAR_NUM; i++) {
        if (symbol == VARIABLE[i]) {
            return TYPE_VAR;
        }
    }

    return TYPE_OP;
}

// Convert infix expression to prefix expression
function infixToPrefix(expr) {
    var resultStack = new Stack();
    var opStack = new Stack();

    for (var i = expr.length - 1; i >= 0; i--) {
        var sym = expr[i];

        // if (sym == OPERATOR[OP_NOT]) {
        //     if (resultStack.empty()) {
        //         throw ERR_INVALID;
        //     }
        // }

        if (getType(sym) != TYPE_OP) {
            resultStack.push(sym);
        } else if (sym == OPERATOR[OP_LBR]) {
            while (true) {
                try {
                    var top = opStack.top();
                    opStack.pop();
                    if (top == OPERATOR[OP_RBR]) {
                        break;
                    } else {
                        resultStack.push(top);
                    }
                } catch (err) {
                    throw ERR_BRACKET;
                }
            }
        } else if (sym == OPERATOR[OP_RBR]) {
            opStack.push(sym);
        } else if (opStack.empty()) {
            opStack.push(sym);
        } else {
            while (true) {
                if (opStack.empty()) {
                    opStack.push(sym);
                    break;
                } else {
                    var top = opStack.top();
                    if (top == OPERATOR[OP_RBR]) {
                        opStack.push(sym);
                        break;
                    } else {
                        if (PRIORITY[sym] <= PRIORITY[top]) {
                            opStack.push(sym);
                            break;
                        } else {
                            opStack.pop();
                            resultStack.push(top);
                        }
                    }
                }

            }
        }
    }

    while (!opStack.empty()) {
        var top = opStack.top();
        // Here, there's no possibility that a ) exists.
        if (top == OPERATOR[OP_RBR]) {
            throw ERR_BRACKET;
        }
        resultStack.push(opStack.top());
        opStack.pop();
    }

    return resultStack.getString();
}

// Apply the calculation of a binary operator.
function _binaryCalc(p, q, op) {
    var rv;

    p = parseInt(p);
    q = parseInt(q);
    switch (op) {
        case OPERATOR[OP_AND]:
            rv = p & q;
            break;
        case OPERATOR[OP_OR]:
            rv = p | q;
            break;
        case OPERATOR[OP_XOR]:
            rv = p ^ q;
            break;
        case OPERATOR[OP_IMP]:
            rv = (!p) | q;
            break;
        case OPERATOR[OP_RIM]:
            rv = (!q) | p;
            break;
        case OPERATOR[OP_EQU]:
            rv = (p == q) ? 1 : 0;
            break;
        default:
            rv = 0;
            break;
    }

    return String(rv);
}

// Apply the calculation of a unary operator.
function _unaryCalc(p, op) {
    var rv;

    p = parseInt(p);
    switch (op) {
        case OPERATOR[OP_NOT]:
            rv = (p == 1) ? 0 : 1;
            break;
        default:
            rv = 0;
            break;
    }
    return String(rv);
}

// Calculate a expression with given value.
function calculate(expr) {
    var stack = new Stack();
    var left, right;

    console.log("Calc: " + expr);
    for (var i = expr.length - 1; i >= 0; i--) {
        var sym = expr[i];

        if (getType(sym) == TYPE_CON) {
            stack.push(sym);
        } else {
            if (sym == OPERATOR[OP_NOT]) {
                try {
                    right = stack.top();
                    stack.pop();
                    stack.push(_unaryCalc(right, sym));
                } catch (err) {
                    throw ERR_INVALID;
                }
            } else {
                try {
                    left = stack.top();
                    stack.pop();
                    right = stack.top();
                    stack.pop();
                    stack.push(_binaryCalc(left, right, sym));
                } catch (err) {
                    throw ERR_INVALID;
                }
            }
        }
    }

    if (stack.getSize() != 1) {
        throw ERR_INVALID;
    }

    return stack.top();
}

// Find certain value in a list.
function _find(list, value) {
    for (var item in list) {
        console.log(list[item] + " + " + value);
        if (list[item] == value) {
            return true;
        }
    }

    return false;
}

// Replace viriables with assignments.
function _replace(expr, map) {
    for (var key in map) {
        var temp = expr.replace(key, map[key]);
        while (expr != temp) {
            expr = temp;
            temp = expr.replace(key, map[key]);
        }
    }

    return expr;
}

// Reverse a string.
function _reverse(str) {
    return str.split('').reverse().join('')
}
// Get the truth table based on the polish notation.
function getTruthTable(expr) {
    var html = "";

    // Generate variable list.
    var varList = [];
    var truthTable = new TruthTable();

    for (var i = 0; i < expr.length; i++) {
        if (getType(expr[i]) != TYPE_VAR) {
            continue;
        }
        if (!_find(varList, expr[i])) {
            varList.push(expr[i]);
        }
    }
    console.log("varList: " + varList);

    varList = varList.sort();
    truthTable.init(varList.join(''));

    // No viriables.
    if (varList.length == 0) {
        try {
            truthTable.append(calculate(expr));
        } catch (err) {
            throw err;
        }
        html = '<tr><th>Value</th></tr><tr><td>' + truthTable.valueList[0] + '</td></tr>'
    } else {
        // has virables.
        var upper = 1 << varList.length;
        var map = {};
        var constExpr = "";
        var value = "";
        var assignment = "";
        for (var n = 0; n < upper; n++) {
            assignment = _reverse(n.toString(2));
            while (assignment.length < varList.length) {
                assignment += '0';
            }

            for (var i = 0; i < varList.length; i++) {
                map[varList[i]] = assignment[i];
            }
            constExpr = _replace(expr, map);

            try {
                value = assignment + calculate(constExpr);
                truthTable.append(value);
            } catch (err) {
                throw err;
            }
        }

        var valueList = truthTable.valueList;
        html += '<tr>';
        for (var i = 0; i < varList.length; i++) {
            html += '<th>' + varList[i] + '</th>'
        }
        html += '<th>Value</th>';
        html += '</tr>'
        for (var i = 0; i < truthTable.length; i++) {
            html += '<tr>';
            for (var j = 0; j < valueList[i].length; j++) {
                html += '<td>' + valueList[i][j] + '</td>';
            }
            html += '</tr>'
        }
    }

    truthResult.innerHTML = html;
    changeBox(BOX_RESULT);

    return truthTable;
}

// Get the principle disjunctive normal form from the truth table.
function getDisjunctiveNormalForm(table) {
    if (table.size == 0) {
        disjResult.innerText = "No Propositional Variable";
        return;
    }

    var form = "";
    for (var i = 0; i < table.length; i++) {
        if (table.valueList[i][table.size] == '0') {
            continue;
        }

        if (form != "") {
            form += " " + OPERATOR[OP_OR] + " ";
        }

        form += OPERATOR[OP_LBR];
        for (var j = 0; j < table.size; j++) {
            if (j != 0) {
                form += OPERATOR[OP_AND];
            }
            if (table.valueList[i][j] == '0') {
                form += OPERATOR[OP_NOT];
            }
            form += table.varList[j];
        }
        form += OPERATOR[OP_RBR]
    }

    if (form == "") {
        form = 'Contradictory Formula';
    }
    disjResult.innerText = form;
}

// Get the principle conjunctive normal form from the truth table.
function getConjunctiveNormalForm(table) {
    if (table.size == 0) {
        conjResult.innerText = "No Propositional Variable";
        return;
    }

    var form = "";
    for (var i = 0; i < table.length; i++) {
        if (table.valueList[i][table.size] == '1') {
            continue;
        }

        if (form != "") {
            form += " " + OPERATOR[OP_AND] + " ";
        }

        form += OPERATOR[OP_LBR];
        for (var j = 0; j < table.size; j++) {
            if (j != 0) {
                form += OPERATOR[OP_OR];
            }
            if (table.valueList[i][j] == '1') {
                form += OPERATOR[OP_NOT];
            }
            form += table.varList[j];
        }
        form += OPERATOR[OP_RBR]
    }

    if (form == "") {
        form = 'Tautology';
    }
    conjResult.innerText = form;
}


// Process all calculations.
function process() {
    var expr = input.innerText;

    if (expr == "") {
        return;
    }

    // Polish Notation.
    var polishExpr;
    try {
        polishExpr = infixToPrefix(expr);
        // console.log("Polish: " + polishExpr);
    } catch (err) {
        console.log(err);
        setError(err);
        changeBox(BOX_ERROR);
        return;
    }
    if (polishExpr == "") {
        setError(ERR_NOTHING);
        changeBox(BOX_ERROR)
        return;
    }

    polishResult.innerText = polishExpr;

    // Get truth table
    var truthTable;
    try {
        truthTable = getTruthTable(polishExpr);
    } catch (err) {
        setError(err);
        changeBox(BOX_ERROR);
        return;
    }

    getDisjunctiveNormalForm(truthTable);
    getConjunctiveNormalForm(truthTable);

    // Principal disjunctive normal form
    changeBox(BOX_RESULT);
}

/////////////////////////////////////////////////////////////////////
// Actions!
/////////////////////////////////////////////////////////////////////
initButton();
initBox();