#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include<string>

using namespace std;


vector<int> readData(string fileName);


int main() {


  ofstream outData;
  outData.open("Results.txt");
  outData<<left<<setw(16)<<"Experiment"<<setw(16)<<"<Intensity>"<<setw(16)<<"Sigma"<<endl;


  string folder;
  int maxNum;

  cout<<"Folder: ";  //   DATA/test4
  cin>>folder;
  cout<<"Maximum file number: "; //87
  cin>>maxNum;


  vector<string> letter;
  letter.push_back("a");
  letter.push_back("b");
  letter.push_back("c");
  letter.push_back("d");
  letter.push_back("e");

  
  // AVERAGE OF INDIVIDUAL EXPERIMENTS

  for(int j=1; j<=maxNum; j++) {

    vector<int> v=  readData(folder+"/hist_"+std::to_string(j)+".txt");

    int count=1;
    
    for(int i=0; i<letter.size(); i++ ) {

      vector<int> vv=  readData(folder+"/hist_"+std::to_string(j)+"_"+letter[i]+".txt");

      
      if(vv.size()==v.size()) {

	count++;

	for(int f=0; f<v.size(); f++) {
	  v[f]=v[f]+vv[f];
	}

      }	
      
    }

    
	for(int f=0; f<v.size(); f++) {

	  v[f]=v[f]/count;
	}




	//AVERAGE INTENSITY
	
	double average=0; //average intensity
	int nTot=0; //total number of pixels

	for(int i=0; i<v.size(); i++) {

	  nTot=nTot+v[i];
	  average=average+i*v[i];
	}

	average=average/nTot;


	//VARIANCE=(SUM (AVERAGE-INTENSITY)^2* N°PIX )/nTot

	double variance=0;

	
	for(int i=0; i<v.size(); i++) {
	  
	  variance=variance+pow(average-i,2)*v[i];
	}

	variance=variance/nTot;


	//ROOT MEAN SQUARE

	double sigma=sqrt(variance);

	
	cout<<"EXPERIMENT "<<j<<" AVERAGE= "<<average<<"  SIGMA= "<<sigma<<endl;

	outData<<left<<setw(16)<<j<<setw(16)<<average<<setw(16)<<sigma<<endl;

  
	
  }

  
  outData.close();
  
  return 0;

}



vector<int> readData(string fileName) {

  vector<int> v;

  
  ifstream inData;
  
  inData.open(fileName);

  if(inData.good()==false){

    cerr<<"Cannot open "<<fileName<<endl;
    return v;
  }

  string firstLine;

  getline(inData, firstLine);

  
  while(inData.eof()==false) {

    string bin;
    string value;
      
    inData>>bin;
    inData>>value;

    if(value.length()>0){

     
      v.push_back(std::stoi(value));
  }

  }

  cout<<"I read "<<v.size()<<" elements from "<<fileName<<endl;

  return v;

}
