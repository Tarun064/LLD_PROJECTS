#include <bits/stdc++.h>
using namespace std;

//abstrcation for document elements
class DocumentElement{
    public:
        virtual string render() = 0; //pure virtual function
};

//concrete implementation for text element
class TextElement: public DocumentElement{
    private:
        string text;
    public:
        TextElement(string text){
            this->text=text;
        }
        string render() override {
            return text;
        }
};

//concrete implementation for image element
class ImageElement: public DocumentElement{
    private:
        string imagePath;
    public:
        ImageElement(string imagePath){
            this->imagePath=imagePath;
        }
        string render() override {
            return "[Image: "+imagePath+"]";
        }
};  

//newline element represents the line break in the document
class NewLineElement: public DocumentElement{
    public:
        string render() override {
            return "\n";
        }
};

//tab space element represents the tab space in the document
class TabSpaceElement: public DocumentElement{
    public:
        string render() override {
            return "\t";
        }
};

//document class represents the holding a collection of elements
class Document{
    private:
        vector<DocumentElement*>documentElements; //vector of pointers to DocumentElement
    public:
        void addElement(DocumentElement* element){
            documentElements.push_back(element);
        }
        string render(){
            string result;
            for(auto element:documentElements){
                result+=element->render();
            }
            return result;
        }
};

//pewrsistence interface
class Persistence{
    public:
        virtual void save(string data) = 0;
};

//file storage implementation of persistence
class FileStorage: public Persistence{
    public:
        void save(string data) override {
            ofstream outFile("document.txt");
            if(outFile){
                outFile<<data;
                outFile.close();
                cout<<"Document saved to "<<filePath<<endl;
            }
            else{
                cout<<"Error opening file for writing."<<endl;
            }
        }
};

//placeholder db storage implementation of persistence
class DBStorage: public Persistence{
    public:
        void save(string data) override {
            //simulating saving to a database ... khud ka koi bhi logic ho skta hai
            cout<<"Document saved to database."<<endl;
        }
};

//document editor class managing client interactions
class DocumentEditor{
    private:
        Document* document;
        Persistence* storage; //persistence interface pointer
        string renderedDocument; //string to store the rendered document
    public:
        DocumentEditor(Document* document,Persistence* storage){
            this->document=document;
            this->storage=storage;
        }
        void addText(string text) {
            document->addElement(new TextElement(text));
        }
        void addImage(string imagePath) {
            document->addElement(new ImageElement(imagePath));
        }
        void addNewLine() {
            document->addElement(new NewLineElement());
        }
        void addTabSpace() {
            document->addElement(new TabSpaceElement());
        }
        string renderDocument() {
            if(renderedDocument.empty()){
                renderedDocument=document->render();
            }
            return renderedDocument;
        }
        void saveDocument(){
            storage->save(renderDocument());
        }
};
    
//client usage example
int main(){
    Document* document=new Document();
    Persistence* persistence=new FileStorage(); //or DBStorage() for database storage
    DocumentEditor* editor = new DocumentEditor(document,persistence);
    
    editor->addText("This is a sample document.");
    editor->addNewLine();
    editor->addText("This is a text before the image in the document editor.");
    editor->addImage("picture.jpg");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("This is a text after the image in the document editor.");
    
    cout<<editor->renderDocument()<<endl;
    
    editor->saveDocument();
    
    delete document; //clean up
    delete storage; //clean up
    return 0;
}