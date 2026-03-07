#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
//#include <bits/stdc++.h>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

struct Equ {
    map<string, float> coef; // x1 is the key and coefficient is the float value
    float consta = 0; // for example equation 1 = 19; 19 is the constant 
};


string fToStr(float x) {
    if (fabs(x - round(x)/*nearest integer*/) < 1e-6) {  // is x close to integer like 3.0000001 >>> then turn it to 3
        // 3.00001 - 3 = 0.0000001 then convert to nearst integer
        return to_string((int)round(x));  // turn it to nearest integer
    }
    ostringstream ss;
    /*
        ostringstream is used because it provides a safe, flexible way to convert the "clean integer"
        (which might actually be a double that's very close to an integer) to a string
        without trailing .000000 artifacts.
    */
    ss << x; // store the clean integer to string
    return ss.str(); // str() = converts the stringstream to a std::string
    /*
        Why not just use to_string()?
            Modern C++ usually uses:
                string s = to_string(x);
            But stringstream is used when:
                combining multiple things
                formatting numbers
                                        Example:
                                        int x = 3;
                                        int y = 5;
                                        stringstream ss;
                                        ss << x << "x1 + " << y << "x2";
                                        cout << ss.str();
                                        Output: 3x1 + 5x2
    */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

string equToStr(const Equ& e) {    // to print the equation
    string res;
    bool first = true;

    for (auto& it : e.coef) {  // (it) is the keys : loop on vector, map, array, etc.
        float c = it.second;                    // second means the float value and first means the key
        if (fabs(c) < 1e-6) continue;  // if coefficient == 0 then skip this cuz anything multiple with 0 = 0

        if (!first && c > 0) res += "+"; // not the first coefficient in the equation then put + in the string and go next

        if (fabs(c) != 1) // if coefficient != 1 then get the number cuz 1 can be empty in coefficient
            res += fToStr(c);
        else if (c == -1)
            res += "-";

        res += it.first; // after add the coefficient then add the key for example x1
        first = false; // now we took first coefficient and the key then go next and add + / -
    }

    if (res.empty()) res = "0";  // no equation
    res += "=" + fToStr(e.consta); // no equation = constant
    return res;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

/*
    input for example
    1
    6-6+3.2x5-5.2y2-*&(&44x3-[[5+]10-2x4-]]10-5+2=10+3x2
    equation 1
*/

Equ parseEquation(string s) {  // token
    Equ e;

    s.erase(remove(s.begin(), s.end(), ' '), s.end()); // remove the spaces in the equation string

    float sign_helper = 1; // store the true sign cuz maybe there is wrong inputs and will destroy my base sign
    int eqPos = s.find('=');  // finds the index of (=)
    string L = s.substr(0, eqPos); // take part of the string from 0 index to (=) index but dont include (=)
    string R = s.substr(eqPos + 1); // everything starting after (=) index thats why we wrote +1
    e.consta = 0; // convert constant to float from string (s to f)
    string LL;

    for (int i = 0; i < (int)L.size(); i++) {                                               //---|
        if (isalnum(L[i]) || L[i] == '+' || L[i] == '-' || L[i] == '=' || L[i] == '.') {    //---|
            string str(1, L[i]); LL.append(str);                                            //---|-----> clear the Left String from any symbols
        }                                                                                   //---|
    }

    if (R[0] == '-') LL.append("+");
    else { LL.append("-"); }

    for (int i = 0; i < (int)R.size(); i++) {                                               //---|
        if (!isalnum(R[i])) {                                                               //---|
            if (R[i] != '+' && R[i] != '-' && R[i] != '=' && R[i] != '.');                  //---|
            else {                                                                          //---|clear the Right String from any symbols and move Left
                string str(1, R[i]); LL.append(str == "+" ? "-" : str == "-" ? "+" : str);  //---|
            }                                                                               //---|
        }                                                                                   //---|
        else { string str(1, R[i]); LL.append(str); }                                       //---|
    }

    L = LL;

    for (int i = 0; i < (int)L.size();) {               // --
        int sign = 1 * sign_helper;                     //   |
        sign_helper = 1;                                //   |
        if (L[i] == '+') i++;                           //   |--> get the sign of the token
        else if (L[i] == '-') {                         //   |
            sign = -1;                                  //   |
            i++;                                        //   |
        }                                               // --

        bool ignore = false;
        if (!isalnum(L[i])) {                                   // --
            if (L[i] != '+' && L[i] != '-' && L[i] != '=') {    //   | 
                ignore = true;                                  //   |
                L[i] = '0';  sign_helper = sign;                //   | ----> ignore any sympole that not (a-z) or (0-9) or (+,-,=)
            }                                                   //   |
        }                                                       // --

        int start = i; string as = "0";
        float coef = 0;  // this var to store the coef
        bool coefficientFound = false;  // flag to check if we found coef
        while (i < (int)L.size() && (isdigit(L[i]) || L[i] == '.')) { // search for numbers and . for float numbers
            coefficientFound = true;    // then we found something like 3.5x1 = in the loop 3 . 5 >> 3 loops

            string str(1, L[i]);        //--------  add the number to string for example 3 . 5 = 3.5
            as += str;                  //--------

            i++; // increase i inside the while loop
            if (i < (int)L.size() && (isdigit(L[i]) || L[i] == '.'));
            else {
                coef = stof(as);
            }
        }
        //cout << endl << coef << endl;
        if (!coefficientFound) coef = 1; // 1 if no coef
        coef *= sign; // add the sign to coef >>>>>  -3x1 = 3 * -1 = -3
        // --

        if (isalpha(L[i])) L[i] = 'x'; // replace any (a-z) to x

        if (i < (int)L.size() && L[i] == 'x') {   // Is this a variable term or a constant term? /If next character is 'x' ? variable/Otherwise ? constant  
            string var;     // to store var name for example x12
            while (i < (int)L.size() && (isalnum(L[i]) || L[i] == 'x')) {   // isalnum >> Checks letter or digit (a-z, A-Z, 0-9) Library: <cctype>
                // isalnum('+') ? false/isalnum('-') ? false ==== break the loop
                var += L[i++]; // loop to read the full name x 1 2 = x12
            }

            e.coef[var] += coef * sign_helper; // store the var name as key and its coef in its value in the map var
        }
        else {
            if (!ignore) {
                //cout << endl << coef << endl;
                e.consta -= coef; // its a constant without x then - the main constant the Right Equation
            }
        }
    }

    return e;
}

/* ---------- Matrix Operations ---------- */

/*
    Libraries Used
    #include <vector>   // vector
    #include <cmath>    // fabs
    #include <algorithm> // swap
*/

float dt(vector<vector<float>> a) { /* it takes the equations as matrix like a[0] = {2, 3, 4} without the x vars
                                                                                      a[1] = {1, 2, 1}
                                                                                      a[2] = {3, 1, 2} */

                                                                                      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                      //////////////////////////////////////////// get the delta of this matrix ////////////////////////////////////////////
                                                                                      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                                      /*
                                                                                      why determinant
                                                                                          the first reason we calculate it is to check solvability.

                                                                                      So determinant is calculated for two purposes
                                                                                          det(A) ? check if system has a unique solution
                                                                                          det(Ai) ? calculate variable values using Cramer’s Rule

                                                                                      What happens if det(A) = 0?
                                                                                          System cannot be solved uniquely
                                                                                          Program prints "No Solution"        x1 = determinant(A1) / determinant(A)
                                                                                      */

    int n = a.size(); // matrix size
    float det = 1;

    for (int i = 0; i < n; i++) {   // Loop over columns
        int piv = i;   // we are in the first column lets check rows of this column
        for (int j = i; j < n; j++) // Loop over rows
            if (fabs(a[j][i]) > fabs(a[piv][i]))  // in the one column which is the largest absolute in the rows of this column
                piv = j;                          // then give me the index of the row so the winner in our matrix is [(3) up up up]

        if (fabs(a[piv][i]) < 1e-6) return 0; // its less than 0.00001

        if (piv != i) {
            swap(a[piv], a[i]); /* a[0] = {3, 3, 4} we swaped for example 3 with 2 in the first column
                                     a[1] = {1, 2, 1}
                                     a[2] = {2, 1, 2} */
            det *= -1; // Row swap flips determinant sign
        }

        det *= a[i][i]; // det = -1 × 3 = -3
        float div = a[i][i]; // store 3 in dive
        /*
            now     det = -3
                    div = 3
                    a[i][i] = 3
        */

        for (int j = i; j < n; j++)
            a[i][j] /= div; // Normalize row 0: | 1  0.33  0.67 |

        for (int j = i + 1; j < n; j++) {
            float factor = a[j][i];
            for (int k = i; k < n; k++)
                a[j][k] -= factor * a[i][k]; // [1 2 1] ? factor × [1 0.33 0.67] ? [0 1.67 0.33]
        }
    }
    return det;
}





/////////////////////////////////////////////////////////////////////////////////
                        /* ---------- Main ---------- */
/////////////////////////////////////////////////////////////////////////////////

int main() {
    int n; // declare variable to store number of equations
    cin >> n; // read number of equations from input
    cin.ignore(); // ignore the remaining newline character after reading n
    vector<Equ> eq(n); // create a vector to store n Equation objects
    set<string> variables; // set to store unique variable names (x1, x2, x3, ...)
    /*
        example on set:
            variables.insert("apple");
            variables.insert("banana");
            variables.insert("cherry");
            variables.insert("apple"); // duplicate - won't be added
            variables = {"apple", "banana", "cherry"}

    /*
        we use set to fix the diplication for example:
        3x1 + 2x2 = 25
        5x1 - 4x2 = 20

        When extracting variables:

        x1
        x2
        x1
        x2
    */

    for (int i = 0; i < n; i++) { // loop to read each equation
        string s; // string to hold the equation line
        getline(cin, s); // read the full equation line (including +, -, =)
        eq[i] = parseEquation(s); // parse the equation string into coefficients and constant
        for (auto& p : eq[i].coef) // loop over each variable-coefficient pair in the equation
            variables.insert(p.first); // insert variable name into the set (duplicates auto removed)
    }


    vector<string> varList(variables.begin(), variables.end()); // convert set of variables into a vector (ordered list of variables)
    string cmd; // string to store command entered by user

    while (cin/*reads words*/ >> cmd) { // keep reading commands until input ends

        if (cmd == "quit") break; // if command is "quit", stop the program
        if (cmd == "num_vars") {  // command to print number of variables
            cout << varList.size() << endl; // print count of unique variables
        }
        else if (cmd == "equation") { // command to print a specific equation
            int i; // equation index
            cin >> i; // read equation number
            cout << equToStr(eq[i - 1]) << endl; // print equation in proper form (1-based index)
        }

        else if (cmd == "column") {
            // command to print coefficient column of a variable

            string v;
            // variable name (e.g., x2)

            cin >> v;
            // read variable name

            for (int i = 0; i < n; i++) {
                // loop through equations

                if (eq[i].coef.count(v))
                    // if variable exists in equation

                    cout << fToStr(eq[i].coef[v]) << endl;
                // print its coefficient

                else
                    cout << "0" << endl;
                // otherwise print 0
            }
        }


        else if (cmd == "add" || cmd == "subtract") {
            // add or subtract two equations

            int a, b;
            // indices of equations

            cin >> a >> b;
            // read equation numbers

            Equ r;
            // result equation

            for (auto& v : varList) {
                // loop over all variables

                float x = eq[a - 1].coef[v];
                // coefficient of variable in equation a

                float y = eq[b - 1].coef[v];
                // coefficient of variable in equation b

                r.coef[v] = (cmd == "add") ? x + y : x - y;
                // add or subtract coefficients
            }

            r.consta = (cmd == "add")
                ? eq[a - 1].consta + eq[b - 1].consta
                : eq[a - 1].consta - eq[b - 1].consta;
            // add or subtract constants

            cout << equToStr(r) << endl;
            // print result equation
        }


        else if (cmd == "substitute") {
            // substitute variable from one equation into another

            string v; // variable to eliminate
            int a, b; // equation indices
            cin >> v >> a >> b; // read variable and equation numbers
            Equ r = eq[a - 1]; // start with equation a
            float c = eq[a - 1].coef[v]; // coefficient of variable v in equation a
            if (fabs(c) > 1e-6) { // if coefficient is not zero
                r.coef.erase(v); // remove variable v from result equation

                for (auto& p : eq[b - 1].coef) {
                    // loop through equation b coefficients

                    if (p.first != v)
                        // skip the substituted variable

                        r.coef[p.first] -= c * p.second / eq[b - 1].coef.at(v);
                    // substitute variable using equation b
                }

                r.consta -= c * eq[b - 1].consta / eq[b - 1].coef.at(v);
                // update constant term
            }

            cout << equToStr(r) << endl;
            // print substituted equation
        }


        else if (cmd == "D" || cmd == "D_value" || cmd == "solve") { // determinant-related commands

            int m = varList.size(); // number of variables
            vector<vector<float>> A(m, vector<float>(m)); // coefficient matrix
            /*
                // 2 rows, 5 columns
                vector<vector<float>> C(2, vector<float>(5));
                /*
                C = [
                      [0, 0, 0, 0, 0],  // row 0 (5 columns)
                      [0, 0, 0, 0, 0]   // row 1 (5 columns)
                    ]
            */
            vector<float> B(m); // constant column

            for (int i = 0; i < m; i++) { // build matrix from equations
                B[i] = eq[i].consta; // store constant values
                for (int j = 0; j < m; j++)
                    A[i][j] = eq[i].coef[varList[j]]; // store coefficients
            }


            if (cmd == "D") { // print coefficient matrix

                if (cin.peek() == '\n') {
                    // user typed: D

                    for (int i = 0; i < m; i++) {
                        for (int j = 0; j < m; j++) {
                            if (j) cout << " ";
                            cout << fToStr(A[i][j]);
                        }
                        cout << endl;
                    }
                }
                else {
                    // user typed: D x1

                    //////////////////////////////////////////////////////////////////////////
                    //                    replace x1 column with constants                  //
                    //////////////////////////////////////////////////////////////////////////

                    string v;
                    cin >> v;

                    int col = find(varList.begin(), varList.end(), v)/*find position*/ - varList.begin();

                    for (int i = 0; i < m; i++) {
                        for (int j = 0; j < m; j++) {

                            float val = (j == col) ? B[i] : A[i][j];

                            if (j) cout << " ";

                            cout << fToStr(val);
                        }
                        cout << endl;
                    }
                }
            }


            else if (cmd == "D_value") { // print determinant value
                cout << fToStr(dt(A)) << endl;
            }

            //////////////////////////////////////////////////////////////////////////
            //                           input = solve                              //
            //////////////////////////////////////////////////////////////////////////
                    //                                                               -
            else { // solve equations using Cramer's rule                            -
                float D = dt(A); // main determinant                                 -
                                            //                                       -
                if (fabs(D) < 1e-6) { // determinant is zero                         -
                    cout << "No Solution" << endl; //                                -
                }                                   //                               -
                else {      //                                                       -
                    for (int i = 0; i < m; i++) { //                                 -
                        // calculate each variable                                   -
                            //                                                       -
                        vector<vector<float>> Ai = A; //                             -
                        // copy matrix                                               -
                        //                                                           -
                        for (int j = 0; j < m; j++) //                               -
                            Ai[j][i] = B[j]; //                                      -
                        // replace column i with constants                           -
                        //                                                           -
                        float Di = dt(Ai);//                                         -
                        // determinant for variable i                                -
                        //                                                           -
                        cout << varList[i] << "=" //                                 -
                            << fToStr(Di / D) << endl;//                             -
                        // print solution                                            -
                    } //                                                             -
                } //                                                                 -
            } //                                                                     -
            //------------------------------------------------------------------------
        }
        
    }

    return 0;
}
