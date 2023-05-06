#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

// định nghĩa các cấu trúc dữ liệu
struct NODE
{
      string data;
      NODE *pLeft;
      NODE *pRight;
};

NODE *CreateNode(string c)
{
      NODE *newNode = new NODE;
      newNode->data = c;
      newNode->pLeft = newNode->pRight = NULL;
      return newNode;
}

// Hàm kiểm tra xem một chuỗi có phải là một toán tử hay không
bool isOperator(string c)
{
      if (c == "+" || c == "-" || c == "*" || c == "/" || c == "^")
      {
            return true;
      }
      return false;
}

// xét độ ưu tiên
int getPrecedence(string op)
{
      if (op == "^")
            return 3;
      else if (op == "*" || op == "/")
            return 2;
      else if (op == "+" || op == "-")
            return 1;
      else
            return 0;
}

string infixToPostFix(string a)
{
      string postFix = "";
      stack<string> st;
      for (int i = 0; i < a.length(); i++)
      {
            if (a[i] >= '0' && a[i] <= '9')
            {
                  string operand = "";
                  while (i < a.length() && a[i] >= '0' && a[i] <= '9')
                  {
                        operand += a[i];
                        i++;
                  }
                  postFix += operand + " ";
                  i--;
            }
            else if (a[i] == '(')
            {
                  st.push("(");
            }
            else if (a[i] == ')')
            {
                  while (!st.empty() && st.top() != "(")
                  {
                        postFix += st.top() + " ";
                        st.pop();
                  }
                  st.pop(); // remove "(" from stack
            }
            else
            {

                  string current_op = string(1, a[i]);
                  while (!st.empty() && st.top() != "(" && getPrecedence(current_op) <= getPrecedence(st.top()))
                  {
                        postFix += st.top() + " ";
                        st.pop();
                  }
                  st.push(current_op);
            }
      }
      while (!st.empty())
      {
            postFix += st.top() + " ";
            st.pop();
      }
      return postFix;
}

NODE *buildExpressionTree(string postFix)
{
      stringstream ss(postFix);
      string a;
      stack<NODE *> st;

      while (ss >> a)
      {
            if (!isOperator(a))
            {
                  NODE *node = CreateNode(a);
                  st.push(node);
            }
            else
            {
                  NODE *node = CreateNode(a);
                  NODE *right = st.top();
                  st.pop();
                  NODE *left = st.top();
                  st.pop();
                  node->pLeft = left;
                  node->pRight = right;
                  st.push(node);
            }
      }

      return st.top();
}

float evaluateTree(NODE *node)
{
      if (node != NULL)
      {
            if (node->pLeft == NULL && node->pRight == NULL) // nếu nút đó là nút lá (là toán hạng)
            {
                  return stof(node->data); // chuyển ký tự sang số và trả về giá trị
            }
            else
            {
                  float leftValue = evaluateTree(node->pLeft);   // tính giá trị của cây con bên trái
                  float rightValue = evaluateTree(node->pRight); // tính giá trị của cây con bên phải
                  if (node->data == "+")
                  {
                        return leftValue + rightValue;
                  }
                  else if (node->data == "-")
                  {
                        return leftValue - rightValue;
                  }
                  else if (node->data == "*")
                  {
                        return leftValue * rightValue;
                  }
                  else if (node->data == "/")
                  {
                        return leftValue / rightValue;
                  }
                  else
                        return pow(leftValue, rightValue);
            }
      }
      return 0;
}

int main()
{
      string choose = "1";
      while (choose == "1")
      {

            string infix;
            cout << "\nEnter inFix expression: ";
            getline(cin, infix);
            string postFix = infixToPostFix(infix);
            cout << "Postfix expression: " << postFix << endl;
            NODE *root = buildExpressionTree(postFix);

            float result = evaluateTree(root);
            cout << " --> Result: " << result << endl;

            cout << "Continue calculator - enter \"1\" : ";
            getline(cin, choose);
      }

      return 0;
}
