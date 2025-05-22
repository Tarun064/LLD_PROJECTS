#include <bits/stdc++.h>
using namespace std;

class DocumentEditor {
    private:
        vector<string>documentElements;
        string renderedDocument; //yeah string store krega rendered document ki mtlb koi baar baar render kre toh bar bar code run na ho direct yha se string mil jaaye render ke liye

    public:
    void addText(string text) {  //add text as plain string
        documentElements.push_back(text);
    }
    void addImage(string imagePath) { //add an image represented as an file path
        documentElements.push_back(imagePath);
    }

    //renders the documents by checking the type of each element at runtime
    string renderDocument() { 
        if(renderedDocument.empty()){
            for(auto element:documentElements){
                if(elements.size()>4 && (element.substr(element.size()-4)==".jpg" ||
                element.substr(element.size()-4)==".png")){
                    result+="[Image: "+element+"]"+"\n";
                }
                else{
                    result+=element+"\n";
                }
            }
            renderedDocument=result;
        }
        return renderedDocument;
    }

    void saveToFile(){
        ofstream file("document.txt");
        if(file.is_open()){
            file<<renderDocument();
            file.close();
            cout<<"Document saved to document.txt"<<endl;
        }
        else{
            cout<<"Error opening file for writing."<<endl;
        }
    }
};

int main(){
    DocumentEditor editor;
    editor.addText("This is a sample document.");
    editor.addText("picture.jpg");
    editor.addText("This is a text after the image int the document editor.");
    cout<<editor.renderDocument()<<endl;
    editor.saveToFile();
}