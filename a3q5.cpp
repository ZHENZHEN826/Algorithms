#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

int main()
{   
	string firstLine, secondLine;
	int gap, mismatch; 
	
	cin >> firstLine >> secondLine >> gap >> mismatch;
	
	int firstLength = firstLine.size();
	int secondLength = secondLine.size();
	

  int matrix[firstLength+1][secondLength+1];

  matrix[0][0] = 0;

  // initialize first row
  for (int i = 1; i <= firstLength; i++) {
    matrix[i][0] = i * gap;
  }

  // initialize first column
  for (int j = 1; j <= secondLength; j++) {
    matrix[0][j] = j * gap;
  }

  // fill the matrix
  for(int i = 1; i <= firstLength; ++i){
    for(int j = 1; j <= secondLength; ++j){
      int mismatchPenalty;
      if (firstLine[i-1] == secondLine[j-1]){
        mismatchPenalty = 0;
      } else {
        mismatchPenalty = mismatch;
      }
      matrix[i][j] = min({matrix[i-1][j-1] + mismatchPenalty, matrix[i-1][j] + gap, matrix[i][j-1] + gap});
      cout << "i:" <<i <<"j:" <<j<<"matrix[i][j]"<<matrix[i][j]<<endl;
    }
  }

  // Back tracking
  int i = firstLength;
  int j = secondLength;
  string firstOut, secondOut, thirdOut;

  while (i > 0 || j > 0){
    if (i > 0 && j == 0){
      // similiar to case 2
      firstOut.insert (0, 1, firstLine[i-1]);
      secondOut.insert(0, 1, ' ');
      thirdOut.insert(0, 1, '-');
      i--;
      continue;
    } else if (i == 0 && j > 0){
      // similiar to case 3
      firstOut.insert (0, 1, '-');
      secondOut.insert(0, 1, ' ');
      thirdOut.insert(0, 1, secondLine[j-1]);
      j--;
      continue;
    } 

    int mismatchPenalty;
    bool sameChar = firstLine[i-1] == secondLine[j-1];
    if (sameChar){
      mismatchPenalty = 0;
    } else {
      mismatchPenalty = mismatch;
    }
    // determine which case was matrix[i][j]
    bool case1 = matrix[i][j] - mismatchPenalty == matrix[i-1][j-1];
    bool case2 = matrix[i][j] - gap == matrix[i-1][j];
    bool case3 = matrix[i][j] - gap == matrix[i][j-1];
    if (case1){
      if (sameChar){
        // match with same char
        firstOut.insert (0, 1, firstLine[i-1]);
        secondOut.insert(0, 1, '|');
        thirdOut.insert(0, 1, secondLine[j-1]);
      } else {
        // match with different cahr
        firstOut.insert (0, 1, firstLine[i-1]);
        secondOut.insert(0, 1, ' ');
        thirdOut.insert(0, 1, secondLine[j-1]);
      }
      i--;
      j--;
    } else if (case2){
      // second line gap
      firstOut.insert (0, 1, firstLine[i-1]);
      secondOut.insert(0, 1, ' ');
      thirdOut.insert(0, 1, '-');
      i--;
    } else if (case3){
      // first line gap
      firstOut.insert (0, 1, '-');
      secondOut.insert(0, 1, ' ');
      thirdOut.insert(0, 1, secondLine[j-1]);
      j--;
    } else {
      cerr<< "something wrong" << endl;
    }
    cout << "case1: " <<case1<<" case2: "<<case2<<" case3: "<<case3<<endl;
    cout << "1: "<<firstOut<<endl;
    cout << "2: " << secondOut << endl;
    cout << "3: " << thirdOut << endl;
  }
  // Output 3 lines result
  cout << firstOut << endl;
  cout << secondOut << endl;
  cout << thirdOut << endl;

  return 0;
}
