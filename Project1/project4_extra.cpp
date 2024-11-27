// Project 4
// Fall 2022
// Sujata Sahu

#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list

using namespace std;

class GL; // prototype for class GL

// node class to store char and generalized linked list called down
class node
{
protected:
    char *charVariable; // single char variable pointer (not an array)
    GL *down;           // going down to the next level

public:
    node(); // default constructor

    // setters
    void setCharVariable(char var);
    void setDown(GL *d);

    // getters
    char *getChar();
    GL *getDown();

    // display
    void displayChar();
};

node::node(){

}
void node::setCharVariable(char var){
    charVariable = new char(var);
}
void node::setDown(GL *d){
    down = d;
}

char *node::getChar(){
    return charVariable;
}

GL *node::getDown(){
    return down;
}
void node::displayChar(){
    cout << *charVariable;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// class Generalized List
class GL
{
protected:
    list<node> head; // head of the list - each object is of type node class

public:
    GL();                                         // default constructor
    void buildGL(string l);                       // to build the generalized list
    bool findCharInExpression(char findThisChar); // given a char, find it in a given expression
    int LCAdistance(char char1, char char2);      // find the LCA distance of two char in the expression
    int heightOfGL();                             // return the height of the GL using the GL
    void searchDuplicates();                      // print all the duplicates in the GL
    void display();                               // display list

    int generateLevels(GL *level, string expression, int expressionPosition); //generate levels of expressions
    string generateExpression(bool addParanthesis); //generate expression in string from GL
    int getDistance(string path, int intersectionPoint); //gives LCA distance 
    string getCharPath(char c); //gives leven of character in an expression
};

//Default Constructor
GL::GL(){

}
// to build the generalized list
void GL::buildGL(string l){
    int expressionSize, expressionPosition = 0; //length(num of characters in expression) & current position in iteration
    string expression = l.substr(1, l.size()-2); //remove first and last paranthesis from string
    expressionSize = expression.size();
    while (expressionPosition < expressionSize)
    {
        char currentCharacter = expression[expressionPosition]; //assign currenct character
        if(currentCharacter == '('){ //this indicates new level in expression
            GL *nextLevel = new GL(); //New Level(GL)
            node nd; //New Down Link Node
            nd.setDown(nextLevel);
            head.push_back(nd); //adding down link node to main head
            expressionPosition = generateLevels(nextLevel, expression, expressionPosition+1); //generate further levels
        }
        if((currentCharacter != '(') && (currentCharacter != ')')){ //condition to verify its character node
            node nd;
            nd.setCharVariable(currentCharacter);
            nd.setDown(NULL);
            head.push_back(nd); //adding character node in main head
            expressionPosition++;
        }
    }
}
//creates further down levels in Expression 
int GL::generateLevels(GL *level, string expression, int expressionPosition){
    while (expressionPosition < expression.size())
    {
        char currentCharacter = expression[expressionPosition];
        if((currentCharacter != '(') && (currentCharacter != ')')){ //condition to verify its character node
            node currentNode;
            currentNode.setCharVariable(currentCharacter);
            currentNode.setDown(NULL);
            level->head.push_back(currentNode); //adding character node in current level head
        }
        else{
            if(currentCharacter == '('){ //this indicates further new down level in expression
                GL *nextLevel = new GL();  //Creates New Level(GL)
                node currentNode; // Creates New Down Link node
                currentNode.setDown(nextLevel);
                level->head.push_back(currentNode); //adding down link node to current level head
                expressionPosition = generateLevels(nextLevel, expression, expressionPosition+1); //recursive call to same function to create further down levels
                continue;
            }
            if(currentCharacter == ')'){ //this indicates end of level
                expressionPosition++;
                break;
            }
        }
        expressionPosition++;
    }
    return expressionPosition;
}
// display list
void GL::display(){
    string finalExpression = generateExpression(false); //call generateExpression to get in string format and print. false means it will not add Paranthesis
    cout << finalExpression;
}
//generate expression in string from GL
string GL::generateExpression(bool addParanthesis){
    std::list<node>::iterator listPosition;
    string cumulativeExpression; //characters will be concatenated to make full expression string
    if(addParanthesis) //if paranthesis needed
        cumulativeExpression +="(";
    for (listPosition = head.begin(); listPosition != head.end(); listPosition++) //loop on list<node> on current level (GL)
    {
        node myNode = *listPosition;
        GL *downLevel = myNode.getDown();
        if(myNode.getDown() != NULL){ //condition to check if it has down level
            cumulativeExpression += downLevel->generateExpression(addParanthesis); //recursively call same function on next level GL
        }
        else{ //character node
            if(!addParanthesis)
                cumulativeExpression += string(1, *myNode.getChar()) + " "; //attach character to string with paranthesis
            else
                cumulativeExpression += string(1, *myNode.getChar()); ////attach character to string with space
        }
    }
    if(addParanthesis)
        cumulativeExpression +=")";
    return cumulativeExpression;
}
// return the height of the GL using the GL
int GL::heightOfGL(){
    int levels = 0; //height of GL
    std::list<node>::iterator listPosition;
    for (listPosition = head.begin(); listPosition != head.end(); listPosition++) //loop on head list of nodes
    {
        node myNode = *listPosition;
        GL *hasDownLevel = myNode.getDown();
        if(hasDownLevel != NULL){ //has down link?
            levels++; //increment level
            int downHeight = hasDownLevel->heightOfGL(); //recursively call same for down levels
            levels += downHeight; //add height to current level
        }
    }
    return levels;
}
// given a char, find it in a given expression
bool GL::findCharInExpression(char findThisChar){
    string exp = generateExpression(false); //generating expression in string format without paranthesis
    return exp.find(findThisChar) != string::npos; //find with string function if given char available in expression
}
// print all the duplicates in the GL
void GL::searchDuplicates(){
    string exp = generateExpression(false);
    int size = exp.size();
    for(int current = 0; current < size; current++){
        for (int cur2 = 0; cur2 < size; cur2++)
        {
            if(exp[cur2] == exp[current]){
                cout << exp[cur2] << endl;
                return;
            } 
        }
    }
}
// find the LCA distance of two char in the expression
int GL::LCAdistance(char char1, char char2){
    string path1, path2; //path1 and path2 are full paths from parent node to given character
    int distance = 1, path1Size, path2Size, loopSize, intersectionPoint; 
    path1 = getCharPath(char1); 
    path2 = getCharPath(char2); 
    path1Size = path1.size();
    path2Size = path2.size();
    loopSize = path1Size > path2Size ? path1Size : path2Size;

    //loop to find the intersection of paths
    for (int i = 0; i < loopSize; i++)
    {
        if(path1Size == i){ //check if path1 Size is equal to current position and break the loop to avoid index out of boound exception
            intersectionPoint = i;
            break;
        }
        else if(path2Size == i){//check if path2 Size is equal to current position and break the loop to avoid index out of boound exception
            intersectionPoint = i;
            break;
        }
        if(path1[i] != path2[i]){ //when characters are different on current position then this is intersection point and we break the loop
            intersectionPoint = i;
            break;
        }
    }
    if(path1Size > path2Size) //checking to largest path as LCA is needed
        return getDistance(path1, intersectionPoint);
    else
        return getDistance(path2, intersectionPoint);
}
//gives LCA distance 
int GL::getDistance(string path, int intersectionPoint){
    int LCADistance = 1;
    for (int i = intersectionPoint-1; i < path.size(); i++)
    {
        if(path[i] == '*')
            LCADistance++;
    }
    return LCADistance;
}
//gives leven of character in an expression
string GL::getCharPath(char c){
    string path = "";
    bool found = false;
    std::list<node>::iterator listIterator = head.begin();
    while (listIterator!=head.end())
    {
        node currentNode = *listIterator;
        if(currentNode.getDown() != NULL){
            GL *nextLevel = currentNode.getDown();
            path += "*";
            path += nextLevel->getCharPath(c);
            for (size_t i = 0; i < path.size(); i++)
            {
                if(path[i] == c){
                    found = true;
                    break;
                }
            }
        }
        else{
            path += string(1, *currentNode.getChar());
            if(c == *currentNode.getChar()){
                found = true;
            }
        }
        if(found)
            break;
        listIterator++;
    }
    if(found)
        return path;
    return "";
}

int main()
{
    int numExpressions; // number of expressions
    char option;        // command from the input file
    string expression;
    int expressionPosition = 0;

    // read the number of expressions given
    cin >> numExpressions;
    cout << "Number of expressions: " << numExpressions << endl;

    GL *expressions = new GL[numExpressions]; // an array of expressions / an array of GL objects
    
    //While loop to read all expressions in input file
    while (expressionPosition < numExpressions){
        cin >> expression;
        expressions[expressionPosition].buildGL(expression);
        expressionPosition++;
    }

    

    // read in and process all the options using switch case
    while (cin >> option)
    {
        switch (option)
        {
        case 'D':
            expressionPosition = 0;
            cout << endl << "Displaying all expressions: " << endl;
            while (expressionPosition < numExpressions){
                cout << "Expression " << expressionPosition <<  " : ";
                expressions[expressionPosition].display();
                cout << endl;
                expressionPosition++;
            }
            break;
        case 'H':
            cin >> expressionPosition;
            cout << endl << "Height of expression " << expressionPosition <<  " : ";
            cout << expressions[expressionPosition].heightOfGL()+1 << endl;
            break;
        case 'F':
            char charToFind;
            cin >> expressionPosition;
            cin >> charToFind;
            cout << endl << "Find " << charToFind << " in " << expressionPosition << " : " << (expressions[expressionPosition].findCharInExpression(charToFind)? "found" : "not found") << endl;
            break;
        case 'U':
            cin >> expressionPosition;
            cout << endl << "Duplicates in " << expressionPosition << " : ";
            expressions[expressionPosition].searchDuplicates();
            break;
        case 'L':
            char descChar1, descChar2;
            cin >> expressionPosition;
            cin >> descChar1 >> descChar2;
            cout << endl << "LCA distance between " << descChar1 << " and " << descChar2 << " in expression " << expressionPosition << " : " << expressions[expressionPosition].LCAdistance(descChar1, descChar2) << endl;
            break;
        default:
            break;
        }
    }
    


    return 0;
}
